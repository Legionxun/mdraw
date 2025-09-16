#include "pch.h"  // 或者 stdafx.h，依据你的项目设置
#include "BorderWidthDialog.h"

IMPLEMENT_DYNAMIC(BorderWidthDialog, CDialogEx)  // 如果不需要动态类型支持，可以移除这一行

BorderWidthDialog::BorderWidthDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_INPUT_BORDER_WIDTH, pParent)
{
    m_nBorderWidth = 1;  // 默认边框粗细
}

void BorderWidthDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_BORDER_WIDTH, m_nBorderWidth);  // 使用 1012 作为 IDC_EDIT_BORDER_WIDTH
    DDV_MinMaxInt(pDX, m_nBorderWidth, 1, 10);  // 限制边框粗细的范围
}

BEGIN_MESSAGE_MAP(BorderWidthDialog, CDialogEx)
END_MESSAGE_MAP()
