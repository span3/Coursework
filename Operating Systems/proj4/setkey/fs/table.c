/* This file contains the table used to map system call numbers onto the
 * routines that perform them.
 */

#define _TABLE

#include "fs.h"
#include <minix/callnr.h>
#include <minix/com.h>
#include "file.h"
#include "fproc.h"
#include "lock.h"
#include "scratchpad.h"
#include "vnode.h"
#include "vmnt.h"

PUBLIC _PROTOTYPE (int (*call_vec[]), (void) ) = {

		do_setkey,	/* 0 = (setkey) */ /*CMPS 111 Project 4*/
		no_sys,		/*  1 = (exit)	*/
		no_sys,		/*  2 = (fork)	*/
		do_read,	/*  3 = read	*/
		do_write,	/*  4 = write	*/
		do_open,	/*  5 = open	*/
		do_close,	/*  6 = close	*/
		no_sys,		/*  7 = wait	*/
		do_creat,	/*  8 = creat	*/
		do_link,	/*  9 = link	*/
		do_unlink,	/* 10 = unlink	*/
		no_sys,		/* 11 = waitpid	*/
		do_chdir,	/* 12 = chdir	*/
		no_sys,		/* 13 = time	*/
		do_mknod,	/* 14 = mknod	*/
		do_chmod,	/* 15 = chmod	*/
		do_chown,	/* 16 = chown	*/
		no_sys,		/* 17 = break	*/
		do_stat,	/* 18 = stat    */
		do_lseek,	/* 19 = lseek	*/
		no_sys,		/* 20 = getpid	*/
		do_mount,	/* 21 = mount	*/
		do_umount,	/* 22 = umount	*/
		no_sys,		/* 23 = setuid  */
		no_sys,		/* 24 = getuid	*/
		no_sys,		/* 25 = stime	*/
		no_sys,		/* 26 = ptrace	*/
		no_sys,		/* 27 = alarm	*/
		do_fstat,	/* 28 = fstat   */
		no_sys,		/* 29 = pause	*/
		do_utime,	/* 30 = utime	*/
		no_sys,		/* 31 = (stty)	*/
		no_sys,		/* 32 = (gtty)	*/
		do_access,	/* 33 = access	*/
		no_sys,		/* 34 = (nice)	*/
		no_sys,		/* 35 = (ftime)	*/
		do_sync,	/* 36 = sync	*/
		no_sys,		/* 37 = kill	*/
		do_rename,	/* 38 = rename	*/
		do_mkdir,	/* 39 = mkdir	*/
		do_unlink,	/* 40 = rmdir	*/
		do_dup,		/* 41 = dup	*/
		do_pipe,	/* 42 = pipe	*/
		no_sys,		/* 43 = times	*/
		no_sys,		/* 44 = (prof)	*/
		do_slink,	/* 45 = symlink	*/
		no_sys,		/* 46 = setgid  */
		no_sys,		/* 47 = getgid	*/
		no_sys,		/* 48 = (signal)*/
		do_rdlink,	/* 49 = readlink*/
		do_lstat,	/* 50 = lstat   */
		no_sys, 	/* 51 = (acct)	*/
		no_sys, 	/* 52 = (phys)	*/
		no_sys,	    /* 53 = (lock)	*/
		do_ioctl,	/* 54 = ioctl	*/
		do_fcntl,	/* 55 = fcntl	*/
		no_sys,		/* 56 = (mpx)	*/
		no_sys, 	/* 57 = unused */
		no_sys,		/* 58 = unused	*/
		do_exec,	/* 59 = execve  */
		do_umask,	/* 60 = umask	*/
		do_chroot,	/* 61 = chroot	*/
		no_sys,		/* 62 = setsid  */
		no_sys,		/* 63 = getpgrp */
		
		no_sys,		/* 64 = KSIG: signals originating in the kernel*/
		do_unpause,	/* 65 = UNPAUSE */
		no_sys, 	/* 66 = unused  */
		do_revive,	/* 67 = REVIVE  */
		no_sys,		/* 68 = TASK_REPLY	*/
		no_sys,		/* 69 = unused  */
		no_sys,		/* 70 = unused  */
		no_sys,		/* 71 = si */
		no_sys,		/* 72 = sigsuspend */
		no_sys,		/* 73 = sigpending */
		no_sys,		/* 74 = sigprocmask */
		no_sys,		/* 75 = sigreturn */
		no_sys,		/* 76 = reboot */
		do_svrctl,	/* 77 = svrctl */
		
		no_sys,		/* 78 = unused */
		do_getsysinfo,		/* 79 = getsysinfo */
		no_sys,	/* 80 = unused */
		do_devctl,	/* 81 = devctl */
		do_fstatfs,	/* 82 = fstatfs */
		no_sys,		/* 83 = memalloc */
		no_sys,		/* 84 = memfree */
		do_select,	/* 85 = select */
		do_fchdir,	/* 86 = fchdir */
		do_fsync,	/* 87 = fsync */
		no_sys,		/* 88 = getpriority */
		no_sys,		/* 89 = setpriority */
		no_sys,		/* 90 = gettimeofday */
		no_sys,		/* 91 = seteuid */
		no_sys,		/* 92 = setegid */
		do_truncate,	/* 93 = truncate */
		do_ftruncate,	/* 94 = truncate */
};
/* This should not fail with "array size is negative": */
extern int dummy[sizeof(call_vec) == NCALLS * sizeof(call_vec[0]) ? 1 : -1];
