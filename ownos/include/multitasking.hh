#ifndef __MYOS__MULTITASKING_H
#define __MYOS__MULTITASKING_H

#include <shared/types.hh>
#include <gdt.hh>

namespace myos
{
    struct CPUState
    {
        shared::uint32_t eax;
        shared::uint32_t ebx;
        shared::uint32_t ecx;
        shared::uint32_t edx;

        shared::uint32_t esi;
        shared::uint32_t edi;
        shared::uint32_t ebp;

        /*
        shared::uint32_t gs;
        shared::uint32_t fs;
        shared::uint32_t es;
        shared::uint32_t ds;
        */
        shared::uint32_t error;

        shared::uint32_t eip;
        shared::uint32_t cs;
        shared::uint32_t eflags;
        shared::uint32_t esp;
        shared::uint32_t ss;
    } __attribute__((packed));

    class Task
    {
        friend class TaskManager;

    private:
        shared::uint8_t stack[4096]; // 4 KiB
        CPUState *cpustate;

    public:
        Task(GlobalDescriptorTable *gdt, void entrypoint());
        ~Task();
    };

    class TaskManager
    {
    private:
        Task *tasks[256];
        int numTasks;
        int currentTask;

    public:
        TaskManager();
        ~TaskManager();
        bool AddTask(Task *task);
        CPUState *Schedule(CPUState *cpustate);
    };
}

#endif
