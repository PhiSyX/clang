#ifndef __MYOS__MEMORYMANAGEMENT_H
#define __MYOS__MEMORYMANAGEMENT_H

#include <shared/types.hh>

namespace myos
{

    struct MemoryChunk
    {
        MemoryChunk *next;
        MemoryChunk *prev;
        bool allocated;
        shared::size_t size;
    };

    class MemoryManager
    {

    protected:
        MemoryChunk *first;

    public:
        static MemoryManager *activeMemoryManager;

        MemoryManager(shared::size_t first, shared::size_t size);
        ~MemoryManager();

        void *malloc(shared::size_t size);
        void free(void *ptr);
    };
}

void *operator new(unsigned size);
void *operator new[](unsigned size);

// placement new
void *operator new(unsigned size, void *ptr);
void *operator new[](unsigned size, void *ptr);

void operator delete(void *ptr);
void operator delete[](void *ptr);

#endif
