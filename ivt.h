/*
 * ivt.h
 *
 *  Created on: Jun 15, 2019
 *      Author: OS1
 */

#ifndef HEADERS_IVT_H_
#define HEADERS_IVT_H_
#include "event.h"
typedef void interrupt (*IntRout)(...);

class Event;

class IVTEntry{
public:
	IVTEntry(int brojUlaza, IntRout novaRutina);
	~IVTEntry();
	void signal();
	void pozoviStaruRutinu();
	void addEvent(Event * ev);
	Event* getEvent();
	void postaviNovuRutinu(int brojUlaza);
	void vratiStaruRutinu(int brojUlaza);
private: //skolni ako smeta
	IntRout novaRutina;
	IntRout staraRutina;
	int brUlaza;
	Event *event;
};



#endif /* HEADERS_IVT_H_ */
