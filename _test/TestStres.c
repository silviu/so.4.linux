#include <stdio.h>

void TestRing();
void TestTree();
void TestStresRW();

void TestStres()
{
    printf("\n======TESTE STRESS=====\n");
    printf("\n=====TEST RING=====\n");
    TestRing();
    printf("\n=====TEST TREE=====\n");
    TestTree();
    printf("\n=====TEST RW=======\n");
    TestStresRW();
    printf("\n\n\n");
}

