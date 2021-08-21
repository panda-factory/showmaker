//
// Created by guozhenxiong on 2021-08-04.
//

#include "element.h"

Element::Element()
{
    layer_ = std::make_unique<ContainerLayer>();
}

Element::~Element() = default;

void Element::Draw(SkCanvas *canvas, Drawable* drawable, const Position2D& position)
{
    drawable->Draw(canvas, position);
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