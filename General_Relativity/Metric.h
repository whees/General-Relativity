#include "dictionary.h"
#include <iostream>
using namespace std;

#pragma once


class Metric
{
public:
	fourParamFunc** uvs; // covariant representation
	
	
	Metric(fourParamFunc** inits);
	Metric();


	float christoff(int u,int v,int a, float* abcd);
	float contra_uvs(int u, int v, float* abcd);

	

};

