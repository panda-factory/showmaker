//
// Created by guozhenxiong on 2021-07-24.
//

#ifndef XXX_LAYER_H
#define XXX_LAYER_H

namespace wtf {
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
    virtual void OnUIStateChanged(const SkString& stateName, const SkString& stateValue) {}
    virtual void OnPrePaint() {}
    virtual void OnPaint(SkSurface*) {}
    virtual void OnResize(int width, int height) {}

private:
    friend class Window;
    bool active_;
};
} // namespace wtf

#endif //XXX_LAYER_H
