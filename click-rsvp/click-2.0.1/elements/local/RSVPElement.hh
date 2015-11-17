#ifndef CLICK_RSVPElement_HH
#define CLICK_RSVPElement_HH
#include <click/element.hh>
#include <clicknet/ip.h>
CLICK_DECLS

struct RSVPCommonHeader {
	// RSVPCommonHeader() : vers(1), flags(0), RSVP_checksum(0), reserved(0) {}
	unsigned    vers : 4;
	unsigned    flags : 4;
	uint8_t     msg_type;
	uint16_t    RSVP_checksum;
	uint8_t     send_TTL;
	uint8_t     reserved;
	uint16_t    RSVP_length;
};

struct RSVPObjectHeader {
	uint16_t length;
	uint8_t class_num;
	uint8_t c_type;
};

struct RSVPSessionClass { // class num = 1, C-type = 1
	in_addr IPv4_dest_address;
	uint8_t protocol_id;
	uint8_t flags;
	uint16_t dst_port;
};

struct RSVPHopClass { // class num = 3, C-type = 1
	in_addr IPv4_next_previous_hop_address;
	uint32_t logical_interface_handle;
};

struct RSVPIntegrityClass { // class num = 4, C-type = 1
	unsigned flags : 4;
	unsigned reserved : 4;
	uint64_t key_identifier : 48;
	uint64_t sequence_number;
	uint64_t keyed_message_digest_1;
	uint64_t keyed_message_digest_2;
};

struct RSVPTimeValuesClass { // class num = 5, C-type = 1
	uint32_t refresh_period_r;
};

struct RSVPErrorSpecClass { // class num = 6, C-type = 1
	in_addr IPv4_error_node_address;
	uint8_t flags;
	uint8_t error_code;
	uint16_t error_value;
};



class RSVPElement : public Element {
	public:
		RSVPElement();
		~RSVPElement();

		const char *class_name() const	{ return "RSVPElement"; }
		const char *port_count() const	{ return "1/1"; }
		const char *processing() const	{ return "h/h"; }
		int configure(Vector<String>&, ErrorHandler*);

		void push(int, Packet *);
		Packet* pull(int);

    static int handle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
    static String handle2(Element *e, void * thunk);
    void add_handlers();
	private:

};

CLICK_ENDDECLS
#endif
