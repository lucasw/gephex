/* This source file is a part of the GePhex Project.

 Copyright (C) 2001-2004

 Georg Seidel <georg@gephex.org> 
 Martin Bayer <martin@gephex.org> 
 Phillip Promesberger <coma@gephex.org>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.*/

#ifndef INCLUDED_TIMER_H
#define INCLUDED_TIMER_H

class Timer
{
public:
	Timer();
	~Timer();
	void start();			//start timer-period
	void stop();			//stop timer-period
	void print();			//print fancy stats to console
	long get_avg_cycles();	//return avg. cycles per timer-period
	int get_runs();			//return numer of timer-periods
	double get_fps();		//avg. return runs per sec
	void reset();			//set back to zero
private:
	double getTime();
	double cycles;
	int runs;
	double start_cycles;
	double cpu_mhz;
};

#endif
