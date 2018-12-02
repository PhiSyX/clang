#ifndef __MYOS__GDT_H
#define __MYOS__GDT_H

#include <shared/types.hh>

namespace myos
{
    class GlobalDescriptorTable
    {
    public:
        class SegmentDescriptor
        {
        private:
            myos::shared::uint16_t limit_lo;
            myos::shared::uint16_t base_lo;
            myos::shared::uint8_t base_hi;
            myos::shared::uint8_t type;
            myos::shared::uint8_t limit_hi;
            myos::shared::uint8_t base_vhi;

        public:
            SegmentDescriptor(myos::shared::uint32_t base, myos::shared::uint32_t limit, myos::shared::uint8_t type);
            myos::shared::uint32_t Base();
            myos::shared::uint32_t Limit();
        } __attribute__((packed));

    private:
        SegmentDescriptor nullSegmentSelector;
        SegmentDescriptor unusedSegmentSelector;
        SegmentDescriptor codeSegmentSelector;
        SegmentDescriptor dataSegmentSelector;

    public:
        GlobalDescriptorTable();
        ~GlobalDescriptorTable();

        myos::shared::uint16_t CodeSegmentSelector();
        myos::shared::uint16_t DataSegmentSelector();
    };
}

#endif
