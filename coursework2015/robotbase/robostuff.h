#pragma once

#define ACT_MOVE   1
#define ACT_ATTACK 2
#define ACT_TECH   3


struct action
{
	int dx;
	int dy;
	int A;
	int P;
	int V;
};

struct step
{
	action **actions;
};

struct stepinfo;

struct object
{
	int type;
	int x;
	int y;
};

typedef void (*robobrain)(stepinfo *Info, step *Step);
struct robot
{
	CString name;
	COLORREF color;
	robobrain DoStep;
	int x;
	int y;
	int E;
	int L;
	int V;
	int A;
	int P;
	int kills;
	bool alive;
	bool killed;
};

struct stepinfo
{
	int stepnum;
	int yourNumber;
	robot **robots;
	object **objects;
	step *history;
};


void DoAction(step *Step, int type, int dx = 0, int dy = 0, int A = 0, int P = 0, int V = 0)
{
	Step->actions[type] = new action;
	Step->actions[type]->dx = dx;
	Step->actions[type]->dy = dy;
	Step->actions[type]->A = A;
	Step->actions[type]->P = P;
	Step->actions[type]->V = V;
}