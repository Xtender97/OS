/*
 * list.h
 *
 *  Created on: Jun 11, 2019
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_
#include "thread.h"
#include "PCB.h"
class PCB;
class Elem {
public:
	PCB * pcb;
	Elem* sled;
	Elem* pret;
	Elem(PCB* p){
		pcb=p;
		sled=0;
		pret=0;
	}
};
class List {
public:
	Elem* prvi;
	Elem* posl;
	int brojPCBova;
	List();
	~List();
	void put(PCB* pcb);
	void remove(ID pcbID);
	PCB* get(ID pcbID);
	Elem* getElem(ID pcbID);
	void odblokirajSVE();
	void povecajVremeSvimBlokiranim();
	PCB* getFirst();

};

#endif /* LIST_H_ */
