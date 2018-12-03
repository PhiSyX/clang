#ifndef __MYOS__DRIVERS__VGA_H
#define __MYOS__DRIVERS__VGA_H

#include <shared/types.hh>
#include <COM/port.hh>
#include <drivers/driver.hh>

namespace myos
{
    namespace drivers
    {
        class VideoGraphicsArray
        {
        protected:
            COM::Port8Bit miscPort;
            COM::Port8Bit crtcIndexPort;
            COM::Port8Bit crtcDataPort;
            COM::Port8Bit sequencerIndexPort;
            COM::Port8Bit sequencerDataPort;
            COM::Port8Bit graphicsControllerIndexPort;
            COM::Port8Bit graphicsControllerDataPort;
            COM::Port8Bit attributeControllerIndexPort;
            COM::Port8Bit attributeControllerReadPort;
            COM::Port8Bit attributeControllerWritePort;
            COM::Port8Bit attributeControllerResetPort;

            void WriteRegisters(shared::uint8_t *registers);
            shared::uint8_t *GetFrameBufferSegment();

            virtual shared::uint8_t GetColorIndex(shared::uint8_t r, shared::uint8_t g, shared::uint8_t b);

        public:
            VideoGraphicsArray();
            ~VideoGraphicsArray();

            virtual bool SupportsMode(shared::uint32_t width, shared::uint32_t height, shared::uint32_t colordepth);
            virtual bool SetMode(shared::uint32_t width, shared::uint32_t height, shared::uint32_t colordepth);
            virtual void PutPixel(shared::uint32_t x, shared::uint32_t y, shared::uint8_t r, shared::uint8_t g, shared::uint8_t b);
            virtual void PutPixel(shared::uint32_t x, shared::uint32_t y, shared::uint8_t colorIndex);
        };
    }
}

#endif
