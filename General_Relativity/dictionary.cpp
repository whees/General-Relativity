#include "dictionary.h"
#include <iostream>
#include <cmath>
using namespace std;


float squared(float x)
{
	return sin(x);
}


float derivitive(fourParamFunc func, int index, float* abcd)
{
	float dparam = 0.001;
	float new_abcd[4] = { abcd[0], abcd[1], abcd[2], abcd[3] };
	new_abcd[index] += dparam;
	float dfunc = func(new_abcd) - func(abcd);

	return dfunc / dparam;
}

float det4(fourParamFunc** opps, float* abcd)
{
	float ret = 0;



	for (int i = 0; i < 4; i++)
	{
		fourParamFunc** mids;
		mids = new fourParamFunc * [3];
		for (int j = 0; j < 3; j++)
		{
			mids[j] = new fourParamFunc[3];
		}
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				mids[j][k] = opps[(i + j + 1) % 4][k + 1];
			}
		}

		ret += opps[i][0](abcd) * det3(mids, abcd);
		delete[] mids;
	}




	return ret;
}

float det3(fourParamFunc** opps, float* abcd)
{

	float ret = 0;

	for (int i = 0; i < 3; i++)
	{
		ret += opps[0][i](abcd) * (opps[1][(i + 1) % 3](abcd) * opps[2][(i + 2) % 3](abcd) - opps[1][(i + 2) % 3](abcd) * opps[2][(i + 1) % 3](abcd));
	}

	return ret;

}
