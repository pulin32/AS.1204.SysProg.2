// robotbase.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include "robotbase.h"

using namespace std;

extern "C" 
void DoStep(stepinfo *Info, step *Step)
{
	//AfxMessageBox("DLL");
	srand(time(0));
	/*Step->action = ACT_MOVE;
	Step->dx = rand() % 3 -1;
	Step->dy = rand() % 3 -1;*/
	Step->numberOfActions = 1;
	Step->actions = new action[Step->numberOfActions];
	Step->actions[0].act = ACT_MOVE;
	Step->actions[0].dx = rand() % 3 - 1;
	Step->actions[0].dy = rand() % 3 - 1;
	SetEvent(CommitStep);
	return;
}

void NewAction(step *Step, int type, int dx = 0, int dy = 0, int A = 0, int P = 0, int V = 0)
{
	int num = Step->numberOfActions;
	Step->numberOfActions++;
	Step->actions[num].act = type;
	Step->actions[num].dx = dx;
	Step->actions[num].dy = dy;
	Step->actions[num].A = A;
	Step->actions[num].P = P;
	Step->actions[num].V = V;
}
