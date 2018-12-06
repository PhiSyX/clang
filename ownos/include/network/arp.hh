
#ifndef __MYOS__NETWORK__ARP_H
#define __MYOS__NETWORK__ARP_H

#include <shared/types.hh>
#include <network/etherframe.hh>

namespace myos
{
    namespace network
    {

        struct AddressResolutionProtocolMessage
        {
            shared::uint16_t hardwareType;
            shared::uint16_t protocol;
            shared::uint8_t hardwareAddressSize; // 6
            shared::uint8_t protocolAddressSize; // 4
            shared::uint16_t command;

            shared::uint64_t srcMAC : 48;
            shared::uint32_t srcIP;
            shared::uint64_t dstMAC : 48;
            shared::uint32_t dstIP;

        } __attribute__((packed));

        class AddressResolutionProtocol : public EtherFrameHandler
        {

            shared::uint32_t IPcache[128];
            shared::uint64_t MACcache[128];
            int numCacheEntries;

        public:
            AddressResolutionProtocol(EtherFrameProvider *backend);
            ~AddressResolutionProtocol();

            bool OnEtherFrameReceived(shared::uint8_t *etherframePayload, shared::uint32_t size);

            void RequestMACAddress(shared::uint32_t IP_BE);
            shared::uint64_t GetMACFromCache(shared::uint32_t IP_BE);
            shared::uint64_t Resolve(shared::uint32_t IP_BE);
        };
    }
}

#endif
