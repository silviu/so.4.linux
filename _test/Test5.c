#include "HeaderTest.h"

void IesireDinWaiting5()
{
	if(GetNrX()==0)
	{
		sleep(1);
		test("Verifica4",Verifica(1,0,1,0,0,1)==0);
		IncNrX();
		Signal(m,1);
		sleep(1);
		test("Verifica5",Verifica(1,0,2,1,0,0)==0);
		Leave(m);
		return;
	}
	if(GetNrX()==1)
	{
		sleep(1);
		test("Verifica6",Verifica(1,0,1,1,0,0)==0);
		IncNrX();
		Leave(m);
		return;
	}
	if(GetNrX()==2)
	{
		sleep(1);
		test("Verifica7",Verifica(1,0,0,2,0,0)==0);
		IncNrX();
		Leave(m);
		return;
	}
}

void* Functie5A(void *params)
{
	Enter(m);
	Wait(m,1);
	IesireDinWaiting5();
			
	return NULL;
}
void* Functie5B(void *params)
{
	Enter(m);
	Wait(m,0);
	IesireDinWaiting5();
			
	return NULL;
}
void* Functie5C(void *params)
{
	sleep(1);
	Enter(m);
	sleep(2);
	test("Verifica1",Verifica(1,0,0,0,1,1)==0);
	Signal(m,0);
	sleep(1);
	test("Verifica2",Verifica(1,0,1,0,0,1)==0);
	Signal(m,1);
	sleep(1);
	test("Verifica3",Verifica(1,0,2,0,0,0)==0);
	Wait(m,1);
	IesireDinWaiting5();
			
	return NULL;
}
void* Functie5D(void *params)
{
	sleep(2);
	Enter(m);
	sleep(1);
	test("Verifica8",Verifica(0,0,0,3,0,0)==0);
	Signal(m,1);
	sleep(1);
	test("Verifica9",Verifica(0,0,0,3,0,0)==0);
	Leave(m);
	
	return NULL;
}

void Test5()
{
	m=Create(2,SIGNAL_AND_CONTINUE);
	test("Create",m!=NULL);
	SetNrCond(2);
	ResetNrX();
	
	pthread_t a,b,c,d;
	
	if (pthread_create(&a, NULL, &Functie5A,NULL) ) 
	{
		perror("ERR test.c ;la crearea fir a;NAT\n;");
		exit(1);
	}
	if (pthread_create(&b, NULL, &Functie5B,NULL)) 
	{
		perror("ERR test.c ;la crearea fir b;NAT\n;");
		exit(1);
	}
	if (pthread_create(&c, NULL, &Functie5C,NULL) ) 
	{
		perror("ERR test.c ;la crearea fir c;NAT\n;");
		exit(1);
	}
	if (pthread_create(&d, NULL, &Functie5D,NULL)) 
	{
		perror("ERR test.c ;la crearea fir d;NAT\n;");
		exit(1);
	}
	
	if (pthread_join(a, NULL))
	{
		perror("ERR test ;asteptarea fir a");
		exit(1);
	}
	
	if (pthread_join(b, NULL))
	{
		perror("ERR test;asteptarea fir b");
		exit(1);
	}
	if (pthread_join(c, NULL))
	{
		perror("ERR test;asteptarea fir c");
		exit(1);
	}
	
	if (pthread_join(d, NULL))
	{
		perror("ERR test;asteptarea fir d");
		exit(1);
	}
	
	FreeNrCond(2);
	test("Destroy",Destroy(m)==0);
}



