#ifndef __MYOS__DRIVERS__KEYBOARD_H
#define __MYOS__DRIVERS__KEYBOARD_H

#include <shared/types.hh>
#include <COM/interrupts.hh>
#include <drivers/driver.hh>
#include <COM/port.hh>

namespace myos
{
    namespace drivers
    {
        class KeyboardEventHandler
        {
        public:
            KeyboardEventHandler();

            virtual void OnKeyDown(char);
            virtual void OnKeyUp(char);
        };

        class KeyboardDriver : public myos::COM::InterruptHandler, public Driver
        {
            myos::COM::Port8Bit dataport;
            myos::COM::Port8Bit commandport;

            KeyboardEventHandler *handler;

        public:
            KeyboardDriver(myos::COM::InterruptManager *manager, KeyboardEventHandler *handler);
            ~KeyboardDriver();
            virtual myos::shared::uint32_t HandleInterrupt(myos::shared::uint32_t esp);
            virtual void Activate();
        };
    }
}

#endif
