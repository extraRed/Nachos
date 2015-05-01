// progtest.cc 
//	Test routines for demonstrating that Nachos can load
//	a user program and execute it.  
//
//	Also, routines for testing the Console hardware device.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "console.h"
#include "addrspace.h"
#include "synch.h"
#include "synchConsole.h"

void Test(int which)
{
    printf("Enter New Thread\n"); 
    currentThread->RestoreUserState();
    currentThread->space->RestoreState();
    machine->Run();
}


//----------------------------------------------------------------------
// StartProcess
// 	Run a user program.  Open the executable, load it into
//	memory, and jump to it.
//----------------------------------------------------------------------

void
StartProcess(char *filename)
{
    OpenFile *executable = fileSystem->Open(filename);
    AddrSpace *space;

    if (executable == NULL) {
	printf("Unable to open file %s\n", filename);
	return;
    }
    space = new AddrSpace(executable);    

    char *tempfile=new char[50];
    char *tid=new char[10];
    sprintf(tid,"%d",currentThread->getTID());
    int filesize = (space ->getPageNum()) * PageSize ;
    strcpy(tempfile,filename);
    strcat(tempfile,tid);
    //printf("name:%s\n",tempfile);
    space->CreateTempFile(executable, tempfile, filesize);

    currentThread->space = space;
    currentThread->space->setFileName(tempfile);
  
    delete executable;			// close file

    space->InitRegisters();		// set the initial register values
    space->RestoreState();		// load page table register
    
    OpenFile *executable2 = fileSystem->Open("../test/sort");
    AddrSpace *space2;

    if (executable2 == NULL) {
	printf("Unable to open file\n");
	return;
    }
    space2 = new AddrSpace(executable2);  
    Thread *thread = new Thread("New Thread");

    char *tempfile2=new char[50];
    char *tid2=new char[10];
    sprintf(tid2,"%d",thread->getTID());
    int filesize2 = (space2->getPageNum()) * PageSize ;
    strcpy(tempfile2,"../test/sort");
    strcat(tempfile2,tid2);
    //printf("name:%s\n",tempfile);
    space2->CreateTempFile(executable2, tempfile2, filesize2);
    
    thread->space = space2;
    thread->space->setFileName(tempfile2);
    thread->InitUserReg();
    thread->Fork(Test, 0);
    delete executable2;			// close file
    
    machine->Run();			// jump to the user progam
    ASSERT(FALSE);			// machine->Run never returns;
					// the address space exits
					// by doing the syscall "exit"
}

// Data structures needed for the console test.  Threads making
// I/O requests wait on a Semaphore to delay until the I/O completes.

static Console *console;
static Semaphore *readAvail;
static Semaphore *writeDone;

//----------------------------------------------------------------------
// ConsoleInterruptHandlers
// 	Wake up the thread that requested the I/O.
//----------------------------------------------------------------------

static void ReadAvail(int arg) { readAvail->V(); }
static void WriteDone(int arg) { writeDone->V(); }

//----------------------------------------------------------------------
// ConsoleTest
// 	Test the console by echoing characters typed at the input onto
//	the output.  Stop when the user types a 'q'.
//----------------------------------------------------------------------

void 
ConsoleTest (char *in, char *out)
{
    char ch;
/*
    console = new Console(in, out, ReadAvail, WriteDone, 0);
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    
    for (;;) {
	readAvail->P();		// wait for character to arrive
	ch = console->GetChar();
	console->PutChar(ch);	// echo it!
	writeDone->P() ;        // wait for write to finish
	if (ch == 'q') return;  // if q, quit
    }
*/
    SynchConsole *synchConsole = new SynchConsole(in,out);
    for(;;){
        ch = synchConsole->GetChar();
        synchConsole->PutChar(ch);
        if(ch == 'q') return;
    }
}
