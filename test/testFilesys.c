/*
Test filesystem operations: Create, Open, Close, Write, Read, Exec, Fork, Yield, Join, Exit
*/
#include "syscall.h"

//#define str "Good job"
//#define len sizeof(str)
/*
int val=1;
void func()
{
	Exit(val);
}
*/
int
main()
{
    /*
    val++;
    Fork(func);
    Yield();
    val++;
    Exit(val);
    */
    
/*
    int i,fid,readsize;
    char buffer[len];
    //buffer = new char[len];
    Create("LMX");
    fid = Open("LMX");
    Write(str,len,fid);
    readsize = Read(buffer, len, fid);
    if(readsize!=len){
        Exit(-1);
    }else{
        //Print("Contents:",2);
        //for(i=0;i<len;i++)
        //    Print(buffer[i],1);
        //Print(buffer,2);
    }
    Close(fid);
 */
 
    int tid;
    int code = 0;
    tid=Exec("sort");
    Join(tid);
    Exit(code);
 
    /* not reached */
}