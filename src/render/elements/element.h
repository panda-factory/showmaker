//
// Created by guozhenxiong on 2021-08-04.
//

#ifndef SHOWMAKER_ELEMENT_H
#define SHOWMAKER_ELEMENT_H

#include <vector>

#include "node/abstract_node.h"
#include "graphics/position.h"
#include "render/drawable.h"
#include "graphics/size.h"
#include "render/layer/container_layer.h"
#include "render/painting/paint_context.h"
#include "render/pipeline/render_object.h"

#include "include/core/SkSurface.h"
#include "include/core/SkCanvas.h"
namespace sm {
class Element : public AbstractNode, public RenderObject {
public:
    // | Node |
    void AdoptChild(AbstractNode *child) override;

    // | Node |
    void DropChild(AbstractNode *child) override;

    // | Node |
    void Attach(void *parent) override;

    // | Node |
    void Detach() override;

    inline void AddElement(std::unique_ptr<Element> element)
    {
        children_.push_back(std::move(element));
    }

    void OnPaint();

    virtual bool HitTest(double x, double y) { return false; }

    virtual void Paint(PaintContext *context) = 0;

    virtual void PerformLayout()
    {};

    inline void SetPosition(const Position &position)
    { position_ = position; }

    inline Position& position() { return position_; }

    virtual Size MeasureSize() = 0;

    Element();

    virtual ~Element();

protected:
    void Draw(SkCanvas *canvas, Drawable *drawable, const Position &position);

    void PaintChildren(PaintContext *context);

    void CompositeChild(Element *element, PaintContext *context);

    bool is_recording_;

    std::vector<std::unique_ptr<Element>> children_;

    Position position_;

    SkRect bound_;
private:
};
} // namespace sm

#endif //SHOWMAKER_ELEMENT_H
