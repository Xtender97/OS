/*
 * jezev.h
 *
 *  Created on: Jun 15, 2019
 *      Author: OS1
 */

#ifndef HEADERS_JEZEV_H_
#define HEADERS_JEZEV_H_
#include "event.h"
#include "jezgro.h"
class Semaphore;

class KernelEv{
public:
	KernelEv(int brojUlaza, Event * ev);
	~KernelEv();//obrisi ulaz u tabeli
	void signal();
	void wait();

private:
	int brUlaza;
	Event * event;
	PCB* eventNit;
	Semaphore* sem;
};



#endif /* HEADERS_JEZEV_H_ */
