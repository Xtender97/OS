/*
 * event.h
 *
 *  Created on: Jun 15, 2019
 *      Author: OS1
 */

#ifndef _event_h_
#define _event_h_
typedef unsigned char IVTNo;
#include "ivt.h"
//priprema ulaz iv tabele i definise prekidnu rutinu koju treba pozvati umesto podrazumevane(implicitni poziv konstruktora)
#define PREPAREENTRY(brojUlaza, staraRutina)\
void interrupt prekidnaRutina##brojUlaza(...);\
IVTEntry ulaz##brojUlaza(brojUlaza, prekidnaRutina##brojUlaza);\
void interrupt prekidnaRutina##brojUlaza(...){\
	ulaz##brojUlaza.signal();\
	if(staraRutina) ulaz##brojUlaza.pozoviStaruRutinu();\
}\

class KernelEv;

class Event {
public:
	Event (IVTNo ivtNo);
 	~Event ();
 	void wait ();

protected:
 	friend class KernelEv;
 	friend class IVTEntry;
 	void signal(); // can call KernelEv

private:
 	KernelEv* myImpl;

};
#endif
