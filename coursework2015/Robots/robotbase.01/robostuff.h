#pragma once

#define ACT_MOVE   1
#define ACT_ATTACK 2
#define ACT_TECH   3


struct action
{
	int act;
	int dx;
	int dy;
	int A;
	int P;
	int V;
};

struct step
{
	vector<action> actions;
};

struct stepinfo
{
	int stepnum;
	int x;
	int y;
	int **matrix;
};


inline void NewAction(step *Step, int type, int dx = 0, int dy = 0, int A = 0, int P = 0, int V = 0)
{
	int num = Step->actions.size();
	Step->actions.push_back(action());
	Step->actions[num].act = type;
	Step->actions[num].dx = dx;
	Step->actions[num].dy = dy;
	Step->actions[num].A = A;
	Step->actions[num].P = P;
	Step->actions[num].V = V;
}
