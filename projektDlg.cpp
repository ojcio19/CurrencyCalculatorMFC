
// projektDlg.cpp : implementation file
//

#include "stdafx.h"
#include "projekt.h"
#include "projektDlg.h"
#include "afxdialogex.h"

#include "currency.h"
#include "helpFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CprojektDlg dialog



CprojektDlg::CprojektDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJEKT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CprojektDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, FromCombo, m_comboBoxCtrl);
	DDX_Control(pDX, ToCombo, m_comboBoxCtrl2);
}

BEGIN_MESSAGE_MAP(CprojektDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(txtInput, &CprojektDlg::OnEnChangetxtinput)
	ON_BN_CLICKED(btnCalculate, &CprojektDlg::OnBnClickedbtncalculate)
	ON_CBN_SELCHANGE(FromCombo, &CprojektDlg::OnCbnSelchangeFromcombo)
	ON_CBN_SELCHANGE(ToCombo, &CprojektDlg::OnCbnSelchangeTocombo)
END_MESSAGE_MAP()


// CprojektDlg message handlers

BOOL CprojektDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString str;
	// Add "About..." menu item to system menu.
	
	vector<string> abc = giveCodes();
	for (int i = 0; i < abc.size(); i++) {
		str = abc[i].c_str();
		m_comboBoxCtrl.AddString(str);
		m_comboBoxCtrl2.AddString(str);
	}
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CprojektDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CprojektDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CprojektDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CprojektDlg::OnEnChangetxtinput()
{
	
}


void CprojektDlg::OnBnClickedbtncalculate()
{
	CString _cashIN, _textLEFT, _textRIGHT, _textOUTPUT;

	GetDlgItemText(txtInput, _cashIN);
	m_comboBoxCtrl.GetLBText(m_comboBoxCtrl.GetCurSel(), _textLEFT);
	m_comboBoxCtrl2.GetLBText(m_comboBoxCtrl2.GetCurSel(), _textRIGHT);
	double cash_IN = _ttof(_cashIN);
	double result;
	CT2CA lewy(_textLEFT);
	CT2CA prawy(_textRIGHT);

	// construct a std::string using the LPCSTR input
	string kurs_kupna(lewy);
	string kurs_sprzedazy(prawy);

	
	result = exchange_values(kurs_kupna, kurs_sprzedazy, cash_IN);

	_textOUTPUT.Format(_T("%f"), result);

	SetDlgItemText(txtOutput, _textOUTPUT);
}


void CprojektDlg::OnCbnSelchangeFromcombo()
{
}


void CprojektDlg::OnCbnSelchangeTocombo()
{
	//combo to
}
