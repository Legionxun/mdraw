
// mdrawView.h: CmdrawView 类的接口
//

#pragma once
#include "CShape.h"
#include "setDlg.h"
#include "mdrawDoc.h"
#include "setAngleDlg.h"
class CmdrawView : public CView
{
protected: // 仅从序列化创建
	CmdrawView() noexcept;
	DECLARE_DYNCREATE(CmdrawView)
	static CmdrawView *Inst;
	setDlg mdlg;
// 特性
public:
	CmdrawDoc* GetDocument() const;

// 操作
public:
	setAngleDlg m_rotateDlg;  // 使用现有的角度输入对话框实例

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CmdrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLine();
	afx_msg void OnRect();
	afx_msg void OnBox();
	afx_msg void OnEllipse();
	afx_msg void OnCircle();
	afx_msg void OnTri1();
	afx_msg void OnTri2();
	afx_msg void OnTri3();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMove();
	afx_msg void OnRotate();
	afx_msg void OnSet();
	afx_msg void OnClear();
	afx_msg void OnUpdateLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateBox(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEllipse(CCmdUI *pCmdUI);
	afx_msg void OnUpdateCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTri1(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTri2(CCmdUI *pCmdUI);
	afx_msg void OnUpdateTri3(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMove(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRotate(CCmdUI *pCmdUI);
	afx_msg void OnScale();
	afx_msg void OnUpdateScale(CCmdUI *pCmdUI);
	afx_msg void Onfill();
	afx_msg void OnUpdatefill(CCmdUI *pCmdUI);
	afx_msg void OnTri4();
	afx_msg void OnUpdateTri4(CCmdUI *pCmdUI);
	afx_msg void OnRotateByAngle();  
	afx_msg void OnUpdateRotateByAngle(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // mdrawView.cpp 中的调试版本
inline CmdrawDoc* CmdrawView::GetDocument() const
   { return reinterpret_cast<CmdrawDoc*>(m_pDocument); }
#endif

