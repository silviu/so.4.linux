#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int NrCit, NrScrit;
int TotalNrScrit; // Nr. total de scriitori care au avut acces la buffer pana acum
                  // Nu e nevoie sa sincronizam accesul, doar scriitorii modifica si ei sunt serializati

void AnnounceStartCit()
{
	NrCit++;
}
void AnnounceStopCit()
{
	NrCit--;
}
void AnnounceStartScrit()
{
	NrScrit++;
    TotalNrScrit++;
}
void AnnounceStopScrit()
{
	NrScrit--;
}
void ResetScritCit()
{
    TotalNrScrit=0;
	NrScrit=0;
	NrCit=0;
}
int VerificaTotalW(int TotalW)
{
    if (TotalNrScrit == TotalW)
        return 0;

    return -1;
}
int VerificaRW(int r, int w)
{
	if(r==NrCit && w==NrScrit)
	{
		return 0;
	}
	return -1;
}
int VerificaW(int w)
{
	if( w==NrScrit)
	{
		return 0;
	}
	return -1;
}
int VerificaR(int r)
{
	if( r==NrCit)
	{
		return 0;
	}
	return -1;
}




