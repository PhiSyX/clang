#ifndef __MYOS__SYSCALLS_H
#define __MYOS__SYSCALLS_H

#include <shared/types.hh>
#include <COM/interrupts.hh>
#include <multitasking.hh>

namespace myos
{

    class SyscallHandler : public COM::InterruptHandler
    {

    public:
        SyscallHandler(COM::InterruptManager *interruptManager, myos::shared::uint8_t InterruptNumber);
        ~SyscallHandler();

        virtual myos::shared::uint32_t HandleInterrupt(myos::shared::uint32_t esp);
    };

}

#endif
