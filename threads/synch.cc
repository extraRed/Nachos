// synch.cc 
//	Routines for synchronizing threads.  Three kinds of
//	synchronization routines are defined here: semaphores, locks 
//   	and condition variables (the implementation of the last two
//	are left to the reader).
//
// Any implementation of a synchronization routine needs some
// primitive atomic operation.  We assume Nachos is running on
// a uniprocessor, and thus atomicity can be provided by
// turning off interrupts.  While interrupts are disabled, no
// context switch can occur, and thus the current thread is guaranteed
// to hold the CPU throughout, until interrupts are reenabled.
//
// Because some of these routines might be called with interrupts
// already disabled (Semaphore::V for one), instead of turning
// on interrupts at the end of the atomic operation, we always simply
// re-set the interrupt state back to its original value (whether
// that be disabled or enabled).
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "synch.h"
#include "system.h"

//----------------------------------------------------------------------
// Semaphore::Semaphore
// 	Initialize a semaphore, so that it can be used for synchronization.
//
//	"debugName" is an arbitrary name, useful for debugging.
//	"initialValue" is the initial value of the semaphore.
//----------------------------------------------------------------------

Semaphore::Semaphore(char* debugName, int initialValue)
{
    name = debugName;
    value = initialValue;
    queue = new List;
}

//----------------------------------------------------------------------
// Semaphore::Semaphore
// 	De-allocate semaphore, when no longer needed.  Assume no one
//	is still waiting on the semaphore!
//----------------------------------------------------------------------

Semaphore::~Semaphore()
{
    delete queue;
}

//----------------------------------------------------------------------
// Semaphore::P
// 	Wait until semaphore value > 0, then decrement.  Checking the
//	value and decrementing must be done atomically, so we
//	need to disable interrupts before checking the value.
//
//	Note that Thread::Sleep assumes that interrupts are disabled
//	when it is called.
//----------------------------------------------------------------------

void
Semaphore::P()
{
    IntStatus oldLevel = interrupt->SetLevel(IntOff);	// disable interrupts
    
    while (value == 0) { 			// semaphore not available
        printf("%s go to sleep\n",currentThread->getName());
        queue->Append((void *)currentThread);	// so go to sleep
        currentThread->Sleep();
    } 
    value--; 					// semaphore available, 
						// consume its value
    
    (void) interrupt->SetLevel(oldLevel);	// re-enable interrupts
}

//----------------------------------------------------------------------
// Semaphore::V
// 	Increment semaphore value, waking up a waiter if necessary.
//	As with P(), this operation must be atomic, so we need to disable
//	interrupts.  Scheduler::ReadyToRun() assumes that threads
//	are disabled when it is called.
//----------------------------------------------------------------------

void
Semaphore::V()
{
    Thread *thread;
    IntStatus oldLevel = interrupt->SetLevel(IntOff);

    thread = (Thread *)queue->Remove();     // disable interrupts
    if (thread != NULL)	                            // make thread ready, consuming the V immediately
	scheduler->ReadyToRun(thread);
    value++;
    (void) interrupt->SetLevel(oldLevel);       // re-enable interrupts
}

// Dummy functions -- so we can compile our later assignments 
// Note -- without a correct implementation of Condition::Wait(), 
// the test case in the network assignment won't work!
//by LMX
Lock::Lock(char* debugName) 
{
    name=debugName;
    lock=new Semaphore(debugName,1);
    owner=NULL;
}
Lock::~Lock() 
{
    delete lock;
}
void 
Lock::Acquire() 
{
    IntStatus oldLevel = interrupt->SetLevel(IntOff);	// disable interrupts
    lock->P();
    owner=currentThread;
    (void) interrupt->SetLevel(oldLevel);                       // re-enable interrupts
}
void 
Lock::Release() 
{
    IntStatus oldLevel = interrupt->SetLevel(IntOff);	// disable interrupts
    //ASSERT(isHeldByCurrentThread());                           // the lock must be held by the current thread
    lock->V();
    owner=NULL;
    (void) interrupt->SetLevel(oldLevel);                       // re-enable interrupts
}
bool 
Lock::isHeldByCurrentThread()
{
    return this->owner==currentThread;
}


Condition::Condition(char* debugName) 
{
    name=debugName;
    queue=new List;
}
Condition::~Condition() 
{
    delete queue;
}
void 
Condition::Wait(Lock* conditionLock) 
{ 
    //ASSERT(FALSE); 
    IntStatus oldLevel = interrupt->SetLevel(IntOff);	// disable interrupts
    ASSERT(conditionLock->isHeldByCurrentThread());
    conditionLock->Release();                                       //release the lock
    queue->Append((void*)currentThread);                    //append into the waiting queue
    printf("%s go to sleep\n",currentThread->getName());
    currentThread->Sleep();                                         
    conditionLock->Acquire();                                       //when signaled, acquire the lock
    (void) interrupt->SetLevel(oldLevel);                       // re-enable interrupts
}
void 
Condition::Signal(Lock* conditionLock) 
{
    Thread* nextThread;
    IntStatus oldLevel = interrupt->SetLevel(IntOff);	// disable interrupts
    ASSERT(conditionLock->isHeldByCurrentThread());
    if(!queue->IsEmpty()){
        nextThread=(Thread*)queue->Remove();
        printf("%s wakes up\n",nextThread->getName());
        scheduler->ReadyToRun(nextThread);                  //signal a thread in the waiting queue to ready status
    }
    (void) interrupt->SetLevel(oldLevel);                       // re-enable interrupts
}
void 
Condition::Broadcast(Lock* conditionLock) 
{
    Thread* nextThread;
    IntStatus oldLevel = interrupt->SetLevel(IntOff);	// disable interrupts
    ASSERT(conditionLock->isHeldByCurrentThread());
    while(!queue->IsEmpty()){
        nextThread=(Thread*)queue->Remove();
        scheduler->ReadyToRun(nextThread);                  //signal all threads in the waiting queue to ready status
    }
    (void) interrupt->SetLevel(oldLevel);                       // re-enable interrupts
}

Barrier::Barrier(char * debugName, int n)
{
    name=debugName;
    brokensize=n;
    barrier_cv=new Condition(name);
    barrier_lock=new Lock(name);
}
Barrier::~ Barrier()
{
    delete barrier_cv;
    delete barrier_lock;
}
void
Barrier::Wait()
{
    barrier_lock->Acquire();
    arrived++;
    if(arrived==brokensize){
        barrier_cv->Broadcast(barrier_lock);
        arrived=0;
    }
    else{
        barrier_cv->Wait(barrier_lock);
    }
    barrier_lock->Release();
}

Read_Write_Lock::Read_Write_Lock(char* debugName)
{
    name=debugName;
    mutex=new Lock("mutex");
    writing=new Lock(name);
    reader=0;
}
Read_Write_Lock::~Read_Write_Lock()
{
    delete mutex;
    delete writing;
}
void
Read_Write_Lock::Read_Acquire()
{
    mutex->Acquire();
    reader++;
    printf("%s arrived, %d readers now\n",currentThread->getName(),reader);
    if(reader==1){
        writing->Acquire();
    }
    mutex->Release();
}
void
Read_Write_Lock::Read_Release()
{
    mutex->Acquire();
    reader--;
    printf("%s left, %d readers now\n",currentThread->getName(),reader);
    if(reader==0){
        writing->Release();
    }
    mutex->Release();
}
void
Read_Write_Lock::Write_Acquire()
{
    printf("%s arrived\n",currentThread->getName());
    writing->Acquire();
}
void
Read_Write_Lock::Write_Release()
{
    printf("%s left\n",currentThread->getName());
    writing->Release();
}