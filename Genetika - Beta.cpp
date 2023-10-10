#include<bits/stdc++.h>
using namespace std;

int main()
{
	int nrand;
	scanf("%d", & nrand);
	int Nx[nrand], Ny[nrand], NR[nrand], tNR[nrand], x, y;
	srand(time(NULL));
	for (x = 0; x < nrand; x++)
	{
		Nx[x] = rand() % ((255/2) + 1) + 1;
		Ny[x] = rand() % (255/2) + 1;
		NR[x] = Nx[x] + Ny[x];
		tNR[x] = NR[x];
	}
	double DNx[nrand], DNy[nrand], allval;
	for (x = 0; x < nrand; x++)
	{
		DNx[x] = (double)Nx[x];
		DNy[x] = (double)Ny[x];
	}
	double functval[nrand], sqrt[nrand], var1[nrand], valsin[nrand], valcos[nrand], sincos[nrand];
	for (x = 0; x < nrand; x++)
	{
		sqrt[x] = (pow(DNx[x], 2)) + (pow(DNy[x], 2));
		var1[x] = 1/(pow(2.71828, sqrt[x]));
		valsin[x] = 4.00 * DNx[x];
		valcos[x] = 8.00 * DNy[x];
		sincos[x] = (sin(valsin[x])) + (cos(valcos[x]));
		functval[x] = (2 + var1[x]) * sincos[x];
	}
	int krom[nrand][8], div[8], source[nrand];
	for (x = 0; x <= 7; x++)
		div[x] = pow(2, 7-x);
	for (x = 0; x < nrand; x++)
		for (y = 0; y < 8; y++)
		{
			if (tNR[x] >= div[y])
			{
				krom[x][y] = 1;
				tNR[x] -= div[y];
			}
			else
				krom[x][y] = 0;
		}
	allval = 0.0;
	int ctrpos = 0, intpercent[nrand];
	double percent[nrand];
	for (y = 0; y < nrand; y++)
	{
		if (functval[y] > 0.0)
		{
			allval += functval[y];
			source[ctrpos] = (y + 1);
			ctrpos++;
		}
		printf("Individu %d = %d, Fungsi = %lf\nKromoson : ", (y + 1), NR[y], functval[y]);
		for (x = 0; x < 8; x++)
			printf("%d", krom[y][x]);
		printf("\n\n");
	}
	double multiple = 1.0;
	for (x = 0; x < ctrpos; x++)
	{
		percent[x] = functval[source[x] - 1] / allval * 100.0;
		bool chc = false;
		while (chc == false)
		{
			if (ctrpos < (pow((10.0), multiple)))
				chc = true;
			else
				multiple += 1.0;
		}
		intpercent[x] = (int)(percent[x] * (pow(10.0, multiple)));
	} 
	printf("\n\nTotal Fungsi = %lf, %d", allval, ctrpos);
	for (x = 0; x < ctrpos; x++)
		printf("\nLolos %d = Individu %d (%d)", (x + 1), source[x], intpercent[x]);
	int newpar;
	printf("\nNew Generation : ");
	scanf("%d", & newpar);
	int parcode[newpar], lim[newpar], ctrpar, parsource[newpar];
	for (x = 0; x < ctrpos; x++)
	{
		lim[x] = intpercent[x];
		if (x > 0)
			lim[x] += lim[x - 1];
		//printf("\n%d", lim[x]);
	}
	lim[newpar - 1] = (int)(pow(10, (multiple + 2)));
	printf("\n");
	int parkrom[newpar][8], crchc[newpar], crstr[newpar], crend[newpar];
	for (x = 0; x < newpar; x++)
	{
		parcode[x] = rand() % ((int)(pow(10, (multiple + 2)))) + 1;
		ctrpar = 0;
		while (parcode[x] > lim[ctrpar])
			ctrpar++;
		if (parcode[x] <= lim[ctrpar])
			parsource[x] = ctrpar + 1;
		printf("Parent %d = Individu %d -> ", (x + 1), source[parsource[x]-1]);
		int arrctr = 0;
		for (y = 0; y <= 7; y++)
		{
			arrctr = 0;
			if (x % 2 == 1)
				arrctr++;
			parkrom[x][y] = krom[source[parsource[x] - 1] - 1][y];
			printf("%d", parkrom[x][y]);
		}
		printf(" %d\n", parcode[x]);
	}
	int crosspar[newpar/2][2][8], newgen[newpar/2][2][8];
	for (x = 1; x <= (newpar/2); x++)
	{
		crchc[x] = rand() % 100 + 1;
		crstr[x] = rand() % 8 + 1;
		crend[x] = rand() % 8 + (crstr[x] + 1);
		if (crend[x] > 8)
			crend[x] = 8;
		printf("\nPasangan %d, Chance = %d (%d - %d)", x, crchc[x], crstr[x], crend[x]);
		for (y = 0; y < 2; y++)
		{
			printf("\nOrtu %d : ", (y + 1));
			for (int z = 0; z <= 7; z++)
			{
				crosspar[x - 1][y][z] = parkrom[(2 * x) - (abs(y - 2))][z];
				printf("%d", crosspar[x - 1][y][z]);
			}
		}
	}
	for (x = 0; x < (newpar/2); x++)
	{
		if (crchc[x] <= 90)
		{
			for (int csr = 0; csr < crstr[x]; csr++)
			{
				newgen[x][0][csr] = crosspar[x][0][csr];
				newgen[x][1][csr] = crosspar[x][1][csr];
			}
			for (int csr = (crstr[x] - 1); csr < crend[x]; csr++)
			{
				newgen[x][0][csr] = crosspar[x][1][csr];
				newgen[x][1][csr] = crosspar[x][0][csr];
			}
			if (crend[x] < 8)
				for (int csr = crend[x]; csr < 8; csr++)
				{
					newgen[x][0][csr] = crosspar[x][0][csr];
					newgen[x][1][csr] = crosspar[x][1][csr];
				}
		}
	else
		for (int y = 0; y <= 1; y++)	
			for (int z = 0; z < 8; z++)
				newgen[x][y][z] = crosspar[x][y][z];
	}
	for (x = 0; x < newpar/2; x++)
		for (y = 0; y <= 1; y++)
		{
			printf("\nKeturunan -> ");
			for (int z = 0; z <= 7; z++)
				printf("%d", newgen[x][y][z]);
		}
}
