/*
 * ivt.cpp
 *
 *  Created on: Jun 15, 2019
 *      Author: OS1
 */

#include "ivt.h"
#include "locks.h"
#include <dos.h>
#include "jezgro.h"
#include "event.h"
class Event;
IVTEntry::IVTEntry(int brojUlaza, IntRout novaRutina){
	event=0;
	this->novaRutina=novaRutina;
	this->brUlaza=brojUlaza;
	postaviNovuRutinu(brUlaza);
	Jezgro::IVTabela[brUlaza]=this;
}


IVTEntry::~IVTEntry(){
	vratiStaruRutinu(brUlaza);
	Jezgro::IVTabela[brUlaza]=0;
}
void IVTEntry::signal(){
	if(event==0) return;
	else{
		event->signal();
	}
}
void IVTEntry::pozoviStaruRutinu(){
	(*staraRutina)();
}
void IVTEntry::addEvent(Event * ev){
	event=ev;
}
Event* IVTEntry::getEvent(){
	return event;
}

void IVTEntry::postaviNovuRutinu(int brojUlaza){
	lock1();
#ifndef BCC_BLOCK_IGNORE
	staraRutina=getvect(brojUlaza);
	setvect(brojUlaza,novaRutina);
#endif
	unlock1();
}

void IVTEntry::vratiStaruRutinu(int brojUlaza){
	lock1();
#ifndef BCC_BLOCK_IGNORE
	setvect(brojUlaza,staraRutina);
#endif
	unlock1();
}
