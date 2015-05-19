#ifndef FILEMGR_H
#define FILEMGR_H

#include "synchlist.h"

class Element{
   public:
      int sector;
      int threadcount;
      Read_Write_Lock *lock;
};
//use the sector number as the list key

class FileManager
{
     private:
         SynchList *fileList; 

     public:
         FileManager();  

         ~FileManager();
 
         bool Append(int sector);  

         bool Remove(int sector);
         
         bool LockReadFile(int sector);

         bool ReleaseReadFile(int sector);
         
         bool LockWriteFile(int sector);

         bool ReleaseWriteFile(int sector);

         int NumThread(int sector);

         void Print();

};
#endif

