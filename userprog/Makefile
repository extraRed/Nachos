# NOTE: this is a GNU Makefile.  You must use "gmake" rather than "make".
#
# Makefile for the multiprogramming assignment
#    Defines set up assuming multiprogramming is done before the file system.
#    If not, use the "filesys first"  defines below. 
#
#
# Copyright (c) 1992 The Regents of the University of California.
# All rights reserved.  See copyright.h for copyright notice and limitation 
# of liability and disclaimer of warranty provisions.

#DEFINES = -DUSER_PROGRAM -DFILESYS_NEEDED -DFILESYS_STUB -DUSE_TLB
#INCPATH = -I../bin -I../filesys -I../userprog -I../threads -I../machine
#HFILES = $(THREAD_H) $(USERPROG_H)
#CFILES = $(THREAD_C) $(USERPROG_C)
#C_OFILES = $(THREAD_O) $(USERPROG_O)

# if file sys done first!
 DEFINES = -DUSER_PROGRAM -DFILESYS_NEEDED -DFILESYS
 INCPATH = -I../bin -I../filesys -I../userprog -I../threads -I../machine
 HFILES = $(THREAD_H) $(USERPROG_H) $(FILESYS_H)
 CFILES = $(THREAD_C) $(USERPROG_C) $(FILESYS_C)
 C_OFILES = $(THREAD_O) $(USERPROG_O) $(FILESYS_O)

include ../Makefile.common
include ../Makefile.dep
#-----------------------------------------------------------------
# DO NOT DELETE THIS LINE -- make depend uses it
# DEPENDENCIES MUST END AT END OF FILE
main.o: ../threads/main.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/utility.h ../threads/bool.h \
 ../machine/sysdep.h ../threads/copyright.h /usr/include/stdio.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../threads/system.h ../threads/thread.h \
 ../threads/list.h ../machine/machine.h ../threads/utility.h \
 ../machine/translate.h ../machine/disk.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h ../threads/scheduler.h \
 ../machine/timer.h ../machine/interrupt.h ../threads/list.h \
 ../machine/stats.h ../userprog/pageManager.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../filesys/synchdisk.h ../machine/disk.h \
 ../threads/synch.h ../filesys/fileManager.h ../threads/synchlist.h \
 ../threads/synch.h ../filesys/fileCache.h
list.o: ../threads/list.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/list.h ../threads/utility.h \
 ../threads/bool.h ../machine/sysdep.h ../threads/copyright.h \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h
scheduler.o: ../threads/scheduler.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/scheduler.h ../threads/list.h \
 ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
 ../threads/copyright.h /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../threads/thread.h ../machine/machine.h \
 ../threads/utility.h ../machine/translate.h ../machine/disk.h \
 ../userprog/addrspace.h ../filesys/filesys.h ../filesys/openfile.h \
 ../machine/timer.h ../threads/system.h ../machine/interrupt.h \
 ../threads/list.h ../machine/stats.h ../userprog/pageManager.h \
 ../userprog/bitmap.h ../filesys/openfile.h ../filesys/synchdisk.h \
 ../machine/disk.h ../threads/synch.h ../filesys/fileManager.h \
 ../threads/synchlist.h ../threads/synch.h ../filesys/fileCache.h
synch.o: ../threads/synch.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/synch.h ../threads/thread.h \
 ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
 ../threads/copyright.h /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../threads/list.h ../machine/machine.h \
 ../threads/utility.h ../machine/translate.h ../machine/disk.h \
 ../userprog/addrspace.h ../filesys/filesys.h ../filesys/openfile.h \
 ../threads/system.h ../threads/scheduler.h ../machine/timer.h \
 ../machine/interrupt.h ../threads/list.h ../machine/stats.h \
 ../userprog/pageManager.h ../userprog/bitmap.h ../filesys/openfile.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../filesys/fileManager.h ../threads/synchlist.h ../filesys/fileCache.h
synchlist.o: ../threads/synchlist.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/synchlist.h ../threads/list.h \
 ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
 ../threads/copyright.h /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../threads/synch.h ../threads/thread.h \
 ../machine/machine.h ../threads/utility.h ../machine/translate.h \
 ../machine/disk.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h
system.o: ../threads/system.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/system.h ../threads/utility.h \
 ../threads/bool.h ../machine/sysdep.h ../threads/copyright.h \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../threads/thread.h ../threads/list.h \
 ../machine/machine.h ../threads/utility.h ../machine/translate.h \
 ../machine/disk.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../machine/timer.h \
 ../machine/interrupt.h ../threads/list.h ../machine/stats.h \
 ../userprog/pageManager.h ../userprog/bitmap.h ../filesys/openfile.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../filesys/fileManager.h ../threads/synchlist.h ../threads/synch.h \
 ../filesys/fileCache.h
thread.o: ../threads/thread.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/thread.h ../threads/utility.h \
 ../threads/bool.h ../machine/sysdep.h ../threads/copyright.h \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../threads/list.h ../machine/machine.h \
 ../threads/utility.h ../machine/translate.h ../machine/disk.h \
 ../userprog/addrspace.h ../filesys/filesys.h ../filesys/openfile.h \
 ../threads/switch.h ../threads/synch.h ../threads/system.h \
 ../threads/scheduler.h ../machine/timer.h ../machine/interrupt.h \
 ../threads/list.h ../machine/stats.h ../userprog/pageManager.h \
 ../userprog/bitmap.h ../filesys/openfile.h ../filesys/synchdisk.h \
 ../machine/disk.h ../threads/synch.h ../filesys/fileManager.h \
 ../threads/synchlist.h ../filesys/fileCache.h /usr/include/unistd.h \
 /usr/include/i386-linux-gnu/bits/posix_opt.h \
 /usr/include/i386-linux-gnu/bits/environments.h \
 /usr/include/i386-linux-gnu/bits/confname.h /usr/include/getopt.h \
 /usr/include/c++/4.8/map /usr/include/c++/4.8/bits/stl_tree.h \
 /usr/include/c++/4.8/bits/stl_algobase.h \
 /usr/include/i386-linux-gnu/c++/4.8/bits/c++config.h \
 /usr/include/i386-linux-gnu/c++/4.8/bits/os_defines.h \
 /usr/include/i386-linux-gnu/c++/4.8/bits/cpu_defines.h \
 /usr/include/c++/4.8/bits/functexcept.h \
 /usr/include/c++/4.8/bits/exception_defines.h \
 /usr/include/c++/4.8/bits/cpp_type_traits.h \
 /usr/include/c++/4.8/ext/type_traits.h \
 /usr/include/c++/4.8/ext/numeric_traits.h \
 /usr/include/c++/4.8/bits/stl_pair.h /usr/include/c++/4.8/bits/move.h \
 /usr/include/c++/4.8/bits/concept_check.h \
 /usr/include/c++/4.8/bits/stl_iterator_base_types.h \
 /usr/include/c++/4.8/bits/stl_iterator_base_funcs.h \
 /usr/include/c++/4.8/debug/debug.h \
 /usr/include/c++/4.8/bits/stl_iterator.h \
 /usr/include/c++/4.8/bits/allocator.h \
 /usr/include/i386-linux-gnu/c++/4.8/bits/c++allocator.h \
 /usr/include/c++/4.8/ext/new_allocator.h /usr/include/c++/4.8/new \
 /usr/include/c++/4.8/exception \
 /usr/include/c++/4.8/bits/atomic_lockfree_defines.h \
 /usr/include/c++/4.8/bits/memoryfwd.h \
 /usr/include/c++/4.8/bits/stl_function.h \
 /usr/include/c++/4.8/backward/binders.h \
 /usr/include/c++/4.8/bits/stl_map.h \
 /usr/include/c++/4.8/bits/stl_multimap.h \
 /usr/include/c++/4.8/bits/range_access.h
utility.o: ../threads/utility.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/utility.h ../threads/bool.h \
 ../machine/sysdep.h ../threads/copyright.h /usr/include/stdio.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../threads/stdarg.h
threadtest.o: ../threads/threadtest.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/system.h ../threads/utility.h \
 ../threads/bool.h ../machine/sysdep.h ../threads/copyright.h \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../threads/thread.h ../threads/list.h \
 ../machine/machine.h ../threads/utility.h ../machine/translate.h \
 ../machine/disk.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../machine/timer.h \
 ../machine/interrupt.h ../threads/list.h ../machine/stats.h \
 ../userprog/pageManager.h ../userprog/bitmap.h ../filesys/openfile.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../filesys/fileManager.h ../threads/synchlist.h ../threads/synch.h \
 ../filesys/fileCache.h
interrupt.o: ../machine/interrupt.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../machine/interrupt.h ../threads/list.h \
 ../threads/copyright.h ../threads/utility.h ../threads/bool.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../threads/system.h ../threads/thread.h \
 ../threads/list.h ../machine/machine.h ../threads/utility.h \
 ../machine/translate.h ../machine/disk.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h ../threads/scheduler.h \
 ../machine/timer.h ../machine/interrupt.h ../machine/stats.h \
 ../userprog/pageManager.h ../userprog/bitmap.h ../filesys/openfile.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../filesys/fileManager.h ../threads/synchlist.h ../threads/synch.h \
 ../filesys/fileCache.h
sysdep.o: ../machine/sysdep.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h /usr/include/signal.h \
 /usr/include/i386-linux-gnu/bits/sigset.h \
 /usr/include/i386-linux-gnu/bits/signum.h /usr/include/time.h \
 /usr/include/i386-linux-gnu/bits/siginfo.h \
 /usr/include/i386-linux-gnu/bits/sigaction.h \
 /usr/include/i386-linux-gnu/bits/sigcontext.h \
 /usr/include/i386-linux-gnu/bits/sigstack.h \
 /usr/include/i386-linux-gnu/sys/ucontext.h \
 /usr/include/i386-linux-gnu/bits/pthreadtypes.h \
 /usr/include/i386-linux-gnu/bits/sigthread.h \
 /usr/include/i386-linux-gnu/sys/types.h /usr/include/endian.h \
 /usr/include/i386-linux-gnu/bits/endian.h \
 /usr/include/i386-linux-gnu/bits/byteswap.h \
 /usr/include/i386-linux-gnu/bits/byteswap-16.h \
 /usr/include/i386-linux-gnu/sys/select.h \
 /usr/include/i386-linux-gnu/bits/select.h \
 /usr/include/i386-linux-gnu/bits/time.h \
 /usr/include/i386-linux-gnu/sys/sysmacros.h \
 /usr/include/i386-linux-gnu/sys/time.h \
 /usr/include/i386-linux-gnu/sys/socket.h \
 /usr/include/i386-linux-gnu/sys/uio.h \
 /usr/include/i386-linux-gnu/bits/uio.h \
 /usr/include/i386-linux-gnu/bits/socket.h \
 /usr/include/i386-linux-gnu/bits/socket_type.h \
 /usr/include/i386-linux-gnu/bits/sockaddr.h \
 /usr/include/i386-linux-gnu/asm/socket.h \
 /usr/include/asm-generic/socket.h \
 /usr/include/i386-linux-gnu/asm/sockios.h \
 /usr/include/asm-generic/sockios.h \
 /usr/include/i386-linux-gnu/sys/file.h /usr/include/fcntl.h \
 /usr/include/i386-linux-gnu/bits/fcntl.h \
 /usr/include/i386-linux-gnu/bits/fcntl-linux.h \
 /usr/include/i386-linux-gnu/bits/stat.h \
 /usr/include/i386-linux-gnu/sys/un.h \
 /usr/include/i386-linux-gnu/sys/mman.h \
 /usr/include/i386-linux-gnu/bits/mman.h \
 /usr/include/i386-linux-gnu/bits/mman-linux.h /usr/include/unistd.h \
 /usr/include/i386-linux-gnu/bits/posix_opt.h \
 /usr/include/i386-linux-gnu/bits/environments.h \
 /usr/include/i386-linux-gnu/bits/confname.h /usr/include/getopt.h \
 /usr/include/errno.h /usr/include/i386-linux-gnu/bits/errno.h \
 /usr/include/linux/errno.h /usr/include/i386-linux-gnu/asm/errno.h \
 /usr/include/asm-generic/errno.h /usr/include/asm-generic/errno-base.h \
 ../machine/interrupt.h ../threads/list.h ../threads/copyright.h \
 ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
 ../threads/system.h ../threads/thread.h ../threads/list.h \
 ../machine/machine.h ../threads/utility.h ../machine/translate.h \
 ../machine/disk.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../machine/timer.h \
 ../machine/interrupt.h ../machine/stats.h ../userprog/pageManager.h \
 ../userprog/bitmap.h ../filesys/openfile.h ../filesys/synchdisk.h \
 ../machine/disk.h ../threads/synch.h ../filesys/fileManager.h \
 ../threads/synchlist.h ../threads/synch.h ../filesys/fileCache.h
stats.o: ../machine/stats.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/utility.h ../threads/copyright.h \
 ../threads/bool.h ../machine/sysdep.h /usr/include/stdio.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../machine/stats.h
timer.o: ../machine/timer.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../machine/timer.h ../threads/utility.h \
 ../threads/copyright.h ../threads/bool.h ../machine/sysdep.h \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../threads/system.h ../threads/utility.h \
 ../threads/thread.h ../threads/list.h ../machine/machine.h \
 ../machine/translate.h ../machine/disk.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h ../threads/scheduler.h \
 ../machine/timer.h ../machine/interrupt.h ../threads/list.h \
 ../machine/stats.h ../userprog/pageManager.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../filesys/synchdisk.h ../machine/disk.h \
 ../threads/synch.h ../filesys/fileManager.h ../threads/synchlist.h \
 ../threads/synch.h ../filesys/fileCache.h
addrspace.o: ../userprog/addrspace.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/system.h ../threads/copyright.h \
 ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../threads/thread.h ../threads/list.h \
 ../machine/machine.h ../threads/utility.h ../machine/translate.h \
 ../machine/disk.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../machine/timer.h \
 ../machine/interrupt.h ../threads/list.h ../machine/stats.h \
 ../userprog/pageManager.h ../userprog/bitmap.h ../filesys/openfile.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../filesys/fileManager.h ../threads/synchlist.h ../threads/synch.h \
 ../filesys/fileCache.h ../userprog/addrspace.h ../bin/noff.h
bitmap.o: ../userprog/bitmap.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../userprog/bitmap.h ../threads/utility.h \
 ../threads/copyright.h ../threads/bool.h ../machine/sysdep.h \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../filesys/openfile.h
exception.o: ../userprog/exception.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/system.h ../threads/copyright.h \
 ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../threads/thread.h ../threads/list.h \
 ../machine/machine.h ../threads/utility.h ../machine/translate.h \
 ../machine/disk.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../machine/timer.h \
 ../machine/interrupt.h ../threads/list.h ../machine/stats.h \
 ../userprog/pageManager.h ../userprog/bitmap.h ../filesys/openfile.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../filesys/fileManager.h ../threads/synchlist.h ../threads/synch.h \
 ../filesys/fileCache.h ../userprog/syscall.h ../threads/thread.h \
 ../filesys/directory.h
progtest.o: ../userprog/progtest.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/system.h ../threads/copyright.h \
 ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../threads/thread.h ../threads/list.h \
 ../machine/machine.h ../threads/utility.h ../machine/translate.h \
 ../machine/disk.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../machine/timer.h \
 ../machine/interrupt.h ../threads/list.h ../machine/stats.h \
 ../userprog/pageManager.h ../userprog/bitmap.h ../filesys/openfile.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../filesys/fileManager.h ../threads/synchlist.h ../threads/synch.h \
 ../filesys/fileCache.h ../machine/console.h ../userprog/addrspace.h \
 ../machine/synchConsole.h ../machine/console.h
console.o: ../machine/console.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../machine/console.h ../threads/utility.h \
 ../threads/copyright.h ../threads/bool.h ../machine/sysdep.h \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../threads/system.h ../threads/utility.h \
 ../threads/thread.h ../threads/list.h ../machine/machine.h \
 ../machine/translate.h ../machine/disk.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h ../threads/scheduler.h \
 ../machine/timer.h ../machine/interrupt.h ../threads/list.h \
 ../machine/stats.h ../userprog/pageManager.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../filesys/synchdisk.h ../machine/disk.h \
 ../threads/synch.h ../filesys/fileManager.h ../threads/synchlist.h \
 ../threads/synch.h ../filesys/fileCache.h
machine.o: ../machine/machine.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../machine/machine.h ../threads/utility.h \
 ../threads/copyright.h ../threads/bool.h ../machine/sysdep.h \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../machine/translate.h ../machine/disk.h \
 ../threads/system.h ../threads/utility.h ../threads/thread.h \
 ../threads/list.h ../machine/machine.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h ../threads/scheduler.h \
 ../machine/timer.h ../machine/interrupt.h ../threads/list.h \
 ../machine/stats.h ../userprog/pageManager.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../filesys/synchdisk.h ../machine/disk.h \
 ../threads/synch.h ../filesys/fileManager.h ../threads/synchlist.h \
 ../threads/synch.h ../filesys/fileCache.h
mipssim.o: ../machine/mipssim.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../machine/machine.h ../threads/utility.h \
 ../threads/copyright.h ../threads/bool.h ../machine/sysdep.h \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../machine/translate.h ../machine/disk.h \
 ../machine/mipssim.h ../threads/system.h ../threads/utility.h \
 ../threads/thread.h ../threads/list.h ../machine/machine.h \
 ../userprog/addrspace.h ../filesys/filesys.h ../filesys/openfile.h \
 ../threads/scheduler.h ../machine/timer.h ../machine/interrupt.h \
 ../threads/list.h ../machine/stats.h ../userprog/pageManager.h \
 ../userprog/bitmap.h ../filesys/openfile.h ../filesys/synchdisk.h \
 ../machine/disk.h ../threads/synch.h ../filesys/fileManager.h \
 ../threads/synchlist.h ../threads/synch.h ../filesys/fileCache.h
translate.o: ../machine/translate.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../machine/machine.h ../threads/utility.h \
 ../threads/copyright.h ../threads/bool.h ../machine/sysdep.h \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../machine/translate.h ../machine/disk.h \
 ../userprog/addrspace.h ../filesys/filesys.h ../filesys/openfile.h \
 ../threads/system.h ../threads/utility.h ../threads/thread.h \
 ../threads/list.h ../machine/machine.h ../threads/scheduler.h \
 ../machine/timer.h ../machine/interrupt.h ../threads/list.h \
 ../machine/stats.h ../userprog/pageManager.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../filesys/synchdisk.h ../machine/disk.h \
 ../threads/synch.h ../filesys/fileManager.h ../threads/synchlist.h \
 ../threads/synch.h ../filesys/fileCache.h
pageManager.o: ../userprog/pageManager.cc /usr/include/stdc-predef.h \
 ../userprog/pageManager.h ../userprog/bitmap.h ../threads/copyright.h \
 ../threads/utility.h ../threads/copyright.h ../threads/bool.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../filesys/openfile.h ../machine/machine.h \
 ../machine/translate.h ../machine/disk.h ../threads/system.h \
 ../threads/utility.h ../threads/thread.h ../threads/list.h \
 ../userprog/addrspace.h ../filesys/filesys.h ../filesys/openfile.h \
 ../threads/scheduler.h ../machine/timer.h ../machine/interrupt.h \
 ../threads/list.h ../machine/stats.h ../userprog/pageManager.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../filesys/fileManager.h ../threads/synchlist.h ../threads/synch.h \
 ../filesys/fileCache.h ../userprog/addrspace.h
synchConsole.o: ../machine/synchConsole.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../machine/synchConsole.h ../threads/utility.h \
 ../threads/copyright.h ../threads/bool.h ../machine/sysdep.h \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../machine/console.h ../threads/synch.h \
 ../threads/thread.h ../threads/utility.h ../threads/list.h \
 ../machine/machine.h ../machine/translate.h ../machine/disk.h \
 ../userprog/addrspace.h ../filesys/filesys.h ../filesys/openfile.h \
 ../threads/system.h ../threads/scheduler.h ../machine/timer.h \
 ../machine/interrupt.h ../threads/list.h ../machine/stats.h \
 ../userprog/pageManager.h ../userprog/bitmap.h ../filesys/openfile.h \
 ../filesys/synchdisk.h ../machine/disk.h ../filesys/fileManager.h \
 ../threads/synchlist.h ../threads/synch.h ../filesys/fileCache.h
directory.o: ../filesys/directory.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/utility.h ../threads/copyright.h \
 ../threads/bool.h ../machine/sysdep.h /usr/include/stdio.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../filesys/filehdr.h ../machine/disk.h \
 ../userprog/bitmap.h ../filesys/openfile.h ../filesys/directory.h \
 ../filesys/openfile.h
filehdr.o: ../filesys/filehdr.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/system.h ../threads/copyright.h \
 ../threads/utility.h ../threads/bool.h ../machine/sysdep.h \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../threads/thread.h ../threads/list.h \
 ../machine/machine.h ../threads/utility.h ../machine/translate.h \
 ../machine/disk.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../machine/timer.h \
 ../machine/interrupt.h ../threads/list.h ../machine/stats.h \
 ../userprog/pageManager.h ../userprog/bitmap.h ../filesys/openfile.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../filesys/fileManager.h ../threads/synchlist.h ../threads/synch.h \
 ../filesys/fileCache.h ../filesys/filehdr.h ../userprog/bitmap.h
filesys.o: ../filesys/filesys.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../machine/disk.h ../threads/utility.h \
 ../threads/copyright.h ../threads/bool.h ../machine/sysdep.h \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../userprog/bitmap.h ../filesys/openfile.h \
 ../filesys/directory.h ../filesys/openfile.h ../filesys/filehdr.h \
 ../filesys/filesys.h ../threads/system.h ../threads/utility.h \
 ../threads/thread.h ../threads/list.h ../machine/machine.h \
 ../machine/translate.h ../machine/disk.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../threads/scheduler.h ../machine/timer.h \
 ../machine/interrupt.h ../threads/list.h ../machine/stats.h \
 ../userprog/pageManager.h ../userprog/bitmap.h ../filesys/synchdisk.h \
 ../threads/synch.h ../filesys/fileManager.h ../threads/synchlist.h \
 ../threads/synch.h ../filesys/fileCache.h
fstest.o: ../filesys/fstest.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../threads/utility.h ../threads/copyright.h \
 ../threads/bool.h ../machine/sysdep.h /usr/include/stdio.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../filesys/filesys.h ../filesys/openfile.h \
 ../threads/system.h ../threads/utility.h ../threads/thread.h \
 ../threads/list.h ../machine/machine.h ../machine/translate.h \
 ../machine/disk.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../threads/scheduler.h ../machine/timer.h ../machine/interrupt.h \
 ../threads/list.h ../machine/stats.h ../userprog/pageManager.h \
 ../userprog/bitmap.h ../filesys/openfile.h ../filesys/synchdisk.h \
 ../machine/disk.h ../threads/synch.h ../filesys/fileManager.h \
 ../threads/synchlist.h ../threads/synch.h ../filesys/fileCache.h \
 ../threads/thread.h
openfile.o: ../filesys/openfile.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../filesys/filehdr.h ../machine/disk.h \
 ../threads/utility.h ../threads/copyright.h ../threads/bool.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../userprog/bitmap.h ../filesys/openfile.h \
 ../filesys/openfile.h ../threads/system.h ../threads/utility.h \
 ../threads/thread.h ../threads/list.h ../machine/machine.h \
 ../machine/translate.h ../machine/disk.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../threads/scheduler.h ../machine/timer.h \
 ../machine/interrupt.h ../threads/list.h ../machine/stats.h \
 ../userprog/pageManager.h ../userprog/bitmap.h ../filesys/synchdisk.h \
 ../threads/synch.h ../filesys/fileManager.h ../threads/synchlist.h \
 ../threads/synch.h ../filesys/fileCache.h
synchdisk.o: ../filesys/synchdisk.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../filesys/synchdisk.h ../machine/disk.h \
 ../threads/utility.h ../threads/copyright.h ../threads/bool.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../threads/synch.h ../threads/thread.h \
 ../threads/utility.h ../threads/list.h ../machine/machine.h \
 ../machine/translate.h ../machine/disk.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h
disk.o: ../machine/disk.cc /usr/include/stdc-predef.h \
 ../threads/copyright.h ../machine/disk.h ../threads/utility.h \
 ../threads/copyright.h ../threads/bool.h ../machine/sysdep.h \
 /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../threads/system.h ../threads/utility.h \
 ../threads/thread.h ../threads/list.h ../machine/machine.h \
 ../machine/translate.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h ../threads/scheduler.h ../machine/timer.h \
 ../machine/interrupt.h ../threads/list.h ../machine/stats.h \
 ../userprog/pageManager.h ../userprog/bitmap.h ../filesys/openfile.h \
 ../filesys/synchdisk.h ../machine/disk.h ../threads/synch.h \
 ../filesys/fileManager.h ../threads/synchlist.h ../threads/synch.h \
 ../filesys/fileCache.h
fileManager.o: ../filesys/fileManager.cc /usr/include/stdc-predef.h \
 ../filesys/fileManager.h ../threads/synchlist.h ../threads/copyright.h \
 ../threads/list.h ../threads/utility.h ../threads/bool.h \
 ../machine/sysdep.h ../threads/copyright.h /usr/include/stdio.h \
 /usr/include/features.h /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../threads/synch.h ../threads/thread.h \
 ../machine/machine.h ../threads/utility.h ../machine/translate.h \
 ../machine/disk.h ../userprog/addrspace.h ../filesys/filesys.h \
 ../filesys/openfile.h
fileCache.o: ../filesys/fileCache.cc /usr/include/stdc-predef.h \
 ../filesys/fileCache.h ../machine/disk.h ../threads/copyright.h \
 ../threads/utility.h ../threads/copyright.h ../threads/bool.h \
 ../machine/sysdep.h /usr/include/stdio.h /usr/include/features.h \
 /usr/include/i386-linux-gnu/sys/cdefs.h \
 /usr/include/i386-linux-gnu/bits/wordsize.h \
 /usr/include/i386-linux-gnu/gnu/stubs.h \
 /usr/include/i386-linux-gnu/gnu/stubs-32.h \
 /usr/lib/gcc/i686-linux-gnu/4.8/include/stddef.h \
 /usr/include/i386-linux-gnu/bits/types.h \
 /usr/include/i386-linux-gnu/bits/typesizes.h /usr/include/libio.h \
 /usr/include/_G_config.h /usr/include/wchar.h ../threads/stdarg.h \
 /usr/include/i386-linux-gnu/bits/stdio_lim.h \
 /usr/include/i386-linux-gnu/bits/sys_errlist.h /usr/include/string.h \
 /usr/include/xlocale.h ../threads/system.h ../threads/utility.h \
 ../threads/thread.h ../threads/list.h ../machine/machine.h \
 ../machine/translate.h ../machine/disk.h ../userprog/addrspace.h \
 ../filesys/filesys.h ../filesys/openfile.h ../threads/scheduler.h \
 ../machine/timer.h ../machine/interrupt.h ../threads/list.h \
 ../machine/stats.h ../userprog/pageManager.h ../userprog/bitmap.h \
 ../filesys/openfile.h ../filesys/synchdisk.h ../threads/synch.h \
 ../filesys/fileManager.h ../threads/synchlist.h ../threads/synch.h \
 ../filesys/fileCache.h
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
