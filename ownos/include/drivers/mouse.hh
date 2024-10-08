#ifndef __MOUSE_HPP__
#define __MOUSE_HPP__

#include <COM/interrupts.hh>
#include <COM/port.hh>
#include <drivers/driver.hh>
#include <shared/types.hh>

class MouseEventHandler
{
  public:
	MouseEventHandler();

  public:
	virtual void on_activate() const;
	virtual void on_mousedown(u8 button) const;
	virtual void on_mouseup(u8 button) const;
	virtual void on_mousemove(i32 x, i32 y) const;
};

class MouseDriver
  : public InterruptHandler
  , public Driver
{
	Port8Bit data_port;
	Port8Bit command_port;

	u8 buffer[3];
	u8 offset;
	u8 buttons;

	MouseEventHandler* handler;

  public:
	MouseDriver(InterruptManager* manager, MouseEventHandler* handler);
	~MouseDriver();

  public:
	virtual /* contains static */ const u32 handle_interrupt(const u32 esp);
	virtual /* contains static */ void activate();
};

#endif
