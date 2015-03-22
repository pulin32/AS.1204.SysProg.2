// CfieldDlg.cpp: файл реализации
//

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
	//matrix = (int*)malloc(FieldParameters.fieldHeight*FieldParameters.fieldWidth*sizeof(int));
	//matrix = new int*[FieldParameters.fieldWidth];
	//for (int i=0; i<FieldParameters.fieldWidth; i++)
	//	matrix[i] = new int[FieldParameters.fieldHeight];
	//matrix[1][1] = 1;
}

CfieldDlg::~CfieldDlg()
{
	for (int i=0;i<FieldParameters.fieldWidth;i++)
		delete matrix[i];
	delete matrix;
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

	
	//AfxMessageBox(_T("Simple message box."));
}

void CfieldDlg::DrawRobot(int x, int y, int r = 0, int g = 255, int b = 0)
{
	CClientDC dc(this);
	GetClientRect(&DrawArea);
	CPen Pen(PS_SOLID,2,RGB(r,g,b));
	dc.SelectObject(Pen);
	int side = DrawArea.bottom/n;
	Ellipse(dc,x*side+1,y*side+1,x*side+side,y*side+side);
}

void CfieldDlg::DrawRobots()
{
	Invalidate();
	OnPaint();
	int xlocal = 0;
	int ylocal = 0;
	for (int x = upperleftCellCoords[0]; x < upperleftCellCoords[0]+n; x++)
	{
		for (int y = upperleftCellCoords[1]; y < upperleftCellCoords[1]+n; y++)
		{
			if (matrix[x][y])
				DrawRobot(xlocal,ylocal);
			ylocal++;
		}
		xlocal++;
		ylocal = 0;
	}
}

void CfieldDlg::OnBnClickedButton1()
{
	//Invalidate();
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
	DrawRobots();
}


void CfieldDlg::OnBnClickedDownbtn()
{
	upperleftCellCoords[1] += cameraStep;
	DrawRobots();
}


void CfieldDlg::OnBnClickedLeftbtn()
{
	upperleftCellCoords[0] -= cameraStep;
	DrawRobots();
}


void CfieldDlg::OnBnClickedRightbtn()
{
	upperleftCellCoords[0] += cameraStep;
	DrawRobots();
}
