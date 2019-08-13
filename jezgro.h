/*
 * jezgro.h
 *
 *  Created on: Jun 11, 2019
 *      Author: OS1
 */

#ifndef JEZGRO_H_
#define JEZGRO_H_
#include "idle.h"
#include "thread.h"
#include <dos.h>
#include "list.h"
#include "ivt.h"
class Jezgro{
public:

	static void interrupt (*StaraRutina)(...);
	static volatile PCB* running;
	static volatile int RequstedContextSwitch;
	static List* blokiraneNaSemaforu;
	static Thread* mainThread;
	static Idle* idle;
	static void Inic();
	static void Restore();
	static void interrupt Timer(...);		//mozda treba (...)
	static void umetniTimer();
	static void vratiTimer();
	static IVTEntry* IVTabela[256];
};

extern void tick();
#endif /* JEZGRO_H_ */
