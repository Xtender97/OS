/*
 * event.cpp
 *
 *  Created on: Jun 15, 2019
 *      Author: OS1
 */


#include "event.h"
#include "ivt.h"
#include "jezgro.h"
#include "jezev.h"

	Event::Event (IVTNo ivtNo){
		myImpl=new KernelEv(ivtNo, this);
		//Jezgro::IVTabela[ivtNo]->addEvent(this); prebaci ovo u KernelEv i obrisi ga u kernel eventu
	}

	Event::~Event (){
		delete myImpl;
	}

 	void Event::wait (){
 		myImpl->wait();
 	}

 	void Event::signal(){
 		myImpl->signal();
 	}
