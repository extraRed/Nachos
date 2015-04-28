#include "pageManager.h"
#include "machine.h"
#include "system.h"
#include "addrspace.h"

PageManager::PageManager()
{
    manager = new BitMap(MemorySize);
}

PageManager::~PageManager()
{
    delete manager;
}

//find a clean page
int 
PageManager::findPage()
{
    int address = manager ->JustFind();  

     if( address == -1 )      
        return -1;
     return address / PageSize;
}

// return the number of clean pages
int 
PageManager::numClean()
{
    int num = manager ->NumClear();   // return how many bytes are clean
    ASSERT(num % PageSize == 0);   // the number must be a multiple of PageSize 
    return num / PageSize;         
}

//mark these pages as allocated
void
PageManager::markPage(int pagenum)
{
    int address = pagenum * PageSize; 
    for(int i = address; i < address + PageSize; i++)
         manager ->Mark(i);     
}

//mark these pages as free            
void 
PageManager::cleanPage(int pagenum)
{
    int address = pagenum * PageSize;
    for(int i = address; i < address + PageSize; i++)
         manager ->Clear(i);     
}

void 
PageManager::loadPage(int address)
{      
     char *filename = currentThread ->space->getFileName();      // get the executable file name of the thread
     int phynum, entryid;
     int vpn = address/ PageSize;

     printf("PageFault from virtual page %d!\n", vpn);
    
     // find a clean page in the memory for the program     
     int availPage=currentThread->space->getAvailPageNum();
     ASSERT(availPage>=0);
     if(availPage==0 || numClean()==0) {
         //entryid= getSwapPageFIFO();  
         entryid = getSwapPageLRU();  
         ASSERT(entryid != -1 && machine->pageTable[entryid].valid==TRUE);
         char *filename=currentThread->space->getFileName();
         phynum = swapPage(entryid,filename);
         ASSERT(phynum!=-1);
     }else{
         phynum = findPage();
         currentThread->space->setAvailPageNum(availPage-1);
         ASSERT(phynum!= -1);
     }
     
     markPage(phynum);     //set the page 
     //printf("virtual page: %d, physical page: %d\n", vpn, phynum); 

     printf("Load virtual page %d to physical page %d from %s\n", vpn, phynum, filename);
     
     //open file and load the page
     OpenFile *executable = fileSystem -> Open(filename);
     executable ->ReadAt(&(machine ->mainMemory[phynum * PageSize]), PageSize, vpn * PageSize);

     // set the pagetable
     machine ->pageTable[vpn].valid = TRUE;
     machine ->pageTable[vpn].physicalPage = phynum;
     machine ->pageTable[vpn].virtualPage = vpn;
     machine ->pageTable[vpn].use = FALSE;
     machine ->pageTable[vpn].dirty = FALSE;
     machine ->pageTable[vpn].readOnly = FALSE;

     machine->pageTable[vpn].comingTime=stats->totalTicks;

     DumpState();
     delete executable;
}


int
PageManager::swapPage(int entryid, char *filename)
{
     ASSERT(machine->pageTable[entryid].valid==TRUE);
     int phynum, vpn;
     vpn=machine->pageTable[entryid].virtualPage;
     phynum=machine->pageTable[entryid].physicalPage;
    
     printf("Page %d will be swapped out!\n",phynum);

     machine ->pageTable[entryid].valid = FALSE;
     
     //open file and write memory data, if the page is dirty
     if(machine ->pageTable[entryid].dirty == TRUE)
     {
        
        printf("Page %d is dirty, write back to %s\n",phynum, filename);
        
         OpenFile *executable = fileSystem -> Open(filename);     
         executable ->WriteAt(&(machine ->mainMemory[phynum * PageSize]), PageSize, vpn * PageSize);
         delete executable;
     }
     //clean the page
     cleanPage(phynum);  
     return phynum;
}

int
PageManager::getSwapPageFIFO()
{
    DEBUG('a',"PageFault, use FIFO swap\n");
    int slot=0;
    int min = stats->totalTicks;
    int pagenum=machine->pageTableSize;
    for(int i = 0; i< pagenum;i++){     				    
       if(machine->pageTable[i].valid==TRUE &&  machine->pageTable[i].comingTime < min){
	   min = machine->pageTable[i].comingTime;
	   slot = i;
	 }
    }
    return slot;
}

int
PageManager::getSwapPageLRU()
{
    DEBUG('a',"PageFault, use LRU swap\n");
    int slot=0;
    int min = stats->totalTicks;
    int pagenum=machine->pageTableSize;
    for(int i = 0; i< pagenum;i++){     				    
       if(machine->pageTable[i].valid==TRUE &&  machine->pageTable[i].lastAccessTime < min){
	   min = machine->pageTable[i].lastAccessTime;
	   slot = i;
	 }
    }
    return slot;
}

void
PageManager::DumpState()
{
    printf("***********\n");
    printf("Pagetable state of %s\n",currentThread->getName());
    for(int i = 0; i< machine->pageTableSize;i++){
        printf("valid:%d, vpn:%d, ppn:%d, dirty:%d, time:%d\n",machine->pageTable[i].valid,machine->pageTable[i].virtualPage,machine->pageTable[i].physicalPage,machine->pageTable[i].dirty,machine->pageTable[i].lastAccessTime);
    }
    printf("***********\n");
}
