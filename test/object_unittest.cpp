//
// Created by guozhenxiong on 2021-11-05.
//


#include "gtest/gtest.h"
#include "render/render_object/render_object.h"
#include "render/pipeline/pipeline_owner.h"
using namespace sm;

class TestRenderObject : public RenderObject {
public:
    constexpr bool IsRepaintBoundary() const override
    { return false; }

    void DebugAssertDoesMeetConstraints() override
    {}

    Rect GetPaintBounds() override
    {
        assert(allow_paint_bounds); // For some tests, this should not get called.
        return Rect::ZERO;
    }

    Rect GetSemanticBounds() override
    {
        return Rect::FromLTWH(0.0, 0.0, 10.0, 20.0);
    }

    void PerformLayout() override
    {}

    void PerformResize() override
    {}

    void DescribeSemanticsConfiguration(SemanticsConfiguration config) override
    {
        RenderObject::DescribeSemanticsConfiguration(config);
        config.SetIsSemanticBoundary(true);
        describeSemanticsConfigurationCallCount++;
    }

    TestRenderObject(bool allow_paint_bounds = false) : allow_paint_bounds(allow_paint_bounds)
    {}

    bool allow_paint_bounds;

    int describeSemanticsConfigurationCallCount = 0;
};

class TestThrowingRenderObject : public RenderObject {
public:
    void PerformLayout() override
    {
        //throw FlutterError('TestThrowingRenderObject does not support performLayout.');
    }

    void DebugAssertDoesMeetConstraints() override {}

    Rect GetPaintBounds() override {
        assert(false); // The test shouldn't call this.
        return Rect::ZERO;
    }

    void PerformResize() override {}


    Rect GetSemanticBounds() override {
        assert(false); // The test shouldn't call this.
        return Rect::ZERO;
    }
};

// ensure frame is scheduled for markNeedsSemanticsUpdate
TEST(RenderObject, CASE01)
{
    // Initialize all bindings because owner.flushSemantics() requires a window
    TestRenderObject renderObject = TestRenderObject();
    int onNeedVisualUpdateCallCount = 0;
    PipelineOwner owner = PipelineOwner([&] () {
        onNeedVisualUpdateCallCount +=1;
    });
    //owner.EnsureSemantics();
    //renderObject.Attach(owner);

    EXPECT_GE(true, false);
}