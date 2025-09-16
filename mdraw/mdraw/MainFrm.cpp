// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "CShape.h"     // 包含 CShape 类定义的头文件
#include "mdrawView.h"  // 包含 CmdrawView 类定义的头文件
#include "MainFrm.h"
#include "Resource.h"
#include "BorderWidthDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
    ON_WM_CREATE()
    ON_COMMAND(ID_CLEAR, &CMainFrame::OnClear) // 添加这一行到现有的消息映射块中
    ON_COMMAND(ID_FILL_COLOR, &CMainFrame::OnFillColor)  // 填充颜色
    ON_COMMAND(ID_INTERSECT_COLOR, &CMainFrame::OnIntersectColor)  // 交集颜色
    ON_COMMAND(ID_BORDER_COLOR, &CMainFrame::OnBorderColor)  // 边框颜色
    ON_COMMAND(ID_BORDER_WIDTH, &CMainFrame::OnBorderWidth)  // 边框粗细


END_MESSAGE_MAP()

static UINT indicators[] =
{
    ID_SEPARATOR,           // 状态行指示器
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
    // TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
        !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
    {
        TRACE0("未能创建工具栏\n");
        return -1;      // 未能创建
    }

    if (!m_wndStatusBar.Create(this))
    {
        TRACE0("未能创建状态栏\n");
        return -1;      // 未能创建
    }
    m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

    // TODO: 如果不需要可停靠工具栏，则删除这三行
    m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_wndToolBar);

    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    if (!CFrameWnd::PreCreateWindow(cs))
        return FALSE;
    // TODO: 在此处通过修改
    //  CREATESTRUCT cs 来修改窗口类或样式

    return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CFrameWnd::Dump(dc);
}
#endif //_DEBUG

// CMainFrame 消息处理程序

void CMainFrame::OnClear()
{
    // 执行清除操作
    AfxMessageBox(_T("清除操作执行"));
    if (CmdrawView::Inst) {
        CmdrawView::Inst->Invalidate();
    }
}
void CMainFrame::OnFillColor()
{
    // 创建颜色选择对话框，初始颜色为当前选中的图形的填充色
    CColorDialog dlg(CShape::sclrfill);
    dlg.m_cc.Flags |= CC_FULLOPEN;  // 显示完整调色板
    dlg.m_cc.Flags |= CC_RGBINIT;   // 使用当前填充色作为默认颜色

    // 如果用户选择了颜色
    if (dlg.DoModal() == IDOK)
    {
        // 获取用户选择的颜色
        CShape::sclrfill = dlg.GetColor();

        // 如果有选中的形状，应用新颜色
        if (CShape::cursel >= 0 && CShape::cursel < CShape::shapes.size())
        {
            // 更新操作类型为填充
            CShape::curopttype = CShape::FILL;

            // 填充当前选中的形状
            CShape::shapes[CShape::cursel]->onfill(true, CShape::sclrfill);

            // 刷新视图，显示新的填充颜色
            CmdrawView::Inst->Invalidate();
        }
    }
}

void CMainFrame::OnBorderColor()
{
    // 创建颜色选择对话框，初始颜色为当前选中的边框颜色
    CColorDialog dlg(CShape::sclrline);
    dlg.m_cc.Flags |= CC_FULLOPEN;  // 显示完整调色板
    dlg.m_cc.Flags |= CC_RGBINIT;   // 使用当前边框颜色作为默认颜色

    // 如果用户选择了颜色
    if (dlg.DoModal() == IDOK)
    {
        // 获取用户选择的颜色
        CShape::sclrline = dlg.GetColor();  // 更新静态变量的边框颜色

        // 如果有选中的形状，应用新颜色
        if (CShape::cursel >= 0 && CShape::cursel < CShape::shapes.size())
        {
            CShape::shapes[CShape::cursel]->clrline = CShape::sclrline;  // 应用边框颜色
            CmdrawView::Inst->Invalidate();  // 刷新视图
        }
    }
}

void CMainFrame::OnBorderWidth()
{
    // 创建并显示边框粗细输入对话框
    BorderWidthDialog dlg;
    dlg.m_nBorderWidth = CShape::swline;  // 设置默认的边框粗细

    if (dlg.DoModal() == IDOK)  // 如果用户点击了“确定”
    {
        CShape::swline = dlg.m_nBorderWidth;  // 更新全局的边框粗细变量

        // 如果有选中的形状，应用新的边框粗细
        if (CShape::cursel >= 0 && CShape::cursel < CShape::shapes.size())
        {
            CShape::shapes[CShape::cursel]->wline = CShape::swline;  // 应用新的边框粗细
            CmdrawView::Inst->Invalidate();  // 刷新视图
        }
    }
}

void CMainFrame::OnIntersectColor()
{
    // 创建颜色选择对话框，初始颜色为当前选中的交集颜色
    CColorDialog dlg(CShape::sclrIntersect);
    dlg.m_cc.Flags |= CC_FULLOPEN;  // 显示完整调色板
    dlg.m_cc.Flags |= CC_RGBINIT;   // 使用当前交集颜色作为默认颜色

    // 如果用户选择了颜色
    if (dlg.DoModal() == IDOK)
    {
        // 获取用户选择的颜色
        CShape::sclrIntersect = dlg.GetColor();  // 更新静态变量的交集颜色

        // 更新所有图形的交集颜色
        for (auto& shape : CShape::shapes) {
            shape->clrIntersect = CShape::sclrIntersect;
        }

        // 刷新视图以显示新的交集颜色
        CmdrawView::Inst->Invalidate();
    }
}

void CMainFrame::OnRotate()
{
    // 设置操作模式为旋转
    CShape::curopttype = CShape::ROTATE;
    // 不再弹出任何对话框
}

void CMainFrame::OnScale()
{
    // 设置操作模式为缩放
    CShape::curopttype = CShape::SCALE;
    // 不再弹出任何对话框
}
