/*
 * idle.h
 *
 *  Created on: Jun 14, 2019
 *      Author: OS1
 */

#ifndef HEADERS_IDLE_H_
#define HEADERS_IDLE_H_

#include "thread.h"
class Idle:public Thread{          //mozda treba dodati done kao kod Vasketa
public:
	Idle(StackSize s, Time t);
	void start();
	virtual void run();
	PCB * getIdlePCB();
};


#endif /* HEADERS_IDLE_H_ */
