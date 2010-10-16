/* Test pentru monitor de tipul SIGNAL_AND_WAIT. Thread-urile sunt aranjate intr-un arbore binar complet
 * de inaltime HEIGHT. Radacina face broadcast catre fiii sai, acestia fac broadcast mai departe, samd.
 * Frunzele incrementeaza o variabila.
 *
 * Cand un thread termina de asteptat, se verifica faptul ca toti stramosii lui din arbore au terminat de asteptat.
 */

#define HEIGHT 7
#define NUM_THREADS ((1 << HEIGHT) - 1)
#define NUM_CONDS (1 << (HEIGHT-1))

#include "HeaderTest.h"

static int test_var = 0;
static int waited[NUM_THREADS];
static int signaled[NUM_THREADS];

// Intoarce nivelul thread-ului cu indicele t
static int GetLevel(int t)
{
    if (t == 0)
        return 1;

    return GetLevel((t-1)/2) + 1;
}

// Testeaza faptul ca toti stramosii lui t au terminat de asteptat
static void TestAncestorsWaited(int t)
{
    char buf[1024];
    int ancestor = t;

    while (ancestor >= 0)
    {
        snprintf(buf, 1024, "Ancestor %d of %d has finished waiting", ancestor, t);
        testAndFail(buf, waited[ancestor] == 1);

        if (ancestor == 0)
            ancestor = -1;
        else
            ancestor = (ancestor-1)/2;
    }
}

static int* CoziAsteptare()
{
    int *result = (int*) calloc(sizeof(int), NUM_CONDS);
    int i;

    for (i = 1; i < NUM_THREADS; i++)
        if (!signaled[(i-1)/2])
            result[(i+1)/2]++;

    return result;
}

static int Waiting()
{
    int i, cnt = 0;

    for (i = 0; i < NUM_THREADS; i++)
        if (signaled[i])
            cnt += (2 - waited[2 * i + 1] - waited[2 * i + 2]);

    return cnt;
}

static int Signaler()
{
    int i, cnt = 0;
    for (i = 0; i < NUM_THREADS; i++)
        cnt += signaled[i];
    return cnt;
}

static void* FunctieTestTree(void *param)
{
    int t = *(int*)param;
    int level = GetLevel(t);

    Enter(m);
    if (level < HEIGHT)
    {
        Wait(m, t == 0 ? 0 : (t+1)/2);
        waited[t] = 1;
        if (t > 0)
            signaled[(t-1)/2] = 1;
        TestAncestorsWaited(t);
     
        // Testam daca starea monitorului e consistenta
        {
            char buf[1024];
            int *q = CoziAsteptare();
            snprintf(buf, 1024, "Starea monitorului cand thread-ul %d ruleaza", t);
            testAndFail(buf, VerificaMult(0, Signaler(), Waiting(), 0, q));
            free(q);
        }

        Broadcast(m, t+1);
    }
    else
    {
        ++test_var;
    }
    Leave(m);

    return NULL;
}


void TestTree()
{
    pthread_t t[NUM_THREADS];
    int params[NUM_THREADS], i;

    memset(waited, 0, NUM_THREADS * sizeof(int));
    memset(signaled, 0, NUM_THREADS * sizeof(int));

    // Creare monitor
    m = Create(NUM_CONDS, SIGNAL_AND_WAIT);
    test("Create", m != NULL);
    SetNrCond(NUM_CONDS);

    // Creare thread-uri
    for (i = 0; i < NUM_THREADS; i++)
    {
        params[i] = i;
        if (pthread_create(t+i, NULL, &FunctieTestTree,&params[i]))
        {
            perror("ERR testTree.c ;la crearea fir;NAT\n;");
            exit(1);
        }
    }

    // Asteptam sa intre toate thread-urile in monitor
    sleep(5);

    // Semnalam radacina arborelui
    Enter(m);
    Broadcast(m, 0);
    Leave(m);

    // Asteptare thread-uri
    for (i = 0; i < NUM_THREADS; i++)
    {
        if (pthread_join(t[i], NULL))
        {
            perror("Eroare la asteptarea unui fir\n");
            exit(1);
        }
    }

    // Daca am ajuns aici, a trecut toate testele cu stramosi + starea intermediara
    test("Starile intermediare ale monitorului", 0 == 0);

    test("Valoarea finala a variabilei", test_var == (1 << (HEIGHT - 1)));

    // Distrugere monitor
    test("Destroy", Destroy(m) == 0);
    FreeNrCond(NUM_CONDS);
}

