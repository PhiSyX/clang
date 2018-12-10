#ifndef __KEYBOARD_HPP__
#define __KEYBOARD_HPP__

#include <driver.hh>
#include <COM/interrupts.hh>
#include <COM/port.hh>
#include <shared/types.hh>

void printf(char *);
void printh(u8);

class KeyboardEventHandler
{
public:
  KeyboardEventHandler();

public:
  virtual void on_keydown(char) const;
  virtual void on_keyup(char) const;
};

class KeyboardDriver
    : public InterruptHandler,
      public Driver
{
  Port8Bit data_port;
  Port8Bit command_port;

  KeyboardEventHandler *handler;

public:
  KeyboardDriver(InterruptManager *im, KeyboardEventHandler *handler);
  ~KeyboardDriver();

public:
  virtual /* contains static */ const u32 handle_interrupt(const u32 esp);
  virtual /* contains static */ void activate();
};

#endif
