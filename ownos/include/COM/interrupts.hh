#ifndef __MYOS__COM__INTERRUPTMANAGER_H
#define __MYOS__COM__INTERRUPTMANAGER_H

#include <gdt.hh>
#include <multitasking.hh>
#include <shared/types.hh>
#include <COM/port.hh>

namespace myos
{
    namespace COM
    {
        class InterruptManager;

        class InterruptHandler
        {
        protected:
            myos::shared::uint8_t InterruptNumber;
            InterruptManager *interruptManager;
            InterruptHandler(InterruptManager *interruptManager, myos::shared::uint8_t InterruptNumber);
            ~InterruptHandler();

        public:
            virtual myos::shared::uint32_t HandleInterrupt(myos::shared::uint32_t esp);
        };

        class InterruptManager
        {
            friend class InterruptHandler;

        protected:
            static InterruptManager *ActiveInterruptManager;
            InterruptHandler *handlers[256];
            TaskManager *taskManager;

            struct GateDescriptor
            {
                myos::shared::uint16_t handlerAddressLowBits;
                myos::shared::uint16_t gdt_codeSegmentSelector;
                myos::shared::uint8_t reserved;
                myos::shared::uint8_t access;
                myos::shared::uint16_t handlerAddressHighBits;
            } __attribute__((packed));

            static GateDescriptor interruptDescriptorTable[256];

            struct InterruptDescriptorTablePointer
            {
                myos::shared::uint16_t size;
                myos::shared::uint32_t base;
            } __attribute__((packed));

            myos::shared::uint16_t hardwareInterruptOffset;
            static void SetInterruptDescriptorTableEntry(myos::shared::uint8_t interrupt,
                                                         myos::shared::uint16_t codeSegmentSelectorOffset, void (*handler)(),
                                                         myos::shared::uint8_t DescriptorPrivilegeLevel, myos::shared::uint8_t DescriptorType);

            static void InterruptIgnore();

            static void HandleInterruptRequest0x00();
            static void HandleInterruptRequest0x01();
            static void HandleInterruptRequest0x02();
            static void HandleInterruptRequest0x03();
            static void HandleInterruptRequest0x04();
            static void HandleInterruptRequest0x05();
            static void HandleInterruptRequest0x06();
            static void HandleInterruptRequest0x07();
            static void HandleInterruptRequest0x08();
            static void HandleInterruptRequest0x09();
            static void HandleInterruptRequest0x0A();
            static void HandleInterruptRequest0x0B();
            static void HandleInterruptRequest0x0C();
            static void HandleInterruptRequest0x0D();
            static void HandleInterruptRequest0x0E();
            static void HandleInterruptRequest0x0F();
            static void HandleInterruptRequest0x31();
            static void HandleInterruptRequest0x80();

            static void HandleException0x00();
            static void HandleException0x01();
            static void HandleException0x02();
            static void HandleException0x03();
            static void HandleException0x04();
            static void HandleException0x05();
            static void HandleException0x06();
            static void HandleException0x07();
            static void HandleException0x08();
            static void HandleException0x09();
            static void HandleException0x0A();
            static void HandleException0x0B();
            static void HandleException0x0C();
            static void HandleException0x0D();
            static void HandleException0x0E();
            static void HandleException0x0F();
            static void HandleException0x10();
            static void HandleException0x11();
            static void HandleException0x12();
            static void HandleException0x13();

            static myos::shared::uint32_t HandleInterrupt(myos::shared::uint8_t interrupt, myos::shared::uint32_t esp);
            myos::shared::uint32_t DoHandleInterrupt(myos::shared::uint8_t interrupt, myos::shared::uint32_t esp);

            Port8BitSlow programmableInterruptControllerMasterCommandPort;
            Port8BitSlow programmableInterruptControllerMasterDataPort;
            Port8BitSlow programmableInterruptControllerSlaveCommandPort;
            Port8BitSlow programmableInterruptControllerSlaveDataPort;

        public:
            InterruptManager(myos::shared::uint16_t hardwareInterruptOffset, myos::GlobalDescriptorTable *globalDescriptorTable, myos::TaskManager *taskManager);
            ~InterruptManager();
            myos::shared::uint16_t HardwareInterruptOffset();
            void Activate();
            void Deactivate();
        };
    }
}

#endif
