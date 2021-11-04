//
// Created by guozhenxiong on 2021-10-28.
//

#include "gtest/gtest.h"
#include "render/layer/clip_path_layer.h"
#include "render/layer/clip_rect_layer.h"
#include "render/layer/clip_rrect_layer.h"
#include "render/layer/container_layer.h"
#include "render/layer/layer_link.h"
#include "render/layer/leader_layer.h"
#include "render/layer/follower_layer.h"
#include "render/layer/picture_layer.h"
#include "render/painting/canvas.h"
#include "render/layer/offset_layer.h"
#include "render/painting/picture_recorder.h"
#include "render/layer/performance_overlay_layer.h"
#include "graphics/offset.h"
#include "wtf/diagnostics/diagnostic_properties_builder.h"

using namespace sm;

class TestAlwaysNeedsAddToSceneLayer : public ContainerLayer {
public:
    bool AlwaysNeedsAddToScene() override { return true; }
};

// updateSubtreeNeedsAddToScene propagates Layer.alwaysNeedsAddToScene up the tree
TEST(LayerTest, AlwaysNeedsAddToScene)
{
    auto a = std::make_unique<ContainerLayer>();
    auto b = std::make_unique<ContainerLayer>();
    auto c = std::make_unique<ContainerLayer>();
    auto d = std::make_unique<TestAlwaysNeedsAddToSceneLayer>();
    auto e = std::make_unique<ContainerLayer>();
    auto f = std::make_unique<ContainerLayer>();

    // Tree structure:
    //        a
    //       / \
    //      b   c
    //     / \
    // (x)d   e
    //   /
    //  f
    a->Append(b.get());
    a->Append(c.get());
    b->Append(d.get());
    b->Append(e.get());
    d->Append(f.get());

    a->DebugMarkClean();
    b->DebugMarkClean();
    c->DebugMarkClean();
    d->DebugMarkClean();
    e->DebugMarkClean();
    f->DebugMarkClean();

    EXPECT_GE(a->DebugSubtreeNeedsAddToScene(), false);
    EXPECT_GE(b->DebugSubtreeNeedsAddToScene(), false);
    EXPECT_GE(c->DebugSubtreeNeedsAddToScene(), false);
    EXPECT_GE(d->DebugSubtreeNeedsAddToScene(), false);
    EXPECT_GE(e->DebugSubtreeNeedsAddToScene(), false);
    EXPECT_GE(f->DebugSubtreeNeedsAddToScene(), false);

    a->UpdateSubtreeNeedsAddToScene();

    EXPECT_GE(a->DebugSubtreeNeedsAddToScene(), true);
    EXPECT_GE(b->DebugSubtreeNeedsAddToScene(), true);
    EXPECT_GE(c->DebugSubtreeNeedsAddToScene(), false);
    EXPECT_GE(d->DebugSubtreeNeedsAddToScene(), true);
    EXPECT_GE(e->DebugSubtreeNeedsAddToScene(), false);
    EXPECT_GE(f->DebugSubtreeNeedsAddToScene(), false);
}

// updateSubtreeNeedsAddToScene propagates Layer._needsAddToScene up the tree
TEST(LayerTest, NeedsAddToScene)
{
    auto a = std::make_unique<ContainerLayer>();
    auto b = std::make_unique<ContainerLayer>();
    auto c = std::make_unique<ContainerLayer>();
    auto d = std::make_unique<ContainerLayer>();
    auto e = std::make_unique<ContainerLayer>();
    auto f = std::make_unique<ContainerLayer>();
    auto g = std::make_unique<ContainerLayer>();
    std::list<ContainerLayer*> all_layers({a.get(), b.get(), c.get(), d.get(), e.get(), f.get(), g.get()});

    // The tree is like the following where b and j are dirty:
    //        a____
    //       /     \
    //   (x)b___    c
    //     / \  \   |
    //    d   e  f  g(x)
    a->Append(b.get());
    a->Append(c.get());
    b->Append(d.get());
    b->Append(e.get());
    b->Append(f.get());
    c->Append(g.get());

    for (auto layer : all_layers) {
        EXPECT_GE(layer->DebugSubtreeNeedsAddToScene(), true);
    }

    for (auto layer : all_layers) {
        layer->DebugMarkClean();
    }

    for (auto layer : all_layers) {
        EXPECT_GE(layer->DebugSubtreeNeedsAddToScene(), false);
    }

    b->MarkNeedsAddToScene();
    a->UpdateSubtreeNeedsAddToScene();

    EXPECT_GE(a->DebugSubtreeNeedsAddToScene(), true);
    EXPECT_GE(b->DebugSubtreeNeedsAddToScene(), true);
    EXPECT_GE(c->DebugSubtreeNeedsAddToScene(), false);
    EXPECT_GE(d->DebugSubtreeNeedsAddToScene(), false);
    EXPECT_GE(e->DebugSubtreeNeedsAddToScene(), false);
    EXPECT_GE(f->DebugSubtreeNeedsAddToScene(), false);
    EXPECT_GE(g->DebugSubtreeNeedsAddToScene(), false);

    g->MarkNeedsAddToScene();
    a->UpdateSubtreeNeedsAddToScene();

    EXPECT_GE(a->DebugSubtreeNeedsAddToScene(), true);
    EXPECT_GE(b->DebugSubtreeNeedsAddToScene(), true);
    EXPECT_GE(c->DebugSubtreeNeedsAddToScene(), true);
    EXPECT_GE(d->DebugSubtreeNeedsAddToScene(), false);
    EXPECT_GE(e->DebugSubtreeNeedsAddToScene(), false);
    EXPECT_GE(f->DebugSubtreeNeedsAddToScene(), false);
    EXPECT_GE(g->DebugSubtreeNeedsAddToScene(), true);

    a->BuildScene(SceneBuilder());
    for (auto layer : all_layers) {
        EXPECT_GE(layer->DebugSubtreeNeedsAddToScene(), false);
    }
}

// leader and follower layers are always dirty
TEST(LayerTest, AlwaysDirty)
{
    LayerLink link = LayerLink();
    LeaderLayer leader = LeaderLayer(&link);
    FollowerLayer follower = FollowerLayer(&link);
    leader.DebugMarkClean();
    follower.DebugMarkClean();
    leader.UpdateSubtreeNeedsAddToScene();
    follower.UpdateSubtreeNeedsAddToScene();
    EXPECT_GE(leader.DebugSubtreeNeedsAddToScene(), true);
    EXPECT_GE(follower.DebugSubtreeNeedsAddToScene(), true);
}

TEST(LayerTest, DepthFirstIterateChildren)
{
    ContainerLayer a = ContainerLayer();
    ContainerLayer b = ContainerLayer();
    ContainerLayer c = ContainerLayer();
    ContainerLayer d = ContainerLayer();
    ContainerLayer e = ContainerLayer();
    ContainerLayer f = ContainerLayer();
    ContainerLayer g = ContainerLayer();

    PictureLayer h = PictureLayer(Offset(0, 0));
    PictureLayer i = PictureLayer(Offset(0, 0));
    PictureLayer j = PictureLayer(Offset(0, 0));

    // The tree is like the following:
    //        a____
    //       /     \
    //      b___    c
    //     / \  \   |
    //    d   e  f  g
    //   / \        |
    //  h   i       j
    a.Append(&b);
    a.Append(&c);
    b.Append(&d);
    b.Append(&e);
    b.Append(&f);
    d.Append(&h);
    d.Append(&i);
    c.Append(&g);
    g.Append(&j);

    EXPECT_GE(a.DepthFirstIterateChildren(), std::list<Layer*>({&b, &d, &h, &i, &e, &f, &c, &g, &j}));

    d.Remove();
    //        a____
    //       /     \
    //      b___    c
    //       \  \   |
    //        e  f  g
    //              |
    //              j
    EXPECT_GE(a.DepthFirstIterateChildren(), std::list<Layer*>({&b, &e, &f, &c, &g, &j}));
}


void CheckNeedsAddToScene(Layer* layer, std::function<void ()> mutate_callback) {
    layer->DebugMarkClean();
    layer->UpdateSubtreeNeedsAddToScene();
    EXPECT_GE(layer->DebugSubtreeNeedsAddToScene(), false);
    mutate_callback();
    layer->UpdateSubtreeNeedsAddToScene();
    EXPECT_GE(layer->DebugSubtreeNeedsAddToScene(), true);
}

std::list<std::string> GetDebugInfo(Layer* layer) {
    DiagnosticPropertiesBuilder builder = DiagnosticPropertiesBuilder();
    layer->DebugFillProperties(&builder);
    auto test = builder.properties().front().ToString();
    return {};
}

TEST(LayerTest, ClipRectLayerPrints)
{
    auto clip = ClipRectLayer();
    //auto test = GetDebugInfo(&clip);
    //EXPECT_GE(1, 1);
}

// mutating PictureLayer fields triggers needsAddToScene
TEST(LayerTest, PictureLayerNeedsAddToScene)
{
    PictureLayer pictureLayer = PictureLayer(Rect::ZERO);

    CheckNeedsAddToScene(&pictureLayer, [&] () {
        PictureRecorder recorder = PictureRecorder();
        auto canvas = Canvas(&recorder);
        pictureLayer.SetPicture(recorder.FinishRecording());
    });

    pictureLayer.SetComplexHint(false);
    CheckNeedsAddToScene(&pictureLayer, [&] () {
        pictureLayer.SetComplexHint(true);
    });

    pictureLayer.SetChangeHint(false);
    CheckNeedsAddToScene(&pictureLayer, [&] () {
        pictureLayer.SetChangeHint(true);
    });
}

const Rect unitRect = Rect::FromLTRB(0, 0, 1, 1);

// mutating PerformanceOverlayLayer fields triggers needsAddToScene
TEST(LayerTest, PerformanceOverlayLayerNeedsAddToScene)
{
    PerformanceOverlayLayer layer = PerformanceOverlayLayer(Rect::ZERO,
                                                            0,
                                                            0,
                                                            false,
                                                            false);
    CheckNeedsAddToScene(&layer, [&] () {
        layer.SetOverlayRect(unitRect);
    });
}

// mutating OffsetLayer fields triggers needsAddToScene
TEST(LayerTest, OffsetLayerNeedsAddToScene)
{
    OffsetLayer layer = OffsetLayer();
    CheckNeedsAddToScene(&layer, [&] () {
        layer.SetOffset(Offset(1, 1));
    });
}

// mutating ClipRectLayer fields triggers needsAddToScene
TEST(LayerTest, ClipRectLayerNeedsAddToScene)
{
    ClipRectLayer layer = ClipRectLayer(Rect::ZERO);
    CheckNeedsAddToScene(&layer, [&] () {
        layer.SetClipRect(unitRect);
    });
    CheckNeedsAddToScene(&layer, [&] () {
        layer.SetClipBehavior(Clip::ANTI_ALIAS_WITH_SAVE_LAYER);
    });
}

// mutating ClipRRectLayer fields triggers needsAddToScene
TEST(LayerTest, ClipRRectLayerNeedsAddToScene)
{
    ClipRRectLayer layer = ClipRRectLayer(RRect::ZERO);
    CheckNeedsAddToScene(&layer, [&] () {
        layer.SetClipRRect(RRect::FromRectAndRadius(unitRect, Radius::ZERO));
    });
    CheckNeedsAddToScene(&layer, [&] () {
        layer.SetClipBehavior(Clip::ANTI_ALIAS_WITH_SAVE_LAYER);
    });
}

// mutating ClipPathLayer fields triggers needsAddToScene
TEST(LayerTest, ClipPathLayerNeedsAddToScene)
{
    ClipPathLayer layer = ClipPathLayer(Path());/*
    CheckNeedsAddToScene(&layer, [&] () {
        Path newPath = Path();
        //newPath.addRect(unitRect);
        //layer.clipPath = newPath;
    });*/
}