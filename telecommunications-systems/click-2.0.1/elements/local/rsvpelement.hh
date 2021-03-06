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
	
	const RSVPNodeSession* sessionForSenderTimer(const Timer *, const RSVPSender**) const;
	const RSVPNodeSession* sessionForReservationTimer(const Timer *, const RSVPSender**) const;
	
	void sendPeriodicPathMessage(const RSVPNodeSession*, const RSVPSender*);
	void sendPeriodicResvMessage(const RSVPNodeSession*, const RSVPSender*);

	virtual void createSession(const RSVPNodeSession&);
	
	virtual void erasePathState(const RSVPNodeSession&, const RSVPSender&);
	virtual void eraseResvState(const RSVPNodeSession&, const RSVPSender&);
	void removeSender(const RSVPNodeSession&, const RSVPSender&);
	void removeReservation(const RSVPNodeSession&, const RSVPSender&);
	virtual void removeAllState();

	virtual const RSVPPathState* pathState(const RSVPNodeSession&, const RSVPSender&) const;
	virtual const RSVPResvState* resvState(const RSVPNodeSession&, const RSVPSender&) const;

	virtual bool hasReservation(const RSVPNodeSession&, const RSVPSender&) const;

	virtual void push(int, Packet *);
	Packet* pull(int);

	WritablePacket* replyToPathMessage(Packet* pathMessage);

	// specify object fields handlers
	// session handle needs to be called first
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
	// calling the path handle will send the first path message
	static int pathHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	static int resvHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	static int pathErrHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	static int resvErrHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	static int pathTearHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	static int resvTearHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	static int resvConfHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	
	static int tosHandle(const String &conf, Element *e, void * thunk, ErrorHandler *errh);
	static String getTTLHandle(Element *e, void * thunk);

	static String sendersTableHandle(Element *e, void *thunk);
	static String reservationsTableHandle(Element *e, void *thunk);

	void add_handlers();
	
	WritablePacket* createPacket(uint16_t packetSize) const;

	WritablePacket* createPathMessage(const RSVPSession* session,
		const RSVPHop* hop,
		const RSVPTimeValues* timeValues,
		const RSVPSenderTemplate* senderTemplate,
		const RSVPSenderTSpec* senderTSpec) const;
	WritablePacket* createResvMessage() const;
	WritablePacket* createResvMessage(const RSVPSession* p_session,
		const RSVPHop* p_hop,
		const RSVPTimeValues* p_timeValues,
		const RSVPResvConf* p_resvConf,
		const RSVPFlowspec* p_flowspec,
		const RSVPFilterSpec* p_filterSpec) const;
	WritablePacket* createPathErrMessage() const;
	WritablePacket* createResvErrMessage() const;
	WritablePacket* createPathTearMessage() const;
	WritablePacket* createResvTearMessage() const;
	WritablePacket* createResvConfMessage() const;
	
	void die();

private:
	bool _autoResv;
	HashTable<RSVPNodeSession, HashTable<RSVPSender, RSVPPathState> > _senders;
	HashTable<RSVPNodeSession, HashTable<RSVPSender, RSVPResvState> > _reservations;

	bool _application;
	void clean();

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
