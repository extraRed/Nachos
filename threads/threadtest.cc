// threadtest.cc 
//	Simple test case for the threads assignment.
//
//	Create two threads, and have them context switch
//	back and forth between themselves by calling Thread::Yield, 
//	to illustratethe inner workings of the thread system.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"

// testnum is set in main.cc
int testnum = 1;

//----------------------------------------------------------------------
// SimpleThread
// 	Loop 5 times, yielding the CPU to another ready thread 
//	each iteration.
//
//	"which" is simply a number identifying the thread, for debugging
//	purposes.
//----------------------------------------------------------------------

void
SimpleThread(int which)
{
    int num;
    
    for (num = 0; num < 5; num++) {
        printf("*** thread %s with threadid %d and priority %d looped %d times\n", 
        currentThread->getName(), which, currentThread->getPriority(), num);
//        currentThread->performTick();
        /*if(which==3 && num==2){
            Thread *temp = new Thread("forked temp");
            temp->setPriority(2);
            temp->Fork(SimpleThread, temp->getTID());
        }*/
                currentThread->Yield();

    }
}

//----------------------------------------------------------------------
// ThreadTest1
// 	Set up a ping-pong between two threads, by forking a thread 
//	to call SimpleThread, and then calling SimpleThread ourselves.
//----------------------------------------------------------------------

void
ThreadTest1()
{
    DEBUG('t', "Entering ThreadTest1");
    /*for(int i=1;i<5;i++){
        Thread *t=new Thread("forked");
        t->Fork(SimpleThread,t->getTID());
    }*/
    
    Thread *t1 = new Thread("forked1");
    Thread *t2 = new Thread("forked2"); 
    Thread *t3 = new Thread("forked3");   
   // Thread *t4 = new Thread("forked4");   
    //Thread *t5 = new Thread("forked5");   

    //t1->setPriority(5);
    //t2->setPriority(4);
    //t3->setPriority(3);
    
    t1->Fork(SimpleThread, t1->getTID());
    t2->Fork(SimpleThread, t2->getTID());
    t3->Fork(SimpleThread, t3->getTID());
    //t4->Fork(SimpleThread, t4->getTID());
    //t5->Fork(SimpleThread, t5->getTID());
    
    //scheduler->Print();
    //printf("\n");
    //SimpleThread(0);
    
}

//by LMX
void ThreadDoNothing(int TID)
{
}

//by LMX
void
ThreadTestTS()
{
    DEBUG('t', "Entering ThreadTest1");
    
    Thread *t1 = new Thread("forked thread1");
    Thread *t2 = new Thread("forked thread2");
    Thread *t3 = new Thread("forked thread3");
    Thread *t4 = new Thread("forked thread4"); 
    
    t1->Fork(ThreadDoNothing, t1->getTID());
    t2->Fork(ThreadDoNothing, t2->getTID());
    t3->Fork(ThreadDoNothing, t3->getTID());
    t4->Fork(ThreadDoNothing, t4->getTID());

    ThreadShow();
    ThreadDoNothing(0);
}
//by LMX
//----------------------------------------------------------------------
// ThreadTestMax
// 	Create more threads than Nachos allowed to see what happens
//----------------------------------------------------------------------
void ThreadTestMax()
{
    for(int i=0;i<MaxThreads;i++){
        Thread *t = new Thread("test max threads");
        //printf("current TID is: %d\n", t->getTID());
        t->Fork(ThreadDoNothing, t->getTID());
        
    }
}

//----------------------------------------------------------------------
// ThreadTest
// 	Invoke a test routine.
//----------------------------------------------------------------------

void
ThreadTest()
{
    switch (testnum) {
    case 1:
	ThreadTest1();
	break;
    case 2:
       ThreadTestMax();
       break;
    case 3:
        ThreadTestTS();
        break;
    default:
	printf("No test specified.\n");
	break;
    }
}

