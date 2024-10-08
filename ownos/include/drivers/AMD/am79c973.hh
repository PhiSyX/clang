#ifndef __AMD_AM79C973_HPP__
#define __AMD_AM79C973_HPP__

#include <COM/interrupts.hh>
#include <COM/pci.hh>
#include <COM/port.hh>
#include <drivers/driver.hh>
#include <types.hh>

void
printf(char*);
void printh(u8);

class amd_am79c973;

class RawDataHandler
{
  protected:
	amd_am79c973* backend;

  public:
	RawDataHandler(amd_am79c973* backend);
	~RawDataHandler();

  public:
	virtual bool on_rawdata_recv(u8* buffer, u32 size);
	void send(u8* buffer, u32 size);
};

class amd_am79c973
  : public Driver
  , public InterruptHandler
{
	struct InitializationBlock
	{
		u16 mode;
		unsigned reserved_1 : 4;
		unsigned total_send_buffers : 4;
		unsigned reserved_2 : 4;
		unsigned total_recv_buffers : 4;
		u64 physical_address : 48;
		u16 reserved_3;
		u64 logical_address;
		u32 recv_buffer_descriptor_address;
		u32 send_buffer_descriptor_address;
	} __attribute__((packed));

	struct BufferDescriptor
	{
		u32 address;
		u32 flags;
		u32 flags_2;
		u32 avail;
	} __attribute__((packed));

	Port16Bit mac_address0_port;
	Port16Bit mac_address2_port;
	Port16Bit mac_address4_port;
	Port16Bit register_data_port;
	Port16Bit register_address_port;
	Port16Bit reset_port;
	Port16Bit bus_control_register_data_port;

	InitializationBlock init_block;

	BufferDescriptor* send_buffer_descriptor;
	u8 send_buffer_descriptor_memory[2048 + 15];
	u8 send_buffers[2 * 1024 + 15][8];
	u8 current_send_buffer;

	BufferDescriptor* recv_buffer_descriptor;
	u8 recv_buffer_descriptor_memory[2048 + 15];
	u8 recv_buffers[2 * 1024 + 15][8];
	u8 current_recv_buffer;

	RawDataHandler* handler;

  public:
	amd_am79c973(const PCIDeviceDescriptor* device, InterruptManager* im);
	~amd_am79c973();

  public:
	/* contains static */ void activate();
	/* contains static */ const i32 reset();

	/* contains static */ const u32 handle_interrupt(const u32 esp);
	/* mut */ void send(u8* buffer, usize count);
	/* mut */ void recv();

	/* mut */ void set_handler(RawDataHandler* handler);
	const u64 get_mac_address() const;
	/* mut */ void set_ip_address(const u32);
	const u32 get_ip_address() const;
};

#endif
