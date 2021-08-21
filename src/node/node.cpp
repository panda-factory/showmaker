//
// Created by guozhenxiong on 2021-08-20.
//

#include "node.h"

Node::~Node() = default;

void Node::Adopt(Node *child)
{
    child->parent_ = this;
}

void Node::Drop(Node *child)
{
    child->parent_ = nullptr;
}

void Node::Attach(Node *parent)
{
    parent_ = parent;
}

void Node::Detach()
{
    parent_ = nullptr;
}