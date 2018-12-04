#ifndef __MYOS__GUI__DESKTOP_H
#define __MYOS__GUI__DESKTOP_H

#include <GUI/widget.hh>
#include <drivers/mouse.hh>

namespace myos
{
    namespace GUI
    {
        class Desktop : public CompositeWidget, public myos::drivers::MouseEventHandler
        {
        protected:
            shared::uint32_t MouseX;
            shared::uint32_t MouseY;

        public:
            Desktop(shared::int32_t w, shared::int32_t h,
                    shared::uint8_t r, shared::uint8_t g, shared::uint8_t b);
            ~Desktop();

            void Draw(shared::GraphicsContext *gc);

            void OnMouseDown(myos::shared::uint8_t button);
            void OnMouseUp(myos::shared::uint8_t button);
            void OnMouseMove(int x, int y);
        };
    }
}

#endif
