#ifndef __MYOS__NETWORK__IPV4_H
#define __MYOS__NETWORK__IPV4_H

#include <shared/types.hh>
#include <network/etherframe.hh>
#include <network/arp.hh>

namespace myos
{
    namespace network
    {

        struct InternetProtocolV4Message
        {
            shared::uint8_t headerLength : 4;
            shared::uint8_t version : 4;
            shared::uint8_t tos;
            shared::uint16_t totalLength;

            shared::uint16_t ident;
            shared::uint16_t flagsAndOffset;

            shared::uint8_t timeToLive;
            shared::uint8_t protocol;
            shared::uint16_t checksum;

            shared::uint32_t srcIP;
            shared::uint32_t dstIP;
        } __attribute__((packed));

        class InternetProtocolProvider;

        class InternetProtocolHandler
        {
        protected:
            InternetProtocolProvider *backend;
            shared::uint8_t ip_protocol;

        public:
            InternetProtocolHandler(InternetProtocolProvider *backend, shared::uint8_t protocol);
            ~InternetProtocolHandler();

            virtual bool OnInternetProtocolReceived(shared::uint32_t srcIP_BE, shared::uint32_t dstIP_BE,
                                                    shared::uint8_t *internetprotocolPayload, shared::uint32_t size);
            void Send(shared::uint32_t dstIP_BE, shared::uint8_t *internetprotocolPayload, shared::uint32_t size);
        };

        class InternetProtocolProvider : EtherFrameHandler
        {
            friend class InternetProtocolHandler;

        protected:
            InternetProtocolHandler *handlers[255];
            AddressResolutionProtocol *arp;
            shared::uint32_t gatewayIP;
            shared::uint32_t subnetMask;

        public:
            InternetProtocolProvider(EtherFrameProvider *backend,
                                     AddressResolutionProtocol *arp,
                                     shared::uint32_t gatewayIP, shared::uint32_t subnetMask);
            ~InternetProtocolProvider();

            bool OnEtherFrameReceived(shared::uint8_t *etherframePayload, shared::uint32_t size);

            void Send(shared::uint32_t dstIP_BE, shared::uint8_t protocol, shared::uint8_t *buffer, shared::uint32_t size);

            static shared::uint16_t Checksum(shared::uint16_t *data, shared::uint32_t lengthInBytes);
        };
    }
}

#endif
