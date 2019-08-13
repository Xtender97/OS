/*
 * main.cpp
 *
 *  Created on: Jun 14, 2019
 *      Author: OS1
 */

#include "jezgro.h"
#include "locks.h"
#include <iostream.h>
int userMain(int argc, char ** argv);

int main(int argc, char ** argv){
	lock2();
	cout<<"Jezgro se pokrece!"<<endl;
	unlock2();
	Jezgro::Inic();
	int rez=userMain(argc, argv);
	Jezgro::Restore();
	lock2();
	cout<<"Jezgro se gasi!"<<endl;
	unlock2();
	return rez;
}
