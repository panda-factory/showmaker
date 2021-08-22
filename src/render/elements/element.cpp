//
// Created by guozhenxiong on 2021-08-04.
//

#include "element.h"

#include "render/layer/transform_layer.h"

Element::Element()
{
    layer_ = std::make_unique<ContainerLayer>();
}

Element::~Element() = default;

void Element::OnPaint()
{
    SkMatrix sk_matrix = SkMatrix::Translate(0, 0);
    auto layer = std::make_shared<TransformLayer>(sk_matrix);
    layer_ = layer;
    auto paint_context = std::make_unique<PaintContext>(SkRect({500, 500}), layer_.get());
    Paint(paint_context.get());
}

void Element::Draw(SkCanvas *canvas, Drawable* drawable, const Position2D& position)
{
    drawable->Draw(canvas, position);
}

void Element::PaintChild(Element* element, PaintContext *context)
{
    CompositeChild(element, context);
}

void Element::CompositeChild(Element* element, PaintContext *context)
{
    element->OnPaint();

    layer_->Add(element->layer());
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