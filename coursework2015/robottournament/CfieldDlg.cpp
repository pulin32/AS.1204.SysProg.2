// CfieldDlg.cpp: файл реализации
//

//#pragma comment(lib,"../robotbase/robotbase.lib")
//#include "../robotbase/robotbase.h"

#include "stdafx.h"
#include "robottournament.h"
#include "CfieldDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include "math.h"


// диалоговое окно CfieldDlg

IMPLEMENT_DYNAMIC(CfieldDlg, CDialogEx)

CfieldDlg::CfieldDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CfieldDlg::IDD, pParent)
{
	upperleftCellCoords[0] = 0;
	upperleftCellCoords[1] = 0;
	n = 20;
}

CfieldDlg::~CfieldDlg()
{
	for (int i=0;i<FieldParameters.fieldWidth;i++)
		delete matrix[i];
	delete matrix;
<<<<<<< HEAD
	for (int i=0;i<FieldParameters.rivals;i++)
		delete robots[i];
		//FreeLibrary(robots[i].Library);
			//delete robots[i].Library;
	delete robots;
=======
	//for (int i=0;i<FieldParameters.rivals;i++)
		//FreeLibrary(robots[i].Library);
			//delete robots[i].Library;
	//delete robots;
>>>>>>> origin/master
}

void CfieldDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CfieldDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CfieldDlg::OnBnClickedOk)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CfieldDlg::OnBnClickedButton1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_UPBTN, &CfieldDlg::OnBnClickedUpbtn)
	ON_BN_CLICKED(IDC_DOWNBTN, &CfieldDlg::OnBnClickedDownbtn)
	ON_BN_CLICKED(IDC_LEFTBTN, &CfieldDlg::OnBnClickedLeftbtn)
	ON_BN_CLICKED(IDC_RIGHTBTN, &CfieldDlg::OnBnClickedRightbtn)
END_MESSAGE_MAP()


// обработчики сообщений CfieldDlg


void CfieldDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialogEx::OnOK();
}

UINT CountCoords(LPVOID pParam)
{
	coords *Coordinates = (coords*)pParam;

	//ofstream file("file.txt");
	//file<<Coordinates->upperleftCellCoords[0]<<endl<<Coordinates->upperleftCellCoords[1]<<endl<<Coordinates->n<<endl<<Coordinates->Data->fieldHeight<<endl<<Coordinates->Data->fieldWidth;
	/*for (int i = 0; i<Coordinates->Data->fieldHeight; i++)
	{
		for (int j = 0; i<Coordinates->Data->fieldWidth; j++)
			file<<Coordinates->matrix[i][j];
		file<<endl;
	}*/

	for (int x = Coordinates->upperleftCellCoords[0]; x < Coordinates->upperleftCellCoords[0]+Coordinates->n; x++)
	{
		Coordinates->xreal = x;
		if (Coordinates->xreal<0)
			Coordinates->xreal+=Coordinates->Data->fieldWidth;
		if (Coordinates->xreal>=Coordinates->Data->fieldWidth)
			Coordinates->xreal-=Coordinates->Data->fieldWidth;
		for (int y = Coordinates->upperleftCellCoords[1]; y < Coordinates->upperleftCellCoords[1]+Coordinates->n; y++)
		{
			Coordinates->yreal = y;
			if (Coordinates->yreal<0)
				Coordinates->yreal+=Coordinates->Data->fieldHeight;
			if (Coordinates->yreal>=Coordinates->Data->fieldHeight)
				Coordinates->yreal-=Coordinates->Data->fieldHeight;
			if (Coordinates->matrix[Coordinates->xreal][Coordinates->yreal] != -1)
				//DrawRobot(xlocal,ylocal,robots[matrix[xreal][yreal]]->color);
					SetEvent(PicCounted);
			Coordinates->ylocal++;
		}
		Coordinates->xlocal++;
		Coordinates->ylocal = 0;
	}
	return 0;
}

void CfieldDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	//CRect DrawArea;
	GetClientRect(&DrawArea);
	DrawArea.right = DrawArea.bottom;
	COLORREF GridColor = RGB(0,0,0);
	double xcoor = DrawArea.left;
	double ycoor = DrawArea.top;
	CPen Pen(PS_SOLID,1,GridColor);
	dc.SelectObject(&Pen);
	//int n = 20;
	for (int i=0;i<=n;i++)
	{
		dc.MoveTo(xcoor,ycoor);
		dc.LineTo(xcoor,DrawArea.right);
		xcoor+=DrawArea.right/n;
	}
	xcoor = DrawArea.left;
	for (int i=0;i<=n;i++)
	{
		dc.MoveTo(xcoor,ycoor);
		dc.LineTo(DrawArea.bottom,ycoor);
		ycoor+=DrawArea.bottom/n;
	}
	// Не вызывать CDialogEx::OnPaint() для сообщений рисования
<<<<<<< HEAD
	/*int xlocal = 0;
	int ylocal = 0;
	int xreal, yreal;
	for (int x = upperleftCellCoords[0]; x < upperleftCellCoords[0]+n; x++)
	{
		xreal = x;
		if (xreal<0)
			xreal+=FieldParameters.fieldWidth;
		if (xreal>=FieldParameters.fieldWidth)
			xreal-=FieldParameters.fieldWidth;
		for (int y = upperleftCellCoords[1]; y < upperleftCellCoords[1]+n; y++)
		{
			yreal = y;
			if (yreal<0)
				yreal+=FieldParameters.fieldHeight;
			if (yreal>=FieldParameters.fieldHeight)
				yreal-=FieldParameters.fieldHeight;
			if (matrix[xreal][yreal] != -1)
				DrawRobot(xlocal,ylocal,robots[matrix[xreal][yreal]]->color);
			ylocal++;
		}
		xlocal++;
		ylocal = 0;
	}*/
	/*coords *Coordinates = new coords;
	Coordinates->xlocal = 0;
	Coordinates->ylocal = 0;
	Coordinates->upperleftCellCoords = upperleftCellCoords;
	Coordinates->n=n;
	Coordinates->Data = &FieldParameters;
	Coordinates->matrix = new int*[FieldParameters.fieldWidth];
	for (int i=0; i<FieldParameters.fieldWidth; i++)
	{
		Coordinates->matrix[i] = new int[FieldParameters.fieldHeight];
		//for (int j=0; j<FieldParameters.fieldHeight; j++)
			//Coordinates->matrix[i][j] = matrix[i][j];
	}
	for (int i=0; i<FieldParameters.fieldWidth; i++)
	{
		for (int j=0; j<FieldParameters.fieldHeight; j++)
			Coordinates->matrix[i][j] = matrix[i][j];
	}
		//Coordinates->matrix = matrix;
	AfxBeginThread(CountCoords,Coordinates);
	WaitForSingleObject(PicCounted,INFINITE);*/

}


void CfieldDlg::DrawRobot(int x, int y, /*int r = 0, int g = 255, int b = 0*/ COLORREF color)
{
	CClientDC dc(this);
	GetClientRect(&DrawArea);
	//CPen Pen(PS_SOLID,2,RGB(r,g,b));
	//CBrush Brush(RGB(r,g,b));
	CBrush Brush(color);
	dc.SelectObject(Brush);
	int side = DrawArea.bottom/n;
	Ellipse(dc,x*side+1,y*side+1,x*side+side,y*side+side);
}

void CfieldDlg::DrawObject(int x, int y, int type)
=======
}

void CfieldDlg::DrawRobot(int x, int y, /*int r = 0, int g = 255, int b = 0*/ COLORREF color)
>>>>>>> origin/master
{
	COLORREF color;
	if (type == OBJ_CHARGER)
		color = RGB(0,0,255);
	else //type == OBJ_TECH
		color = RGB(255,0,0);
	CClientDC dc(this);
	GetClientRect(&DrawArea);
<<<<<<< HEAD
	CPen Pen(PS_SOLID,2,color);
	dc.SelectObject(Pen);
=======
	//CPen Pen(PS_SOLID,2,RGB(r,g,b));
	//CBrush Brush(RGB(r,g,b));
	CBrush Brush(color);
	dc.SelectObject(Brush);
>>>>>>> origin/master
	int side = DrawArea.bottom/n;
	dc.MoveTo(x*side+1,y*side+1);
	dc.LineTo(x*side+side,y*side+side);
	dc.MoveTo(x*side+1,y*side+side);
	dc.LineTo(x*side+side,y*side+1);
}

void CfieldDlg::DrawRobots()
{
	//WaitForSingleObject(PicCounted,INFINITE);
	Invalidate();
	//AfxGetApp()->PumpMessage();
	OnPaint();
	int xlocal = 0;
	int ylocal = 0;
	int xreal, yreal;
	for (int x = upperleftCellCoords[0]; x < upperleftCellCoords[0]+n; x++)
	{
		xreal = x;
		if (xreal<0)
			xreal+=FieldParameters.fieldWidth;
		if (xreal>=FieldParameters.fieldWidth)
			xreal-=FieldParameters.fieldWidth;
		for (int y = upperleftCellCoords[1]; y < upperleftCellCoords[1]+n; y++)
		{
			yreal = y;
			if (yreal<0)
				yreal+=FieldParameters.fieldHeight;
			if (yreal>=FieldParameters.fieldHeight)
				yreal-=FieldParameters.fieldHeight;
<<<<<<< HEAD
			if (matrix[xreal][yreal] > -1)
				DrawRobot(xlocal,ylocal,robots[matrix[xreal][yreal]]->color);
			if (matrix[xreal][yreal] < -1)
				DrawObject(xlocal,ylocal,matrix[xreal][yreal]);
=======
			if (matrix[xreal][yreal] != -1)
				DrawRobot(xlocal,ylocal,robots[matrix[xreal][yreal]].color);
>>>>>>> origin/master
			ylocal++;
		}
		xlocal++;
		ylocal = 0;
	}
}


<<<<<<< HEAD

//int actingRobot;

UINT thread(LPVOID pParam)
{
	//robots[actingRobot]->DoStep(NULL,Step);
	// struct Data *tData = (struct Data *)threadData;
	toThread *Data = (toThread*)pParam;
	Data->Function(Data->Info,Data->Step);
	
	return 0;
}

void CfieldDlg::Play()
{
	while (true)
	{
		for (int actingRobot=0; actingRobot<FieldParameters.rivals; actingRobot++)
		{
			//Step = NULL;
			//actingRobot = i;
			toThread *threadData = new toThread;
			step *Step = new step;
			stepinfo *Stepinfo = new stepinfo;
			/*Stepinfo->A = robots[actingRobot]->A;
			Stepinfo->P = robots[actingRobot]->P;
			Stepinfo->V = robots[actingRobot]->V;
			Stepinfo->E = robots[actingRobot]->E;
			Stepinfo->x = robots[actingRobot]->x;
			Stepinfo->y = robots[actingRobot]->y;*/
			Stepinfo->robots = new robot*[FieldParameters.rivals];
			Stepinfo->objects = new object*[Ne+Nl];
			for (int i=0; i<FieldParameters.rivals; i++)
				Stepinfo->robots[i] = robots[i];
			for (int i=0; i<Ne+Nl; i++)
				Stepinfo->objects[i] = objects[i];

			Stepinfo->history = history;
			threadData->Function = robots[actingRobot]->DoStep;
			threadData->Info = Stepinfo;
			threadData->Step = Step;
			AfxBeginThread(thread,threadData);
			WaitForSingleObject(StepCommitted,T);
			history[actingRobot] = *Step;
			if (Step)
			{
				int curx = robots[actingRobot]->x;
				int cury = robots[actingRobot]->y;
				/*switch (Step->action)
				{
				case ACT_MOVE:
					{
						matrix[curx][cury] = -1;
						curx+=Step->dx;
						cury+=Step->dy;
						if (curx<0)
							curx+=FieldParameters.fieldWidth;
						else if (curx>=FieldParameters.fieldWidth)
							curx-=FieldParameters.fieldWidth;
						if (cury<0)
							cury+=FieldParameters.fieldHeight;
						else if (cury>=FieldParameters.fieldHeight)
							cury-=FieldParameters.fieldHeight;
						matrix[curx][cury] = actingRobot;
						robots[actingRobot]->x = curx;
						robots[actingRobot]->y = cury;
						break;
					}
				}*/
				for (int i = 0; i<Step->numberOfActions; i++)
				{
					switch (Step->actions[i].act)
					{
						case ACT_MOVE:
							{
								if (sqrt(pow(Step->actions[i].dx,2) + pow(Step->actions[i].dy,2)) <= Vmax*robots[actingRobot]->V/Lmax*robots[actingRobot]->E/Emax)
								{
									int newx = curx+Step->actions->dx;
									int newy = cury+Step->actions->dy;
									if (newx<0)
										newx+=FieldParameters.fieldWidth;
									else if (newx>=FieldParameters.fieldWidth)
										newx-=FieldParameters.fieldWidth;
									if (newy<0)
										newy+=FieldParameters.fieldHeight;
									else if (newy>=FieldParameters.fieldHeight)
										newy-=FieldParameters.fieldHeight;
									if (matrix[newx][newy] == -1)
									{
										matrix[curx][cury] = -1;
										matrix[newx][newy] = actingRobot;
										robots[actingRobot]->x = newx;
										robots[actingRobot]->y = newy;
										robots[actingRobot]->E -= dEv;
										for (int oi=-1; oi<=1; oi++)	//проверка наличия рядом объектов
										{
											for (int oj=-1; oj<=1; oj++)
											{
												int ox = newx + oi;
												int oy = newy + oj;
												if (ox<0)
													ox+=FieldParameters.fieldWidth;
												else if (ox>=FieldParameters.fieldWidth)
													ox-=FieldParameters.fieldWidth;
												if (oy<0)
													oy+=FieldParameters.fieldHeight;
												else if (oy>=FieldParameters.fieldHeight)
													oy-=FieldParameters.fieldHeight;
												if (matrix[ox][oy] == OBJ_CHARGER)
												{
													robots[actingRobot]->E += dE;
													if (robots[actingRobot]->E > Emax)
														robots[actingRobot]->E = Emax;
												}
												if (matrix[ox][oy] == OBJ_TECH)
												{
													robots[actingRobot]->P += dL;
													if (robots[actingRobot]->P + robots[actingRobot]->A + robots[actingRobot]->V > Lmax)
														robots[actingRobot]->P -= robots[actingRobot]->P + robots[actingRobot]->A + robots[actingRobot]->V - Lmax;
												}
											}
										}
									}
								}
								break;
							}
						case ACT_ATTACK:
							{
								if ( (sqrt(pow(Step->actions[i].dx,2) + pow(Step->actions[i].dy,2)) <= Rmax*robots[actingRobot]->V/Lmax*robots[actingRobot]->E/Emax)/* && (Step->actions[i].power <= robots[actingRobot]->A*robots[actingRobot]->E/Emax) */)
								{
									int destx = robots[actingRobot]->x + Step->actions[i].dx;
									int desty = robots[actingRobot]->y + Step->actions[i].dy;
									int victim = matrix[destx][desty];
									if (victim != -1)
									{
										robots[actingRobot]->E -= dEa;
										robots[victim]->E -= dEp;
										srand(time(0));
										double rnd = (rand() % 6 + 2)/10;
										double A = rnd*robots[actingRobot]->A*robots[actingRobot]->E/Emax;
										double P = (1-rnd)*robots[victim]->P*robots[victim]->E/Emax;
										if (A > P)
										{
											if (robots[victim]->P > 0)
												robots[victim]->P -= A-P;
											else
												robots[victim]->E -= abs(P - A)*Emax/Lmax;
										}
										else
										{
											if (robots[actingRobot]->A > 0)
												robots[actingRobot]->P -= P-A;
											else
												robots[actingRobot]->E -= abs(P - A)*Emax/Lmax;
										}
									}
								}
								break;
							}
						case ACT_TECH:
							{
								int Lcur = robots[actingRobot]->A + robots[actingRobot]->P + robots[actingRobot]->V;
								int Ldes = Step->actions[i].A + Step->actions[i].P + Step->actions[i].V;
								if (Ldes <= Lcur)
								{
									robots[actingRobot]->A = Step->actions[i].A;
									robots[actingRobot]->P = Step->actions[i].P;
									robots[actingRobot]->V = Step->actions[i].V;
								}
								break;
							}
					}
				}
			}
		}
		DrawRobots();
		Sleep(100);
	}
}


//typedef void (*PF)();
=======
//typedef void (*PF)();

>>>>>>> origin/master
void CfieldDlg::OnBnClickedButton1()
{
	/*HINSTANCE hLib = LoadLibrary("robotbase.dll");
	PF ff = (PF)GetProcAddress(hLib, "DoStep");
	ff();*/

<<<<<<< HEAD
	//robots[0]->DoStep();

	srand(time(NULL));
	int xrand = 0;
	int yrand = 0;
	for (int i = 0; i<Ne; i++)
	{
		do
		{
		xrand = rand() % FieldParameters.fieldWidth;
		yrand = rand() % FieldParameters.fieldHeight;
		}
		while (matrix[xrand][yrand] != -1);
		matrix[xrand][yrand] = OBJ_CHARGER;
		objects[i]->type = OBJ_CHARGER;
		objects[i]->x = xrand;
		objects[i]->y = yrand;
	}
	for (int i = Ne; i<Ne+Nl; i++)
	{
		do
		{
		xrand = rand() % FieldParameters.fieldWidth;
		yrand = rand() % FieldParameters.fieldHeight;
		}
		while (matrix[xrand][yrand] != -1);
		matrix[xrand][yrand] = OBJ_TECH;
		objects[i]->type = OBJ_TECH;
		objects[i]->x = xrand;
		objects[i]->y = yrand;
	}
=======
	srand (time(NULL));
	int xrand = 0;
	int yrand = 0;
>>>>>>> origin/master
	for (int i=0; i<FieldParameters.rivals; i++)
	{
		do
		{
			xrand = rand() % FieldParameters.fieldWidth;
			yrand = rand() % FieldParameters.fieldHeight;
		}
		while (matrix[xrand][yrand] != -1);
		matrix[xrand][yrand] = i;
<<<<<<< HEAD
		robots[i]->x = xrand;
		robots[i]->y = yrand;
	}
=======
		robots[i].x = xrand;
		robots[i].y = yrand;
	}

>>>>>>> origin/master
	DrawRobots();
	Play();	
}


void CfieldDlg::OnClose()
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CDialogEx::OnClose();
}


void CfieldDlg::OnBnClickedUpbtn()
{
	upperleftCellCoords[1] -= cameraStep;
	if (upperleftCellCoords[1]<0)
		upperleftCellCoords[1]+=FieldParameters.fieldHeight;
	DrawRobots();
}


void CfieldDlg::OnBnClickedDownbtn()
{
	upperleftCellCoords[1] += cameraStep;
	if (upperleftCellCoords[1]>=FieldParameters.fieldHeight)
		upperleftCellCoords[1]-=FieldParameters.fieldHeight;
	DrawRobots();
}


void CfieldDlg::OnBnClickedLeftbtn()
{
	upperleftCellCoords[0] -= cameraStep;
	if (upperleftCellCoords[0]<0)
		upperleftCellCoords[0]+=FieldParameters.fieldWidth;
	DrawRobots();
}


void CfieldDlg::OnBnClickedRightbtn()
{
	upperleftCellCoords[0] += cameraStep;
	if (upperleftCellCoords[0]>=FieldParameters.fieldWidth)
		upperleftCellCoords[0]-=FieldParameters.fieldWidth;
	DrawRobots();
}
