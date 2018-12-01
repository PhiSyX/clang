#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "types.hh"
#include "interrupts.hh"
#include "port.hh"

class KeyboardDriver : public InterruptHandler
{
    Port8Bit dataport;
    Port8Bit commandport;

public:
    KeyboardDriver(InterruptManager *manager);
    ~KeyboardDriver();
    virtual uint32_t HandleInterrupt(uint32_t esp);
};

#endif
