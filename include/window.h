//
// Created by guozhenxiong on 2021-07-21.
//

#ifndef WTF_WINDOW_H
#define WTF_WINDOW_H

namespace wtf {
class Window {
public:
    static Window* CreateNativeWindow(void* platformData);

    virtual bool Attach() = 0;
    virtual void Show() = 0;
    void Detach();

    void OnPaint();

    int width() const;
    int height() const;

    virtual ~Window();

protected:
    Window();


};
} // namespace wtf

#endif //WTF_WINDOW_H
