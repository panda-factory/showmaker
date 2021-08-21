//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef XXX_ELEMENT_H
#define XXX_ELEMENT_H

#include <vector>

#include "node/node.h"
#include "render/position2d.h"
#include "render/drawable.h"
#include "render/size.h"
#include "render/layer/container_layer.h"

#include "include/core/SkSurface.h"
#include "include/core/SkCanvas.h"

class Element : public Node {
public:
    // | Node |
    void Adopt(Node *child) override;

    // | Node |
    void Drop(Node *child) override;

    // | Node |
    void Attach(Node *parent) override;

    // | Node |
    void Detach() override;

    virtual void Draw(SkCanvas* canvas) = 0;

    virtual void PerformLayout() {};

    inline void SetPosition(const Position2D& position) {position_ = position;}

    virtual Size2D MeasureSize() = 0;

    inline std::shared_ptr<ContainerLayer> layer() {return layer_;}

    Element();

    virtual ~Element();
protected:
    void Draw(SkCanvas* canvas, Drawable* drawable, const Position2D& position);

    std::shared_ptr<ContainerLayer> layer_;

    Position2D position_;
private:
};


#endif //XXX_ELEMENT_H
