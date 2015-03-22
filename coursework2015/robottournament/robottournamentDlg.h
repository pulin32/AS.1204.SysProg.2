
// robottournamentDlg.h : файл заголовка
//

#pragma once
#include "FieldParameters.h"
#include "CfieldDlg.h"

// диалоговое окно CrobottournamentDlg
class CrobottournamentDlg : public CDialogEx
{
// Создание
public:
	CrobottournamentDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_ROBOTTOURNAMENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CfieldDlg Field;
	data Data;
	afx_msg void OnBnClickedOk();
	int fieldHeight;
	int fieldWidth;
};


