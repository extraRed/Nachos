// addrspace.cc 
//	Routines to manage address spaces (executing user programs).
//
//	In order to run a user program, you must:
//
//	1. link with the -N -T 0 option 
//	2. run coff2noff to convert the object file to Nachos format
//		(Nachos object code format is essentially just a simpler
//		version of the UNIX executable object code format)
//	3. load the NOFF file into the Nachos file system
//		(if you haven't implemented the file system yet, you
//		don't need to do this last step)
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "addrspace.h"
#include "noff.h"
#ifdef HOST_SPARC
#include <strings.h>
#endif

//----------------------------------------------------------------------
// SwapHeader
// 	Do little endian to big endian conversion on the bytes in the 
//	object file header, in case the file was generated on a little
//	endian machine, and we're now running on a big endian machine.
//----------------------------------------------------------------------

static void 
SwapHeader (NoffHeader *noffH)
{
	noffH->noffMagic = WordToHost(noffH->noffMagic);
	noffH->code.size = WordToHost(noffH->code.size);
	noffH->code.virtualAddr = WordToHost(noffH->code.virtualAddr);
	noffH->code.inFileAddr = WordToHost(noffH->code.inFileAddr);
	noffH->initData.size = WordToHost(noffH->initData.size);
	noffH->initData.virtualAddr = WordToHost(noffH->initData.virtualAddr);
	noffH->initData.inFileAddr = WordToHost(noffH->initData.inFileAddr);
	noffH->uninitData.size = WordToHost(noffH->uninitData.size);
	noffH->uninitData.virtualAddr = WordToHost(noffH->uninitData.virtualAddr);
	noffH->uninitData.inFileAddr = WordToHost(noffH->uninitData.inFileAddr);
}

//----------------------------------------------------------------------
// AddrSpace::AddrSpace
// 	Create an address space to run a user program.
//	Load the program from a file "executable", and set everything
//	up so that we can start executing user instructions.
//
//	Assumes that the object code file is in NOFF format.
//
//	First, set up the translation from program memory to physical 
//	memory.  For now, this is really simple (1:1), since we are
//	only uniprogramming, and we have a single unsegmented page table
//
//	"executable" is the file containing the object code to load into memory
//----------------------------------------------------------------------

AddrSpace::AddrSpace(OpenFile *executable)
{
    NoffHeader noffH;
    unsigned int i, size;

    executable->ReadAt((char *)&noffH, sizeof(noffH), 0);
    if ((noffH.noffMagic != NOFFMAGIC) && 
		(WordToHost(noffH.noffMagic) == NOFFMAGIC))
    	SwapHeader(&noffH);
    ASSERT(noffH.noffMagic == NOFFMAGIC);

// how big is address space?
    size = noffH.code.size + noffH.initData.size + noffH.uninitData.size 
			+ UserStackSize;	// we need to increase the size
						// to leave room for the stack
    numPages = divRoundUp(size, PageSize);
    size = numPages * PageSize;
    //ASSERT(numPages <= NumPhysPages);		// check we're not trying
						// to run anything too big --
						// at least until we have
						// virtual memory
						
    //We use fixed allocation strategy, now each thread can have up to 8 physical pages
    availNumPages = NumPhysPages/4;
    DEBUG('a', "Initializing address space, num pages %d, size %d\n", 
					numPages, size);
// first, set up the translation 
    pageTable = new TranslationEntry[numPages];
    for (i = 0; i < numPages; i++) {
	pageTable[i].virtualPage = i;	// for now, virtual page # = phys page #
	//pageTable[i].physicalPage = i;
	pageTable[i].physicalPage = -1;
	//by LMX
	/*
	int phynum = pageManager->findPage();
       ASSERT(phynum>=0 && phynum<NumPhysPages);
       pageManager->markPage(phynum);
	pageTable[i].physicalPage = phynum;
       printf("vpn:%d goes to ppn:%d allocated\n",i,phynum);
       */
       
       //We use lazy-loading now!,so no page is valid!
	//pageTable[i].valid = TRUE;
       pageTable[i].valid = FALSE;
       pageTable[i].use = FALSE;
	pageTable[i].dirty = FALSE;
	pageTable[i].readOnly = FALSE;  // if the code segment was entirely on 
					// a separate page, we could set its 
					// pages to be read-only
	 pageTable[i].lastAccessTime = 0;
    }
    //printf("%d physical pages left\n",pageManager->numClean());
    
// zero out the entire address space, to zero the unitialized data segment 
// and the stack segment
    //bzero(machine->mainMemory, size);
    /*
    for(i=0; i<numPages; i++){
		bzero( &(machine->mainMemory[pageTable[i].physicalPage * PageSize]), PageSize );
    }
    */
// then, copy in the code and data segments into memory
    /*
    if (noffH.code.size > 0) {
        DEBUG('a', "Initializing code segment, at 0x%x, size %d\n", 
			noffH.code.virtualAddr, noffH.code.size);
        executable->ReadAt(&(machine->mainMemory[noffH.code.virtualAddr]),
			noffH.code.size, noffH.code.inFileAddr);
    }
    if (noffH.initData.size > 0) {
        DEBUG('a', "Initializing data segment, at 0x%x, size %d\n", 
			noffH.initData.virtualAddr, noffH.initData.size);
        executable->ReadAt(&(machine->mainMemory[noffH.initData.virtualAddr]),
			noffH.initData.size, noffH.initData.inFileAddr);
    }
    */
    //by LMX
    /*
    int vpos;

    if (noffH.code.size > 0) {
        DEBUG('a', "Initializing code segment, at 0x%x, size %d\n", noffH.code.virtualAddr, noffH.code.size);
        vpos = noffH.code.virtualAddr;
        for(int i = 0;i < noffH.code.size;i++){
            executable->ReadAt(&(machine->mainMemory[AddrTrans(vpos)]), 1, noffH.code.inFileAddr + (vpos - noffH.code.virtualAddr));
            vpos++;
        }
    }
    if (noffH.initData.size > 0) {
        DEBUG('a', "Initializing code segment, at 0x%x, size %d\n", noffH.initData.virtualAddr, noffH.initData.size);
        vpos = noffH.initData.virtualAddr;
        while(vpos < (noffH.initData.size + noffH.initData.virtualAddr) ){
            executable->ReadAt(&(machine->mainMemory[AddrTrans(vpos)]), 1, noffH.initData.inFileAddr + (vpos - noffH.initData.virtualAddr));
            vpos++;
        }
    }
    */
}

AddrSpace::AddrSpace(int _tid, void* _fatherSpace){
    AddrSpace* fatherSpace =(AddrSpace*) _fatherSpace;
    numPages = fatherSpace->numPages;
    pageTable = new TranslationEntry[numPages];                    
    availNumPages = NumPhysPages/4;
    for (int i = 0; i < numPages; i++) {
        pageTable[i].virtualPage = i;   
        pageTable[i].physicalPage = -1; 
        pageTable[i].valid = FALSE;    
        pageTable[i].use = FALSE;            
        pageTable[i].dirty = FALSE;
        pageTable[i].readOnly = FALSE; 
        pageTable[i].lastAccessTime = 0;
    }

    filename=new char[10];//[FileNameMaxLen+1];
    char tid[3];
    sprintf(tid,"%d",_tid);    
    strcpy(filename,fatherSpace->filename);
    strcat(filename,"_");
    strcat(filename,tid);
    
    printf("forked filename: %s\n",filename);
    //Create the swap file and copy it from its father
    fileSystem->Create(filename, numPages * PageSize);
    fileSystem->Copy(fatherSpace->filename, filename, numPages * PageSize);

    OpenFile * fileHandler = fileSystem->Open(filename);
    //write back dirty pages of the father
    for (int vpn = 0; vpn < numPages; vpn++){
        if (fatherSpace->pageTable[vpn].dirty==TRUE){
            int fatherppn = fatherSpace->pageTable[vpn].physicalPage;
            fileHandler->WriteAt(&(machine->mainMemory[fatherppn * PageSize]), PageSize, vpn * PageSize);
        }
    }
    delete fileHandler;
}
//----------------------------------------------------------------------
// AddrSpace::~AddrSpace
// 	Dealloate an address space.  Nothing for now!
//----------------------------------------------------------------------

AddrSpace::~AddrSpace()
{
   //by LMX
   //fileSystem->Remove(filename);
   for(int i = 0;i < numPages;i++)
        if(pageTable[i].valid==TRUE)
            pageManager->cleanPage(pageTable[i].physicalPage);
   delete pageTable;
}

//----------------------------------------------------------------------
// AddrSpace::InitRegisters
// 	Set the initial values for the user-level register set.
//
// 	We write these directly into the "machine" registers, so
//	that we can immediately jump to user code.  Note that these
//	will be saved/restored into the currentThread->userRegisters
//	when this thread is context switched out.
//----------------------------------------------------------------------

void
AddrSpace::InitRegisters()
{
    int i;

    for (i = 0; i < NumTotalRegs; i++)
	machine->WriteRegister(i, 0);

    // Initial program counter -- must be location of "Start"
    machine->WriteRegister(PCReg, 0);	

    // Need to also tell MIPS where next instruction is, because
    // of branch delay possibility
    machine->WriteRegister(NextPCReg, 4);

   // Set the stack register to the end of the address space, where we
   // allocated the stack; but subtract off a bit, to make sure we don't
   // accidentally reference off the end!
    machine->WriteRegister(StackReg, numPages * PageSize - 16);
    DEBUG('a', "Initializing stack register to %d\n", numPages * PageSize - 16);
}

//----------------------------------------------------------------------
// AddrSpace::SaveState
// 	On a context switch, save any machine state, specific
//	to this address space, that needs saving.
//
//	For now, nothing!
//----------------------------------------------------------------------

void 
AddrSpace::SaveState() 
{
    //pageTable = machine->pageTable;
    //numPages = machine->pageTableSize;
}

//----------------------------------------------------------------------
// AddrSpace::RestoreState
// 	On a context switch, restore the machine state so that
//	this address space can run.
//
//      For now, tell the machine where to find the page table.
//----------------------------------------------------------------------

void 
AddrSpace::RestoreState() 
{
    //printf("Change Pagetable to %s\n", currentThread->getName());
    machine->pageTable = pageTable;
    machine->pageTableSize = numPages;
    if(machine->tlb!=NULL){
        for (int i = 0; i < TLBSize; i++)
	    machine->tlb[i].valid = FALSE;
    }
}


int 
AddrSpace::AddrTrans ( int virtAddr)
{
	return pageTable[virtAddr/PageSize].physicalPage * PageSize + (virtAddr %PageSize);
}

int 
AddrSpace::getStackReg()
{
    return machine->registers[StackReg];
}

//Write the Executable file into a file, so we can load them when we meet a pagefault
char Buffer[0x10000];  //create a large buffer

void 
AddrSpace::CreateTempFile(OpenFile *executable, char *tempfile, int filesize)
{
    NoffHeader noffH;
    executable -> ReadAt((char *)&noffH, sizeof(noffH), 0);
    if ((noffH.noffMagic != NOFFMAGIC) && (WordToHost(noffH.noffMagic) == NOFFMAGIC))
    	SwapHeader(&noffH);
    ASSERT(noffH.noffMagic == NOFFMAGIC);
    //read the original executable file to the buffer
    memset(Buffer, 0, sizeof(Buffer));
    if (noffH.code.size > 0) {
        executable -> ReadAt(Buffer, noffH.code.size, noffH.code.inFileAddr);
    }
    if (noffH.initData.size > 0) {
        executable -> ReadAt(Buffer + noffH.code.size, noffH.initData.size, noffH.initData.inFileAddr);
    }
    //create a new file    
    fileSystem -> Create(tempfile, filesize);    
    //write the data to the new file
    OpenFile *tempexe = fileSystem -> Open(tempfile);
    tempexe -> WriteAt(Buffer, filesize, 0);
    delete tempexe;  
}

void
AddrSpace::SwapOut()
{
   for(int i = 0;i < numPages;i++){
        if(pageTable[i].valid==TRUE){
            int phynum, vpn;
            vpn=pageTable[i].virtualPage;
            phynum=pageTable[i].physicalPage;
            printf("Page %d will be swapped out!\n",phynum);
            pageTable[i].valid = FALSE;
     
            //open file and write memory data, if the page is dirty
            if(pageTable[i].dirty == TRUE){  
                printf("Page %d is dirty, write back to %s\n",phynum, filename);       
                OpenFile *executable = fileSystem -> Open(filename);     
                executable ->WriteAt(&(machine ->mainMemory[phynum * PageSize]), PageSize, vpn * PageSize);
                delete executable;
            }
            //clean the page
            pageManager->cleanPage(phynum);  
        }
   }
   setAvailPageNum(NumPhysPages/4);
}