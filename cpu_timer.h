/*
 * cpu_timer.h
 *
 *  Created on: Sep 12, 2015
 *      Author: richer
 */

#ifndef CPU_TIMER_H_
#define CPU_TIMER_H_
#include <stdint.h>
#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

class CPUTimer {
public:

	/**
	 * default constructor
	 */
	CPUTimer();

	/**
	 * start chrono and record clocks
	 */
	void start();

	/**
	 * stop chrono and record clocks
	 */
	void stop();

	/**
	 *
	 */
	ostream& print(ostream& out);

	friend ostream& operator<<(ostream& out, CPUTimer& c) {
		return c.print(out);
	}

private:

	double ts_start, ts_stop;
};


#endif /* CPU_TIMER_H_ */
