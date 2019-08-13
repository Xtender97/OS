/*
 * jezev.cpp
 *
 *  Created on: Jun 15, 2019
 *      Author: OS1
 */

#include "jezev.h"
#include "ivt.h"
#include "semaphor.h"
KernelEv::KernelEv(int brojUlaza, Event * ev){
	event=ev;
	brUlaza=brojUlaza;
	sem=new Semaphore(0);
	eventNit=(PCB*)Jezgro::running;
	Jezgro::IVTabela[brUlaza]->addEvent(event);
}
KernelEv::~KernelEv(){
	Jezgro::IVTabela[brUlaza]->addEvent(0);
	delete sem;
	delete eventNit;
}
void KernelEv::signal(){//mozda treba zakljucati
	if(sem->val()==1){
		return;
	}
	else{
		sem->signal(0);
	}
}
void KernelEv::wait(){//mozda treba zakljucati
	if (eventNit!=(PCB*)Jezgro::running){
		return;
	}
	else{
		sem->wait(0);
	}
}


