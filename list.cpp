/*
 * list.cpp
 *
 *  Created on: Jun 11, 2019
 *      Author: OS1
 */

#include "list.h"
#include "locks.h"
#include "SCHEDULE.H"
#include "jezsem.h"
#include <iostream.h>
List::List() {
	prvi = 0;
	posl = 0;
	brojPCBova = 0;
}
List::~List(){
	lock1();
	if (prvi!=0){
		Elem * tek=prvi;
		while(tek){
			Elem * pom=tek;
			tek=tek->sled;
			delete pom;
		}
	}
	unlock1();




	unlock1();
}
void List::put(PCB* pcb) {
	if(pcb!=0){
	lock1();
	//cout<<pcb->getIDPCB()<<" stavljen\n";
	Elem* novi = new Elem(pcb);
	if (prvi == 0) { // mozda dodaj i posl==0
		prvi = novi;
		posl = novi;
	} else {
		posl->sled = novi;
		novi->pret = posl;
		posl = novi;

	}

	brojPCBova++;
	unlock1();}
}
void List::remove(ID pcbID) {
	lock1();
	Elem* pom = 0;
	if (prvi != 0) {
		if (pcbID == prvi->pcb->getIDPCB()) {
			pom = prvi;
			prvi = prvi->sled;
			prvi->pret=0;

		} else {
			if (pcbID == posl->pcb->getIDPCB()) {
				pom=posl;
				posl=posl->pret;
				posl->sled=0;
			} else {

				pom = getElem(pcbID);
				if(pom==0) return;
				pom->pret->sled = pom->sled;
				pom->sled->pret = pom->pret;
			}
		}
		//delete pom;               ipak pazi da ne napravi problem
		brojPCBova--;

	}
	unlock1();
}
Elem* List::getElem(ID pcbID){
	lock1();
		Elem *tek = prvi;
		while (tek) {
			if (tek->pcb->getIDPCB() == pcbID) {
				unlock1();
				return tek;
			}
			tek = tek->sled;
		}
		unlock1();
		return 0;
}
PCB* List::get(ID pcbID) { //nadji gde se koristi i obezbedi sta se desava kada se vrati nula
	lock1();
	Elem *tek = prvi;
	while (tek) {
		if (tek->pcb->getIDPCB() == pcbID) {
			unlock1();
			return tek->pcb;
		}
		tek = tek->sled;
	}
	unlock1();
	return 0;
}
void List::odblokirajSVE() {
	lock1();
	Elem *tek = prvi;
	while (tek) {
		if (tek->pcb->stanje == PCB::BLOCKED) {
			tek->pcb->stanje = PCB::READY;
			Scheduler::put(tek->pcb);
		}
		tek = tek->sled;
	}
	unlock1();
}
void List::povecajVremeSvimBlokiranim(){
	lock1();
		if (prvi!=0){
			Elem *tek=prvi;
			while(tek){
				if (tek->pcb->stanje==PCB::BLOCKED){
					tek->pcb->blokirana++;
					if(tek->pcb->blokirana==tek->pcb->blokiranaNa->maxTime){
						tek->pcb->istekloVreme=1; //indikator da se nit odblokirala zato sto je isteklo vreme
						tek->pcb->stanje=PCB::READY;
						remove(tek->pcb->getIDPCB());//BAS PAZI NA OVOOOO ISTESTIRAJ DA LI RADI KAKO TREBA
						Scheduler::put(tek->pcb);
					}
				}
				tek=tek->sled;
			}
		}

	unlock1();
}
PCB* List::getFirst(){//dohvata prvi elemnt i uklanja ga iz liste
	if(prvi!=0){
		Elem * pom = prvi;
		prvi=prvi->sled;
		prvi->pret=0;
		brojPCBova--;
		return pom->pcb;
	}
	else return 0;



}
