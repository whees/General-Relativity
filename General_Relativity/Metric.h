#include "functions.h"
#pragma once



class Metric
{
public:
	typedef float (*threeIndexFourParamFunc) (Metric*, int u, int v, int s, float* abcd);

	fourParamFunc** covar; // covariant representation
	float contra(int u, int v, float* abcd); //contravariant representation

	Metric(fourParamFunc** init);
	Metric();

	float christoff_tensor(int e, int u, int v, int s, float* abcd);
	float einstein_tensor(int u, int v, float* abcd);
	float christoff_derivitive(threeIndexFourParamFunc func, int index, int u, int v, int s, float* abcd);
};


float christoff_3index(Metric* g, int u, int v, int s, float* abcd);

