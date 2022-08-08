/*
    Task.h
    Version 0.0.1
    Created 8.08.2022
    Author: MSZ98 (github.com/MSZ98)

    Copyright (C) 2022 MSZ98

    This file is part of the C Concurrent.h library.

    The Concurrent.h library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.
    
    The Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU Lesser General Public License for more details.
    
    You should have received a copy of the GNU Lesser General Public
    License along with the GNU C Library; if not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TASK_H
#define TASK_H

class Task {

private:
    typedef void (*vfp)(); // void function pointer
    vfp func;
    long long period, last_run, time_limit;
    int n;
    
public:
    enum RETVAL {
        OK   = 2, // Function executed
        WAIT = 1, // Waiting for period to expire
        DONE = 0  // Done completely, delete from list
    };

    Task(vfp func, long long period, long long last_run, int n, long long time_limit) {
        this->func = func;
        this->period = period;
        this->last_run = last_run;
        this->n = n;
        this->time_limit = time_limit == 0 ? 0 : last_run + time_limit;
    }
    
    int run(long long time) {
        if(n == 0) return DONE;
        if(time_limit != 0 && time > time_limit) return DONE;
        long long dt = time - last_run;
        if(dt >= period) {
            last_run = time;
            func();
            if(n > 0) n--;
            return OK;
        }
        return WAIT;
    }
    
    vfp getFunc() {
        return func;
    }
    
};

#endif /* TASK_H */