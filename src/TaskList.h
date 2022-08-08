/*
    TaskList.h
    Version 0.0.1
    Created 7.08.2022
    Author: MSZ98 (github.com/MSZ98)

    Copyright (C) 2022 MSZ98

    This file is part of the C Concurrent.h library.

    The TaskList.h library is free software; you can redistribute it and/or
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

/**
 * This is a custom list because Arduino AVR doesn't support standard cpp <list>.
 * It has a lot different iteration than std list, so be warned.
 * It can't be iterated at once from multiple threads.
 * It's going to be changed in some free time.
*/

#ifndef TASKLIST_H
#define TASKLIST_H

#include "Task.h"

class TaskList {
    
private:
    typedef struct {
        Task *task;
        void *next;
    } Node;
    Node *first = NULL, *iter = NULL;
    void *temp = NULL;
	int size = 0;
    
public:
    ~TaskList() {
	    removeall();
	}
	
	void add(Task *task) {
	    Node *n = new Node;
		n->task = task;
		n->next = NULL;
		if(first == NULL) first = n;
		else {
		    Node *last = first;
	        for(int i = 0;i < size-1;i++) last = (Node*) last->next;
		    last->next = n;
		}
		size++;
	}
	
	Task* get(int index) {
        if(index < 0 || index >= size) return NULL;
        Node *n = first;
        for(int i = 0;i < index;i++) n = (Node*) n->next;
        return n->task;
    }
    
    	Task* remove(int index) {
	    if(index < 0 || index >= size) return NULL;
        Node *n = first, *p = NULL;
        for(int i = 0;i < index;i++) {
            p = n;
            n = (Node*) n->next;
        }
        if(p == NULL) {
            if(n->next == NULL) first = NULL;
            else first = (Node*) n->next;
        }
        else p->next = n->next;
        if(iter == n) temp = n->next;
        Task *task = n->task;
        delete n;
		size--;
		return task;
	}
	
    Task* remove(Task *task) {
        if(first == NULL) return NULL;
        Node *n = first, *p = NULL;
        while(n->task != task) {
            p = n;
            n = (Node*) n->next;
        }
        if(p == NULL) {
            if(n->next == NULL) first = NULL;
            else first = (Node*) n->next;
        }
        else p->next = n->next;
        if(iter == n) temp = n->next;
        task = n->task;
        delete n;
		size--;
		return task;
	}
    
    int len() {return size;}
    
    void removeall() {
	    if(first == NULL) return;
	    Node *n = first;
	    do {
	        Node *t = n;
	        n = (Node*) n->next;
	        
	        delete t;
	        
	    } while(n != NULL);
	    first = NULL;
	    size = 0;
	}
	
	int indexof(Task *task) {
	    if(first == NULL) return -1;
        Node *n = first;
        int i = 0;
        while(n != NULL && n->task != task) {
            n = (Node*) n->next;
            i++;
        }
        return i == size ? -1 : i;
	}
    
    void begin() {
        iter = NULL;
    }
    
    Task* next() {
        if(temp != NULL) {
            iter = (Node*) temp;
            temp = NULL;
        }
        if(iter == NULL) iter = first;
        Task *task = iter->task;
        iter = (Node*) iter->next;
        return task;
    }
    
};

#endif /* TASKLIST_H */