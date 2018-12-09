#ifndef __MYOS__NETWORK__TCP_H
#define __MYOS__NETWORK__TCP_H

#include <shared/types.hh>
#include <network/ipv4.hh>
#include <memorymanagement.hh>

namespace myos
{
    namespace network
    {
        enum TransmissionControlProtocolSocketState
        {
            CLOSED,
            LISTEN,
            SYN_SENT,
            SYN_RECEIVED,

            ESTABLISHED,

            FIN_WAIT1,
            FIN_WAIT2,
            CLOSING,
            TIME_WAIT,

            CLOSE_WAIT
            // LAST_ACK
        };

        enum TransmissionControlProtocolFlag
        {
            FIN = 1,
            SYN = 2,
            RST = 4,
            PSH = 8,
            ACK = 16,
            URG = 32,
            ECE = 64,
            CWR = 128,
            NS = 256
        };

        struct TransmissionControlProtocolHeader
        {
            shared::uint16_t srcPort;
            shared::uint16_t dstPort;
            shared::uint32_t sequenceNumber;
            shared::uint32_t acknowledgementNumber;

            shared::uint8_t reserved : 4;
            shared::uint8_t headerSize32 : 4;
            shared::uint8_t flags;

            shared::uint16_t windowSize;
            shared::uint16_t checksum;
            shared::uint16_t urgentPtr;

            shared::uint32_t options;
        } __attribute__((packed));

        struct TransmissionControlProtocolPseudoHeader
        {
            shared::uint32_t srcIP;
            shared::uint32_t dstIP;
            shared::uint16_t protocol;
            shared::uint16_t totalLength;
        } __attribute__((packed));

        class TransmissionControlProtocolSocket;
        class TransmissionControlProtocolProvider;

        class TransmissionControlProtocolHandler
        {
        public:
            TransmissionControlProtocolHandler();
            ~TransmissionControlProtocolHandler();
            virtual bool HandleTransmissionControlProtocolMessage(TransmissionControlProtocolSocket *socket, shared::uint8_t *data, shared::uint16_t size);
        };

        class TransmissionControlProtocolSocket
        {
            friend class TransmissionControlProtocolProvider;

        protected:
            shared::uint16_t remotePort;
            shared::uint32_t remoteIP;
            shared::uint16_t localPort;
            shared::uint32_t localIP;
            shared::uint32_t sequenceNumber;
            shared::uint32_t acknowledgementNumber;

            TransmissionControlProtocolProvider *backend;
            TransmissionControlProtocolHandler *handler;

            TransmissionControlProtocolSocketState state;

        public:
            TransmissionControlProtocolSocket(TransmissionControlProtocolProvider *backend);
            ~TransmissionControlProtocolSocket();
            virtual bool HandleTransmissionControlProtocolMessage(shared::uint8_t *data, shared::uint16_t size);
            virtual void Send(shared::uint8_t *data, shared::uint16_t size);
            virtual void Disconnect();
        };

        class TransmissionControlProtocolProvider : InternetProtocolHandler
        {
        protected:
            TransmissionControlProtocolSocket *sockets[65535];
            shared::uint16_t numSockets;
            shared::uint16_t freePort;

        public:
            TransmissionControlProtocolProvider(InternetProtocolProvider *backend);
            ~TransmissionControlProtocolProvider();

            virtual bool OnInternetProtocolReceived(shared::uint32_t srcIP_BE, shared::uint32_t dstIP_BE,
                                                    shared::uint8_t *internetprotocolPayload, shared::uint32_t size);

            virtual TransmissionControlProtocolSocket *Connect(shared::uint32_t ip, shared::uint16_t port);
            virtual void Disconnect(TransmissionControlProtocolSocket *socket);
            virtual void Send(TransmissionControlProtocolSocket *socket, shared::uint8_t *data, shared::uint16_t size,
                              shared::uint16_t flags = 0);

            virtual TransmissionControlProtocolSocket *Listen(shared::uint16_t port);
            virtual void Bind(TransmissionControlProtocolSocket *socket, TransmissionControlProtocolHandler *handler);
        };
    }
}

#endif
