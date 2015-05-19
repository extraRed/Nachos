// fstest.cc 
//	Simple test routines for the file system.  
//
//	We implement:
//	   Copy -- copy a file from UNIX to Nachos
//	   Print -- cat the contents of a Nachos file 
//	   Perftest -- a stress test for the Nachos file system
//		read and write a really large file in tiny chunks
//		(won't work on baseline system!)
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"

#include "utility.h"
#include "filesys.h"
#include "system.h"
#include "thread.h"
#include "disk.h"
#include "stats.h"

#define TransferSize 	10 	// make it small, just to be difficult

//----------------------------------------------------------------------
// Copy
// 	Copy the contents of the UNIX file "from" to the Nachos file "to"
//----------------------------------------------------------------------

void
Copy(char *from, char *to)
{
    FILE *fp;
    OpenFile* openFile;
    int amountRead, fileLength;
    char *buffer;

// Open UNIX file
    if ((fp = fopen(from, "r")) == NULL) {	 
	printf("Copy: couldn't open input file %s\n", from);
	return;
    }

// Figure out length of UNIX file
    fseek(fp, 0, 2);		
    fileLength = ftell(fp);
    fseek(fp, 0, 0);

// Create a Nachos file of the same length
    DEBUG('f', "Copying file %s, size %d, to file %s\n", from, fileLength, to);
    if (!fileSystem->Create(to, fileLength)) {	 // Create Nachos file
	printf("Copy: couldn't create output file %s\n", to);
	fclose(fp);
	return;
    }

    openFile = fileSystem->Open(to);
    ASSERT(openFile != NULL);
    
// Copy the data in TransferSize chunks
    buffer = new char[TransferSize];
    while ((amountRead = fread(buffer, sizeof(char), TransferSize, fp)) > 0)
	openFile->Write(buffer, amountRead);	
    delete [] buffer;

// Close the UNIX and the Nachos files
    delete openFile;
    fclose(fp);
}

//----------------------------------------------------------------------
// Print
// 	Print the contents of the Nachos file "name".
//----------------------------------------------------------------------

void
Print(char *name)
{
    OpenFile *openFile;    
    int i, amountRead;
    char *buffer;

    if ((openFile = fileSystem->Open(name)) == NULL) {
	printf("Print: unable to open file %s\n", name);
	return;
    }
    
    buffer = new char[TransferSize];
    while ((amountRead = openFile->Read(buffer, TransferSize)) > 0){
	for (i = 0; i < amountRead; i++)
	    printf("%c", buffer[i]);
        printf("\n");
    }
    delete [] buffer;

    delete openFile;		// close the Nachos file
    return;
}

//----------------------------------------------------------------------
// PerformanceTest
// 	Stress the Nachos file system by creating a large file, writing
//	it out a bit at a time, reading it back a bit at a time, and then
//	deleting the file.
//
//	Implemented as three separate routines:
//	  FileWrite -- write the file
//	  FileRead -- read the file
//	  PerformanceTest -- overall control, and print out performance #'s
//----------------------------------------------------------------------

#define FileName 	"TestFile"
#define Contents 	"1234567890"
#define NewContents "0987654321"
#define ContentSize 	strlen(Contents)
#define FileSize 	((int)(ContentSize * 100))

//static void 
void
FileWrite(int arg)
{
    OpenFile *openFile;    
    int i, numBytes;

    printf("Sequential write of %d byte file, in %d byte chunks\n", 
	FileSize, ContentSize);
    if(arg==0){
    if (!fileSystem->Create(FileName, FileSize)) {
      printf("Perf test: can't create %s\n", FileName);
      return;
    }
    }
    openFile = fileSystem->Open(FileName);
    if (openFile == NULL) {
	printf("Perf test: unable to open %s\n", FileName);
	return;
    }
    for (i = 0; i < FileSize; i += ContentSize) {
        if(arg==0)
            numBytes = openFile->Write(Contents, ContentSize);
        else
            numBytes = openFile->Write(NewContents, ContentSize);
        //printf("NumB: %d\n",numBytes);
	if (numBytes < 10) {
	    printf("Perf test: unable to write %s\n", FileName);
	    delete openFile;
	    return;
	}
    }
    delete openFile;	// close file
}

//static void 
void
FileRead(int arg)
{
    OpenFile *openFile;    
    char *buffer = new char[ContentSize];
    int i, numBytes;

    printf("Sequential read of %d byte file, in %d byte chunks\n", 
	FileSize, ContentSize);

    if ((openFile = fileSystem->Open(FileName)) == NULL) {
	printf("Perf test: unable to open file %s\n", FileName);
	delete [] buffer;
	return;
    }
    for (i = 0; i < FileSize; i += ContentSize) {
        numBytes = openFile->Read(buffer, ContentSize);
        printf("content read: %s\n",buffer);
	  if ((numBytes < 10) || strncmp(buffer, Contents, ContentSize)) {
	    printf("Perf test: unable to read %s\n", FileName);
	    delete openFile;
	    delete [] buffer;
	    return;
	}
    }
    delete [] buffer;
    delete openFile;	// close file
}

void
TestMutiDir()
{
    fileSystem->CreateDirectory("LMX");
    fileSystem->CreateDirectory("OS", "/LMX");
    fileSystem->CreateDirectory("Nachos", "/LMX/OS");
    fileSystem->Create("Lab4", 1000, "/LMX/OS/Nachos");
    fileSystem->Create("Lab5", 1000, "/LMX/OS/Nachos");
    fileSystem->Print();
    fileSystem->RemoveDirectory("OS", "/LMX");
    fileSystem->Print();
}

void openAndclose(int arg)
{
    OpenFile *openFile;    
    if ((openFile = fileSystem->Open(FileName)) == NULL) {
	printf("Perf test: unable to open file %s\n", FileName);
	return;
    }
    printf("file %s opened by %s\n",FileName,currentThread->getName());
    if(arg==2){
        //currentThread->Yield();

        delete openFile;
        if (!fileSystem->Remove(FileName)) {
            printf("Perf test: unable to remove %s\n", FileName);
        }else{
            printf("Perf test: %s is removed by thread %\n", FileName, currentThread->getName());
        }
    }
     
}

void 
TestMutiThread()
{
    Thread *t1=new Thread("reader1");
    Thread *t2=new Thread("writer1");
    //Thread *t3=new Thread("writer2");
    t1->Fork(FileRead,0);
    t2->Fork(FileWrite,1);
    //t3->Fork(Writer,2);
}

void
PerformanceTest()
{
    printf("Starting file system performance test:\n");
    //fileSystem->Print();
    //stats->Print();
    FileWrite(0);
    FileRead(0);
    //fileSystem->Print();
    if (!fileSystem->Remove(FileName)) {
      printf("Perf test: unable to remove %s\n", FileName);
      return;
    }
    //stats->Print();
    
    //TestMutiDir();
    //TestMutiThread();
}

