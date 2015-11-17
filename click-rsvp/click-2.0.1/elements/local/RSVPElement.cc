#include <click/config.h>
#include <click/confparse.hh>
#include <click/error.hh>
#include "RSVPElement.hh"

CLICK_DECLS
RSVPElement::RSVPElement()
{}

RSVPElement::~ RSVPElement()
{}

int RSVPElement::configure(Vector<String> &conf, ErrorHandler *errh) {
	if (conf.size() > 0)
		return errh->error("Only empty configuraion string");
	return 0;
}

void RSVPElement::push(int, Packet *p){

}

Packet* RSVPElement::pull(int){

}

int RSVPElement::handle(const String &conf, Element *e, void * thunk, ErrorHandler *errh) {
  RSVPElement * me = (RSVPElement *) e;
  
  int i;
  
  if(cp_va_kparse(conf, me, errh, "INTEGER", cpkM + cpkP, cpInteger, &i, cpEnd) < 0) return -1;
  
  click_chatter("received integer: %d", (int) i);
  
  //me->doSomething
  return 666;
}

String RSVPElement::handle2(Element *e, void * thunk) {
  RSVPElement *me = (RSVPElement *) e;
  return "123211232132131";
}

void RSVPElement::add_handlers() {
  add_write_handler("a", &handle, (void *)0);
  add_read_handler("b", &handle2, (void *)0);
}

CLICK_ENDDECLS
EXPORT_ELEMENT(RSVPElement)
