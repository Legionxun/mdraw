#pragma once


// setDlg 对话框

class setDlg : public CDialogEx
{
	DECLARE_DYNAMIC(setDlg)

public:
	setDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~setDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	BOOL bfill;
	CComboBox mcom;
	CString wline;
	CString fastr;
	afx_msg void OnClose();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedButton1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnChangeEdit1();
	CString scale;
};
