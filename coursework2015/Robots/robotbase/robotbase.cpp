// robotbase.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include "robotbase.h"

using namespace std;

extern "C" 
void DoStep(stepinfo *Info, step *Step)
{
	srand(time(0));
	NewAction(Step, ACT_MOVE, rand() % 3 - 1, rand() % 3 - 1);
}

