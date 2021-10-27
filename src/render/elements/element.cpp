//
// Created by guozhenxiong on 2021-08-04.
//

#include "element.h"

#include "render/layer/offset_layer.h"

namespace sm {
Element::Element()
{
    MarkNeedsPaint();
}

Element::~Element() = default;

void Element::OnPaint()
{
    auto layer = std::make_shared<OffsetLayer>(position_.x, position_.y);
    layer_ = layer;
    auto paint_context = std::make_unique<PaintContext>(SkRect::MakeXYWH(0, 0, 10, 10), layer_.get());
    Paint(paint_context.get());

    PaintChildren(paint_context.get());
}

void Element::Draw(SkCanvas *canvas, Drawable *drawable, const Position &position)
{
    drawable->Draw(canvas, position);
}

void Element::PaintChildren(PaintContext *context)
{
    for (std::size_t i = 0; i < children_.size(); ++i) {
        CompositeChild(children_[i].get(), context);
    }
}

void Element::CompositeChild(Element *child, PaintContext *context)
{
    child->OnPaint();

    layer_->Add(child->layer());
}

void Element::Adopt(Node *child)
{
    Node::Adopt(child);
}

void Element::Drop(Node *child)
{
    Node::Drop(child);
}

void Element::Attach(Node *parent)
{
    Node::Attach(parent);
}

void Element::Detach()
{
    Node::Detach();
}
} // namespace sm