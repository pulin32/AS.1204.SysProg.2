
// robottournamentDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "robottournament.h"
#include "robottournamentDlg.h"
#include "afxdialogex.h"
#include <fstream>
//#include "CfieldDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// диалоговое окно CrobottournamentDlg



CrobottournamentDlg::CrobottournamentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CrobottournamentDlg::IDD, pParent)
	, fieldHeight(1000)
	, fieldWidth(1000)
	, PathToDllList(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CrobottournamentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, fieldHeight);
	DDX_Text(pDX, IDC_EDIT2, fieldWidth);
	DDX_Text(pDX, IDC_EDIT_DLLLIST, PathToDllList);
}

BEGIN_MESSAGE_MAP(CrobottournamentDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CrobottournamentDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_LOADDLL, &CrobottournamentDlg::OnBnClickedButtonLoaddll)
END_MESSAGE_MAP()


// обработчики сообщений CrobottournamentDlg

BOOL CrobottournamentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна. Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	robotsNumber = 0;

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CrobottournamentDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок. Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CrobottournamentDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CrobottournamentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CrobottournamentDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	
	//data *Data = new data;
	UpdateData();
	if (fieldHeight < 20 || fieldWidth < 20)
		AfxMessageBox("Поле слишком маленькое");
	else if (robotsNumber == 0)
		AfxMessageBox("Роботы не загружены");
	else
	{
		Data.fieldHeight = fieldHeight;
		Data.fieldWidth = fieldWidth;
		Data.rivals=robotsNumber;
		Field.FieldParameters = Data;

		Field.matrix = new int*[fieldWidth];
		for (int i=0; i<fieldWidth; i++)
			Field.matrix[i] = new int[fieldHeight];
		for (int i=0; i<fieldWidth; i++)
		{
			for (int j=0; j<fieldHeight; j++)
				Field.matrix[i][j] = -1;
		}

		LoadRobots();
		Field.matrix[10][3] = 100;		//TEST!!!!!!!!!!!!!!!!!!!!!!
		/*Field.matrix[5][8] = 1;		//////////////
		Field.matrix[25][10] = 1;		//////////////right
		Field.matrix[30][8] = 1;		//////////////
		Field.matrix[21][10] = 1;		//////////////
		Field.matrix[10][21] = 1;		//////////////bottom
		Field.matrix[15][30] = 1;		//////////////
		Field.matrix[7][24] = 1;		//////////////
		Field.matrix[999][5] = 1;		//////////////left
		Field.matrix[995][8] = 1;		//////////////
		Field.matrix[7][998] = 1;		//////////////up
		Field.matrix[10][993] = 1;		//////////////    */

		this->ShowWindow(SW_HIDE);
		Field.DoModal();
		CDialogEx::OnOK();
	}
}


void CrobottournamentDlg::OnBnClickedButtonLoaddll()
{
	UpdateData();
	robotsNumber = 0;
	CFileDialog fd(true);
	if (fd.DoModal()==IDOK) 
	{ 
		PathToDllList=fd.GetPathName();
		UpdateData(false);
		CountRobots();
	} 
}


void CrobottournamentDlg::CountRobots()
{
	ifstream List(PathToDllList);
	char c;
	char buffer[3];
	while(List.get(c))
	{
		if (c=='.')
		{
			if (List.read(buffer,3) && buffer[0] == 'd' && buffer[1] == 'l' && buffer[2] == 'l')
				robotsNumber++;
			else
			{
				List.unget(); List.unget(); List.unget();
			}
		}
	}
	List.close();
}


void CrobottournamentDlg::LoadRobots()
{
	Field.robots = new robot[Data.rivals];
	ifstream List(PathToDllList);
	char c;
	char buffer[3];
	string name = "";
	int i = 0;
	//HINSTANCE hLib;
	srand (time(NULL));;
	while(List.get(c))
	{
		if (c=='.')
		{
			if (List.read(buffer,3) && buffer[0] == 'd' && buffer[1] == 'l' && buffer[2] == 'l')
			{
				Field.robots[i].name = name.c_str();
				name+=".dll";
				Field.robots[i].Library = LoadLibrary("name");
				//Field.robots[i].DoStep = (robobrain)GetProcAddress(hLib, "DoStep");
				Field.robots[i++].color = RGB(rand() % 256, rand() % 256, rand() % 256);
				name="";
			}
			else
			{
				List.unget(); List.unget(); List.unget();
				name+=c;
			}
		}
		else
			if (c != '\n')
				name+=c;
	}
	List.close();
}