// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "openfile.h"
#include "thread.h"
#include "directory.h"

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------
void 
getStringFromMem(int baseAddr, char *name)
{
    int value = -1;
    int size = 0;
    while(value != 0) {
        machine->ReadMem(baseAddr + size, 1,&value);
        size++;
    }
    name[--size] = '\0';
    int counter = 0;
    while(size--) {
    	    machine->ReadMem(baseAddr++,1,&value);
	    name[counter++] = (char)value;
    }
}

void threadExec(int arg)
{
    printf("In thread exec\n");
    currentThread->RestoreUserState();
    currentThread->space->RestoreState();
    machine->Run();
}

void threadFork(int arg)
{
    printf("In thread fork\n");
    currentThread->RestoreUserState();
    currentThread->space->RestoreState();
    machine->Run();
}
    
void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);

    if ((which == SyscallException) && (type == SC_Halt)) {
	DEBUG('a', "Shutdown, initiated by user program.\n");
   	interrupt->Halt();
    }else if((which == SyscallException) && (type == SC_Create)){
        int baseAddr = machine->ReadRegister(4);
        char name[FileNameMaxLen+1];
        getStringFromMem(baseAddr,name);
        bool create_res=fileSystem->Create(name,0);
        if(!create_res)
		printf("Create file failed.\n");
    }else if((which == SyscallException) && (type == SC_Open)){
       int baseAddr = machine->ReadRegister(4);
	char name[FileNameMaxLen+1];
       getStringFromMem(baseAddr,name);
       
	OpenFile* file = fileSystem->Open(name);
	OpenFileId fid = file->GetFileDescriptor();
       printf("OpenFileId is %d\n", fid);
       machine->WriteRegister(2,fid);

       //fileManager->Append(file->FileSector());
    }else if((which == SyscallException) && (type == SC_Close)){
       int fd = machine->ReadRegister(4);
	OpenFile* file = new OpenFile(fd);
	//fileManager->Remove(file->FileSector());
       delete file;
    }else if ((which == SyscallException) && (type == SC_Write)) {
	int fd = machine->ReadRegister(6);
	int size = machine->ReadRegister(5);
	int baseAddr = machine->ReadRegister(4);

	char* buffer = new char[size];
	int i = 0;
	while(i < size) {
		machine->ReadMem(baseAddr + i, 1,(int *)&buffer[i]);
		i++;
	}
       if (fd==ConsoleOutput){
            for(int i=0;i<size;i++)
                printf("%c",buffer[i]);
       }else{
	    OpenFile* file = new OpenFile(fd);
	    int realSize = file->Write(buffer,size);
	    if(realSize != size) {
		    printf("Only wrote %d bytes of size.\n",realSize,size);
	    }
        }
	delete buffer;
    } else if ((which == SyscallException) && (type == SC_Read)) {
	DEBUG('a', "Read a file.\n");
	int fd = machine->ReadRegister(6);
	int size = machine->ReadRegister(5);
	int baseAddr = machine->ReadRegister(4);
	char* buffer = new char[size];
       int realSize = 0;
       
       if (fd==ConsoleInput){
            for(int i=0;i<size;i++)
                scanf("%c",&buffer[i]);
            realSize = size;
       }else{
	    OpenFile* file = new OpenFile(fd);
	    realSize = file->Read(buffer,size);
    	    if(realSize != size) {
		printf("Exception: Only wrote %d bytes of size.\n",realSize,size);
	    }
       }
       int i = 0;
	while(i < size) {
		machine->WriteMem(baseAddr + i, 1,(int)buffer);
		i++;
	}
       printf("Read: %s\n",buffer);
       machine->WriteRegister(2, realSize);
	delete buffer;
    }else if ((which == SyscallException) && (type == SC_Exec)) {
       int baseAddr = machine->ReadRegister(4);
	char name[FileNameMaxLen+1];
       getStringFromMem(baseAddr,name);

       OpenFile *executable = fileSystem->Open(name);
       if (executable == NULL) {
            printf("Unable to open file %s\n", name);
            machine->WriteRegister(2, -1);
            return;
      }

       Thread * t = new Thread("ExecThread");
       
       AddrSpace * space = new AddrSpace(executable); 
       char *tempfile=new char[FileNameMaxLen+1];
       char tid[3];
       sprintf(tid,"%d",t->getTID());
       int filesize = (space ->getPageNum()) * PageSize ;
       strcpy(tempfile,name);
       strcat(tempfile,tid);
       //printf("name:%s\n",tempfile);
        space->CreateTempFile(executable, tempfile, filesize);

       t->space = space;
       t->space->setFileName(tempfile);
       t->InitUserReg();
       delete executable;
       machine->WriteRegister(2, t->getTID());
       t->Fork(threadExec,0);
    }else if ((which == SyscallException) && (type == SC_Fork)) {
        Thread * t = new Thread("ForkThread");
        AddrSpace *space = new AddrSpace(t->getTID(), currentThread->space);
        t->space = space;
        int forkFunc = (int) machine->ReadRegister(4);
        // Copy machine registers of current thread to new thread
        t->SaveUserState(); 
        t->SetUserRegister(PCReg, forkFunc);
        t->SetUserRegister(NextPCReg, forkFunc + 4);
        t->Fork(threadFork,0);
    }else if ((which == SyscallException) && (type == SC_Join)) {
        int tid = machine->ReadRegister(4);
        printf("Thread %s need to wait until Thread with tid %d finishes\n",currentThread->getName(),tid);
        currentThread->addToJoinTable(tid);
        IntStatus oldLevel = interrupt->SetLevel(IntOff);	// disable interrupts
        currentThread->Sleep();
        (void) interrupt->SetLevel(oldLevel);	// re-enable interrupts
    }else if ((which == SyscallException) && (type == SC_Yield)) {
        currentThread->Yield();
    }else if((which == SyscallException) && (type == SC_Exit)){
        int exitCode = machine->ReadRegister(4);
        printf("Thread %s exit with code %d\n",currentThread->getName(),exitCode);
        currentThread->Finish();
    }else if((which == SyscallException) && (type == SC_Print)){
        int arg = machine->ReadRegister(4);
        int choice = machine->ReadRegister(5);
        if(choice==0){
            printf("%d",arg);
        }else if(choice==1){
            printf("%c",char(arg));
        }else{
            int value = -1;
            char *content;
            int size = 0;
            while(value != 0) {
                machine->ReadMem(arg + size, 1,&value);
                size++;
            }
            content = new char[size];
            content[--size] = '\0';
            int counter = 0;
            while(size--) {
		    machine->ReadMem(arg++,1,&value);
		    content[counter++] = (char)value;
            }
            printf("%s",content);
        }
    }else if(which ==TLBMissException){
        (stats->numTLBMisses) ++;
        int address=machine->registers[BadVAddrReg];
        //machine->TLBSwapFIFO(address);
        machine->TLBSwapLRU(address);
        DEBUG('a',"%x missed in TLB.\n",address);
    }else if(which==PageFaultException){
        (stats->numPageFaults) ++;
        int address=machine->registers[BadVAddrReg];
        pageManager->loadPage(address);
    }else {
	printf("Unexpected user mode exception %d %d\n", which, type);
       ASSERT(FALSE);
    }
}
