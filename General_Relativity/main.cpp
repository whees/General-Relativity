// General_Relativity.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <cmath>
#include "Metric.h"
#include "functions.h"
using namespace std;

float M = 1;


float g11(float* abcd)
{
	float r = abcd[0];
	float f = 1 - M / r;
	return -1/f;

}



float g22(float* abcd)
{
	float r = abcd[0];
	return -r*r;

}


float g33(float* abcd)
{
	float r = abcd[0];
	float t = abcd[1];

	return - r * r * sin(t)*sin(t);

}

float g44(float* abcd)
{
	float r = abcd[0];
	float f = 1 - M / r;
	return f;

}

float schwartz_null(float* abcd)
{
	return 0;
}

int main()
{
	fourParamFunc ** uvs = new fourParamFunc * [4];
	for (int i = 0; i < 4; i++)
	{
		uvs[i] = new fourParamFunc[4];
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i != j)
				uvs[i][j] = &schwartz_null;
			else 
				switch (i)
				{
				case 0:
					uvs[i][j] = &g11;
					break;
				case 1:
					uvs[i][j] = &g22;
					break;
				case 2:
					uvs[i][j] = &g33;
					break;
				case 3:
					uvs[i][j] = &g44;
					break;
				default:
					break;
				}

		}
	}

	Metric* g = new Metric(uvs);
	float abcd[4] = { 2,1,0,0 };

	cout << christoff_3index(g, 0, 1, 1, abcd);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
