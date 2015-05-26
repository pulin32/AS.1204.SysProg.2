#pragma once

#define N    1000
#define T    100
#define Emax 1000
#define Lmax 100
#define Vmax 10
#define Rmax 5
#define dL   10
#define dEs  1
#define dEv  2
#define dEa  10
#define dEp  5
#define dE   100
#define Ne   10
#define Nl   10

#define cameraStep 1

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
	step *history;
};

typedef void (*robobrain)(stepinfo *Info, step *Step);

struct fieldData
{
	int fieldHeight;
	int fieldWidth;
	int rivals;
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
	int kills;
	bool alive;
};

struct toThread
{
	robobrain Function;
	stepinfo *Info;
	step *Step;
};

static HANDLE PicCounted = CreateEvent(NULL, FALSE, FALSE, "PicCounted");

#define ACT_MOVE   1
#define ACT_ATTACK 2
#define ACT_TECH   3

#define OBJ_CHARGER -2
#define OBJ_TECH -3

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