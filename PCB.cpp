#include "PCB.h"
#include "jezgro.h"
#include <iostream.h>
const int PCB::NEW=1;
const int PCB::READY=2;
const int PCB::BLOCKED=3;
const int PCB::DONE=4;


ID PCB::globalID = 0;
List* PCB::allPCBs = new List();

PCB::PCB(Thread* nit, StackSize stackSize, Time timeSlice) {
	this->stackSize = stackSize;
	this->timeSlice = timeSlice;
	this->nit = nit;
	blokiraneNiti=new List();
	blokiranaNa=0;
	blokirana=0;//vrati na nulu posle gde treba nemoj da zaboravis konju glupi
	istekloVreme=0;
	stack = 0;
	timeRunning = 0;
	ss = 0;
	sp = 0;
	bp = 0;
	id = globalID++;//krece od nule
	stanje=NEW;
	allPCBs->put(this);

};

void PCB::NewStack() {
	lock1();
	stack=new unsigned[stackSize];

	stack[stackSize-1] =0x200;					//setovan I fleg u pocetnom PSW-u za nit
	#ifndef BCC_BLOCK_IGNORE
		stack[stackSize-2] = FP_SEG(&PCB::wrapper);
		stack[stackSize-3] = FP_OFF(&PCB::wrapper);
		sp = FP_OFF(stack+stackSize-12); 		//svi sacuvani registri pri ulasku u interrupt rutinu
		ss = FP_SEG(stack+stackSize-12);
	#endif
		bp=sp;
	unlock1();

};

PCB::~PCB(){
	lock1();
	allPCBs->remove(this->id);//BRISANJE IZ LISTE SVIH PCBOVA

	if (stack!=0)
	delete [] stack;
	if(blokiraneNiti!=0) delete blokiraneNiti;
	unlock1();

};


ID PCB::getIDPCB(){
	return this->id;
}
void PCB::wrapper()
{

	Jezgro::running->nit->run();
	lock1();
	Jezgro::running->stanje=DONE;
	Jezgro::running->blokiraneNiti->odblokirajSVE();

	dispatch();
	unlock1();
	//treba jos nesto sigurnoooooo
}










