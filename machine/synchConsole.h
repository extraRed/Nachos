#ifndef SYNCHCONSOLE
#define SYNCHCONSOLE


#include "copyright.h"
#include "utility.h"
#include "console.h"
#include "synch.h"

class SynchConsole {
  public:
    SynchConsole(char *readFile, char *writeFile);
    ~SynchConsole();			
    void PutChar(char ch);	
    char GetChar();	   	
    void WriteDone();	 	
    void CheckCharAvail();

  private:
    Console *console;
    Semaphore *writeSemaphore;
    Semaphore *readSemaphore;
    Lock *putLock;
    Lock *getLock;
};

#endif 

