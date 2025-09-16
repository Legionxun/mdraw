#include "pch.h"
#include "CShape.h"
#include "mdrawView.h" 

CmdrawView* theView = nullptr;

vector<CShape*> CShape::shapes;
vector<CPoint> CShape::spoints;
bool CShape::sbmd = false;
bool CShape::sbfill = false;
int CShape::swline = 1;
int CShape::stline = 0;
COLORREF CShape::sclrline = RGB(0, 0, 0);
COLORREF CShape::sclrfill = RGB(255, 255, 255);
COLORREF CShape::sclrIntersect = RGB(255, 0, 0);
CShape::etype CShape::smtype = CShape::LINE;
CPoint CShape::point1;
CPoint CShape::point2;
CPoint CShape::org;
int CShape::cursel = -1;
CShape::opttype CShape::curopttype = CShape::DRAW;
int CShape::state = 0;
vector<CShape::IntersectionInfo> CShape::intersections;

IMPLEMENT_SERIAL(CShape, CObject, 1)

CShape &CShape ::operator = (const CShape & tmp)
{
	wline = tmp.wline;
	tline = tmp.tline;
	clrline = tmp.clrline;
	clrfill = tmp.clrfill;
	bfill = tmp.bfill;
	ogrpoints = tmp.ogrpoints;
	mtype = tmp.mtype;
	return *this;
}

CShape::CShape(const CShape  & tmp)
{
	wline = tmp.wline;
	tline = tmp.tline;
	clrline = tmp.clrline;
	clrfill = tmp.clrfill;
	bfill = tmp.bfill;
	ogrpoints = tmp.ogrpoints;
	mtype = tmp.mtype;
}

COLORREF CShape::blendColors(COLORREF color1, COLORREF color2) {
	int red = min(GetRValue(color1) + GetRValue(color2), 255);
	int green = min(GetGValue(color1) + GetGValue(color2), 255);
	int blue = min(GetBValue(color1) + GetBValue(color2), 255);
	return RGB(red, green, blue);
}

void CShape::onedgesel(CPoint pt)
{
	idsel = -1;
	for (int i = 0;i < edges.size();i++)
	{
		if (edges[i].PtInRect(pt))
		{
			idsel = i;
			break;
		}
	}
}

void CShape::setcenter()
{
	int len = curpoints.size();
	if (len < 1)
	{
		return;
	}
	int x = 0;
	int y = 0;
	for (int i = 0;i < len;i++) 
	{
		x += curpoints[i].x;
		y += curpoints[i].y;
	}
	center.x = x / len;
	center.y = y / len;
}

void CShape::OnRButtonUp(CPoint point)
{
	if (cursel >= 0 && cursel < shapes.size()) //ȡ��ѡ��
	{
		shapes[cursel]->bsel = false;
	}
	cursel = -1;

	if (CShape::smtype != TRIANGLE1 && CShape::smtype != TRIANGLE2
		&& CShape::smtype != TRIANGLE3 && CShape::smtype != TRIANGLE4&&sbmd)
	{
		state = 1; //������ͼ
	}
	sbmd = false;
	spoints.clear(); //��ն��ͼ�ε�
}

void CShape::OnLButtonUp(CPoint point, bool bs)
{
	sbmd = false;
	if (state == 1&&CShape::smtype!=TRIANGLE1 && 
		CShape::smtype != TRIANGLE2 && CShape::smtype != TRIANGLE3 && CShape::smtype != TRIANGLE4)
	{
		state = 0;
		return;
	}
	if (curopttype == opttype::DRAW)
	{
		CPoint vec = point2 - point1;
		int d = vec.x*vec.x + vec.y*vec.y;
		if (!bs) //�߶�̫�̲���ͼ��
		{
			if (d < 5)
			{
				return;
			}
		}
		//����ͼ��
		CShape *tmp=new CShape();
		tmp->wline = swline;
		tmp->tline = stline;
		tmp->clrfill = sclrfill;
		tmp->clrline = sclrline;
		tmp->bfill = sbfill;
		tmp->mtype = smtype;


		CPoint pt1;
		CPoint pt2;
		CPoint pt3;
		pt1.x = min(point1.x, point.x);
		pt1.y = min(point1.y, point.y);
		pt2.x = max(point1.x, point.x);
		pt2.y = max(point1.y, point.y);
		int len = min(abs(vec.x), abs(vec.y));
		//����ͼ��
		if (smtype == CShape::LINE ) 
		{
			tmp->ogrpoints.push_back(point1);
			pt1 = point1;
			pt1.x = point2.x;
			tmp->ogrpoints.push_back(pt1);
			tmp->ogrpoints.push_back(point2);
			pt1 = point1;
			pt1.y = point2.y;
			tmp->ogrpoints.push_back(pt1);
		}
		else if (smtype == CShape::RECT|| smtype == CShape::ELLIPSE)
		{
			tmp->ogrpoints.push_back(point1);
			pt1 = point1;
			pt1.x = point2.x;
			tmp->ogrpoints.push_back(pt1);
			tmp->ogrpoints.push_back(point2);
			pt1 = point1;
			pt1.y = point2.y;
			tmp->ogrpoints.push_back(pt1);
		}
		else if (smtype == CShape::SQUARE|| smtype == CShape::CIRCLE)
		{
			tmp->ogrpoints.push_back(point1);
			pt1 = point1;
			pt1.x = point2.x;
			tmp->ogrpoints.push_back(pt1);
			tmp->ogrpoints.push_back(point2);
			pt1 = point1;
			pt1.y = point2.y;
			tmp->ogrpoints.push_back(pt1);
		}
		else if (smtype == etype::TRIANGLE1)
		{
			if (spoints.size() >= 3)
			{
				for (int i=0;i<3;i++)
				{
					tmp->ogrpoints.push_back(spoints[i]);
				}
				spoints.clear();
			}
		}
		else if (smtype == etype::TRIANGLE2) //����
		{
			CPoint pt((pt1.x + pt2.x) / 2, pt1.y); //��������
			tmp->ogrpoints.push_back(pt);
			pt = pt2;
			pt.x = pt1.x;
			tmp->ogrpoints.push_back(pt);
			tmp->ogrpoints.push_back(pt2);
		}
		else if (smtype == etype::TRIANGLE3) //ֱ��
		{
			tmp->ogrpoints.push_back(pt1);
			CPoint pt(pt1.x,pt2.y);
			tmp->ogrpoints.push_back(pt);
			tmp->ogrpoints.push_back(pt2);
		}
		else if (smtype == etype::TRIANGLE4)//�ȱ�
		{
			CPoint vec = point2 - point1;
			int r = sqrt(vec.x*vec.x + vec.y*vec.y);
			pt1 = point1;
			pt2 = point1;
			pt3 = point1;

			pt1.y -= r; //�ȱ߳���
			pt2 = rotatepoint(point1, pt1, 120);
			pt3 = rotatepoint(point1, pt1, -120);

			tmp->ogrpoints.push_back(pt1);
			tmp->ogrpoints.push_back(pt2);
			tmp->ogrpoints.push_back(pt3);
		}
		tmp->setrgn(true);
		shapes.push_back(tmp);
	}
	else if (curopttype == MOVE) 
	{
		if (cursel >= 0 && cursel < shapes.size())
		{
			shapes[cursel]->setrgn(true);
		}
	}
	
}

void CShape::clear()
{
	int len = shapes.size();
	for (int i = 0;i < len;i++)
	{
		delete shapes[i];
	}
	shapes.clear();
	spoints.clear();
	sbmd = false;
	cursel = -1;
	intersections.clear();
}

void  CShape::OnMouseMove(CPoint point,CDC*pDC)
{
	if (curopttype == DRAW)
	{
		if (sbmd|| (smtype == etype::TRIANGLE1&&spoints.size()>0))
		{
			COLORREF bclr = pDC->GetBkColor();
			CPen bpen;
			bpen.CreatePen(stline, swline, bclr); //����
			CPen npen;
			npen.CreatePen(stline, swline, sclrline);  //ǰ��
	
			CBrush bkr;
			bkr.CreateSolidBrush(bclr);
			pDC->SelectObject(&bpen);
			pDC->SelectObject(bkr);
			if (smtype == etype::LINE)
			{
				pDC->MoveTo(point1);
				pDC->LineTo(point2);
			}
			else if (smtype == etype::RECT || smtype == etype::SQUARE)
			{
				pDC->Rectangle(point1.x, point1.y, point2.x, point2.y);
			}
			else if (smtype == etype::ELLIPSE || smtype == etype::CIRCLE)
			{
				pDC->Ellipse(point1.x, point1.y, point2.x, point2.y);
			}
			else if (smtype == etype::TRIANGLE1)
			{
				pDC->MoveTo(point1);
				pDC->LineTo(point2);
			}
			else if (smtype == etype::TRIANGLE2)
			{
				drawtri2(point1, point2, pDC);
			}
			else if (smtype == etype::TRIANGLE3)
			{
				drawtri3(point1, point2, pDC);
			}
			else if (smtype == etype::TRIANGLE4)
			{
				drawtri4(point1, point2, pDC);
			}
			pDC->SelectObject(npen);
			CBrush bbr;
			if (sbfill)
			{
				bbr.CreateSolidBrush(sclrfill);
				pDC->SelectObject(bbr);
			}
			else
			{
				pDC->SelectObject(CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH)));
			}
			CPoint pt1;
			CPoint pt2;
			pt1.x = min(point1.x, point.x);
			pt1.y = min(point1.y, point.y);
			pt2.x = max(point1.x, point.x);
			pt2.y = max(point1.y, point.y);
			CPoint vec = point - point1;
			int len = min(abs(vec.x), abs(vec.y));
			//����ͼ��
			if (smtype == etype::LINE)
			{
				pDC->MoveTo(point1);
				pDC->LineTo(point);
	
			}
			else if (smtype == etype::RECT)
			{
				pDC->Rectangle(point1.x, point1.y, point.x, point.y);
	
			}
			else if (smtype == etype::SQUARE)
			{
				if (abs(vec.x) > abs(vec.y))  //x�ϳ�
				{
					if (vec.x >= 0)  //�޸�x��yһ������
					{
						point.x = point1.x + abs(vec.y);
					}
					else
					{
						point.x = point1.x - abs(vec.y);
					}
				}
				else //y�ϴ�
				{
					if (vec.y >= 0) //�޸�y��xһ������
					{
						point.y = point1.y + abs(vec.x);
					}
					else
					{
						point.y = point1.y - abs(vec.x);
					}
	
				}
				pDC->Rectangle(point1.x, point1.y, point.x, point.y);
		
			}
			else if (smtype == etype::ELLIPSE)
			{
				pDC->Ellipse(point1.x, point1.y, point.x, point.y);
		
				
			}
			else if (smtype == etype::CIRCLE)
			{
				if (abs(vec.x) > abs(vec.y)) //x�ϳ�
				{
					if (vec.x >= 0) //�޸�x��yһ������
					{
						point.x = point1.x + abs(vec.y);
					}
					else
					{
						point.x = point1.x - abs(vec.y);
					}

				}
				else
				{
					if (vec.y >= 0) //�޸�y��xһ������
					{
						point.y = point1.y + abs(vec.x);
					}
					else
					{
						point.y = point1.y - abs(vec.x);
					}
				}
				pDC->Ellipse(point1.x, point1.y, point.x, point.y);
			
			}
			else if (smtype == etype::TRIANGLE1)
			{
				pDC->MoveTo(point1);
				pDC->LineTo(point);
		

			}
			else if (smtype == etype::TRIANGLE2)
			{
				drawtri2(point1, point, pDC);
		
			}
			else if (smtype == etype::TRIANGLE3)
			{
				drawtri3(point1, point, pDC);
		
			}
			else if (smtype == etype::TRIANGLE4)
			{
				drawtri4(point1, point, pDC);
			}
			DeleteObject(npen);
			DeleteObject(bpen);
		}
	}
	else if (curopttype == MOVE)
	{
		if (sbmd)
		{
			if (cursel >= 0 && cursel < shapes.size())
			{
				int x = point.x - point2.x;
				int y = point.y - point2.y;
				shapes[cursel]->move(x, y); 
			}
		}
	}
	else if (curopttype == ROTATE)
	{
		if (sbmd)
		{
			if (cursel >= 0 && cursel < shapes.size())
			{
				CPoint center = shapes[cursel]->center;
				CPoint initialVec = point2 - center;
				CPoint currentVec = point - center;
				double initialAngle = atan2((double)initialVec.y, (double)initialVec.x) * 180.0 / PI;
				double currentAngle = atan2((double)currentVec.y, (double)currentVec.x) * 180.0 / PI;
				double angleDiff = currentAngle - initialAngle;
				shapes[cursel]->rotateTo(shapes[cursel]->angle + angleDiff);
			}
		}
	}
	else if (curopttype == SCALE)
	{
		if (sbmd)
		{
			if (cursel >= 0 && cursel < shapes.size())
			{
				CPoint vec = point - point2;
				float f = vec.y / 10.0; //���ű�
				shapes[cursel]->scaleshape(f,true);
			}
		}
	}
	point2 = point;
}

void CShape::OnLButtonDown(CPoint point)
{
	// 检查是否点击在交集区域
	for (int i = 0; i < intersections.size(); i++) {
		IntersectionInfo& info = intersections[i];
		
		if (info.shapeIndex1 >= 0 && info.shapeIndex1 < shapes.size() && 
			info.shapeIndex2 >= 0 && info.shapeIndex2 < shapes.size()) {
			
			// 检查点是否在交集区域内
			if (info.intersectionRegion.PtInRegion(point)) {
				// 弹出颜色选择对话框，使用当前交集颜色作为默认颜色
				COLORREF defaultColor;
				if (shapes[info.shapeIndex1]->clrIntersect == shapes[info.shapeIndex2]->clrIntersect) {
					defaultColor = shapes[info.shapeIndex1]->clrIntersect;
				} else {
					// 如果两个形状的交集颜色不同，使用混合色作为默认颜色
					defaultColor = blendColors(
						shapes[info.shapeIndex1]->clrfill, 
						shapes[info.shapeIndex2]->clrfill
					);
				}
				
				CColorDialog dlg(defaultColor);
				dlg.m_cc.Flags |= CC_FULLOPEN;  // 显示完整调色板
				dlg.m_cc.Flags |= CC_RGBINIT;   // 使用当前交集颜色作为默认颜色

				// 如果用户选择了颜色
				if (dlg.DoModal() == IDOK) {
					// 获取用户选择的颜色
					COLORREF selectedColor = dlg.GetColor();
					
					// 更新两个相交图形的交集颜色
					shapes[info.shapeIndex1]->clrIntersect = selectedColor;
					shapes[info.shapeIndex2]->clrIntersect = selectedColor;
					
					// 更新静态变量的交集颜色（用于新图形的默认值）
					sclrIntersect = selectedColor;
				}
				
				// 重新绘制视图
				extern CmdrawView* theView;
				if (theView) {
					theView->Invalidate();
				}
				
				return; // 处理完交集点击后直接返回
			}
		}
	}

	// 原有的点击处理逻辑
	org = point;
	point1 = point;
	point2 = point;
	sbmd = true;
	if (curopttype == opttype::DRAW)
	{
		if (smtype == TRIANGLE1 || smtype == TRIANGLE2
			|| smtype == TRIANGLE3 || smtype == TRIANGLE4)
		{
			spoints.push_back(point);
		}
	}
	if (cursel >= 0 && cursel < shapes.size())
	{
		shapes[cursel]->bsel = false;
	}
	cursel = -1;
	int len = shapes.size();
	for (int i = len - 1; i >= 0; i--)
	{
		if (PtInRegion(shapes[i]->mrgn, point.x, point.y))
		{
			cursel = i;
			shapes[i]->bsel = true;
			shapes[i]->onedgesel(point);
			break;
		}
	}
}

void CShape::setpoints()
{
	int len = ogrpoints.size();
	curpoints = ogrpoints; //ԭʼ��
	if (len < 1)
	{
		return;
	}
	for (int i = 0;i < len;i++) //�ƶ�
	{
		curpoints[i] = ogrpoints[i] + offset;
	}
	setcenter(); //����
	for (int i = 0;i < len;i++)
	{
		curpoints[i] = rotatepoint(center, curpoints[i], angle); //��ת
	}
    setscale(scale);	//����

	edges.clear();
	edges.resize(len);
	for (int i = 0;i < len;i++) //�߿��
	{
		edges[i].left = curpoints[i].x - SELSIZE;
		edges[i].top = curpoints[i].y - SELSIZE;
		edges[i].right = curpoints[i].x + SELSIZE;
		edges[i].bottom = curpoints[i].y + SELSIZE;
	}

	
}

void CShape::move(int x, int y)
{
	int len = ogrpoints.size();
	offset.x += x;
	offset.y += y;
	setrgn(true);
}

void CShape::onfill(bool bfill, COLORREF color)
{
	this->bfill = bfill;  // �����Ƿ����
	this->clrfill = color;  // �����ɫӦΪ��ɫ����ɫ
}

float CShape::normalizeAngle(float angle) {
	angle = fmod(angle, 360.0f);
	if (angle < 0) {
		angle += 360.0f;
	}
	return angle;
}

void CShape::rotateTo(float newAngle) {
	angle = normalizeAngle(newAngle);
	setrgn(true);
}

void CShape::rotate(float fa,bool ba)
{
	if (ba) 
	{
		angle += fa;
	}
	else
	{
		angle = fa;
	}
	angle = normalizeAngle(angle);
	setrgn(true);
}

void CShape::scaleshape(float s,bool ba)
{
	if (ba) //�ۻ�
	{
		scale+=s;
		if (scale < 0.1)
		{
			scale = 0.1;
		}
		else if (scale > 6)
		{
			scale = 6;
		}
	}
	else
	{
		scale = s;
	}
	
	setrgn(true);
}

CPoint CShape::rotatepoint(CPoint pcenter,CPoint point, float a)
{
	CPoint vec;
	vec.x = point.x - pcenter.x; //����
	vec.y = point.y - pcenter.y;

	double fa = PI / 180.0*a;	//ѡ�Ƕ�

	point.x = vec.x*cos(fa) - vec.y*sin(fa); //��ת
	point.y = vec.x*sin(fa) + vec.y*cos(fa);

	point.x += pcenter.x;	//ѡ��λ��
	point.y += pcenter.y;
	return point;
}

void CShape::drawtmptriangle(CDC* pDC)	//��ʱ�����λ���
{
	CPen pen, * ppen;
	pen.CreatePen(stline, swline, sclrline);
	ppen = pDC->SelectObject(&pen);  // ����֮ǰ�Ļ���

	if (smtype == TRIANGLE1)
	{
		if (spoints.size() > 1)
		{
			for (int i = 0; i < spoints.size() - 1; i++)
			{
				pDC->MoveTo(spoints[i]);
				pDC->LineTo(spoints[i + 1]);
			}
		}
	}

	pDC->SelectObject(ppen);  // �ָ�֮ǰ�Ļ���
}

void CShape::drawshape(vector<CPoint>pvec,CDC*pDC)
{
	if (pvec.size() > 2)
	{
		int len = pvec.size() - 1;
		for (int i = 0;i < len;i++) //�����߶�
		{
			pDC->MoveTo(pvec[i]);
			pDC->LineTo(pvec[i + 1]);
		}
		pDC->MoveTo(pvec[0]);
		pDC->LineTo(pvec[len]);
	}
}

void CShape::drawtri2(CPoint p1,CPoint p2,CDC*pDC) //����
{
	CPoint pt1;
	CPoint pt2;
	pt1.x = min(p1.x, p2.x);
	pt1.y = min(p1.y, p2.y);
	pt2.x = max(p1.x, p2.x);
	pt2.y = max(p1.y, p2.y);
	CPoint vec = p2 - p1;
	CPoint pt3 = CPoint((pt1.x + pt2.x) / 2, pt1.y);
	pt1.y = pt2.y;
	
	pDC->MoveTo(pt1);
	pDC->LineTo(pt2);
	pDC->MoveTo(pt2);
	pDC->LineTo(pt3);
	pDC->MoveTo(pt3);
	pDC->LineTo(pt1);

}

void CShape::drawtri3(CPoint p1, CPoint p2, CDC*pDC)
{
	CPoint p3 = p1;
	p3.y = p2.y;
	pDC->MoveTo(p1);
	pDC->LineTo(p2);
	pDC->MoveTo(p2);
	pDC->LineTo(p3);
	pDC->MoveTo(p3);
	pDC->LineTo(p1);
}

void CShape::drawtri4(CPoint p1, CPoint p2, CDC*pDC)
{
	CPoint vec = p2 - p1;
	int r = sqrt(vec.x*vec.x + vec.y*vec.y);
	CPoint pt1= p1;
	CPoint pt2= p1;
	CPoint pt3= p1;

	pt1.y -= r;
	pt2 = rotatepoint(p1, pt1, 120);
	pt3 = rotatepoint(p1, pt1, -120);

	pDC->MoveTo(pt1);
	pDC->LineTo(pt2);
	pDC->MoveTo(pt2);
	pDC->LineTo(pt3);
	pDC->MoveTo(pt3);
	pDC->LineTo(pt1);
}

void CShape::setrgn(bool bc)
{
	if (bc)
	{
		setpoints();
	}
	
	if (mrgn.m_hObject != NULL)
	{
		mrgn.DeleteObject();
	}
	
	int len = curpoints.size();
	if (len > 1)
	{
		if (mtype == CIRCLE || mtype == ELLIPSE)
		{
			// 对于椭圆和圆形，我们需要创建与GDI+绘制结果一致的区域
			CPoint spt = setscale(ogrpoints[0]+offset, scale);
			CPoint ept = setscale(ogrpoints[2] + offset, scale);
			
			// 计算中心点
			CPoint center;
			center.x = (spt.x + ept.x) / 2;
			center.y = (spt.y + ept.y) / 2;
			
			if (abs(angle) > 0.001) {
				// 当有旋转时，创建更高精度的多边形近似区域
				const int numPoints = 180; // 增加点数以提高精度
				CPoint* pt = new CPoint[numPoints];
				
				// 计算椭圆的宽度和高度的一半
				int a = abs(ept.x - spt.x) / 2;
				int b = abs(ept.y - spt.y) / 2;
				
				// 更精确地生成椭圆上的点并应用旋转
				for (int i = 0; i < numPoints; i++) {
					double angleRad = 2 * PI * i / numPoints;
					// 椭圆参数方程
					CPoint ellipsePoint;
					ellipsePoint.x = center.x + (int)(a * cos(angleRad));
					ellipsePoint.y = center.y + (int)(b * sin(angleRad));
					// 应用旋转
					pt[i] = rotatepoint(center, ellipsePoint, angle);
				}
				
				mrgn.CreatePolygonRgn(pt, numPoints, WINDING);
				delete[] pt;
			} else {
				// 无旋转时，直接创建椭圆区域
				CRect boundingRect(spt, ept);
				boundingRect.NormalizeRect();
				mrgn.CreateEllipticRgnIndirect(boundingRect);
			}
		}
		else if (mtype == RECT || mtype == SQUARE)
		{
			CPoint* pt = new CPoint[len];
			for (int i = 0; i < len; i++)
			{
				pt[i] = curpoints[i];
			}
			mrgn.CreatePolygonRgn(pt, len, WINDING);
			delete[] pt;
		}
		else
		{
			CPoint* pt = new CPoint[len];
			for (int i = 0; i < len; i++)
			{
				pt[i] = curpoints[i];
			}
			mrgn.CreatePolygonRgn(pt, len, WINDING);
			delete[] pt;
		}
	}
	
	if (intersectRgn.m_hObject != NULL) {
		intersectRgn.DeleteObject();
	}
	intersectRgn.CreateRectRgn(0, 0, 0, 0);
}

void CShape::draw(CDC *pDC)
{
	CPen bpen;
	bpen.CreatePen(tline, wline, clrline);
	pDC->SelectObject(&bpen);
	CBrush br(clrfill);
	if (bfill)
	{
		pDC->SelectObject(&br);
	}
	else
	{
		pDC->SelectObject(GetStockObject(NULL_BRUSH));
	}

	if (mtype == LINE)
	{
		if (curpoints.size() > 1)
		{
			pDC->MoveTo(curpoints[0]);
			pDC->LineTo(curpoints[2]);
		}
	}
	else if (mtype == CIRCLE||mtype==ELLIPSE)
	{
		if (curpoints.size() > 1)
		{
			// 始终使用GDI+绘制完美的椭圆/圆形
			Gdiplus::Graphics graphics(pDC->m_hDC);
			Gdiplus::Pen greenPen(Gdiplus::Color(GetRValue(clrline), GetGValue(clrline), GetBValue(clrline)), wline);

			CPoint spt = setscale(ogrpoints[0]+offset, scale);
			CPoint ept = setscale(ogrpoints[2] + offset, scale);
			
			// 计算中心点
			CPoint center;
			center.x = (spt.x + ept.x) / 2;
			center.y = (spt.y + ept.y) / 2;

			// 应用旋转变换
			Matrix m;
			m.RotateAt(angle, PointF((Gdiplus::REAL)center.x, (Gdiplus::REAL)center.y));
			graphics.SetTransform(&m);

			if (bfill)
			{
				Gdiplus::SolidBrush *SolidBrush =new Gdiplus::SolidBrush(Gdiplus::Color(GetRValue(clrfill), GetGValue(clrfill), GetBValue(clrfill)));
				graphics.FillEllipse(SolidBrush, spt.x, spt.y ,
					abs(ept.x - spt.x), abs(ept.y - spt.y));

				graphics.DrawEllipse(&greenPen, spt.x , spt.y,
					abs(ept.x - spt.x), abs(ept.y - spt.y));
			}
			else
			{
				graphics.DrawEllipse(&greenPen, spt.x, spt.y,
					abs(ept.x - spt.x), abs(ept.y - spt.y));
			}
		}
	}
	else if (mtype == RECT||mtype== SQUARE)
	{
		if (curpoints.size() > 1)
		{
			drawshape(curpoints, pDC);
		}
	}
	else if (mtype == TRIANGLE1)
	{
		
		if (curpoints.size() > 1)
		{
			drawshape(curpoints, pDC);
		}
	}
	else if (mtype == TRIANGLE2)
	{
		if (curpoints.size() > 1)
		{
			drawshape(curpoints, pDC);
		}
	}
	else if (mtype == TRIANGLE3)
	{
		if (curpoints.size() > 1)
		{
			drawshape(curpoints, pDC);
		}
	}
	else if (mtype == TRIANGLE4)
	{
		if (curpoints.size() > 1)
		{
			drawshape(curpoints, pDC);
		}
	}
	if (bfill)
	{
		if (mtype != CIRCLE && mtype != ELLIPSE)
		{
			FillRgn(pDC->m_hDC, mrgn, br);
		}
		
	}
	
	if (curopttype == MOVE || curopttype == ROTATE|| curopttype == SCALE || curopttype == FILL)
	{
		if (bsel)
		{
			int len = edges.size();
			for (int i = 0;i < len;i++)
			{
				pDC->Ellipse(edges[i]);
			}
		}
	}
	br.DeleteObject();
}

bool CShape::checkIntersect(CShape* s1, CShape* s2) {
	if (s1->mrgn.m_hObject == NULL || s2->mrgn.m_hObject == NULL)
		return false;

	CRgn intersect;
	intersect.CreateRectRgn(0, 0, 0, 0);
	int result = intersect.CombineRgn(&s1->mrgn, &s2->mrgn, RGN_AND);
	
	bool intersects = (result != NULLREGION && result != ERROR);
	intersect.DeleteObject();
	return intersects;
}

void CShape::calculateIntersections() {
	intersections.clear();

	for (int i = 0; i < shapes.size(); i++) {
		for (int j = i + 1; j < shapes.size(); j++) {
			if (checkIntersect(shapes[i], shapes[j])) {
				CRgn intersectRegion;
				intersectRegion.CreateRectRgn(0, 0, 0, 0);
				int result = intersectRegion.CombineRgn(&shapes[i]->mrgn, &shapes[j]->mrgn, RGN_AND);
				
				if (result != NULLREGION && result != ERROR) {
					IntersectionInfo info(i, j);
					info.intersectionRegion.CopyRgn(&intersectRegion);
					intersections.push_back(std::move(info));
				}
				intersectRegion.DeleteObject();
			}
		}
	}
}

void CShape::fillIntersections(CDC* pDC) {
	for (int i = 0; i < intersections.size(); i++) {
		IntersectionInfo& info = intersections[i];
		
		if (info.shapeIndex1 >= 0 && info.shapeIndex1 < shapes.size() && 
			info.shapeIndex2 >= 0 && info.shapeIndex2 < shapes.size()) {
			COLORREF colorToUse;
			if (shapes[info.shapeIndex1]->clrIntersect == shapes[info.shapeIndex2]->clrIntersect &&
				shapes[info.shapeIndex1]->clrIntersect != RGB(255, 0, 0)) { // 白色作为默认值
				// 使用用户自定义的交集颜色
				colorToUse = shapes[info.shapeIndex1]->clrIntersect;
			} else {
				// 使用混合色
				colorToUse = blendColors(
					shapes[info.shapeIndex1]->clrfill, 
					shapes[info.shapeIndex2]->clrfill
				);
			}
			CBrush intersectBrush(colorToUse);
			
			CRect rect;
			if (info.intersectionRegion.GetRgnBox(&rect) != NULLREGION && !rect.IsRectEmpty()) {
				FillRgn(pDC->m_hDC, info.intersectionRegion, intersectBrush);
			}
			
			intersectBrush.DeleteObject();
		}
	}
}

void CShape::Serialize(CArchive& ar)
{

}

CPoint CShape::setscale(CPoint pt, float f)
{
	CPoint tmp;
	tmp.x = pt.x - center.x;
	tmp.y = pt.y - center.y;

	float r = sqrt(double(tmp.x*tmp.x*1.0 + tmp.y*tmp.y*1.0));
	if (r > 0)
	{
		float a = asin(tmp.y / r);
		if (tmp.x <= 0 && tmp.y >= 0)
		{
			a = PI - a;
		}
		else if (tmp.x <= 0 && tmp.y <= 0)
		{
			a = -PI - a;
		}
		tmp.y = r * sin(a)*f;
		tmp.x = r * cos(a)*f;
	}
	pt.x = tmp.x + center.x;
	pt.y = tmp.y + center.y;
	return pt;
}

void CShape::setscale(float f)
{
	int len = curpoints.size();
	if (f >= 0.1&&f <= 10)
	{
		for (int i = 0;i < len;i++)
		{
			curpoints[i]= setscale(curpoints[i], f);
		}
	}
}

void CShape::setRotationAngle(float angleDegrees) {
	if (cursel >= 0 && cursel < shapes.size()) {
		shapes[cursel]->rotateTo(angleDegrees);
	}
}

float CShape::getRotationAngle() {
	if (cursel >= 0 && cursel < shapes.size()) {
		return shapes[cursel]->angle;
	}
	return 0.0f;
}