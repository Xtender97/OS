/*
 * thread.cpp
 *
 *  Created on: Jun 11, 2019
 *      Author: OS1
 */
#include "thread.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "jezgro.h"
#include <iostream.h>

Thread::Thread(StackSize stackSize, Time timeSlice){
	lock1();

	if(stackSize>65536){
		stackSize=65536;
	}

	stackSize/=sizeof(unsigned);

	myPCB=new PCB(this, stackSize, timeSlice);
	unlock1();


}


void Thread::start(){
	lock1();
	if (myPCB->stanje==PCB::NEW){
		myPCB->stanje=PCB::READY;
		myPCB->NewStack();
		Scheduler::put(myPCB);
	}
	unlock1();
}

void Thread::waitToComplete(){
	lock1();
	if (this->myPCB==Jezgro::running){
		//cout<<getId()<<" RUNNING ID NA KOJEM SE SPAVA";
		unlock1();
		return;
	}
	if (this->myPCB==Jezgro::idle->getIdlePCB()){
		unlock1();
		return;
	}
	if (this->myPCB->stanje==PCB::NEW){
		unlock1();
		return;
	}
	if (myPCB->stanje==PCB::DONE){
		unlock1();
		return;
	}
	Jezgro::running->stanje=PCB::BLOCKED;

	myPCB->blokiraneNiti->put((PCB*)Jezgro::running);
	lock2();
	cout<<this->getRunningId()<<" ceka da zavrsi "<<getId() <<endl;
	unlock2();
	dispatch();
	unlock1();



}

Thread::~Thread(){
	waitToComplete();
	delete myPCB;
}

ID Thread::getId(){
	if (this!=0){
		//cout<<Thread::myPCB->getIDPCB()<<endl;
		return Thread::myPCB->getIDPCB();
	}

	else return 100;
}

ID Thread::getRunningId(){
	PCB* trenutni=(PCB*)Jezgro::running;
	return trenutni->getIDPCB();
}

Thread * Thread::getThreadById(ID id){
	PCB* pom=PCB::allPCBs->get(id);
	if(pom==0){
		return 0;
	}else{
		return pom->nit;
	}
}

void dispatch(){
	lock2();
	//cout<<"dispatch pozvan\n";
	Jezgro::RequstedContextSwitch=1;
	Jezgro::Timer();
	unlock2();

}
