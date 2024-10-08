#ifndef __ARP_HPP__
#define __ARP_HPP__

#include <network/etherframe.hh>
#include <shared/types.hh>

// Address Resolution Protocol Message
struct ARPMessage
{
	u16 hardware_type;
	u16 protocol;
	u8 hardware_address_size; // 6
	u8 protocol_address_size; // 4
	u16 command;

	u64 src_mac : 48;
	u32 src_ip;
	u64 dst_mac : 48;
	u32 dst_ip;
} __attribute__((packed));

// Address Resolution Protocol
class ARP : public EtherFrameHandler
{
	u32 ip_cache[128];
	u64 mac_cache[128];
	int total_cache_entries;

  public:
	ARP(EtherFrameProvider* backend);
	~ARP();

  public:
	bool on_etherframe_recv(const u8* etherframe_payload, const u32 size);

	void request_mac_address(const u32 ip_be);
	const u64 get_mac_from_cache(const u32 ip_be) const;
	u64 resolve(const u32 ip_be);
	void broadcast_mac_address(const u32 ip_be);
};

#endif
