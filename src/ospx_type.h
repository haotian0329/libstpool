#ifndef __OSPX_TYPE_H__
#define __OSPX_TYPE_H__

/* piggy_xrh@163.com */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN   // Exclude rarely-used stuff from Windows headers

#include <sys/timeb.h>
#include <windows.h>
#include <winsock2.h>
#include <process.h>


typedef __int8  int8_t;
typedef __int16 int16_t;
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int8  uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;
typedef int mode_t;
typedef long off_t;
typedef int ssize_t;
typedef long in_addr_t;
#define AF_LOCAL AF_INET

struct timezone {
	int tz_minuteswest;     /* minutes west of Greenwich */
	int tz_dsttime;         /* type of DST correction */
};

/* NOTE: The theory is from libevent */
typedef struct {
	ssize_t n_waiting, n_to_wake, generation;
	CRITICAL_SECTION section;
	HANDLE  hEvent;
} OSPX_pthread_cond_t;

typedef struct {
	int magic;
	CRITICAL_SECTION section;
	int waiters;
	int cakes;
	HANDLE  hSem;
} OSPX_sem_t;

/* NOTE: The theory is from UNIX Network Programming (version2) */
typedef struct {
	CRITICAL_SECTION rw_mut;
	OSPX_pthread_cond_t rw_condreaders;
	OSPX_pthread_cond_t rw_condwriters;
	int  rw_magic, rw_ref;
	int  rw_nwaitreaders, rw_nwaitwriters;
} OSPX_pthread_rwlock_t;

typedef struct {
	HANDLE   h;
	uint64_t error;	
	char *errprefix;
	uint16_t errprefix_bufflen;
	uint16_t f_ltls:1;
	uint16_t f_resv:15;
} OSPX_tls_t;

typedef DWORD  OSPX_pthread_key_t;
typedef HANDLE OSPX_pthread_t;
typedef CRITICAL_SECTION OSPX_pthread_mutex_t;

#else
#include <stdint.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>        
#include <fcntl.h>

typedef struct {
	uint64_t error;
	char *errprefix;
	uint16_t errprefix_bufflen;
	uint16_t f_ltls:1;
	uint16_t f_resv:15;
} OSPX_tls_t;

typedef pthread_key_t OSPX_pthread_key_t;
typedef pthread_t OSPX_pthread_t;
typedef pthread_mutex_t OSPX_pthread_mutex_t;
typedef pthread_cond_t  OSPX_pthread_cond_t;
typedef pthread_rwlock_t OSPX_pthread_rwlock_t;
typedef sem_t OSPX_sem_t;

#endif

#endif
