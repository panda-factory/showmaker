//
// Created by guozhenxiong on 2021-08-20.
//

#ifndef XXX_RENDER_PIPELINE_H
#define XXX_RENDER_PIPELINE_H

#include <memory>

#include "wtf/all_static.h"

class Element;
class Scene;

class RenderPipeline : public AllStatic {
public:
    static void FlushLayout(Element*);

    static void FlushPaint(Element*);

    static std::unique_ptr<Scene> CompositeFrame(Element*);

};


#endif //XXX_RENDER_PIPELINE_H
