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
#include "synch.h"

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

/*********for synch tests***********/

Semaphore *mutex = new Semaphore("mutex",1);   
Semaphore *full = new Semaphore("fillcount",0);
Semaphore *empty = new Semaphore("empty",5);
const int buffersize=5;
int in=0;
int out=0;

void producerSem(int arg) 
{
    while(arg--) {
        //produce an item
        empty->P();         //wait for an empty space
        mutex->P();        //wait for mutex
        //put item into buffer
        printf("%s puts an item into slot %d.\n",currentThread->getName(),in);
        in=(in+1)%buffersize;
        mutex->V();
        full->V();
    }
}

void consumerSem(int arg) 
{
    while(arg--) {
        full->P();
        mutex->P();
        //get an item from buffer
        printf("%s gets an item from slot %d.\n",currentThread->getName(),out);
        out=(out+1)%buffersize;
        mutex->V();
        empty->V();
        //consume this item
    }
}

void ThreadTestSem()
{
    Thread *producer1 = new Thread("Producer1");
    Thread *consumer1 = new Thread("Consumer1");
    Thread *producer2 = new Thread("Producer2");
    Thread *consumer2 = new Thread("Consumer2");
    producer1->Fork(producerSem,6);
    consumer1->Fork(consumerSem,8);
    consumer2->Fork(consumerSem,3);
    producer2->Fork(producerSem,6);
}

Condition *isFull = new Condition("Producer");
Condition *isEmpty = new Condition("Consumer");
Lock *pro_con = new Lock("pro_con");
int filled_slot = 0;

void producerCond(int arg) 
{
    while(arg--) {
        pro_con->Acquire();
        while(filled_slot == buffersize) {                //buffer is full
            printf("Buffer is full!\n");
            isEmpty->Wait(pro_con);
        }
        filled_slot++;
        printf("%s puts an item, ",currentThread->getName());
        printf("now %d items in buffer\n",filled_slot);
        isFull->Signal(pro_con);
        pro_con->Release();
        
    }
}
void consumerCond(int arg) 
{
    while(arg--) {
        pro_con->Acquire();
        while(filled_slot== 0) {                           //buffer is empty
            printf("Buffer is empty!\n");
            isFull->Wait(pro_con);
        }
        filled_slot--;
        printf("%s gets an item, ",currentThread->getName());
        printf("now %d items left\n",filled_slot);
        isEmpty->Signal(pro_con);
        pro_con->Release();
       
    }
}
void ThreadTestCond()
{
    Thread *producer1 = new Thread("Producer1");
    Thread *consumer1 = new Thread("Consumer1");
    Thread *producer2 = new Thread("Producer2");
    Thread *consumer2 = new Thread("Consumer2");
    producer1->Fork(producerCond,6);
    consumer1->Fork(consumerCond,8);
    consumer2->Fork(consumerCond,3);
    producer2->Fork(producerCond,6);
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
    case 4:
        //ThreadTestSem();
        ThreadTestCond();
        break;
    default:
	printf("No test specified.\n");
	break;
    }
}

