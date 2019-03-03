
#pragma once


// CprojektDlg dialog
class CprojektDlg : public CDialogEx
{
// Construction
public:
	CprojektDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PROJEKT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnEnChangetxtinput();
	afx_msg void OnBnClickedbtncalculate();
	afx_msg void OnCbnSelchangeFromcombo();
	afx_msg void OnCbnSelchangeTocombo();
	CComboBox m_comboBoxCtrl;
	CComboBox m_comboBoxCtrl2;
};
