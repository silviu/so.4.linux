#include "HeaderTest.h"

void IesireDinSignal4()
{
	if(GetNrX()==4)
	{
		sleep(1);
		test("Verifica6",Verifica(1,1,0,4,0,0)==0);
		IncNrX();
		Leave(m);
		return;
	}
	if(GetNrX()==5)
	{
		sleep(1);
		test("Verifica7",Verifica(1,0,0,5,0,0)==0);
		IncNrX();
		Leave(m);
		return;
	}
}
void IesireDinWait4()
{
	if(GetNrX()==0)
	{
		sleep(1);
		test("Verifica2",Verifica(1,1,2,0,0,0)==0);
		IncNrX();
		Wait(m,0);
		IesireDinWait4();
		return;
	}
	if(GetNrX()==1)
	{
		sleep(1);
		test("Verifica3",Verifica(1,1,1,1,1,0)==0);
		IncNrX();
		Signal(m,0);
		IesireDinSignal4();
		return;
	}
	if(GetNrX()==2)
	{
		sleep(1);
		test("Verifica4",Verifica(1,2,1,2,0,0)==0);
		IncNrX();
		Leave(m);
		return;
	}
	if(GetNrX()==3)
	{
		sleep(1);
		test("Verifica5",Verifica(1,2,0,3,0,0)==0);
		IncNrX();
		Leave(m);
		return;
	}
}
void* Functie4ABC(void *params)
{
	Enter(m);
	Wait(m,0);
	IesireDinWait4();
		
	return NULL;
}
void* Functie4D(void *params)
{
	sleep(1);
	Enter(m);
	sleep(2);
	test("Verifica1",Verifica(1,0,0,0,3,0)==0);
	Broadcast(m,0);
	IesireDinSignal4();	
		
	return NULL;
}
void* Functie4E(void *params)
{
	sleep(2);
	Enter(m);
	sleep(1);
	test("Verifica8",Verifica(0,0,0,6,0,0)==0);
	Signal(m,0);
	sleep(1);
	test("Verifica9",Verifica(0,0,0,6,0,0)==0);
	Leave(m);
		
	return NULL;
}
void Test4()
{
	pthread_t a,b,c,d,e;
	
	m=Create(2,SIGNAL_AND_WAIT);
	test("Create",m!=NULL);
	SetNrCond(1);
	ResetNrX();
	
	if (pthread_create(&a, NULL, &Functie4ABC,NULL) ) 
	{
		perror("ERR test.c ;la crearea fir a;NAT\n;");
		exit(1);
	}
	if (pthread_create(&b, NULL, &Functie4ABC,NULL)) 
	{
		perror("ERR test.c ;la crearea fir b;NAT\n;");
		exit(1);
	}
	if (pthread_create(&c, NULL, &Functie4ABC,NULL) ) 
	{
		perror("ERR test.c ;la crearea fir c;NAT\n;");
		exit(1);
	}
	if (pthread_create(&d, NULL, &Functie4D,NULL)) 
	{
		perror("ERR test.c ;la crearea fir d;NAT\n;");
		exit(1);
	}
	if (pthread_create(&e, NULL, &Functie4E,NULL)) 
	{
		perror("ERR test.c ;la crearea fir e;NAT\n;");
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
	if (pthread_join(e, NULL))
	{
		perror("ERR test;asteptarea fir d");
		exit(1);
	}
	
	FreeNrCond(1);
	test("Destroy",Destroy(m)==0);
}


