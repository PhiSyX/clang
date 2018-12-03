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

            void SelectDrivers(myos::drivers::DriverManager *driverManager);
            PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(myos::shared::uint16_t bus, myos::shared::uint16_t device, myos::shared::uint16_t function);
        };

    }
}

#endif
