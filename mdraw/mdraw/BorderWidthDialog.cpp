#include "pch.h"  // ���� stdafx.h�����������Ŀ����
#include "BorderWidthDialog.h"

IMPLEMENT_DYNAMIC(BorderWidthDialog, CDialogEx)  // �������Ҫ��̬����֧�֣������Ƴ���һ��

BorderWidthDialog::BorderWidthDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_INPUT_BORDER_WIDTH, pParent)
{
    m_nBorderWidth = 1;  // Ĭ�ϱ߿��ϸ
}

void BorderWidthDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_BORDER_WIDTH, m_nBorderWidth);  // ʹ�� 1012 ��Ϊ IDC_EDIT_BORDER_WIDTH
    DDV_MinMaxInt(pDX, m_nBorderWidth, 1, 10);  // ���Ʊ߿��ϸ�ķ�Χ
}

BEGIN_MESSAGE_MAP(BorderWidthDialog, CDialogEx)
END_MESSAGE_MAP()
