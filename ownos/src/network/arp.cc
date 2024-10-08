
#include "network/arp.hh"

ARP::ARP(EtherFrameProvider* backend)
  : EtherFrameHandler(backend, 0x806)
{
	total_cache_entries = 0;
}

ARP::~ARP() {}

bool
ARP::on_etherframe_recv(const u8* etherframe_payload, const u32 size)
{
	if (size < sizeof(ARPMessage))
	{
		return false;
	}

	ARPMessage* arp = (ARPMessage*)etherframe_payload;
	if (arp->hardware_type == 0x0100)
	{
		if (arp->protocol == 0x0008 && arp->hardware_address_size == 6 &&
			arp->protocol_address_size == 4 &&
			arp->dst_ip == backend->get_ip_address())
		{

			switch (arp->command)
			{
				case 0x0100: // request
					arp->command = 0x0200;
					arp->dst_ip = arp->src_ip;
					arp->dst_mac = arp->src_mac;
					arp->src_ip = backend->get_ip_address();
					arp->src_mac = backend->get_mac_address();
					return true;
					break;

				case 0x0200: // response
					if (total_cache_entries < 128)
					{
						ip_cache[total_cache_entries] = arp->src_ip;
						mac_cache[total_cache_entries] = arp->src_mac;
						total_cache_entries++;
					}
					break;
			}
		}
	}

	return false;
}

void
ARP::request_mac_address(const u32 ip_be)
{
	ARPMessage arp;
	arp.hardware_type = 0x0100;	   // ethernet
	arp.protocol = 0x0008;		   // ipv4
	arp.hardware_address_size = 6; // mac
	arp.protocol_address_size = 4; // ipv4
	arp.command = 0x0100;		   // request

	arp.src_mac = backend->get_mac_address();
	arp.src_ip = backend->get_ip_address();
	arp.dst_mac = 0xFFFFFFFFFFFF;
	arp.dst_ip = ip_be;

	send(arp.dst_mac, (u8*)&arp, sizeof(ARPMessage));
}

const u64
ARP::get_mac_from_cache(const u32 ip_be) const
{
	for (int i = 0; i < total_cache_entries; i++)
	{
		if (ip_cache[i] == ip_be)
		{
			return mac_cache[i];
		}
	}
	return 0xFFFFFFFFFFFF;
}

u64
ARP::resolve(const u32 ip_be)
{
	u64 result = get_mac_from_cache(ip_be);
	if (result == 0xFFFFFFFFFFFF)
	{
		request_mac_address(ip_be);
	}

	while (result == 0xFFFFFFFFFFFF)
	{
		result = get_mac_from_cache(ip_be);
	}

	return result;
}

void
ARP::broadcast_mac_address(const u32 ip_be)
{
	ARPMessage arp;

	arp.hardware_type = 0x0100;	   // ethernet
	arp.protocol = 0x0008;		   // ipv4
	arp.hardware_address_size = 6; // mac
	arp.protocol_address_size = 4; // ipv4
	arp.command = 0x0200;		   // "response"

	arp.src_mac = backend->get_mac_address();
	arp.src_ip = backend->get_ip_address();
	arp.dst_mac = resolve(ip_be);
	arp.dst_ip = ip_be;

	send(arp.dst_mac, (u8*)&arp, sizeof(ARPMessage));
}
