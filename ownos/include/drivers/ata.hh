#ifndef __MYOS__DRIVERS__ATA_H
#define __MYOS__DRIVERS__ATA_H

#include <shared/types.hh>
#include <COM/interrupts.hh>
#include <COM/port.hh>

namespace myos
{
    namespace drivers
    {
        class AdvancedTechnologyAttachment
        {
        protected:
            bool master;
            COM::Port16Bit dataPort;
            COM::Port8Bit errorPort;
            COM::Port8Bit sectorCountPort;
            COM::Port8Bit lbaLowPort;
            COM::Port8Bit lbaMidPort;
            COM::Port8Bit lbaHiPort;
            COM::Port8Bit devicePort;
            COM::Port8Bit commandPort;
            COM::Port8Bit controlPort;

        public:
            AdvancedTechnologyAttachment(bool master, shared::uint16_t portBase);
            ~AdvancedTechnologyAttachment();

            void Identify();
            void Read28(shared::uint32_t sectorNum, int count = 512);
            void Write28(shared::uint32_t sectorNum, shared::uint8_t *data, shared::uint32_t count);
            void Flush();
        };
    }
}

#endif
