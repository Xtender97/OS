/*
 * idle.cpp
 *
 *  Created on: Jun 14, 2019
 *      Author: OS1
 */


#include "idle.h"
#include "locks.h"
#include "PCB.h"
#include <iostream.h>
Idle::Idle(StackSize s, Time t) : Thread(s,t){}

void Idle::run(){
	while(1){
		//cout<<"idlee\n";
	}
}
void Idle::start(){
	lock1();
//mozda trebqa dodati uslov ==NEW
	myPCB->stanje=PCB::READY;
	myPCB->NewStack();
	unlock1();
}
PCB* Idle::getIdlePCB(){
	return myPCB;
}
