#include "fileManager.h"

int sectorCheck;
Element *TempItem;

bool Find;


void CheckFile(int ptr)
{
    Element *element = (Element *)ptr;
    if(element ->sector == sectorCheck){
        Find = TRUE;
        TempItem = element;
    }
}

void PrintInfo(int ptr)
{
    Element *element = (Element *)ptr;
    printf("sector: %d, threadcount: %d\n",element->sector,element->threadcount);
}


FileManager::FileManager()
{
    fileList = new SynchList();

}

FileManager::~FileManager()
{
    delete fileList;
}

bool
FileManager::Append(int sector)
{
    sectorCheck = sector;
    Find = FALSE;
   
    fileList ->Mapcar(CheckFile); 

    if(Find){   
        TempItem ->threadcount++;
        return FALSE;    // find the file, we don't append it 
    }else{
        Element *element = new Element();
        element ->sector = sector;
        //element ->lock = new Lock("mutex");
        element ->lock = new Read_Write_Lock("mutex");
        element ->threadcount = 1;

        fileList ->Append(element, sector);
        return TRUE;
    }
}

bool
FileManager::Remove(int sector)
{
    sectorCheck = sector;
    Find = FALSE;

    fileList ->Mapcar(CheckFile);

    ASSERT(Find);
    
    TempItem ->threadcount--;
    if(TempItem ->threadcount == 0){    // if the thread count equal 0, means no threads hold the file, we delete it
        Element *element = (Element*)fileList ->RemoveByKey(sector);
  
        ASSERT(element != NULL);
        delete element;
    }
    return TRUE;
}

bool 
FileManager::LockReadFile(int sector)
{
    sectorCheck = sector;
    Find = FALSE;
    TempItem = NULL;

    fileList ->Mapcar(CheckFile);
    
    ASSERT(Find);

    ASSERT(TempItem != NULL);
    TempItem ->lock->Read_Acquire();

    return TRUE;
}

bool 
FileManager::ReleaseReadFile(int sector)
{
    sectorCheck = sector;
    Find = FALSE;
    TempItem = NULL;

    fileList ->Mapcar(CheckFile);
    
    ASSERT(Find);

    ASSERT(TempItem != NULL);
    TempItem ->lock->Read_Release();

    return TRUE;
}

bool 
FileManager::LockWriteFile(int sector)
{
    sectorCheck = sector;
    Find = FALSE;
    TempItem = NULL;

    fileList ->Mapcar(CheckFile);
    
    ASSERT(Find);

    ASSERT(TempItem != NULL);
    TempItem ->lock->Write_Acquire();

    return TRUE;
}
bool 
FileManager::ReleaseWriteFile(int sector)
{
    sectorCheck = sector;
    Find = FALSE;
    TempItem = NULL;

    fileList ->Mapcar(CheckFile);
    
    ASSERT(Find);

    ASSERT(TempItem != NULL);
    TempItem ->lock ->Write_Release();

    return TRUE;
}

int 
FileManager::NumThread(int sector)
{

    sectorCheck = sector;
    Find = FALSE;
    TempItem = NULL;

    fileList ->Mapcar(CheckFile);
    
    //ASSERT(Find);          //we must find the file
    
    if(Find){
        ASSERT(TempItem != NULL);
        return TempItem ->threadcount;    
    }else
        return 0;
}

void
FileManager::Print()
{
    printf("Printing the file list\n");
    fileList ->Mapcar(PrintInfo);
}