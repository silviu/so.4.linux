#include "HeaderTest.h"

//==============================================TEST1==============================================================
static void* Functie1ABC(void *params)
{
	StartCit(m);
	sleep(2);
	test("Verifica1/2/3",VerificaRW(3,0)==0);
	sleep(1);
	StopCit(m);
	
	return NULL;
}
static void Test1()
{
	pthread_t a,b,c;
	
	if (pthread_create(&a, NULL, &Functie1ABC,NULL)) 
	{
		perror("ERR test.c ;la crearea fir a;NAT\n;");
		exit(1);
	}
	if (pthread_create(&b, NULL, &Functie1ABC,NULL)) 
	{
		perror("ERR test.c ;la crearea fir b;NAT\n;");
		exit(1);
	}
	if (pthread_create(&c, NULL, &Functie1ABC,NULL)) 
	{
		perror("ERR test.c ;la crearea fir c;NAT\n;");
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
	if (pthread_join(c, NULL))
	{
		perror("ERR RW ;asteptarea fir c");
		exit(1);
	}
	

}
//==============================================endTEST1==============================================================
//==============================================TEST2==============================================================
static void* Functie2A(void *params)
{
	StartScrit(m);
	sleep(4);
	test("Verifica3",VerificaRW(0,1)==0);
	StopScrit(m);
	
	return NULL;
}
static void* Functie2BC(void *params)
{
	sleep(1);
	test("Verifica1/2",VerificaRW(0,1)==0);
	StartCit(m);
	test("Verifica4/5",VerificaW(0)==0);
	sleep(1);
	test("Verifica6/7",VerificaRW(2,0)==0);
	sleep(1);
	StopCit(m);
	return NULL;
}


static void Test2()
{
	pthread_t a,b,c;
	
	if (pthread_create(&a, NULL, &Functie2A,NULL)) 
	{
		perror("ERR test.c ;la crearea fir a;NAT\n;");
		exit(1);
	}
	if (pthread_create(&b, NULL, &Functie2BC,NULL)) 
	{
		perror("ERR test.c ;la crearea fir b;NAT\n;");
		exit(1);
	}
	if (pthread_create(&c, NULL, &Functie2BC,NULL)) 
	{
		perror("ERR test.c ;la crearea fir c;NAT\n;");
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
	if (pthread_join(c, NULL))
	{
		perror("ERR RW ;asteptarea fir c");
		exit(1);
	}
	

}
//==============================================endTEST2==============================================================
//==============================================TEST3==============================================================
static void* Functie3AB(void *params)
{
	StartScrit(m);
	sleep(1);
	test("Verifica1/2",VerificaRW(0,1)==0);
	StopScrit(m);
	return NULL;
}

static void Test3()
{
	pthread_t a,b;
	
	if (pthread_create(&a, NULL, &Functie3AB,NULL)) 
	{
		perror("ERR test.c ;la crearea fir a;NAT\n;");
		exit(1);
	}
	if (pthread_create(&b, NULL, &Functie3AB,NULL)) 
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


}
//==============================================endTEST3==============================================================
//==============================================TEST4==============================================================
static void* Functie4ABC(void *params)
{
	StartCit(m);
	sleep(3);
	test("Verifica1/2/3",VerificaRW(3,0)==0);
	sleep(1);
	StopCit(m);
	return NULL;
}
static void* Functie4DE(void *params)
{
	sleep(1);
	StartScrit(m);
	test("Verifica4/5",VerificaR(0)==0);
	sleep(1);
	test("Verifica4/5",VerificaRW(0,1)==0);
	sleep(1);
	StopScrit(m);
	return NULL;
}
static void Test4()
{
	pthread_t a,b,c,d,e;
	
	if (pthread_create(&a, NULL, &Functie4ABC,NULL)) 
	{
		perror("ERR test.c ;la crearea fir a;NAT\n;");
		exit(1);
	}
	if (pthread_create(&b, NULL, &Functie4ABC,NULL)) 
	{
		perror("ERR test.c ;la crearea fir b;NAT\n;");
		exit(1);
	}
	if (pthread_create(&c, NULL, &Functie4ABC,NULL)) 
	{
		perror("ERR test.c ;la crearea fir c;NAT\n;");
		exit(1);
	}
	if (pthread_create(&d, NULL, &Functie4DE,NULL)) 
	{
		perror("ERR test.c ;la crearea fir d;NAT\n;");
		exit(1);
	}
	if (pthread_create(&e, NULL, &Functie4DE,NULL)) 
	{
		perror("ERR test.c ;la crearea fir e;NAT\n;");
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
	if (pthread_join(c, NULL))
	{
		perror("ERR RW ;asteptarea fir c");
		exit(1);
	}
	if (pthread_join(d, NULL))
	{
		perror("ERR RW ;asteptarea fir d");
		exit(1);
	}
	if (pthread_join(e, NULL))
	{
		perror("ERR RW ;asteptarea fir e");
		exit(1);
	}
	


}
//==============================================endTEST4==============================================================
//==============================================TEST5==============================================================
static void* Functie5AB(void *params)
{
	StartScrit(m);
	sleep(3);
	test("Verifica5/6",VerificaRW(0,1)==0);
	sleep(1);
	StopScrit(m);
	return NULL;
}
static void* Functie5CDEF(void *params)
{
	sleep(1);
	test("Verific1/2/3/4",VerificaRW(0,1)==0);
	StartCit(m);
	test("Verifica7/8/9/10",VerificaW(0)==0);
	sleep(2);
	test("Verifica11/12/13/14",VerificaRW(4,0)==0);
	sleep(1);
	StopCit(m);
	return NULL;
}
static void Test5()
{
	pthread_t a,b,c,d,e,f;
	
	if (pthread_create(&a, NULL, &Functie5AB,NULL)) 
	{
		perror("ERR test.c ;la crearea fir a;NAT\n;");
		exit(1);
	}
	if (pthread_create(&b, NULL, &Functie5AB,NULL)) 
	{
		perror("ERR test.c ;la crearea fir b;NAT\n;");
		exit(1);
	}
	if (pthread_create(&c, NULL, &Functie5CDEF,NULL)) 
	{
		perror("ERR test.c ;la crearea fir c;NAT\n;");
		exit(1);
	}
	if (pthread_create(&d, NULL, &Functie5CDEF,NULL)) 
	{
		perror("ERR test.c ;la crearea fir d;NAT\n;");
		exit(1);
	}
	if (pthread_create(&e, NULL, &Functie5CDEF,NULL)) 
	{
		perror("ERR test.c ;la crearea fir e;NAT\n;");
		exit(1);
	}
	if (pthread_create(&f, NULL, &Functie5CDEF,NULL)) 
	{
		perror("ERR test.c ;la crearea fir f;NAT\n;");
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
	if (pthread_join(c, NULL))
	{
		perror("ERR RW ;asteptarea fir c");
		exit(1);
	}
	if (pthread_join(d, NULL))
	{
		perror("ERR RW ;asteptarea fir d");
		exit(1);
	}
	if (pthread_join(e, NULL))
	{
		perror("ERR RW ;asteptarea fir e");
		exit(1);
	}
	if (pthread_join(f, NULL))
	{
		perror("ERR RW ;asteptarea fir f");
		exit(1);
	}


}
//==============================================endTEST5==============================================================
void TestRW()
{
	m=CreateRWMonitor();
	SetNrCond(GetNrConds());

	printf("\n======TESTE RW=====\n");
	printf("\n=====TEST1========\n");
	Test1();
	printf("\n=====TEST2========\n");
	Test2();
	printf("\n=====TEST3========\n");
	Test3();
	printf("\n=====TEST4========\n");
	Test4();
	printf("\n=====TEST5========\n");
	Test5();
	printf("\n\n\n");

	FreeNrCond(GetNrConds());
	Destroy(m);
	
	
}

