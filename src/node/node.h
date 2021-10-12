//
// Created by guozhenxiong on 2021-08-20.
//

#ifndef SHOWMAKER_NODE_H
#define SHOWMAKER_NODE_H

#include <vector>

class Node {
public:
    virtual void Adopt(Node *child);

    virtual void Drop(Node *child);

    virtual void Attach(Node *parent);

    virtual void Detach();

    virtual ~Node();

protected:
    Node *parent_;

private:
};


#endif //SHOWMAKER_NODE_H
