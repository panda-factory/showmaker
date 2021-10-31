//
// Created by guozhenxiong on 2021-08-20.
//

#ifndef SHOWMAKER_ABSTRACT_NODE_H
#define SHOWMAKER_ABSTRACT_NODE_H

#include <vector>
namespace sm {
class AbstractNode {
public:
    virtual void Attach(void *owner);

    virtual void Detach();

    virtual void RedepthChildren() { }

    bool Attached() { return owner_ != nullptr; }

    AbstractNode();

    virtual ~AbstractNode();

protected:
    void RedepthChild(AbstractNode* child);

    virtual void AdoptChild(AbstractNode *child);

    virtual void DropChild(AbstractNode *child);

    AbstractNode *parent_ = nullptr;

    void* owner_ = nullptr;

private:
    int depth_ = 0;
};
} // namespace sm

#endif //SHOWMAKER_ABSTRACT_NODE_H
