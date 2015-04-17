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
    int address = manager -> Find();  

     if( address == -1 )      
        return -1;
     return address / PageSize;
}

// return the number of clean pages
int 
PageManager::numClean()
{
    int num = manager -> NumClear();   // return how many bytes are clean
    ASSERT(num % PageSize == 0);   // the number must be a multiple of PageSize 
    return num / PageSize;         
}

//mark these pages as allocated
void
PageManager::markPage(int pagenum)
{
    int address = pagenum * PageSize; 
    for(int i = address; i < address + PageSize; i++)
         manager -> Mark(i);     
}

//mark these pages as free            
void 
PageManager::cleanPage(int pagenum)
{
    int address = pagenum * PageSize;
    for(int i = address; i < address + PageSize; i++)
         manager -> Clear(i);     
}
