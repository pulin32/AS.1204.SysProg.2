// CfieldDlg.cpp: файл реализации
//

//#pragma comment(lib,"../robotbase/robotbase.lib")
//#include "../robotbase/robotbase.h"

#include "stdafx.h"
#include "robottournament.h"
#include "CfieldDlg.h"
#include "afxdialogex.h"


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
	//for (int i=0;i<FieldParameters.rivals;i++)
		//FreeLibrary(robots[i].Library);
			//delete robots[i].Library;
	//delete robots;
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

void CfieldDlg::DrawRobots()
{
	Invalidate();
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
			if (matrix[xreal][yreal] != -1)
				DrawRobot(xlocal,ylocal,robots[matrix[xreal][yreal]].color);
			ylocal++;
		}
		xlocal++;
		ylocal = 0;
	}
}


//typedef void (*PF)();

void CfieldDlg::OnBnClickedButton1()
{
	/*HINSTANCE hLib = LoadLibrary("robotbase.dll");
	PF ff = (PF)GetProcAddress(hLib, "DoStep");
	ff();*/

	srand (time(NULL));
	int xrand = 0;
	int yrand = 0;
	for (int i=0; i<FieldParameters.rivals; i++)
	{
		do
		{
			xrand = rand() % FieldParameters.fieldWidth;
			yrand = rand() % FieldParameters.fieldHeight;
		}
		while (matrix[xrand][yrand] != -1);
		matrix[xrand][yrand] = i;
		robots[i].x = xrand;
		robots[i].y = yrand;
	}

	DrawRobots();
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
