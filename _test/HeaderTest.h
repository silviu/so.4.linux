#ifndef _HEADERTEST_H_
#define _HEADERTEST_H_

//////////////INCLUDE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "Constante.h"


//////////////PENTRU TESTE
int Verifica(int e,int s,int w,int x,int q00,int q11);
void IncNrX();
void DecNrX();
int GetNrX();
void ResetNrX();
void SetNrCond(int nrCond);
void FreeNrCond(int nrCond);
int VerificaTotalW(int TotalW);
int VerificaRW(int r, int w);
int VerificaW(int w);
int VerificaR(int r);
int VerificaMult(int e, int s, int w, int x, int *q);
int* AllOnes(int n);
int* SomeOnes(int n, int p);
int* AllocSpec(int n, int pozToSet, ...);

typedef void Monitor;
/////////////EXPORTATE DE LibMonitor.lib
Monitor* Create(int conditions,char policy);
int Enter(Monitor *m);
int Leave(Monitor *m);
int Wait(Monitor *m, int cond);
int Signal(Monitor *m, int cond);
int Broadcast(Monitor *m, int cond);
int Destroy(Monitor *m);

////////////EXPORTATE DE LibRW.lib
Monitor* CreateRWMonitor();
int GetNrConds();
void StartCit(Monitor* m);
void StopCit(Monitor *m);
void StartScrit(Monitor* m);
void StopScrit(Monitor *m);
void ResetScritCit();


////////////MONITORUL
static Monitor *m ;

///////////MACRO TEST
#define testAndMightFail(s, t, f) \
do {\
	int i;\
	int r=(t);\
	\
    if (!(f) || (!r && (f))) \
    { \
        printf("test: %s", s); \
	    fflush(stdout);\
	    for(i=0; i<60-strlen(s); i++)\
		    putchar('.');\
	    if (!r)\
	        printf("failed\n");\
	    else\
		    printf("passed\n");\
	    fflush(stdout);\
        if (f) \
            exit(-1); \
    } \
} while (0)

#define test(s, t) testAndMightFail(s, t, 0);
#define testAndFail(s, t) testAndMightFail(s, t, 1);

#endif

