
#ifndef __MYOS__DRIVERS__MOUSE_H
#define __MYOS__DRIVERS__MOUSE_H

#include <shared/types.hh>
#include <com/port.hh>
#include <drivers/driver.hh>
#include <com/interrupts.hh>

namespace myos
{
    namespace drivers
    {
        class MouseEventHandler
        {
        public:
            MouseEventHandler();

            virtual void OnActivate();
            virtual void OnMouseDown(myos::shared::uint8_t button);
            virtual void OnMouseUp(myos::shared::uint8_t button);
            virtual void OnMouseMove(int x, int y);
        };

        class MouseDriver : public myos::COM::InterruptHandler, public Driver
        {
            myos::COM::Port8Bit dataport;
            myos::COM::Port8Bit commandport;
            myos::shared::uint8_t buffer[3];
            myos::shared::uint8_t offset;
            myos::shared::uint8_t buttons;

            MouseEventHandler *handler;

        public:
            MouseDriver(myos::COM::InterruptManager *manager, MouseEventHandler *handler);
            ~MouseDriver();
            virtual myos::shared::uint32_t HandleInterrupt(myos::shared::uint32_t esp);
            virtual void Activate();
        };
    }
}

#endif
