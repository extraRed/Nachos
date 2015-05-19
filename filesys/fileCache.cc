#include "fileCache.h"
#include "system.h"

FileCache::FileCache()
{
    cacheblock = new CacheBlock[NumBlock];
    for(int i=0;i<NumBlock; i++){
        cacheblock[i].datablock=new char[SectorSize];
        cacheblock[i].sector=-1;
        cacheblock[i].valid=FALSE;
        cacheblock[i].dirty=FALSE;
    }
}

FileCache::~FileCache()
{
    for(int i=0;i<NumBlock; i++){
        delete cacheblock[i].datablock;
    }
    delete [] cacheblock;
}

void
FileCache::LoadBlock(int sectorNumber)
{
    int blockId = FindEmptyBlock();
    synchDisk->ReadSector(sectorNumber, cacheblock[blockId].datablock);
    cacheblock[blockId].valid=TRUE;
    cacheblock[blockId].dirty=FALSE;
    cacheblock[blockId].sector=sectorNumber;
}

int 
FileCache::FindEmptyBlock()
{
    for(int i=0;i<NumBlock;i++){
        if(cacheblock[i].valid==FALSE)
            return i;
    }

    SwapABlock();

    for(int i=0;i<NumBlock;i++){
        if(cacheblock[i].valid==FALSE)
            return i;
    }    
    ASSERT(FALSE);
    return -1;
}

void
FileCache::SwapABlock()
{
    int minTime = stats->totalTicks;
    int swapBlock;
    for(int i=0;i<NumBlock;i++){
        if(cacheblock[i].lastAccessTime<minTime){
            minTime=cacheblock[i].lastAccessTime;
            swapBlock = i;
        }
    }
    printf("FileCache block %d will be swapped out!\n",swapBlock);
    if(cacheblock[swapBlock].dirty==TRUE){
        printf("The block is dirty, will write back to SynchDisk\n");
        synchDisk->WriteSector(cacheblock[swapBlock].sector, cacheblock[swapBlock].datablock);
    }
    cacheblock[swapBlock].valid = FALSE;
}

void
FileCache::CacheReadSector(int sectorNumber, char* data)
{
    printf("In cache read\n");
    for(int i=0;i<NumBlock;i++){
        if(cacheblock[i].sector==sectorNumber){
            printf("Sector %d hit in the cache!\n",sectorNumber);
            //strncpy(data,cacheblock[i].datablock,SectorSize);
            bcopy(cacheblock[i].datablock,data,SectorSize);
            cacheblock[i].lastAccessTime=stats->totalTicks;
            return ;
        }
    }
    printf("Sector %d missed in the cache!\n",sectorNumber);

    LoadBlock(sectorNumber);
    
    for(int i=0;i<NumBlock;i++){
        if(cacheblock[i].sector==sectorNumber){
            printf("Sector %d hit in the cache!\n",sectorNumber);
            //strncpy(data,cacheblock[i].datablock,SectorSize);
            bcopy(cacheblock[i].datablock,data,SectorSize);
            cacheblock[i].lastAccessTime=stats->totalTicks;
            return ;
        }
    }
    ASSERT(FALSE);
}

void 
FileCache::CacheWriteSector(int sectorNumber, char* data)
{
    printf("In cache write\n");
    for(int i=0;i<NumBlock;i++){
        if(cacheblock[i].sector==sectorNumber){
            printf("Sector %d hit in the cache!\n",sectorNumber);
            //strncpy(data,cacheblock[i].datablock,SectorSize);
            bcopy(data,cacheblock[i].datablock,SectorSize);            
            cacheblock[i].lastAccessTime=stats->totalTicks;
            cacheblock[i].dirty = TRUE;
            return ;
        }
    }
    printf("Sector %d missed in the cache!\n",sectorNumber);

    LoadBlock(sectorNumber);
    
    for(int i=0;i<NumBlock;i++){
        if(cacheblock[i].sector==sectorNumber){
            printf("Sector %d hit in the cache!\n",sectorNumber);
            //strncpy(data,cacheblock[i].datablock,SectorSize);
            bcopy(data,cacheblock[i].datablock,SectorSize);            
            cacheblock[i].lastAccessTime=stats->totalTicks;
            cacheblock[i].dirty = TRUE;
            return ;
        }
    }
    ASSERT(FALSE);
}
