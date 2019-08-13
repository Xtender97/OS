/*
 * jezsem.cpp
 *
 *  Created on: Jun 15, 2019
 *      Author: OS1
 */
#include "jezsem.h"
#include "list.h"
#include "PCB.h"
#include "SCHEDULE.H"
KernelSem::KernelSem(Semaphore * s, int val) {
	blokiraneNiti = new List();
	value = val;
	sem = s;
	maxTime = 0; //pazi na ovo mozda pravi problem
}
KernelSem::~KernelSem() {
	if (blokiraneNiti != 0) {
		delete blokiraneNiti;
	}
}

int KernelSem::getValue() {
	return value;
}
int KernelSem::wait(Time maxTime) { // ako je value veca od nule pusti odmah// to nisam uradio
	lock1();
	if (value > 0) {//ako je vrednost veca od 0 ne blokiraj se
		--value;
		unlock1();
		return 1;
	} else {//ako je 0 ili manja od nule, zablokiraj se
		this->maxTime = maxTime;
		--value;
		Jezgro::running->stanje = PCB::BLOCKED;
		blokiraneNiti->put((PCB*) Jezgro::running);
		Jezgro::running->blokiranaNa = this;
		Jezgro::blokiraneNaSemaforu->put((PCB*) Jezgro::running);
		dispatch();
		Jezgro::running->blokirana = 0;
		Jezgro::running->blokiranaNa = 0;

		if (Jezgro::running->istekloVreme) {
			blokiraneNiti->remove(Jezgro::running->id); //pazi na ovaj id mozda je nesto sjebano
			Jezgro::running->istekloVreme = 0;
			unlock1();
			return 0;

		} else {
			unlock1();
			return 1;
		}
	}
}
int KernelSem::signal(int n) {
	lock1();
	if (n < 0) {
		unlock1();
		return n;
	}
	if (n == 0) {
		value++;
		if (blokiraneNiti->brojPCBova != 0) {
			PCB* pom = blokiraneNiti->getFirst();
			pom->stanje = PCB::READY;
			Scheduler::put(pom);

		}
		unlock1();
		return 0;
	}
	if (n > 0) {
		value += n;
		if (n > blokiraneNiti->brojPCBova) { // ako je broj veci od broja niti odblokiraj sve niti
			while (blokiraneNiti->brojPCBova) {
				PCB* pom = blokiraneNiti->getFirst();
				pom->stanje = PCB::READY;
				Scheduler::put(pom);
			}
		} else { // ako nije odblokiraj n niti
			int i = n;
			while (i) {
				PCB* pom = blokiraneNiti->getFirst();
				pom->stanje = PCB::READY;
				Scheduler::put(pom);
				i--;
			}
		}
		unlock1();
		return n;
	}
	return 0;//pripazi na ovo i prepravi u vise if else struktura

}

