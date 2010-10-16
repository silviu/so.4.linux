/*
 * Thread-urile sunt organizate in inel (ring). Thread-ul t asteapta sa fie semnalizat de t-1 si va semnaliza
 * pe thread-ul t+1. Se fac ROUNDS runde.
 */
#include "HeaderTest.h"

#define NUM_THREADS 100
#define ROUNDS 20

static void* FunctieTestRing(void *param)
{
    int t = *(int*)param, i, j;
    int *q;
    char buf[1024];

    Enter(m);
    Wait(m, NUM_THREADS);

    for (i = 0; i < ROUNDS; i++)
    {
        snprintf(buf, 1024, "T%d (round %d) verifica thread-uri in asteptare (I)", t, i);

        if (i > 0) 
        {
			q = (int*) calloc(NUM_THREADS + 1, sizeof(int));
			for (j = 0; j < NUM_THREADS; j++)
				if (j != t && j != ((t+1) % NUM_THREADS))
					q[j] = 1;
            testAndFail(buf, VerificaMult(0, 0, 1, 0, q) == 0);
            free(q);
        }

        Wait(m, t);

        snprintf(buf, 1024, "T%d (round %d) verifica thread-uri in asteptare (II)", t, i);

        if (i != ROUNDS - 1) 
        {
            q = (int*) calloc(NUM_THREADS + 1, sizeof(int));
			for (j = 0; j < NUM_THREADS; j++)
				if (j != t)
					q[j] = 1;
            testAndFail(buf, VerificaMult(0, 0, 0, 0, q) == 0);
			free(q);
        }
        else
        {
			q = (int*) calloc(NUM_THREADS + 1, sizeof(int));
			for (j = t+1; j < NUM_THREADS + 1; j++)
					q[j] = 1;
            q[NUM_THREADS] = 0;
            testAndFail(buf, VerificaMult(0, 0, 0, 0, q) == 0);
			free(q);
        }
		
		// Ultimul thread nu mai are de ce sa dea signal la ultima runda; e un signal dat in gol
		if (i != ROUNDS - 1 || t != NUM_THREADS-1)
			Signal(m, (t+1) % NUM_THREADS);
    }

    Leave(m);

    return NULL;
}


void TestRing() 
{
    pthread_t t[NUM_THREADS];
    int params[NUM_THREADS];
    int i, *q;

    ResetNrX();
    m = Create(NUM_THREADS + 1, SIGNAL_AND_CONTINUE);
    test("Create", m != NULL);

    SetNrCond(NUM_THREADS + 1);

    for (i = 0; i < NUM_THREADS; i++)
    {
        params[i] = i;
        if (pthread_create(t+i, NULL, &FunctieTestRing,&params[i]))
        {
            perror("ERR testRing.c ;la crearea fir;NAT\n;");
            exit(1);
        }
    }

    // Lasam timp pt. ca toate thread-urile sa fie create, si sa intre in monitor, in starea "waiting"
    sleep(5);
	q = (int*) calloc(NUM_THREADS + 1, sizeof(int));
	q[NUM_THREADS] = NUM_THREADS;
    test("Toate thread-urile asteapta sa fie pornite", VerificaMult(0, 0, 0, 0, q) == 0);
    free(q);
    
    // Pornim toate thread-urile
    Enter(m);
    Broadcast(m, NUM_THREADS);
	q = (int*) calloc(NUM_THREADS + 1, sizeof(int));
    test("Toate thread-urile mutate in coada waiting", VerificaMult(0, 0, NUM_THREADS, 0, q) == 0);
    free(q);
    Leave(m);

    // Lasam timp sa fie planificate toate thread-urile o data, astfel incat fiecare sa astepte la variabila
    // de conditie asociata
    sleep(5);

    // Semnalizam primul thread, declansand o reactie in lant
    Enter(m);
    Signal(m, 0);
    Leave(m);

    for (i = 0; i < NUM_THREADS; i++)
    {
        if (pthread_join(t[i], NULL))
        {
            perror("Eroare la asteptarea unui fir\n");
            exit(1);
        }
    }

    // Daca am ajuns pana aici, inseamna ca au fost trecute toate testele
    test("Starea monitorului in pasii intermediari", 0 == 0);
    
    test("Destroy", Destroy(m) == 0);

    FreeNrCond(NUM_THREADS + 1);
}

