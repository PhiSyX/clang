#ifndef __MYOS__DRIVERS__AMD_AM79C973_H
#define __MYOS__DRIVERS__AMD_AM79C973_H

#include <shared/types.hh>
#include <drivers/driver.hh>
#include <COM/pci.hh>
#include <COM/interrupts.hh>
#include <COM/port.hh>

namespace myos
{
    namespace drivers
    {

        class amd_am79c973 : public Driver, public COM::InterruptHandler
        {
            struct InitializationBlock
            {
                shared::uint16_t mode;
                unsigned reserved1 : 4;
                unsigned numSendBuffers : 4;
                unsigned reserved2 : 4;
                unsigned numRecvBuffers : 4;
                shared::uint64_t physicalAddress : 48;
                shared::uint16_t reserved3;
                shared::uint64_t logicalAddress;
                shared::uint32_t recvBufferDescrAddress;
                shared::uint32_t sendBufferDescrAddress;
            } __attribute__((packed));

            struct BufferDescriptor
            {
                shared::uint32_t address;
                shared::uint32_t flags;
                shared::uint32_t flags2;
                shared::uint32_t avail;
            } __attribute__((packed));

            COM::Port16Bit MACAddress0Port;
            COM::Port16Bit MACAddress2Port;
            COM::Port16Bit MACAddress4Port;
            COM::Port16Bit registerDataPort;
            COM::Port16Bit registerAddressPort;
            COM::Port16Bit resetPort;
            COM::Port16Bit busControlRegisterDataPort;

            InitializationBlock initBlock;

            BufferDescriptor *sendBufferDescr;
            shared::uint8_t sendBufferDescrMemory[2048 + 15];
            shared::uint8_t sendBuffers[2 * 1024 + 15][8];
            shared::uint8_t currentSendBuffer;

            BufferDescriptor *recvBufferDescr;
            shared::uint8_t recvBufferDescrMemory[2048 + 15];
            shared::uint8_t recvBuffers[2 * 1024 + 15][8];
            shared::uint8_t currentRecvBuffer;

        public:
            amd_am79c973(myos::COM::PeripheralComponentInterconnectDeviceDescriptor *dev,
                         myos::COM::InterruptManager *interrupts);
            ~amd_am79c973();

            void Activate();
            int Reset();
            shared::uint32_t HandleInterrupt(shared::uint32_t esp);

            void Send(shared::uint8_t *buffer, int count);
            void Receive();
        };

    }
}

#endif
