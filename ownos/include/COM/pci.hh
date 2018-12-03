#ifndef __MYOS__COM__PCI_H
#define __MYOS__COM__PCI_H

#include <COM/port.hh>
#include <drivers/driver.hh>
#include <shared/types.hh>
#include <COM/interrupts.hh>

namespace myos
{
    namespace COM
    {

        enum BaseAddressRegisterType
        {
            MemoryMapping = 0,
            InputOutput = 1
        };

        class BaseAddressRegister
        {
        public:
            bool prefetchable;
            myos::shared::uint8_t *address;
            myos::shared::uint32_t size;
            BaseAddressRegisterType type;
        };

        class PeripheralComponentInterconnectDeviceDescriptor
        {
        public:
            myos::shared::uint32_t portBase;
            myos::shared::uint32_t interrupt;

            myos::shared::uint16_t bus;
            myos::shared::uint16_t device;
            myos::shared::uint16_t function;

            myos::shared::uint16_t vendor_id;
            myos::shared::uint16_t device_id;

            myos::shared::uint8_t class_id;
            myos::shared::uint8_t subclass_id;
            myos::shared::uint8_t interface_id;

            myos::shared::uint8_t revision;

            PeripheralComponentInterconnectDeviceDescriptor();
            ~PeripheralComponentInterconnectDeviceDescriptor();
        };

        class PeripheralComponentInterconnectController
        {
            Port32Bit dataPort;
            Port32Bit commandPort;

        public:
            PeripheralComponentInterconnectController();
            ~PeripheralComponentInterconnectController();

            myos::shared::uint32_t Read(myos::shared::uint16_t bus, myos::shared::uint16_t device, myos::shared::uint16_t function, myos::shared::uint32_t registeroffset);
            void Write(myos::shared::uint16_t bus, myos::shared::uint16_t device, myos::shared::uint16_t function, myos::shared::uint32_t registeroffset, myos::shared::uint32_t value);
            bool DeviceHasFunctions(myos::shared::uint16_t bus, myos::shared::uint16_t device);

            void SelectDrivers(myos::drivers::DriverManager *driverManager, myos::COM::InterruptManager *interrupts);
            myos::drivers::Driver *GetDriver(PeripheralComponentInterconnectDeviceDescriptor dev, myos::COM::InterruptManager *interrupts);
            PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(myos::shared::uint16_t bus, myos::shared::uint16_t device, myos::shared::uint16_t function);
            BaseAddressRegister GetBaseAddressRegister(myos::shared::uint16_t bus, myos::shared::uint16_t device, myos::shared::uint16_t function, myos::shared::uint16_t bar);
        };

    }
}

#endif