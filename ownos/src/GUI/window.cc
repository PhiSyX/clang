#include "gui/window.hh"

Window::Window(const Widget* parent,
			   const i32 x,
			   const i32 y,
			   const i32 w,
			   const i32 h,
			   const u8 r,
			   const u8 g,
			   const u8 b)
  : CompositeWidget(parent, x, y, w, h, r, g, b)
{
	dragging = false;
}

Window::~Window() {}

void
Window::on_mousedown(i32 x, i32 y, u8 button)
{
	dragging = button == 1;
	CompositeWidget::on_mousedown(x, y, button);
}

void
Window::on_mouseup(i32 x, i32 y, u8 button)
{
	dragging = false;
	CompositeWidget::on_mouseup(x, y, button);
}

void
Window::on_mousemove(i32 old_x, i32 old_y, i32 new_x, i32 new_y)
{
	if (dragging)
	{
		x += new_x - old_x;
		y += new_y - old_y;
	}
	CompositeWidget::on_mousemove(old_x, old_y, new_x, new_y);
}
