#include "Metric.h"

float mink_space(float* abcd)
{
	return -1;
}
float mink_time(float* abcd)
{
	return 1;
}
float null(float* abcd)
{
	return 0;
}

Metric::Metric(fourParamFunc** inits)
{
	covar = new fourParamFunc*[4];
	for (int i = 0; i < 4; i++)
	{
		covar[i] = new fourParamFunc[4];
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			covar[i][j] = inits[i][j];
		}
	}
}

Metric::Metric()
{
	covar = new fourParamFunc * [4];
	for (int i = 0; i < 4; i++)
	{
		covar[i] = new fourParamFunc[4];
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i != j)
				covar[i][j] = &null;
			else if (i == 3)
				covar[i][j] = &mink_time;
			else
				covar[i][j] = &mink_space;
		}
	}
}


float Metric::contra(int u, int v, float* abcd)
{
	float det = det4(covar, abcd);

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

			mids[j][k] = covar[(v + j + 1) % 4][(u + k + 1) % 4];
		}
	}

	float cov =  det3(mids, abcd);
	delete[] mids;
	
	return cov / det;
}


float Metric::christoff_tensor(int e, int u, int v, int s, float* abcd)
{
	float ret = 0;
	

	for (int a = 0; a < 4; a++)
	{

		ret += christoff_3index(this,u, s, a, abcd) * christoff_3index(this,a, v, e, abcd);
	}

	for (int a = 0; a < 4; a++)
	{
		ret -= christoff_3index(this,u, v, a, abcd) * christoff_3index(this,a, s, e, abcd);
	}

	ret -= christoff_derivitive(&christoff_3index, v, u, s, e, abcd);
	ret -= christoff_derivitive(&christoff_3index, s, u, v, e, abcd);

	return ret;
}

float Metric::christoff_derivitive(threeIndexFourParamFunc func, int index, int u, int v, int s, float* abcd)
{
	float dparam = 0.001;
	float new_abcd[4] = { abcd[0], abcd[1], abcd[2], abcd[3] };
	new_abcd[index] += dparam;
	float dfunc = func(this,u, v, s, new_abcd) - func(this,u, v, s, abcd);

	return dfunc / dparam;
}


float christoff_3index(Metric* g, int u, int v, int s, float* abcd)
{
	float ret = 0;

	for (int l = 0; l < 4; l++)
	{
		ret += g->contra(s, l, abcd) * (derivitive(g->covar[u][l], v, abcd) + derivitive(g->covar[v][l], u, abcd) - derivitive(g->covar[u][v], l, abcd));
	}

	ret *= 0.5;


	return ret;
}