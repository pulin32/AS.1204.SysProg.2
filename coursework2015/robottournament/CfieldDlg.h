#pragma once

#include "Parameters.h"

using namespace std;
// диалоговое окно CfieldDlg

class CfieldDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CfieldDlg)

public:
	CfieldDlg(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CfieldDlg();

// Данные диалогового окна
	enum { IDD = IDD_FIELDDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	fieldData FieldParameters;
	CString *Dlls;
	CRect DrawArea;
	int n;
	int **matrix;
	int upperleftCellCoords[2];
<<<<<<< HEAD
	robot **robots;
	object **objects;
	void DrawRobot(int x, int y, /*int r, int g, int b*/ COLORREF color);
	void DrawObject(int x, int y, int type);
=======
	robot *robots;
	void DrawRobot(int x, int y, /*int r, int g, int b*/ COLORREF color);
>>>>>>> origin/master
	void DrawRobots();
	//UINT thread(LPVOID pParam);
	int actingRobot;
	//step *Step;
	void Play();
	step *history;
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
	afx_msg void OnBnClickedUpbtn();
	afx_msg void OnBnClickedDownbtn();
	afx_msg void OnBnClickedLeftbtn();
	afx_msg void OnBnClickedRightbtn();
};

