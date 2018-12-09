#ifndef __MYOS__NETWORK__ETHERFRAME_H
#define __MYOS__NETWORK__ETHERFRAME_H

#include <shared/types.hh>
#include <drivers/amd_am79c973.hh>
#include <memorymanagement.hh>

namespace myos
{
    namespace network
    {
        struct EtherFrameHeader
        {
            shared::uint64_t dstMAC_BE : 48;
            shared::uint64_t srcMAC_BE : 48;
            shared::uint16_t etherType_BE;
        } __attribute__((packed));

        typedef shared::uint32_t EtherFrameFooter;

        class EtherFrameProvider;

        class EtherFrameHandler
        {
        protected:
            EtherFrameProvider *backend;
            shared::uint16_t etherType_BE;

        public:
            EtherFrameHandler(EtherFrameProvider *backend, shared::uint16_t etherType);
            ~EtherFrameHandler();

            virtual bool OnEtherFrameReceived(shared::uint8_t *etherframePayload, shared::uint32_t size);
            void Send(shared::uint64_t dstMAC_BE, shared::uint8_t *etherframePayload, shared::uint32_t size);
            shared::uint32_t GetIPAddress();
        };

        class EtherFrameProvider : public myos::drivers::RawDataHandler
        {
            friend class EtherFrameHandler;

        protected:
            EtherFrameHandler *handlers[65535];

        public:
            EtherFrameProvider(drivers::amd_am79c973 *backend);
            ~EtherFrameProvider();

            bool OnRawDataReceived(shared::uint8_t *buffer, shared::uint32_t size);
            void Send(shared::uint64_t dstMAC_BE, shared::uint16_t etherType_BE, shared::uint8_t *buffer, shared::uint32_t size);

            shared::uint64_t GetMACAddress();
            shared::uint32_t GetIPAddress();
        };
    }
}

#endif
