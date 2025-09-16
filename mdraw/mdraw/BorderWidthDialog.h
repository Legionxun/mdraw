#pragma once
#include "afxwin.h"
#include "resource.h"  // 确保包含 resource.h 文件

class BorderWidthDialog : public CDialogEx
{
public:
    BorderWidthDialog(CWnd* pParent = nullptr);   // 标准构造函数

    enum { IDD = IDD_INPUT_BORDER_WIDTH };  // 使用资源 ID 定义

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

public:
    int m_nBorderWidth;  // 存储边框粗细

    DECLARE_DYNAMIC(BorderWidthDialog)  // 如果需要动态类型识别，保留这一行

        DECLARE_MESSAGE_MAP()
};
