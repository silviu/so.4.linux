#include "HeaderTest.h"

void Test1()//micro
{
	m=Create(1,SIGNAL_AND_WAIT);
	test("Create",m!=NULL);
	
	test("Enter",Enter(m)==0);
	test("Enter",Enter(m)==-1);
	test("Leave",Leave(m)==0);
	
	test("Leave",Leave(m)==-1);
	test("Wait",Wait(m,2)==-1);
	test("Signal",Signal(m,2)==-1);
	test("Broadcast",Broadcast(m,3)==-1);
	
	test("Enter",Enter(m)==0);
	test("Distroy", Destroy(m)==-1);
	test("Leave",Leave(m)==0);
	
	test("Destroy",Destroy(m)==0);
}
