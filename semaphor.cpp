/*
 * semaphor.cpp
 *
 *  Created on: Jun 15, 2019
 *      Author: OS1
 */
#include "locks.h"
#include "semaphor.h"
#include "jezsem.h"
Semaphore::Semaphore(int init){
	myImpl=new KernelSem(this, init);
}

Semaphore:: ~Semaphore(){
	lock1();
		if (myImpl!=0) delete myImpl;
	unlock1();
}

int Semaphore::wait(Time maxTimeToWait){
	lock1();
		int i=myImpl->wait(maxTimeToWait);
	unlock1();
	return i;
}

int Semaphore:: signal(int n){
	lock1();
		int i=myImpl->signal(n);
	unlock1();
	return i;

}

int Semaphore:: val() const{
	return myImpl->getValue();
};

