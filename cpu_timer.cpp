#include "cpu_timer.h"


CPUTimer::CPUTimer() {
	ts_start = ts_stop = 0.0;
}

void CPUTimer::start() {
	struct timespec ts;
		clock_gettime(CLOCK_REALTIME, &ts);
		ts_start = ts.tv_sec + 1e-9*ts.tv_nsec;
}

void CPUTimer::stop() {
	struct timespec ts;
		clock_gettime(CLOCK_REALTIME, &ts);
		ts_stop = ts.tv_sec + 1e-9*ts.tv_nsec;
}

ostream& CPUTimer::print(ostream& out) {
	// convert to milli seconds
	double diff = (ts_stop - ts_start) * 1000.0;
	out << fixed;
	out << diff;
	return out;
}


