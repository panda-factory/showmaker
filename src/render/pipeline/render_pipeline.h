//
// Created by guozhenxiong on 2021-08-20.
//

#ifndef SHOWMAKER_RENDER_PIPELINE_H
#define SHOWMAKER_RENDER_PIPELINE_H

#include <memory>
#include <list>
#include "wtf/all_static.h"

namespace sm {
class Element;
class RenderObject;
class Scene;

class RenderPipeline : public AllStatic {
public:
    static void FlushLayout(Element *);

    static void FlushPaint(Element *);

    static std::unique_ptr<Scene> CompositeFrame(Element *);

    static void AddNodeNeedingPaint(RenderObject*);

private:
    static std::list<RenderObject*> nodes_needing_paint_;
};
} // namespace sm

#endif //SHOWMAKER_RENDER_PIPELINE_H
