/*
 * locks.h
 *
 *  Created on: Jun 11, 2019
 *      Author: OS1
 */

#ifndef HEADERS_LOCKS_H_
#define HEADERS_LOCKS_H_

#define lock1() asm pushf;\
		asm cli;
#define unlock1() asm popf;
#define lock2() asm cli;
#define unlock2() asm sti;



#endif /* HEADERS_LOCKS_H_ */
