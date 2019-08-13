/*
 * jezgro.cpp
 *
 *  Created on: Jun 11, 2019
 *      Author: OS1
 */
#include "jezgro.h"
#include "locks.h"
#include <dos.h>
#include "PCB.h"
#include "SCHEDULE.H"
#include <iostream.h>

volatile unsigned pomSS, pomSP, pomBP;
IVTEntry* Jezgro::IVTabela[256];//proveri ovo
void interrupt (*Jezgro::StaraRutina)(...)=0;
volatile PCB* Jezgro::running=0;
volatile int Jezgro::RequstedContextSwitch=0;
Thread* Jezgro::mainThread=0;
Idle* Jezgro::idle=0;
List * Jezgro::blokiraneNaSemaforu=0;


void Jezgro::Inic(){
	lock1();
	umetniTimer();
	mainThread=new Thread(4096,2);
	mainThread->myPCB->stanje=PCB::READY;
	running=mainThread->myPCB;
	blokiraneNaSemaforu=new List();
	idle=new Idle(defaultStackSize, defaultTimeSlice);
	idle->start();
	unlock1();
}
void Jezgro::umetniTimer(){
	lock1();
#ifndef BCC_BLOCK_IGNORE
	StaraRutina=getvect(0x08);
	setvect(0x08,Timer);
#endif
	unlock1();

}

void Jezgro::Restore(){
	lock1();
	if(running==mainThread->myPCB){
		vratiTimer();
		delete idle;
		delete mainThread;
		delete PCB::allPCBs;

	}
	unlock1();



}
void Jezgro::vratiTimer(){
	lock1();
#ifndef BCC_BLOCK_IGNORE
	setvect(0x08,StaraRutina);
#endif
	unlock1();
}

void interrupt Jezgro::Timer(...){
	asm cli;
	if(!RequstedContextSwitch){
		running->timeRunning++;
		StaraRutina();
		tick();
		blokiraneNaSemaforu->povecajVremeSvimBlokiranim();
	}
	if(running->timeRunning==running->timeSlice||RequstedContextSwitch){
		if (RequstedContextSwitch){
			//cout<<"RequstedContextSwitch"<<endl;
			//lock2();
		}
		else{
			running->timeRunning=0;
			//cout<<"Isteklo vreme"<<endl;
			//lock2();
		}
		asm{
			mov pomSS, ss
			mov pomSP, sp
			mov pomBP, bp
		}
		running->ss=pomSS;
		running->sp=pomSP;
		running->bp=pomBP;

		if (running->stanje==PCB::READY && running!=idle->myPCB){
			Scheduler::put((PCB*)running);
		}
		running=(volatile PCB*)Scheduler::get();
		while(running->stanje==PCB::BLOCKED){
			running=(volatile PCB*)Scheduler::get();
		}
		if(running==0){
			running=idle->myPCB;
		}
		//cout<<"izabrao sam: "<<running->getIDPCB()<<endl;
		//asm cli;
		pomSS=running->ss;
		pomSP=running->sp;
		pomBP=running->bp;

		asm {
			mov ss, pomSS
			mov sp, pomSP
			mov bp, pomBP
		}


	}
	RequstedContextSwitch=0;

	asm sti;
}































