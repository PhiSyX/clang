#ifndef __MYOS__NETWORK__UDP_H
#define __MYOS__NETWORK__UDP_H

#include <shared/types.hh>
#include <network/ipv4.hh>
#include <memorymanagement.hh>

namespace myos
{
    namespace network
    {
        struct UserDatagramProtocolHeader
        {
            shared::uint16_t srcPort;
            shared::uint16_t dstPort;
            shared::uint16_t length;
            shared::uint16_t checksum;
        } __attribute__((packed));

        class UserDatagramProtocolSocket;
        class UserDatagramProtocolProvider;

        class UserDatagramProtocolHandler
        {
        public:
            UserDatagramProtocolHandler();
            ~UserDatagramProtocolHandler();
            virtual void HandleUserDatagramProtocolMessage(UserDatagramProtocolSocket *socket, shared::uint8_t *data, shared::uint16_t size);
        };

        class UserDatagramProtocolSocket
        {
            friend class UserDatagramProtocolProvider;

        protected:
            shared::uint16_t remotePort;
            shared::uint32_t remoteIP;
            shared::uint16_t localPort;
            shared::uint32_t localIP;
            UserDatagramProtocolProvider *backend;
            UserDatagramProtocolHandler *handler;
            bool listening;

        public:
            UserDatagramProtocolSocket(UserDatagramProtocolProvider *backend);
            ~UserDatagramProtocolSocket();
            virtual void HandleUserDatagramProtocolMessage(shared::uint8_t *data, shared::uint16_t size);
            virtual void Send(shared::uint8_t *data, shared::uint16_t size);
            virtual void Disconnect();
        };

        class UserDatagramProtocolProvider : InternetProtocolHandler
        {
        protected:
            UserDatagramProtocolSocket *sockets[65535];
            shared::uint16_t numSockets;
            shared::uint16_t freePort;

        public:
            UserDatagramProtocolProvider(InternetProtocolProvider *backend);
            ~UserDatagramProtocolProvider();

            virtual bool OnInternetProtocolReceived(shared::uint32_t srcIP_BE, shared::uint32_t dstIP_BE,
                                                    shared::uint8_t *internetprotocolPayload, shared::uint32_t size);

            virtual UserDatagramProtocolSocket *Connect(shared::uint32_t ip, shared::uint16_t port);
            virtual UserDatagramProtocolSocket *Listen(shared::uint16_t port);
            virtual void Disconnect(UserDatagramProtocolSocket *socket);
            virtual void Send(UserDatagramProtocolSocket *socket, shared::uint8_t *data, shared::uint16_t size);

            virtual void Bind(UserDatagramProtocolSocket *socket, UserDatagramProtocolHandler *handler);
        };
    }
}

#endif
