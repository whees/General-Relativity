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
	uvs = new fourParamFunc*[4];
	for (int i = 0; i < 4; i++)
	{
		uvs[i] = new fourParamFunc[4];
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			uvs[i][j] = inits[i][j];
		}
	}
}

Metric::Metric()
{
	uvs = new fourParamFunc * [4];
	for (int i = 0; i < 4; i++)
	{
		uvs[i] = new fourParamFunc[4];
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i != j)
				uvs[i][j] = &null;
			else if (i == 3)
				uvs[i][j] = &mink_time;
			else
				uvs[i][j] = &mink_space;
		}
	}
}


float Metric::contra_uvs(int u, int v, float* abcd)
{
	float det = det4(uvs, abcd);

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

			mids[j][k] = uvs[(v + j + 1) % 4][(u + k + 1) % 4];
		}
	}

	float cov =  det3(mids, abcd);
	delete[] mids;
	
	return cov / det;
}

float Metric::christoff(int u, int v, int a, float* abcd)
{
	float ret = 0;

	for (int l = 0; l < 4; l++)
	{
		ret += contra_uvs(a,l,abcd) * (derivitive(uvs[u][l], v, abcd) + derivitive(uvs[v][l], u, abcd) - derivitive(uvs[u][v], l, abcd));
	}

	ret *= 0.5;

	return ret;
}