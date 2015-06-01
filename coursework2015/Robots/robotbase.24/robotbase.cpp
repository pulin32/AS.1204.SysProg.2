// robotbase.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include "robotbase.h"

using namespace std;

extern "C" 
void DoStep(stepinfo *Info, step *Step)
{
	int me = Info->yourNumber;
	int myx = Info->robots[me]->x;
	int myy = Info->robots[me]->y;
	double minDistanceToCharger = Info->field->fieldWidth;
	int index = 0;
	if (Info->field->Ne > 0)
	{
		for (int i = 0; i<Info->field->Ne + Info->field->Nl; i++)
		{
			if (Info->objects[i]->type == OBJ_CHARGER)
			{
				double curDist = sqrt(pow(Info->objects[i]->x-myx, 2) + pow(Info->objects[i]->y-myy, 2));
				if (curDist < minDistanceToCharger)
				{
					minDistanceToCharger = curDist;
					index = i;
				}
			}
		}
	}
	else if (Info->field->Nl > 0)
	{
		for (int i = 0; i<Info->field->Ne + Info->field->Nl; i++)
		{
			if (Info->objects[i]->type == OBJ_TECH)
			{
				double curDist = sqrt(pow(Info->objects[i]->x-myx, 2) + pow(Info->objects[i]->y-myy, 2));
				if (curDist < minDistanceToCharger)
				{
					minDistanceToCharger = curDist;
					index = i;
				}
			}
		}
	}
	else
	{
		DoAction(Step,ACT_TECH,0,Info->robots[me]->L,0);
		return;
	}

	if (minDistanceToCharger > 0)
	{
		double maxStep = Info->robots[me]->V*Info->field->Vmax/Info->field->Lmax*Info->robots[me]->E/Info->field->Emax;	
		double reqSteps = minDistanceToCharger/maxStep;	
		int destx = Info->objects[index]->x;
		int desty = Info->objects[index]->y;
		if (reqSteps > 1)
		{
			DoAction(Step,ACT_TECH,0,Info->robots[me]->L-Info->field->Vmax,Info->field->Vmax);	
			int dx = (destx - myx)/reqSteps;
			int dy = (desty - myy)/reqSteps;
			DoAction(Step,ACT_MOVE,dx,dy);
		}
		else
		{
			DoAction(Step,ACT_TECH,0,Info->robots[me]->L,0);
			DoAction(Step,ACT_MOVE,destx-myx,desty-myy);
		}
	}
	else
		DoAction(Step,ACT_TECH,0,Info->robots[me]->L,0);

	return;
}


