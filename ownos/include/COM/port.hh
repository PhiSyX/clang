#ifndef __MYOS__COM__PORT_H
#define __MYOS__COM__PORT_H

#include <shared/types.hh>

namespace myos
{
    namespace COM
    {
        class Port
        {
        protected:
            Port(myos::shared::uint16_t portnumber);
            ~Port();
            myos::shared::uint16_t portnumber;
        };

        class Port8Bit : public Port
        {
        public:
            Port8Bit(myos::shared::uint16_t portnumber);
            ~Port8Bit();

            virtual myos::shared::uint8_t Read();
            virtual void Write(myos::shared::uint8_t data);

        protected:
            static inline myos::shared::uint8_t Read8(myos::shared::uint16_t _port)
            {
                myos::shared::uint8_t result;
                __asm__ volatile("inb %1, %0" : "=a"(result) : "Nd"(_port));
                return result;
            }

            static inline void Write8(myos::shared::uint16_t _port, myos::shared::uint8_t _data)
            {
                __asm__ volatile("outb %0, %1" : : "a"(_data), "Nd"(_port));
            }
        };

        class Port8BitSlow : public Port8Bit
        {
        public:
            Port8BitSlow(myos::shared::uint16_t portnumber);
            ~Port8BitSlow();

            virtual void Write(myos::shared::uint8_t data);

        protected:
            static inline void Write8Slow(myos::shared::uint16_t _port, myos::shared::uint8_t _data)
            {
                __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:" : : "a"(_data), "Nd"(_port));
            }
        };

        class Port16Bit : public Port
        {
        public:
            Port16Bit(myos::shared::uint16_t portnumber);
            ~Port16Bit();

            virtual myos::shared::uint16_t Read();
            virtual void Write(myos::shared::uint16_t data);

        protected:
            static inline myos::shared::uint16_t Read16(myos::shared::uint16_t _port)
            {
                myos::shared::uint16_t result;
                __asm__ volatile("inw %1, %0" : "=a"(result) : "Nd"(_port));
                return result;
            }

            static inline void Write16(myos::shared::uint16_t _port, myos::shared::uint16_t _data)
            {
                __asm__ volatile("outw %0, %1" : : "a"(_data), "Nd"(_port));
            }
        };

        class Port32Bit : public Port
        {
        public:
            Port32Bit(myos::shared::uint16_t portnumber);
            ~Port32Bit();

            virtual myos::shared::uint32_t Read();
            virtual void Write(myos::shared::uint32_t data);

        protected:
            static inline myos::shared::uint32_t Read32(myos::shared::uint16_t _port)
            {
                myos::shared::uint32_t result;
                __asm__ volatile("inl %1, %0" : "=a"(result) : "Nd"(_port));
                return result;
            }

            static inline void Write32(myos::shared::uint16_t _port, myos::shared::uint32_t _data)
            {
                __asm__ volatile("outl %0, %1" : : "a"(_data), "Nd"(_port));
            }
        };
    }
}

#endif
