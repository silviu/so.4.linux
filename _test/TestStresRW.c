#include "HeaderTest.h"

#define NRR 	60
#define NRW		20
#define NR_ITERATII	200
#define TIME_INSIDE 5000 // 5 ms inside
#define TIME_OUTSIDE_W 15000 // 15 ms outside - ca sa nu fie starvation pt. readeri
int var;    // variabila pe care o incrementam din writer-i si o accesam din readeri

static void* FunctieR(void *params)
{
	int i=0;
	for(i=0;i<NR_ITERATII;i++)
	{
		StartCit(m);
        testAndFail("Reader VerificaW", VerificaW(0) == 0);
        testAndFail("Reader VerificaTotalW", VerificaTotalW(var) == 0);
		StopCit(m);
	}

	return NULL;
}

static void* FunctieW(void *params)
{
	int i=0;

	for(i=0;i<NR_ITERATII;i++)
	{
		StartScrit(m);
        ++var;
        testAndFail("Writer VerificaTotalW", VerificaTotalW(var) == 0);
        testAndFail("Writer VerificaW", VerificaW(1) == 0);
        testAndFail("Writer VerificaR", VerificaR(0) == 0);
		StopScrit(m);
        usleep(TIME_OUTSIDE_W);
	}


	return NULL;
}

static int Test()
{
	pthread_t r[NRR], w[NRW];

    var = 0;
	
	int i=0;
	for(i=0;i<NRR;i++)
	{
		if (pthread_create(r+i, NULL, &FunctieR,NULL)) 
		{
			perror("ERR testStres.c ;la crearea fir r;NAT\n;");
			exit(1);
		}
	}
	for(i=0;i<NRW;i++)
	{
		if (pthread_create(w+i, NULL, &FunctieW,NULL)) 
		{
			perror("ERR testStres.c ;la crearea fir w;NAT\n;");
			exit(1);
		}
	}

	for(i=0;i<NRR;i++)
	{
		if (pthread_join(r[i], NULL))
		{
			perror("ERR RW ;asteptarea fir r");
			exit(1);
		}
	}
	for(i=0;i<NRW;i++)
	{
		if (pthread_join(w[i], NULL))
		{
			perror("ERR RW ;asteptarea fir w");
			exit(1);
		}
	}

	return 0;
	
}

void TestStresRW()
{
    ResetScritCit();
	m=CreateRWMonitor();
	SetNrCond(GetNrConds());
	test("Verifica stress RW",Test()==0);
	FreeNrCond(GetNrConds());
	Destroy(m);
		
}

