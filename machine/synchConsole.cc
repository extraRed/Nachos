#include "copyright.h"
#include "synchConsole.h"
#include "system.h"

//// Dummy functions because C++ is weird about pointers to member functions
static void SynchConsoleRead(int c)
{
	SynchConsole *synchConsole = (SynchConsole *)c;
	synchConsole->CheckCharAvail();
}
static void SynchConsoleWrite(int c)
{
	SynchConsole *synchConsole = (SynchConsole *)c;
	synchConsole->WriteDone();
}

SynchConsole::SynchConsole(char *readFile, char *writeFile)
{
	writeSemaphore = new Semaphore("Synch Console Write", 0);
	readSemaphore = new Semaphore("Sync Console Avail", 0);
	putLock = new Lock("Synch Console Put Lock");
	getLock = new Lock("Synch Console Get Lock");
	console = new Console(readFile, writeFile, SynchConsoleRead, SynchConsoleWrite, (int)this);
}

SynchConsole::~SynchConsole()
{
	delete console;
	delete getLock;
	delete putLock;
	delete readSemaphore;
	delete writeSemaphore;
}

void
SynchConsole::CheckCharAvail()
{
	readSemaphore->V();
}

void
SynchConsole::WriteDone()
{
	writeSemaphore->V();
}

char
SynchConsole::GetChar()
{
	getLock->Acquire();
	readSemaphore->P();
	char ch = console->GetChar();
	getLock->Release();
	return ch;
}

void
SynchConsole::PutChar(char ch)
{
	putLock->Acquire();
	console->PutChar(ch);
	writeSemaphore->P();
	putLock->Release();
}
