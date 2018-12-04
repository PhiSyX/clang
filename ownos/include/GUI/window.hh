#ifndef __MYOS__GUI__WINDOW_H
#define __MYOS__GUI__WINDOW_H

#include <GUI/widget.hh>
#include <drivers/mouse.hh>

namespace myos
{
    namespace GUI
    {
        class Window : public CompositeWidget
        {
        protected:
            bool Dragging;

        public:
            Window(Widget *parent,
                   shared::int32_t x, shared::int32_t y, shared::int32_t w, shared::int32_t h,
                   shared::uint8_t r, shared::uint8_t g, shared::uint8_t b);
            ~Window();

            void OnMouseDown(shared::int32_t x, shared::int32_t y, shared::uint8_t button);
            void OnMouseUp(shared::int32_t x, shared::int32_t y, shared::uint8_t button);
            void OnMouseMove(shared::int32_t oldx, shared::int32_t oldy, shared::int32_t newx, shared::int32_t newy);
        };
    }
}

#endif
