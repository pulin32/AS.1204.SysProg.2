#pragma once

/*#define N    1000
#define T    100
#define Emax 1000
#define Lmax 100
#define Vmax 30
#define Rmax 5
#define dL   10
#define dEs  1
#define dEv  2
#define dEa  10
#define dEp  5
#define dE   100
#define Ne   10
#define Nl   10*/

#define cameraStep 1
#define fieldSide 20

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
	action* actions[3];
};

struct object
{
	int type;
	int x;
	int y;
};

struct robot;
struct stepinfo
{
	int stepnum;
	int yourNumber;
	robot **robots;
	object **objects;
	/*int x;
	int y;
	int **matrix;
	int A;
	int P;
	int V;
	int E;*/
	step **history;
};

typedef void (*robobrain)(stepinfo *Info, step *Step);

struct fieldData
{
	int fieldHeight;
	int fieldWidth;
	int rivals,
	N,    //1000
	T,    //100
	Emax, //1000
	Lmax, //100
	Vmax, //30
	Rmax, //5
	dL,   //10
	dEs,  //1
	dEv,  //2
	dEa,  //10
	dEp,  //5
	dE,   //100
	Ne,   //10
	Nl;   //10
};

struct robot
{
	CString name;
	COLORREF color;
	robobrain DoStep;
	//HINSTANCE Library;
	int x;
	int y;
	int E;
	int L;
	int V;
	int A;
	int P;
	int newA;
	int newP;
	int newL;
	int newE;
	int kills;
	bool alive;
	bool killed;
};

struct toThread
{
	robobrain Function;
	stepinfo *Info;
	step *Step;
};

#define ACT_MOVE   0
#define ACT_ATTACK 1
#define ACT_TECH   2

#define OBJ_CHARGER -2
#define OBJ_TECH -3
#define OBJ_DEAD -4
#define SEVERAL -5

struct coords
{
	int xlocal;
	int ylocal;
	int xreal;
	int yreal;
	int *upperleftCellCoords;
	int **matrix;
	int n;
	fieldData *Data;
};


inline void DoAction(step *Step, int type, int dx = 0, int dy = 0, int A = 0, int P = 0, int V = 0)
{
	if (Step->actions[type])
		delete Step->actions[type];
	Step->actions[type] = new action;
	Step->actions[type]->dx = dx;
	Step->actions[type]->dy = dy;
	Step->actions[type]->A = A;
	Step->actions[type]->P = P;
	Step->actions[type]->V = V;
}
