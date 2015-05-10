#pragma once

#define ACT_MOVE   1
#define ACT_ATTACK 2
#define ACT_TECH   3

HANDLE CommitStep = CreateEvent(NULL, FALSE, FALSE, "StepCommitted");

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
	int numberOfActions;
	//int *acts;
	//int action;
	//int dx;
	//int dy;
	action *actions;
};

struct stepinfo
{
	int stepnum;
	int x;
	int y;
	int **matrix;
};


