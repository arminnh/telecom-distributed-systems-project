#ifndef CLICK_RSVPELEMENT_HH
#define CLICK_RSVPELEMENT_HH
#include <click/element.hh>
#include <clicknet/ip.h>
#include <clicknet/ether.h>
#include <click/timer.hh>
#include "rsvpnode.hh"
CLICK_DECLS

class RSVPElement : public RSVPNode {
public:
	RSVPElement();
	~RSVPElement();

	const char *class_name() const	{ return "RSVPElement"; }
	const char *port_count() const	{ return "-1/1"; }
	const char *processing() const	{ return "h/h"; }
	int configure(Vector<String>&, ErrorHandler*);
	int initialize(ErrorHandler *);
	void run_timer(Timer *);

	virtual void push(int, Packet *);
	Packet* pull(int);

	// specify object fields handlers
	static int sessionHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	static int hopHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	static int errorSpecHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	static int timeValuesHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	static int resvConfObjectHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	static int scopeHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	static int senderDescriptorHandle(const String &conf, Element *e, void *thunk, ErrorHandler *errh);
	static int flowDescriptorHandle(const String & conf, Element *e, void *thunk, ErrorHandler *errh);

	static int nameHandle(const String &conf, Element *e, void *thunk, ErrorHandler *errh);

	// send message handlers
	static int pathHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	static int resvHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	static int pathErrHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	static int resvErrHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	static int pathTearHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	static int resvTearHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	static int resvConfHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	
	static String getTTLHandle(Element *e, void * thunk);
	
	void add_handlers();
	
	WritablePacket* createPacket(uint16_t packetSize) const;

	Packet* createPathMessage() const;
	Packet* createResvMessage() const;
	Packet* createPathErrMessage() const;
	Packet* createResvErrMessage() const;
	Packet* createPathTearMessage() const;
	Packet* createResvTearMessage() const;
	Packet* createResvConfMessage() const;
	
private:

	bool _application;
	String _name;
	void clean();

	Timer _timer;
	uint8_t _TTL;
	
	RSVPSession _session;
	RSVPErrorSpec _errorSpec;
	RSVPHop _hop;
	RSVPTimeValues _timeValues;
	
	bool _senderDescriptor;
	RSVPSenderTemplate _senderTemplate;
	RSVPSenderTSpec _senderTSpec;

	bool _flowDescriptor;
	RSVPFlowspec _flowspec;
	RSVPFilterSpec _filterSpec;

	bool _resvConf_given;
	RSVPResvConf _resvConf;

	Vector<in_addr> _scope_src_addresses;
};

CLICK_ENDDECLS
#endif