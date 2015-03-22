#pragma once

#include "FieldParameters.h"

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
	data FieldParameters;
	CRect DrawArea;
	int n;
	int **matrix;
	int upperleftCellCoords[2];
	void DrawRobot(int x, int y, int r, int g, int b);
	void DrawRobots();
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
	afx_msg void OnBnClickedUpbtn();
	afx_msg void OnBnClickedDownbtn();
	afx_msg void OnBnClickedLeftbtn();
	afx_msg void OnBnClickedRightbtn();
};

