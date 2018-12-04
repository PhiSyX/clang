#ifndef __MYOS__GUI__WIDGET_H
#define __MYOS__GUI__WIDGET_H

#include <shared/types.hh>
#include <shared/graphicscontext.hh>

namespace myos
{
    namespace GUI
    {
        class Widget
        {
        protected:
            Widget *parent;
            shared::int32_t x;
            shared::int32_t y;
            shared::int32_t w;
            shared::int32_t h;

            shared::uint8_t r;
            shared::uint8_t g;
            shared::uint8_t b;
            bool Focussable;

        public:
            Widget(Widget *parent,
                   shared::int32_t x, shared::int32_t y, shared::int32_t w, shared::int32_t h,
                   shared::uint8_t r, shared::uint8_t g, shared::uint8_t b);
            ~Widget();

            virtual void GetFocus(Widget *widget);
            virtual void ModelToScreen(shared::int32_t &x, shared::int32_t &y);

            virtual void Draw(GraphicsContext *gc);
            virtual void OnMouseDown(shared::int32_t x, shared::int32_t y);
            virtual void OnMouseUp(shared::int32_t x, shared::int32_t y);
            virtual void OnMouseMove(shared::int32_t oldx, shared::int32_t oldy, shared::int32_t newx, shared::int32_t newy);

            virtual void OnKeyDown(shared::int32_t x, shared::int32_t y);
            virtual void OnKeyUp(shared::int32_t x, shared::int32_t y);
        };

        class CompositeWidget : public Widget
        {
        private:
            Widget *children[100];
            int numChildren;
            Widget *focussedChild;

        public:
            CompositeWidget(Widget *parent,
                            shared::int32_t x, shared::int32_t y, shared::int32_t w, shared::int32_t h,
                            shared::uint8_t r, shared::uint8_t g, shared::uint8_t b);
            ~CompositeWidget();

            virtual void GetFocus(Widget *widget);

            virtual void Draw(GraphicsContext *gc);
            virtual void OnMouseDown(shared::int32_t x, shared::int32_t y);
            virtual void OnMouseUp(shared::int32_t x, shared::int32_t y);
            virtual void OnMouseMove(shared::int32_t oldx, shared::int32_t oldy, shared::int32_t newx, shared::int32_t newy);

            virtual void OnKeyDown(shared::int32_t x, shared::int32_t y);
            virtual void OnKeyUp(shared::int32_t x, shared::int32_t y);
        };

    }
}

#endif
