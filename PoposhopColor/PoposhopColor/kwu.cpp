#include "stdafx.h"
#include "kwu.h"


kwu::kwu(void)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Mask[i * 3 + j] = 0.0;
		}
	}
	Avg = -1.0;
	Dist = -1.0;
}


kwu::~kwu(void)
{
}

void kwu::setAvg()
{
	double sum = 0.0;
	for (int i = 0; i < 9; i++)
	{
		sum += Mask[i];
	}
	Avg = sum / 9;
}

void kwu::setDist()
{
	double sum = 0.0;
	for (int i = 0; i < 9; i++)
	{
		sum += pow(fabs(Avg - Mask[i]), 2.0);
	}
	Dist = sum / 9;
}

