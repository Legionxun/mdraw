
// MainFrm.h: CMainFrame 类的接口
//

#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:
public:
	// 声明旋转和缩放函数
	afx_msg void OnRotate();   // 旋转功能
	afx_msg void OnScale();    // 缩放功能
	afx_msg void OnIntersectColor(); // 交集颜色选择
public:
	// 添加这两个函数的声明
	afx_msg void OnBorderColor();   // 边框颜色选择
	afx_msg void OnBorderWidth();   // 边框粗细输入
public:
	afx_msg void OnFillColor();  // 声明函数
// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	afx_msg void OnClear();

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

};


