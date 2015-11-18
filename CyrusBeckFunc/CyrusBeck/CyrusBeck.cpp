// CyrusBeck.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <limits.h>

struct POINT2D
{
	float x;
	float y;
};

#define MAX_SOMMET 100
#define N1 100
#define N3 100

POINT2D Poly[MAX_SOMMET];
POINT2D Normale[MAX_SOMMET];

bool coupe(POINT2D S, POINT2D P, POINT2D F1, POINT2D F2)
{
	return true;
}

bool visible(POINT2D S, POINT2D F1, POINT2D F2)
{
	return true;
}

POINT2D intersection(POINT2D S, POINT2D P, POINT2D F1, POINT2D F2)
{
	return S;
}

POINT2D* Sutherland(POINT2D* Poly, POINT2D* Fenetre, unsigned int n1)
{
	int i, j;
	int n2;
	POINT2D S, F, I;
	POINT2D PS[MAX_SOMMET];

	for (i = 1; i < N3 - 1; i++)
	{
		n2 = 0;
		for (j = 1; j < n1; j++)
		{			
			if (j == 1)
				F = Poly[j];
			else
			{
				if (coupe(S, Poly[j], Fenetre[i], Fenetre[i+1]))
				{
					I = intersection(S, Poly[j], Fenetre[i], Fenetre[i+1]);
					PS[n2] = I;
					n2++;
				}
			}
			S = Poly[j];
			if (visible(S, Fenetre[i], Fenetre[i + 1]))
			{
				PS[n2] = S;
				n2++;
			}
		}
		if (n2 > 0)
		{
			// Traitement du dernier côté de PL
			if (coupe(S, F, Fenetre[i], Fenetre[i + 1]))
			{
				I = intersection(S, F, Fenetre[i], Fenetre[i + 1]);
				PS[n2] = I;
				n2++;
			}
			// Découpage pour chacun des sous polygones
			Poly = PS;
			n1 = n2;
		}
	}
}

bool cyrusBeck(float* X1, float* Y1, float* X2, float* Y2, POINT2D* Poly, POINT2D* Normale, unsigned int Nbsom)
{
	float t, tinf, tsup;
	bool tinfInit, tsupInit;
	float DX, DY, WN, DN, Prod;
	POINT2D C;
	unsigned int i, Nbseg;

	DX = *X2 - *X1;
	DY = *Y2 - *Y1;
	Nbseg = Nbsom - 1;
	tinfInit = false;
	tsupInit = false;

	for (i = 0; i < Nbseg; i++)
	{
		C.x = Poly[i].x;
		C.y = Poly[i].y;
		DN = DX*Normale[i].x + DY*Normale[i].y;
		WN = (*X1 - C.x)*Normale[i].x + (*Y1 - C.y)*Normale[i].y;

		if (DN == 0)
		{
			Prod = (*X1 - C.x)*Normale[i].x + (*Y1 - C.y)*Normale[i].y;
			if (Prod == 0)
				return true;
			else
				return false;
		}
		else
		{
			t = -WN / DN;
			if (DN > 0)
			{
				if (tinfInit)
				{
					if (t > tinf)
						tinf = t;
				}
				else
				{
					tinf = t;
					tinfInit = true;
				}
			}
			else
			{
				if (tsupInit)
				{
					if (t < tsup)
						tsup = t;
				}
				else
				{
					tsup = t;
					tsupInit = true;
				}
			}
		}
	}

	if (tinf < tsup)
	{
		if ((tinf < 0) && (tsup > 1))
			return true;
		else
		{
			if ((tinf > 1) || (tsup < 0))
				return false;
			else
			{
				if (tinf < 0)
					tinf = 0;
				else
				{
					if (tsup > 1)
						tsup = 1;
				}
				*X2 = *X1 + DX*tsup;
				*Y2 = *Y1 + DY*tsup;
				*X1 = *X1 + DX*tinf;
				*Y1 = *Y1 + DY*tinf;
				return true;
			}
		}
	}
	else
		return false;
}

int main(int argc, char* argv[])
{
	return 0;
}

