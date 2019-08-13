/*
 * PDB.h
 *
 *  Created on: Jun 5, 2019
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_
#include "list.h"
#include "locks.h"
#include "thread.h"
#include <dos.h>
class List;
class Jezgro;
class KernelSem;
class PCB {
public:
	static ID globalID;
	static const int NEW,READY,BLOCKED,DONE;
	KernelSem* blokiranaNa;
	Time blokirana;
	unsigned istekloVreme;
	ID id;
	Thread* nit;// Mozda treba da bude private :D
	unsigned sp;
	unsigned bp; //dodaj ovo u timer
	unsigned ss;
	unsigned stanje;
	unsigned* stack;
	Time timeSlice; //koliko moze da radi bez prekida
	Time timeRunning; //koliko je radila
	StackSize stackSize;
	List* blokiraneNiti;

	PCB(Thread* nit, StackSize stackSize, Time timeSlice);
	~PCB();
	ID getIDPCB();
	void NewStack();
	static void wrapper();

private:
	static List* allPCBs;// lista svih napravljenih PCB-ova
	friend class Thread;
	friend class Jezgro;
};

#endif /* PCB_H_ */
