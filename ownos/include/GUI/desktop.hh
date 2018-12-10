#ifndef __DESKTOP_HPP__
#define __DESKTOP_HPP__

#include <GUI/widget.hh>
#include <drivers/mouse.hh>
#include <drivers/vga.hh>
#include <shared/types.hh>

class Desktop
  : public CompositeWidget
  , public MouseEventHandler
{
  protected:
	u32 mousex;
	u32 mousey;

  public:
	Desktop(const i32 w, const i32 h, const u8 r, const u8 g, const u8 b);
	~Desktop();

  public:
	void draw(VGA* gc);

	void on_mousedown(const u8 button);
	void on_mouseup(const u8 button);
	void on_mousemove(i32 x, i32 y);
};

#endif
