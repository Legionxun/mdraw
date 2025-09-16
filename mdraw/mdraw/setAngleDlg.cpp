// setAngleDlg.cpp : 实现文件
//

#include "pch.h"
#include "mdraw.h"
#include "setAngleDlg.h"
#include "afxdialogex.h"


// setAngleDlg

IMPLEMENT_DYNAMIC(setAngleDlg, CDialogEx)

setAngleDlg::setAngleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(setAngleDlg::IDD, pParent)
	, m_fAngle(0)
{

}

setAngleDlg::~setAngleDlg()
{
}

void setAngleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ROTATE_ANGLE, m_editAngle);
	DDX_Text(pDX, IDC_EDIT_ROTATE_ANGLE, m_fAngle);
}


BEGIN_MESSAGE_MAP(setAngleDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &setAngleDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// setAngleDlg 


BOOL setAngleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置默认角度值为0
	m_fAngle = 0;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void setAngleDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	CDialogEx::OnOK();
}