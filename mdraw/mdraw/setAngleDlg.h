#pragma once
#include "afxwin.h"
#include "resource.h"

// setAngleDlg

class setAngleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(setAngleDlg)

public:
	setAngleDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~setAngleDlg();

// 对话框数据
	enum { IDD = IDD_INPUT_ROTATE_ANGLE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editAngle;
	float m_fAngle;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};