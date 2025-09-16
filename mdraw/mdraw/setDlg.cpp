// setDlg.cpp: 实现文件
//

#include "pch.h"
#include "mdraw.h"
#include "setDlg.h"
#include "afxdialogex.h"
#include "CShape.h"
#include "mdrawView.h"
// setDlg 对话框

IMPLEMENT_DYNAMIC(setDlg, CDialogEx)

setDlg::setDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, bfill(FALSE)
	, wline(_T("1"))

{

}

setDlg::~setDlg()
{
}

void setDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, bfill);
	DDX_Control(pDX, IDC_COMBO1, mcom);
	DDX_Text(pDX, IDC_EDIT1, wline);


}



BEGIN_MESSAGE_MAP(setDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBO1, &setDlg::OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON4, &setDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_CHECK1, &setDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON1, &setDlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_FILL_COLOR, &setDlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &setDlg::OnChangeEdit1)
END_MESSAGE_MAP()


// setDlg 消息处理程序


BOOL setDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mcom.AddString(_T("实线"));
	mcom.AddString(_T("虚线"));
	mcom.AddString(_T("点划线"));
	mcom.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void setDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
}


void setDlg::OnSelchangeCombo1()
{
	CShape::stline = mcom.GetCurSel();

	if (CShape::cursel >= 0 && CShape::cursel < CShape::shapes.size())
	{

		CShape::shapes[CShape::cursel]->tline = CShape::stline;
		CmdrawView::Inst->Invalidate();
	}
}


void setDlg::OnBnClickedButton4()
{
	UpdateData();
	CShape::swline = _wtoi(wline);
	if (CShape::swline < 1)
	{
		CShape::swline = 1;
		wline = _T("1");
	}
}



void setDlg::OnBnClickedButton1()
{
	CColorDialog dlg(CShape::sclrline);
	dlg.m_cc.Flags |= CC_FULLOPEN;
	dlg.m_cc.Flags |= CC_RGBINIT;
	if (dlg.DoModal() == IDOK)
	{
		CShape::sclrline = dlg.GetColor();

		if (CShape::cursel >= 0 && CShape::cursel < CShape::shapes.size())
		{

			CShape::shapes[CShape::cursel]->clrline = CShape::sclrline;
			CmdrawView::Inst->Invalidate();
		}

		Invalidate();
	}
}
void setDlg::OnBnClickedButton2()
{
	CColorDialog dlg(CShape::sclrfill);
	dlg.m_cc.Flags |= CC_FULLOPEN;
	dlg.m_cc.Flags |= CC_RGBINIT;

	if (dlg.DoModal() == IDOK)
	{
		CShape::sclrfill = dlg.GetColor();

		if (CShape::cursel >= 0 && CShape::cursel < CShape::shapes.size())
		{
			CShape::curopttype = CShape::FILL;
			CShape::shapes[CShape::cursel]->onfill(CShape::shapes[CShape::cursel]->bfill, CShape::sclrfill);
			CmdrawView::Inst->Invalidate();
		}

		Invalidate();
	}
}




void setDlg::OnBnClickedCheck1()
{
	UpdateData();
	CShape::curopttype = CShape::FILL;
	if (CShape::cursel >= 0 && CShape::cursel < CShape::shapes.size())
	{
		CShape::shapes[CShape::cursel]->onfill(bfill, CShape::sclrfill);
		CmdrawView::Inst->Invalidate();
	}
	CShape::sbfill = bfill;
}





HBRUSH setDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	CRect rc;
	pWnd->GetClientRect(rc);
	if (pWnd->GetDlgCtrlID() == IDC_STATIC1)
	{
		pDC->FillSolidRect(rc, CShape::sclrline);
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATIC2)
	{
		pDC->FillSolidRect(rc, CShape::sclrfill);
		return (HBRUSH)GetStockObject(NULL_BRUSH);
	}
	return hbr;
}




void setDlg::OnChangeEdit1()
{
	UpdateData();
	CShape::swline = _wtoi(wline);
	if (CShape::swline < 1)
	{
		CShape::swline = 1;
		wline = _T("1");
	}
	else if (CShape::swline > 50)
	{
		CShape::swline = 50;
		wline = _T("50");
	}

	if (CShape::cursel >= 0 && CShape::cursel < CShape::shapes.size())
	{

		CShape::shapes[CShape::cursel]->wline = CShape::swline;
		CmdrawView::Inst->Invalidate();
	}
}


