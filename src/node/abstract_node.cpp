//
// Created by guozhenxiong on 2021-08-20.
//

#include "abstract_node.h"

#include <third_party/flutter/fml/logging.h>

namespace sm {
AbstractNode::AbstractNode() = default;

AbstractNode::~AbstractNode() = default;

void AbstractNode::AdoptChild(AbstractNode *child)
{
    child->parent_ = this;
    if (Attached()) {
        child->Attach(owner_);
    }
    RedepthChild(child);
}

void AbstractNode::Attach(void* owner) {
    FML_CHECK(owner != nullptr);
    FML_CHECK(owner_ == nullptr);
    owner_ = owner;
}

void AbstractNode::DropChild(AbstractNode *child)
{
    child->parent_ = nullptr;
    if (Attached()) {
        child->Detach();
    }
}

void AbstractNode::Detach()
{
    FML_CHECK(owner_ != nullptr);
    owner_ = nullptr;
    FML_CHECK(parent_ == nullptr || Attached() == parent_->Attached());
    parent_ = nullptr;
}

void AbstractNode::RedepthChild(AbstractNode* child) {
    FML_CHECK(child->owner_ == owner_);
    if (child->depth_ <= depth_) {
        child->depth_ = depth_ + 1;
        child->RedepthChildren();
    }
}
} // namespace sm