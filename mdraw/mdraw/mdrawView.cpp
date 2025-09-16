// mdrawView.cpp: CmdrawView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "mdraw.h"
#endif

#include "mdrawDoc.h"
#include "mdrawView.h"
#include "setAngleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmdrawView

IMPLEMENT_DYNCREATE(CmdrawView, CView)

BEGIN_MESSAGE_MAP(CmdrawView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_LINE, &CmdrawView::OnLine)
	ON_COMMAND(ID_RECT, &CmdrawView::OnRect)
	ON_COMMAND(ID_BOX, &CmdrawView::OnBox)
	ON_COMMAND(ID_ELLIPSE, &CmdrawView::OnEllipse)
	ON_COMMAND(ID_CIRCLE, &CmdrawView::OnCircle)
	ON_COMMAND(ID_TRI1, &CmdrawView::OnTri1)
	ON_COMMAND(ID_TRI2, &CmdrawView::OnTri2)
	ON_COMMAND(ID_TRI3, &CmdrawView::OnTri3)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_MOVE, &CmdrawView::OnMove)
	ON_COMMAND(ID_ROTATE, &CmdrawView::OnRotate)
	ON_COMMAND(ID_SET, &CmdrawView::OnSet)
	ON_COMMAND(ID_CLEAR, &CmdrawView::OnClear)
	ON_UPDATE_COMMAND_UI(ID_LINE, &CmdrawView::OnUpdateLine)
	ON_UPDATE_COMMAND_UI(ID_BOX, &CmdrawView::OnUpdateBox)
	ON_UPDATE_COMMAND_UI(ID_RECT, &CmdrawView::OnUpdateRect)
	ON_UPDATE_COMMAND_UI(ID_ELLIPSE, &CmdrawView::OnUpdateEllipse)
	ON_UPDATE_COMMAND_UI(ID_CIRCLE, &CmdrawView::OnUpdateCircle)
	ON_UPDATE_COMMAND_UI(ID_TRI1, &CmdrawView::OnUpdateTri1)
	ON_UPDATE_COMMAND_UI(ID_TRI2, &CmdrawView::OnUpdateTri2)
	ON_UPDATE_COMMAND_UI(ID_TRI3, &CmdrawView::OnUpdateTri3)
	ON_UPDATE_COMMAND_UI(ID_MOVE, &CmdrawView::OnUpdateMove)
	ON_UPDATE_COMMAND_UI(ID_ROTATE, &CmdrawView::OnUpdateRotate)
	ON_COMMAND(ID_SCALE, &CmdrawView::OnScale)
	ON_UPDATE_COMMAND_UI(ID_SCALE, &CmdrawView::OnUpdateScale)
	ON_COMMAND(ID_fill, &CmdrawView::Onfill)
	ON_UPDATE_COMMAND_UI(ID_fill, &CmdrawView::OnUpdatefill)
	ON_COMMAND(ID_TRI4, &CmdrawView::OnTri4)
	ON_UPDATE_COMMAND_UI(ID_TRI4, &CmdrawView::OnUpdateTri4)
	ON_COMMAND(ID_ROTATE_BY_ANGLE, &CmdrawView::OnRotateByAngle) 
	ON_UPDATE_COMMAND_UI(ID_ROTATE_BY_ANGLE, &CmdrawView::OnUpdateRotateByAngle) 
END_MESSAGE_MAP()

// CmdrawView 构造/析构
CmdrawView *CmdrawView::Inst = NULL;;
CmdrawView::CmdrawView() noexcept
{
	Inst = this;
	ULONG_PTR m_gdiplusToken;
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);
}

CmdrawView::~CmdrawView()
{
}

BOOL CmdrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CmdrawView 绘图

void CmdrawView::OnDraw(CDC* pDC)
{
	CmdrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rect;
	GetClientRect(&rect);

	CDC mdc;
	mdc.CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	mdc.SelectObject(&bmp);
	mdc.FillSolidRect(rect, RGB(255, 255, 255));

	CShape::drawtmptriangle(&mdc);
	
	// 计算交集
	CShape::calculateIntersections();
	
	// 绘制图形
	int len = CShape::shapes.size();
	for (int i = 0;i < len;i++)
	{
		CShape::shapes[i]->draw(&mdc);
	}
	
	// 填充交集区域
	CShape::fillIntersections(&mdc);
	
	if (CShape::curopttype == CShape::ROTATE)
	{
	/*	CPen pen, *ppen;
		pen.CreatePen(1, 1, RGB(0, 0, 0));
		ppen = mdc.SelectObject(&pen);
		mdc.MoveTo(CShape::point1);
		mdc.LineTo(CShape::point2);
		mdc.SelectObject(ppen);
		pen.DeleteObject();*/
	}
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &mdc, 0, 0, SRCCOPY);
	DeleteObject(bmp);
	DeleteObject(mdc);
	
	
}


// CmdrawView 打印

BOOL CmdrawView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CmdrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CmdrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CmdrawView 诊断

#ifdef _DEBUG
void CmdrawView::AssertValid() const
{
	CView::AssertValid();
}

void CmdrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmdrawDoc* CmdrawView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmdrawDoc)));
	return (CmdrawDoc*)m_pDocument;
}
#endif //_DEBUG


// CmdrawView 消息处理程序


void CmdrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	CShape::OnLButtonDown(point);
	if (mdlg.m_hWnd != NULL)
	{
		if (mdlg.IsWindowVisible())
		{
			if (CShape::cursel >= 0 && CShape::cursel < CShape::shapes.size())
			{

				mdlg.bfill = CShape::shapes[CShape::cursel]->bfill;
				mdlg.mcom.SetCurSel(CShape::shapes[CShape::cursel]->tline);
				mdlg.wline.Format(_T("%d"), CShape::shapes[CShape::cursel]->wline);
				mdlg.fastr.Format(_T("%.1f"), CShape::shapes[CShape::cursel]->angle);
				mdlg.scale.Format(_T("%.1f"), CShape::shapes[CShape::cursel]->scale);
				mdlg.UpdateData(FALSE);
				mdlg.Invalidate();
			}
		}
	}
	

	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}


void CmdrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CShape::OnLButtonUp(point);
	Invalidate();

	CView::OnLButtonUp(nFlags, point);
}


void CmdrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	CDC *pDC = GetDC();
	CShape::OnMouseMove(point, pDC);
	if (CShape::curopttype == CShape::MOVE || CShape::curopttype == CShape::ROTATE
		|| CShape::curopttype == CShape::SCALE)
	{	
		CShape::calculateIntersections();
		Invalidate();
		if (CShape::curopttype == CShape::ROTATE|| CShape::curopttype == CShape::SCALE)
		{
			if (mdlg.m_hWnd != NULL)
			{
				if (mdlg.IsWindowVisible())
				{
					if (CShape::cursel >= 0 && CShape::cursel < CShape::shapes.size())
					{
						mdlg.fastr.Format(_T("%.1f"), CShape::shapes[CShape::cursel]->angle);
						mdlg.scale.Format(_T("%.1f"), CShape::shapes[CShape::cursel]->scale);
						mdlg.UpdateData(FALSE);
					}
				}
			}

		}
	}
	CView::OnMouseMove(nFlags, point);
}


void CmdrawView::OnRButtonUp(UINT nFlags, CPoint point)
{

	CShape::OnRButtonUp(point);
	Invalidate();
	CView::OnRButtonUp(nFlags, point);
}


void CmdrawView::OnLine()
{
	CShape::curopttype = CShape::DRAW;
	CShape::smtype = CShape::LINE;
	Invalidate();
}


void CmdrawView::OnRect()
{
	CShape::curopttype = CShape::DRAW;
	CShape::smtype = CShape::RECT;
	Invalidate();
}


void CmdrawView::OnBox()
{
	CShape::curopttype = CShape::DRAW;
	CShape::smtype = CShape::SQUARE;
	Invalidate();
}


void CmdrawView::OnEllipse()
{
	CShape::curopttype = CShape::DRAW;
	CShape::smtype = CShape::ELLIPSE;
	Invalidate();
}


void CmdrawView::OnCircle()
{
	CShape::curopttype = CShape::DRAW;
	CShape::smtype = CShape::CIRCLE;
	Invalidate();
}


void CmdrawView::OnTri1()
{
	CShape::curopttype = CShape::DRAW;
	CShape::smtype = CShape::TRIANGLE1;
	Invalidate();
}


void CmdrawView::OnTri2()
{
	CShape::curopttype = CShape::DRAW;
	CShape::smtype = CShape::TRIANGLE2;
	Invalidate();
}


void CmdrawView::OnTri3()
{
	CShape::curopttype = CShape::DRAW;
	CShape::smtype = CShape::TRIANGLE3;
	Invalidate();
}

void CmdrawView::OnTri4()
{
	CShape::curopttype = CShape::DRAW;
	CShape::smtype = CShape::TRIANGLE4;
	Invalidate();
}

BOOL CmdrawView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return true;
	return CView::OnEraseBkgnd(pDC);
}


void CmdrawView::OnMove()
{
	
	CShape::curopttype = CShape::MOVE;
}


void CmdrawView::OnRotate()
{

	CShape::curopttype = CShape::ROTATE;
	OnSet();
}

void CmdrawView::Onfill()
{
	CShape::curopttype = CShape::FILL;
	OnSet();
}

void CmdrawView::OnScale()
{
	CShape::curopttype = CShape::SCALE;
	OnSet();
}
void CmdrawView::OnSet()
{

}


void CmdrawView::OnClear()
{
	CShape::clear();
	Invalidate();
}


void CmdrawView::OnUpdateLine(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(CShape::smtype == CShape::LINE&&CShape::curopttype == CShape::DRAW);
}


void CmdrawView::OnUpdateBox(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(CShape::smtype == CShape::SQUARE&&CShape::curopttype == CShape::DRAW);
}


void CmdrawView::OnUpdateRect(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(CShape::smtype == CShape::RECT&&CShape::curopttype == CShape::DRAW);
}


void CmdrawView::OnUpdateEllipse(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(CShape::smtype == CShape::ELLIPSE&&CShape::curopttype == CShape::DRAW);
}


void CmdrawView::OnUpdateCircle(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(CShape::smtype == CShape::CIRCLE&&CShape::curopttype == CShape::DRAW);
}


void CmdrawView::OnUpdateTri1(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(CShape::smtype == CShape::TRIANGLE1&&CShape::curopttype == CShape::DRAW);
}


void CmdrawView::OnUpdateTri2(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(CShape::smtype == CShape::TRIANGLE2&&CShape::curopttype == CShape::DRAW);
}


void CmdrawView::OnUpdateTri3(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(CShape::smtype == CShape::TRIANGLE3&&CShape::curopttype == CShape::DRAW);
}



void CmdrawView::OnUpdateTri4(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(CShape::smtype == CShape::TRIANGLE4&&CShape::curopttype == CShape::DRAW);
}
void CmdrawView::OnUpdateMove(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(CShape::curopttype == CShape::MOVE);
}


void CmdrawView::OnUpdateRotate(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(CShape::curopttype == CShape::ROTATE);
}





void CmdrawView::OnUpdateScale(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(CShape::curopttype == CShape::SCALE);
}



void CmdrawView::OnUpdatefill(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(CShape::curopttype == CShape::FILL);
}

void CmdrawView::OnRotateByAngle()
{
	if (CShape::cursel < 0 || CShape::cursel >= CShape::shapes.size()) {
		AfxMessageBox(_T("请先选择一个图形！"));
		return;
	}
	setAngleDlg dlg;
	if (dlg.DoModal() == IDOK) {
		float angle = dlg.m_fAngle;
		CShape::shapes[CShape::cursel]->rotateTo(CShape::shapes[CShape::cursel]->angle + angle);
		Invalidate();
	}
}

void CmdrawView::OnUpdateRotateByAngle(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(CShape::cursel >= 0 && CShape::cursel < CShape::shapes.size());
}
