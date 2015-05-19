// filehdr.cc 
//	Routines for managing the disk file header (in UNIX, this
//	would be called the i-node).
//
//	The file header is used to locate where on disk the 
//	file's data is stored.  We implement this as a fixed size
//	table of pointers -- each entry in the table points to the 
//	disk sector containing that portion of the file data
//	(in other words, there are no indirect or doubly indirect 
//	blocks). The table size is chosen so that the file header
//	will be just big enough to fit in one disk sector, 
//
//      Unlike in a real system, we do not keep track of file permissions, 
//	ownership, last modification date, etc., in the file header. 
//
//	A file header can be initialized in two ways:
//	   for a new file, by modifying the in-memory data structure
//	     to point to the newly allocated data blocks
//	   for a file already on disk, by reading the file header from disk
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"

#include "system.h"
#include "filehdr.h"

//----------------------------------------------------------------------
// FileHeader::Init
// 	Set the type (directoty or file) and the path of file
//----------------------------------------------------------------------
void FileHeader::Init(int type, int path)
{
    this->type = type;
    this->createTime = stats->totalTicks;
    this->path = path;
}
//----------------------------------------------------------------------
// FileHeader::Allocate
// 	Initialize a fresh file header for a newly created file.
//	Allocate data blocks for the file out of the map of free disk blocks.
//	Return FALSE if there are not enough free blocks to accomodate
//	the new file.
//
//	"freeMap" is the bit map of free disk sectors
//	"fileSize" is the bit map of free disk sectors
//----------------------------------------------------------------------

bool
FileHeader::Allocate(BitMap *freeMap, int fileSize)
{ 
    numBytes = fileSize;
    numSectors  = divRoundUp(fileSize, SectorSize);
    int leftSectors = numSectors; 
    if (freeMap->NumClear() < numSectors)
	return FALSE;		// not enough space
    //Do not need first indexes
    if (numSectors <= NumDirect){
        for (int i = 0; i < numSectors; i++)
	    dataSectors[i] = freeMap->Find();
        return TRUE;
    }else{
        for (int i = 0; i < NumDirect; i++)
	    dataSectors[i] = freeMap->Find();
        leftSectors -= NumDirect;
    }
    for(int i=0;leftSectors>0;i++,leftSectors-=NumFirstDirect){
        dataSectors[NumDirect+i] = freeMap->Find();
        //how many indexes will be used(total is 32)
        int numUse = leftSectors<NumFirstDirect?leftSectors:NumFirstDirect;
        int *firstIndex = new int[numUse];
        for(int j=0;j<numUse;j++){
            firstIndex[j]=freeMap->Find();
        }
        //Write back to the sector that contains first indexes
        synchDisk->WriteSector(dataSectors[NumDirect+i],(char*)firstIndex);
        delete firstIndex;
    } 
    return TRUE;
}

//----------------------------------------------------------------------
// FileHeader::Deallocate
// 	De-allocate all the space allocated for data blocks for this file.
//
//	"freeMap" is the bit map of free disk sectors
//----------------------------------------------------------------------

void 
FileHeader::Deallocate(BitMap *freeMap)
{
    int leftSectors = numSectors;
    if (numSectors <= NumDirect){
        for (int i = 0; i < numSectors; i++) {
	    ASSERT(freeMap->Test((int) dataSectors[i]));  // ought to be marked!
	    freeMap->Clear((int) dataSectors[i]);
        }
        return ;
    }else{
        for (int i = 0; i < NumDirect; i++) {
	    ASSERT(freeMap->Test((int) dataSectors[i]));  // ought to be marked!
	    freeMap->Clear((int) dataSectors[i]);
        }
        leftSectors -= NumDirect;
    }
    for(int i=0; leftSectors>0;i++,leftSectors-=NumFirstDirect){
        int numUse = leftSectors<NumFirstDirect?leftSectors:NumFirstDirect;
        char *buffer = new char[SectorSize];
        synchDisk->ReadSector(dataSectors[NumDirect+i], buffer);
        int *firstIndex=(int *)buffer;
        for(int j=0;j<numUse;j++){
           ASSERT(freeMap->Test((int) firstIndex[j]));  // ought to be marked!
	    freeMap->Clear((int) firstIndex[j]);
        }
        ASSERT(freeMap->Test((int) dataSectors[NumDirect+i]));  // ought to be marked!
	 freeMap->Clear((int) dataSectors[NumDirect+i]);
    }
}

//----------------------------------------------------------------------
// FileHeader::FetchFrom
// 	Fetch contents of file header from disk. 
//
//	"sector" is the disk sector containing the file header
//----------------------------------------------------------------------

void
FileHeader::FetchFrom(int sector)
{
    //fileCache->CacheReadSector(sector, (char *)this);
    synchDisk->ReadSector(sector, (char *)this);
}

//----------------------------------------------------------------------
// FileHeader::WriteBack
// 	Write the modified contents of the file header back to disk. 
//
//	"sector" is the disk sector to contain the file header
//----------------------------------------------------------------------

void
FileHeader::WriteBack(int sector)
{
    //fileCache->CacheWriteSector(sector, (char *)this);
    synchDisk->WriteSector(sector, (char *)this); 
}

//----------------------------------------------------------------------
// FileHeader::ByteToSector
// 	Return which disk sector is storing a particular byte within the file.
//      This is essentially a translation from a virtual address (the
//	offset in the file) to a physical address (the sector where the
//	data at the offset is stored).
//
//	"offset" is the location within the file of the byte in question
//----------------------------------------------------------------------

int
FileHeader::ByteToSector(int offset)
{
    int sectorIndex = offset / SectorSize;
    if(sectorIndex < NumDirect)
        return(dataSectors[sectorIndex]);
    else{
        sectorIndex-=NumDirect;
        for(int i=0;sectorIndex>=0;i++,sectorIndex-=NumFirstDirect){
            if(sectorIndex<NumFirstDirect){
                char *buffer = new char[SectorSize];
                synchDisk->ReadSector(dataSectors[NumDirect+i], buffer);
                int *firstIndex = (int *)buffer;
                int sector = firstIndex[sectorIndex];
                delete buffer;
                return sector;
            }
        }
    }
}

//----------------------------------------------------------------------
// FileHeader::FileLength
// 	Return the number of bytes in the file.
//----------------------------------------------------------------------

int
FileHeader::FileLength()
{
    return numBytes;
}

//----------------------------------------------------------------------
// FileHeader::Print
// 	Print the contents of the file header, and the contents of all
//	the data blocks pointed to by the file header.
//----------------------------------------------------------------------

void
FileHeader::Print()
{
    int i;
    printf("type:%d, createTime: %d, accessTime: %d, modifyTime: %d\n", type, createTime, accessTime, modifyTime);
    printf("FileHeader contents.  File size: %d.  File blocks:\n", numBytes);
    int leftSectors = numSectors;
    if(numSectors<NumDirect){
        printf("Direct indexes:\n");
        for (i = 0; i < numSectors; i++)
	    printf("%d ", dataSectors[i]);
        printf("\n");
        leftSectors=0;
    }else{
        printf("Direct indexes:\n");
        for (i = 0; i < NumDirect; i++)
	    printf("%d ", dataSectors[i]);
        printf("\n");
        leftSectors -= NumDirect;
    }
    for(int i=0; leftSectors>0;i++,leftSectors-=NumFirstDirect){
        int numUse = leftSectors<NumFirstDirect?leftSectors:NumFirstDirect;
        char *buffer = new char[SectorSize];
        synchDisk->ReadSector(dataSectors[NumDirect+i], buffer);
        int *firstIndex=(int *)buffer;
        printf("First indexes: %d\n",dataSectors[NumDirect+i]);
        printf("Direct indexes of the first index:\n");
        for(int j=0;j<numUse;j++){
            printf("%d ",firstIndex[j]);
        }
        printf("\n");
    }

    
    int j, k;
    char *data = new char[SectorSize];
    printf("\nFile contents:\n");
    for (i = k = 0; i < numSectors; i++) {
	synchDisk->ReadSector(dataSectors[i], data);
        for (j = 0; (j < SectorSize) && (k < numBytes); j++, k++) {
	    if ('\040' <= data[j] && data[j] <= '\176')   // isprint(data[j])
		printf("%c", data[j]);
            else
		printf("\\%x", (unsigned char)data[j]);
	}
        printf("\n"); 
    }
    delete [] data;
    
}

//by LMX
//----------------------------------------------------------------------
// FileHeader::ChangeSize
//     Reset the size of the file, this function is used when we increase the size of the file
//----------------------------------------------------------------------

bool
FileHeader::ChangeSize(BitMap *freeMap, int newSize)
{  
     int newSectorNum = divRoundUp(newSize, SectorSize);
     ASSERT(newSectorNum >= numSectors)
     if(newSize > MaxFileSize || (freeMap ->NumClear()) < (newSectorNum - numSectors))
        return FALSE;

     if(numSectors == newSectorNum){    //if the accural disk sector remain same, do nothing                               
         numBytes = newSize;
     }else{
         IncreaseFile(freeMap, newSectorNum - numSectors);
         numSectors = newSectorNum;
         numBytes = newSize;
     } 
     return TRUE;
}

//----------------------------------------------------------------------
// FileHeader::IncreaseFile
// 	
//     Increase the size of the file, more precisely, increase the number of disk sectors 
//      allocated for that files
//
//----------------------------------------------------------------------

void
FileHeader::IncreaseFile(BitMap *freeMap, int newSectors)
{
     if (numSectors+newSectors<=NumDirect){ //Increased file can also just use first indexes
            for(int i=0;i<newSectors;i++)
                dataSectors[numSectors+i]=freeMap->Find();
     }else if(numSectors<=NumDirect){   //Original file just use first indexes, but now we need second indexes
            int leftDirectSectors = NumDirect-numSectors;
            for(int i=0;i<leftDirectSectors;i++)
                dataSectors[numSectors+i]=freeMap->Find();
            
            //other sectors need first indexes!
            int leftSectors = newSectors-leftDirectSectors;
            for(int i=0;leftSectors>0;i++,leftSectors-=NumFirstDirect){
                dataSectors[NumDirect+i] = freeMap->Find();
                //how many indexes will be used(total is 32)
                int numUse = leftSectors<NumFirstDirect?leftSectors:NumFirstDirect;
                int *firstIndex = new int[numUse];
                for(int j=0;j<numUse;j++)
                    firstIndex[j]=freeMap->Find();
                
                //Write back to the sector that contains first indexes
                synchDisk->WriteSector(dataSectors[NumDirect+i],(char*)firstIndex);
                delete firstIndex;
            }
     }else{ //Original file has already used first indexes!
        int lastLeftSectors = numSectors-NumDirect;
        if(lastLeftSectors%NumFirstDirect==0){  //Original file has exactly used up direct indexes in its first indexes
            int lastFreeFirstIndex = lastLeftSectors/NumFirstDirect + NumDirect;
            int leftSectors = newSectors;
            
            for(int i=0;leftSectors>0;i++,leftSectors-=NumFirstDirect){
                dataSectors[lastFreeFirstIndex+i] = freeMap->Find();
                //how many indexes will be used(total is 32)
                int numUse = leftSectors<NumFirstDirect?leftSectors:NumFirstDirect;
                int *firstIndex = new int[numUse];
                for(int j=0;j<numUse;j++)
                    firstIndex[j]=freeMap->Find();
                
                //Write back to the sector that contains first indexes
                synchDisk->WriteSector(dataSectors[lastFreeFirstIndex+i],(char*)firstIndex);
                delete firstIndex;
            }
        }else{  //There are free direct indexes in the last first index of original file
            int usedDirectIndex = lastLeftSectors%NumFirstDirect;
            int lastFreeFirstIndex = lastLeftSectors/NumFirstDirect + NumDirect;
            int leftSectors = newSectors;
            //read out the last direct index
            char *buffer = new char[SectorSize];
            synchDisk->ReadSector(dataSectors[lastFreeFirstIndex], buffer);
            int *firstIndex=(int *)buffer;
            
            if(newSectors+usedDirectIndex<=NumFirstDirect){  // This first index is enough
                for(int i=0;i<newSectors;i++)
                    firstIndex[usedDirectIndex+i]=freeMap->Find();
                //Write back to the sector that contains first indexes
                synchDisk->WriteSector(dataSectors[lastFreeFirstIndex],(char*)firstIndex);
                delete buffer;
            }else{  //Still need new first index!
                for(int i=0;usedDirectIndex+i<NumFirstDirect;i++)
                    firstIndex[usedDirectIndex+i]=freeMap->Find();
                //Write back to the sector that contains first indexes
                synchDisk->WriteSector(dataSectors[lastFreeFirstIndex],(char*)firstIndex);
                delete buffer;
                
                leftSectors-=(NumFirstDirect-usedDirectIndex);
                lastFreeFirstIndex++;
                 
                for(int i=0;leftSectors>0;i++,leftSectors-=NumFirstDirect){
                    dataSectors[lastFreeFirstIndex+i] = freeMap->Find();
                    //how many indexes will be used(total is 32)
                    int numUse = leftSectors<NumFirstDirect?leftSectors:NumFirstDirect;
                    int *firstIndex = new int[numUse];
                    for(int j=0;j<numUse;j++)
                        firstIndex[j]=freeMap->Find();
                
                    //Write back to the sector that contains first indexes
                    synchDisk->WriteSector(dataSectors[lastFreeFirstIndex+i],(char*)firstIndex);
                    delete firstIndex;
                }
            }
        }
     }
}
