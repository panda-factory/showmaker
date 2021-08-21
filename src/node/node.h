//
// Created by guozhenxiong on 2021-08-20.
//

#ifndef XXX_NODE_H
#define XXX_NODE_H

#include <vector>

class Node {
public:
    virtual void Adopt(Node *child);

    virtual void Drop(Node *child);

    virtual void Attach(Node *parent);

    virtual void Detach();

    virtual ~Node();

protected:
    std::vector<Node *> children_;

    Node *parent_;

private:
};


#endif //XXX_NODE_H
