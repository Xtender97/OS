/*
 * jezsem.h
 *
 *  Created on: Jun 15, 2019
 *      Author: OS1
 */

#ifndef HEADERS_JEZSEM_H_
#define HEADERS_JEZSEM_H_

#include "list.h"
#include "jezgro.h"
class Semaphore;
class KernelSem{
public:
	List* blokiraneNiti;
	int value;
	Semaphore * sem;
	Time maxTime;
	KernelSem(Semaphore* s,int val);
	~KernelSem();
	int getValue();
	int wait(Time maxTime);
	int signal(int n);

};


#endif /* HEADERS_JEZSEM_H_ */
