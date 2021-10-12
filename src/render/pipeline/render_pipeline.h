//
// Created by guozhenxiong on 2021-08-20.
//

#ifndef SHOWMAKER_RENDER_PIPELINE_H
#define SHOWMAKER_RENDER_PIPELINE_H

#include <memory>

#include "wtf/all_static.h"

namespace sm {
class Element;

class Scene;

class RenderPipeline : public AllStatic {
public:
    static void FlushLayout(Element *);

    static void FlushPaint(Element *);

    static std::unique_ptr<Scene> CompositeFrame(Element *);

};
} // namespace sm

#endif //SHOWMAKER_RENDER_PIPELINE_H
