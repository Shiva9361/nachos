// scheduler.h
//	Data structures for the thread dispatcher and scheduler.
//	Primarily, the list of threads that are ready to run.
//
// Copyright (c) 1992-1996 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation
// of liability and disclaimer of warranty provisions.

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "copyright.h"
#include "list.h"
#include "thread.h"
#include <queue>
#include <vector>

// The following class defines the scheduler/dispatcher abstraction --
// the data structures and operations needed to keep track of which
// thread is running, and which threads are ready but not running.

class PriorityThread {
   public:
    bool operator()(Thread*& t1, Thread*& t2) {
        return t1->priority < t2->priority;
    }
};

class Scheduler {
   public:
    Scheduler();   // Initialize list of ready threads
    ~Scheduler();  // De-allocate ready list

    void ReadyToRun(Thread* thread);
    // Thread can be dispatched.
    Thread* FindNextToRun();  // Dequeue first thread on the ready
                              // list, if any, and return thread.
    void Run(Thread* nextThread, bool finishing);
    // Cause nextThread to start running
    void CheckToBeDestroyed();  // Check if thread that had been
                                // running needs to be deleted
    void Print();               // Print contents of ready list
    void waitUntil(int x);
    // SelfTest for scheduler is implemented in class Thread
    void checkSleepList();
    void checkWaitList(bool);
    void waitForProcess(int pid);

   private:
    List<Thread*>* readyList;  // queue of threads that are ready to run,
    priority_queue<Thread*, vector<Thread*>, PriorityThread> readyQueue;
    List<Thread*>* sleepList;  // but not running
    List<Thread*>* waitList;
    Thread* toBeDestroyed;  // finishing thread to be destroyed
                            // by the next thread that runs
};

#endif  // SCHEDULER_H
