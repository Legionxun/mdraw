#pragma once
#include "afxwin.h"
#include "resource.h"  // ȷ������ resource.h �ļ�

class BorderWidthDialog : public CDialogEx
{
public:
    BorderWidthDialog(CWnd* pParent = nullptr);   // ��׼���캯��

    enum { IDD = IDD_INPUT_BORDER_WIDTH };  // ʹ����Դ ID ����

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

public:
    int m_nBorderWidth;  // �洢�߿��ϸ

    DECLARE_DYNAMIC(BorderWidthDialog)  // �����Ҫ��̬����ʶ�𣬱�����һ��

        DECLARE_MESSAGE_MAP()
};
