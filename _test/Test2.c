#include "HeaderTest.h"

void* FunctieA(void *params)
{
	Enter(m);
	sleep(2);
	test("FunctiaA", Verifica(1,0,0,0,0,0)==0);
	Leave(m);
	
	return NULL;
}
void* FunctieB(void *params)
{
	sleep(1);
	Enter(m);
	sleep(1);
	test("FunctiaB", Verifica(0,0,0,0,0,0)==0);
	Leave(m);
	
	return NULL;
}
void Test2()//mini
{	
	pthread_t a,b;
	m=Create(1,SIGNAL_AND_WAIT);
	test("Create",m!=NULL);
	
	if (pthread_create(&a, NULL, &FunctieA,NULL)) 
	{
		perror("ERR test.c ;la crearea fir a;NAT\n;");
		exit(1);
	}
	if (pthread_create(&b, NULL, &FunctieB,NULL)) 
	{
		perror("ERR test.c ;la crearea fir b;NAT\n;");
		exit(1);
	}
	
	if (pthread_join(a, NULL))
	{
		perror("ERR RW ;asteptarea fir a");
		exit(1);
	}
	
	if (pthread_join(b, NULL))
	{
		perror("ERR RW ;asteptarea fir b");
		exit(1);
	}
	
	test("Destroy",Destroy(m)==0);
}


