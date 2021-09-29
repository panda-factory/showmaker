//
// Created by guozhenxiong on 2021-07-24.
//

#ifndef STRUGGLE_WTF_LAYER_H
#define STRUGGLE_WTF_LAYER_H

#include "third_party/skia/include/core/SkSurface.h"
#include "third_party/skia/include/core/SkRect.h"
#include "third_party/skia/include/core/SkTypes.h"
#include "third_party/skia/include/core/SkString.h"
#include "third_party/skia/include/private/SkTDArray.h"

namespace strg {
class Window;
class Layer {
public:
    Layer() : active_(true) {}
    virtual ~Layer() = default;

    bool GetActive() { return active_; }
    void SetActive(bool active) { active_ = active; }

    // return value of 'true' means 'I have handled this event'
    virtual void OnBackendCreated() {}
    virtual void OnAttach(Window* window) {}
    virtual bool OnChar(const std::string& utf8) {return false;};
    virtual void OnUIStateChanged(const SkString& stateName, const SkString& stateValue) {}
    virtual void OnPrePaint() {}
    virtual void OnPaint(SkSurface*) {}
    virtual void OnResize(int width, int height) {}

private:
    friend class Window;
    bool active_;
};
} // namespace strg

#endif //STRUGGLE_LAYER_H
