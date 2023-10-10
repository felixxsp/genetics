#include<bits/stdc++.h>
using namespace std;

int main()
{
	//Random Decimal
	int Nx[4], Ny[4], Ttl[4], x, y;
	int Rnd = 255/2;
	srand(time(NULL));
	for (x = 0; x <= 3; x++)
	{
		Nx[x] = rand() % (Rnd+1) + 1;
		Ny[x] = rand() % Rnd + 1;
		Ttl[x] = Nx[x] + Ny[x]; 
		printf("%d\n", Ttl[x]);
	}
	int start[4], str[4], ctr;
	for (x = 0; x < 4; x++)
	{
		start[x] = 0;
		ctr = 0;
		while (ctr < Ttl[x])
		{
			start[x] = start[x] + 1;
			ctr = pow(2,start[x]);
		}
		str[x] = ctr;
	}
	int krom[4][8], div[8];
	for (x = 0; x <= 7; x++)
		div[x] = pow(2, 7-x);
	//Decimal to Biner
	for (x = 0; x < 4; x++)
		for (y = 0; y < 8; y++)
		{
			if (Ttl[x] >= div[y])
			{
				krom[x][y] = 1;
				Ttl[x] -= div[y];
			}
			else
				krom[x][y] = 0;
		}
	for (y = 0; y <= 3; y++)
	{
		printf("\n");
		for (x = 0; x < 8; x++)
			printf("%d", krom[y][x]);
	}
	//Integer to Double
	double DNx[4], DNy[4];
	for (x = 0; x <= 3; x++)
	{
		DNx[x] = (double)Nx[x];
		DNy[x] = (double)Ny[x];
	}
	//Fungsi Fitness
	printf("\n");
	double functval[4], sqrt[4], var1[4], valsin[4], valcos[4], sincos[4];
	for (x = 0; x <= 3; x++)
	{
		sqrt[x] = (pow(DNx[x], 2)) + (pow(DNy[x], 2));
		var1[x] = 1/(pow(2.71828, sqrt[x]));
		valsin[x] = 4.00 * DNx[x];
		valcos[x] = 8.00 * DNy[x];
		sincos[x] = (sin(valsin[x])) + (cos(valcos[x]));
		functval[x] = (2 + var1[x]) * sincos[x];
		printf("\n%lf ", functval[x]);
	}
	//Eliminasi
	printf("\n");
	double all, percent[4];
	all = 0;
	int ctrpos = 0;
	int prenew[4][8];
	for (x = 0; x <= 3; x++)
		if (functval[x] >= 0.0)
		{	
			all += functval[x];
			for (y = 0; y <= 7; y++)
				prenew[ctrpos][y] = krom[x][y];
			ctrpos += 1;
		}
	printf("\n%lf\n", all);
	double newfunct[ctrpos];
	int intpercnt[ctrpos], source[ctrpos], ctrpar2, tempctr[ctrpos], parkrom[ctrpos][8];
	ctrpar2 = 1;
	for (x = 0; x <= 3; x++)
		if (functval[x] >= 0.0)
			{
				percent[x] = (functval[x] / all) * 100.0;
				newfunct[x] = functval[x];
				intpercnt[x + 1] = (int)(percent[x] + 0.55);
				//printf("\n%lf", percent[x]);
				printf("\n%d", intpercnt[x + 1]);
				tempctr[ctrpar2] = intpercnt[x + 1];
				source[ctrpar2] = x;
				//printf("\n*%d", source[ctrpar2]);
				ctrpar2++;
			}
	printf("\n");
	int newpar[4], parcode[4], ctrnum;
	//Arranging for next elimination
	srand(time(NULL));
	tempctr[0] = 0;
	for (y = 0; y <= ctrpos; y++)
	{
		if (y > 0)
			tempctr[y] += tempctr[y - 1];
		printf("\n%d", tempctr[y]);
	}
	printf("\n");
	if (ctrpos > 1)
		for (x = 0; x < 4; x++)
		{
			newpar[x] = rand() % 100 + 1;
			ctrnum = 1;
			while (newpar[x] > tempctr[ctrnum])
				ctrnum++;
			if (newpar[x] <= tempctr[ctrnum])
				parcode[x] = ctrnum;
			printf("\n%d -> %d", newpar[x], parcode[x]);
		}
	else
			for (x = 0; x < 4; x++)
		{
			newpar[x] = 0;
			printf("\n%d", newpar[x]);
		}
	printf("\n");
	if (ctrpos > 1)
		for (x = 0; x < 4; x++)
		{
			printf("\n");
			for (y = 0; y < 8; y++)
			{
				parkrom[x][y] = krom[source[parcode[x]]][y];
				printf("%d", parkrom[x][y]);
			}
		}
	else
		printf("\n%d", source[ctrpar2]);
	//New Parents - Crossing
	int cross[2], crstr[2], crend[2], newgen[4][8], newgenctr;
	newgenctr = 0;
	printf("\n");
	for (x = 0; x <= 1; x++)
	{
		cross[x] = rand() % 100 + 1;
		crstr[x] = rand() % 8 + 1;
		crend[x] = rand() % (8 - crstr[x]) + (crstr[x] + 1);
		printf("\n%d %d %d", cross[x], crstr[x], crend[x]);
		for (y = 0; y < crstr[x]; y++)
		{
			newgen[x][y] = parkrom[x][y];
			newgen[x + 1][y] = parkrom[x + 1][y];
		}
		for (y = crstr[x]; y <= crend[x]; y++)
		{
			newgen[x][y] = parkrom[x + 1][y];
			newgen[x + 1][y] = parkrom[x][y];
		}
		for (y = (crend[x] + 1); y < 8; y++)
		{
			newgen[x][y] = parkrom[x][y];
			newgen[x + 1][y] = parkrom[x + 1][y];
		}
		newgenctr += 2;	
	}
	for (x = 0; x < 4; x++)
	{
		printf("\n");
		for (y = 0; y < 8; y++)
			printf("%d", newgen[x][y]);
	}
}
