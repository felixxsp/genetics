#include<bits/stdc++.h>
using namespace std;

int main()
{
	int x, random[3];
	double funct[4][3];
	x = pow(2,8);
	int krom[4][8];
	srand(time(NULL));
	//random generator
	for (int i = 1; i <= 4; i++)
	{
		random[0] = rand() % (x/2) + 1;
		funct[i-1][0] = random[0];
		random[1] = rand() % (x/2) + 1;
		funct[i-1][1] = random[1];
		funct[i-1][2] = random[0] + random[1];
		printf("%d", funct[i-1][2]);
		printf("\nKromosom %d: ", i);
		random[2] = random[0] + random[1];
		for (int x = 7; x >= 0; x--)
		{
			if ((int)funct[i-1][2] % 2 == 1)
				krom[i-1][x] = 1;
				else
				krom[i-1][x] = 0;
			random[2] = funct[i-1][2]/2;
			printf("%d", krom[i-1][x]);
		}
		printf("\n");
	}
	//fungsi fitness
	/*double function[4], sqrt[4], xf, yf;
	xf = funct[0];
	yf = funct[1];
	for (int x = 0; x <= 3; x++)
	{
		sqrt[x] = (pow(xf,2)) + (funct[1] * funct[1]);
		function[x] = 2 + (1/sqrt[x]) * (sin(4 * funct[0]) + cos(8 * funct[1]));
		printf("%d", function[x]);
	}*/
}
