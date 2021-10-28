//
// Created by guozhenxiong on 2021-10-28.
//

#include "gtest/gtest.h"
#include "render/layer/container_layer.h"

using namespace sm;

// updateSubtreeNeedsAddToScene propagates Layer._needsAddToScene up the tree
TEST(TaskRunner, CreateAndTerminate)
{
    ContainerLayer a = ContainerLayer();
    ContainerLayer b = ContainerLayer();
    ContainerLayer c = ContainerLayer();
    ContainerLayer d = ContainerLayer();
    ContainerLayer e = ContainerLayer();
    ContainerLayer f = ContainerLayer();
    ContainerLayer g = ContainerLayer();

    // The tree is like the following where b and j are dirty:
    //        a____
    //       /     \
    //   (x)b___    c
    //     / \  \   |
    //    d   e  f  g(x)
    a.Append(&b);
    a.Append(&c);
    b.Append(&d);
    b.Append(&e);
    b.Append(&f);
    c.Append(&g);

    ASSERT_NE(nullptr, nullptr);
}