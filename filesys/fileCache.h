#ifndef FILECACHE_H
#define FILECACHE_H

#include "disk.h"

#define NumBlock 8

class CacheBlock{

    public:
        bool valid;
        bool dirty;
        int sector;
        int lastAccessTime;
        char *datablock;
};

class FileCache{
    public:
        FileCache();
        ~FileCache();
        void CacheReadSector(int sectorNumber, char *data);
        void CacheWriteSector(int sectorNumber, char *data);
        void LoadBlock(int sectorNumber);
        int FindEmptyBlock();
        void SwapABlock();
    private:
        CacheBlock *cacheblock;
};

#endif

