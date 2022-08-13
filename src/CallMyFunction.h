/*
    CallMyFunction.h
    Version 0.0.1
    Created 8.08.2022
    Author: MSZ98 (github.com/MSZ98)

    Copyright (C) 2022 MSZ98

    This file is part of the C Concurrent.h library.

    The CallMyFunction.h library is free software; you can redistribute it and/or
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

#ifndef CALLMYFUNCTION_H
#define CALLMYFUNCTION_H

#include <stdlib.h>
#include <stdio.h>
#include "TaskList.h"
#include "Task.h"

class Callf_t {
    
private:
    unsigned long (*timef)();
    TaskList tasks;
    
public:
    void begin(unsigned long (*timef)()) {
        this->timef = timef;
    }
    
    Task* every(void (*func)(), unsigned long period) {
        Task *task = new Task(func, period, timef(), -1, 0);
        if(task != NULL) tasks.add(task);
        return task;
    }
    
    Task* every(void (*func)(), unsigned long period, int n) {
        Task *task = new Task(func, period, timef(), n, 0);
        if(task != NULL) tasks.add(task);
        return task;
    }
    
    Task* four(void (*func)(), unsigned long period, unsigned long time) {
        Task *task = new Task(func, period, timef(), -1, time);
        if(task != NULL) tasks.add(task);
        return task;
    }
    
    Task* after(void (*func)(), unsigned long time) {
        Task *task = new Task(func, time, (long long) timef(), 1, 0);
        if(task != NULL) tasks.add(task);
        return task;
    }

    void loop() {
        tasks.begin();
        while(Task *t = tasks.next()) {
            int result = t->run(timef());
            if(result == 0) {
                tasks.remove(t);
                // delete t;
            }
        }
    }
    
    TaskList* getTaskList() {
        return &tasks;
    }

    int len() {
        return tasks.len();
    }
    
    bool done(Task *task) {
        bool found = false;
        tasks.begin();
        while(Task *t = tasks.next()) {
            if(t == task) {
                found = true;
                break;
            }
        }
        return !found;
    }
    
    void stop(Task *task) {
        Task *t = tasks.remove(task);
        if(t != NULL) delete task;
    }

};

static Callf_t Callf;

#endif /* CALLMYFUNCTION_H */
