#include <syscalls.hh>

using namespace myos;
using namespace myos::shared;
using namespace myos::COM;

SyscallHandler::SyscallHandler(InterruptManager *interruptManager, uint8_t InterruptNumber)
    : InterruptHandler(interruptManager, InterruptNumber + interruptManager->HardwareInterruptOffset())
{
}

SyscallHandler::~SyscallHandler()
{
}

void printf(char *);

uint32_t SyscallHandler::HandleInterrupt(uint32_t esp)
{
    CPUState *cpu = (CPUState *)esp;

    switch (cpu->eax)
    {
    case 4:
        printf((char *)cpu->ebx);
        break;

    default:
        break;
    }

    return esp;
}
