#ifndef __MYOS__NETWORK__ICMP_H
#define __MYOS__NETWORK__ICMP_H

#include <shared/types.hh>
#include <network/ipv4.hh>

namespace myos
{
    namespace network
    {
        struct InternetControlMessageProtocolMessage
        {
            shared::uint8_t type;
            shared::uint8_t code;

            shared::uint16_t checksum;
            shared::uint32_t data;

        } __attribute__((packed));

        class InternetControlMessageProtocol : InternetProtocolHandler
        {
        public:
            InternetControlMessageProtocol(InternetProtocolProvider *backend);
            ~InternetControlMessageProtocol();

            bool OnInternetProtocolReceived(shared::uint32_t srcIP_BE, shared::uint32_t dstIP_BE,
                                            shared::uint8_t *internetprotocolPayload, shared::uint32_t size);
            void RequestEchoReply(shared::uint32_t ip_be);
        };
    }
}

#endif
