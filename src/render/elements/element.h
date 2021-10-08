//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef STRUGGLE_ELEMENT_H
#define STRUGGLE_ELEMENT_H

#include <vector>

#include "node/node.h"
#include "render/position2d.h"
#include "render/drawable.h"
#include "render/size.h"
#include "render/layer/container_layer.h"
#include "render/painting/paint_context.h"

#include "include/core/SkSurface.h"
#include "include/core/SkCanvas.h"
namespace strg {
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

    inline void AddElement(std::unique_ptr<Element> element)
    {
        children_.push_back(std::move(element));
    }

    void OnPaint();

    virtual void Paint(PaintContext *context) = 0;

    virtual void PerformLayout()
    {};

    inline void SetPosition(const Position2D &position)
    { position_ = position; }

    virtual Size2D MeasureSize() = 0;

    inline std::shared_ptr<ContainerLayer> layer()
    { return layer_; }

    Element();

    virtual ~Element();

protected:
    void Draw(SkCanvas *canvas, Drawable *drawable, const Position2D &position);

    void PaintChildren(PaintContext *context);

    void CompositeChild(Element *element, PaintContext *context);

    bool is_recording_;

    std::vector<std::unique_ptr<Element>> children_;

    std::shared_ptr<ContainerLayer> layer_;

    Position2D position_;

    SkRect bound_;
private:
};
} // namespace strg

#endif //STRUGGLE_ELEMENT_H
