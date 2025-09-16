#pragma once
#include "pch.h"
#include <vector>
#include <gdiplus.h>
using namespace Gdiplus;
#define  SELSIZE 5
#define PI 3.1416
using namespace std;

class CmdrawView;
extern CmdrawView* theView;

class CShape :public CObject
{
public:
	enum etype 
	{
		LINE, CIRCLE, ELLIPSE, RECT, SQUARE, TRIANGLE1, TRIANGLE2, TRIANGLE3, TRIANGLE4
	};
	enum opttype
	{
		DRAW,MOVE,ROTATE,SCALE,FILL
	};
	struct IntersectionInfo {
		int shapeIndex1;
		int shapeIndex2;
		CRgn intersectionRegion;
		
		IntersectionInfo(int index1, int index2) : shapeIndex1(index1), shapeIndex2(index2) {
			intersectionRegion.CreateRectRgn(0, 0, 0, 0);
		}
		
		// ��ʽ����Ĭ�Ϲ��캯��
		IntersectionInfo() : shapeIndex1(-1), shapeIndex2(-1) {
			intersectionRegion.CreateRectRgn(0, 0, 0, 0);
		}
		
		// ���ÿ������캯���Ϳ�����ֵ������
		IntersectionInfo(const IntersectionInfo&) = delete;
		IntersectionInfo& operator=(const IntersectionInfo&) = delete;
		
		// ��ʽ�����ƶ����캯��
		IntersectionInfo(IntersectionInfo&& other) noexcept 
			: shapeIndex1(other.shapeIndex1), shapeIndex2(other.shapeIndex2) {
			// �ƶ�CRgn����
			intersectionRegion.Attach(other.intersectionRegion.Detach());
		}
		
		// ��ʽ�����ƶ���ֵ������
		IntersectionInfo& operator=(IntersectionInfo&& other) noexcept {
			if (this != &other) {
				shapeIndex1 = other.shapeIndex1;
				shapeIndex2 = other.shapeIndex2;
				intersectionRegion.DeleteObject();
				intersectionRegion.Attach(other.intersectionRegion.Detach());
			}
			return *this;
		}
		
		// ��������
		~IntersectionInfo() {
			if (intersectionRegion.m_hObject) {
				intersectionRegion.DeleteObject();
			}
		}
	};
	
	static vector<IntersectionInfo> intersections; // �洢�뵱ǰͼ���ཻ�ľ�ȷ������Ϣ

	static vector<CShape*> shapes;  //ͼ���б�
	static vector<CPoint> spoints; //ͼ��ԭʼ��
	
	static bool sbmd;			//��갴�� 
	static bool sbfill;		    //���
	static int swline;			//�߿�
	static int stline;			 //���� 
	static COLORREF sclrline;   //������ɫ
	static COLORREF sclrfill;   //�����ɫ
	static COLORREF sclrIntersect;   // Ĭ�Ͻ���������ɫ
	static CShape::etype smtype;     //��ͼ����
	static CPoint point1;			 //��ͼ���
	static CPoint point2;			 //��ͼ�յ�
	static CPoint org;				 //����ϵƽ��
	static int cursel;				//ѡ��ͼ��
	static opttype curopttype;   //��������
	static int state;			//����״̬
	 
	int idsel;                //�߿��ѡ��
	CShape()	
	{
		mtype = etype::LINE;
		bsel = false;
		wline = 1;
		tline = 0;
		bfill = false;
		clrline = RGB(0, 0, 0);
		clrfill = RGB(255, 255, 255);
		clrIntersect = sclrIntersect; // ��ʼ������������ɫ
		angle = 0;
		scale = 1;
	}
	
	vector<CShape*> intersectingShapes; // �洢�뵱ǰͼ���ཻ������ͼ��
	vector<CRect> edges; //ͼ�α߿�
	float scale;     //����
	float angle;	//��ת
	CPoint offset;	//ƫ��
	etype mtype;	//ͼ������
	CRgn mrgn;		//ͼ������
	CRgn intersectRgn; //��������
	CPoint center;	//���ĵ�
	int wline;		//�߿�
	int tline;		//����
	COLORREF clrline;	//��ɫ
	COLORREF clrfill;	//���ɫ
	COLORREF clrIntersect; //����������ɫ
	bool bfill;			//�Ƿ����
	bool bsel;			//�Ƿ�ѡ��
	
	vector<CPoint> ogrpoints;		//ԭʼ��
	vector<CPoint> curpoints;		//�ƶ���ת���ź��

	void draw(CDC *pDC); //��ʾͼ��
	void onedgesel(CPoint pt);	//�߿�ѡ��
	void setcenter();		//��������
	static CPoint rotatepoint(CPoint pcenter, CPoint point, float a);	//��ת��
	void  rotate(float fa,bool ba=true);	//��ת
	void  rotateTo(float newAngle); // ���õ�ָ���Ƕ�
	float normalizeAngle(float angle); // �Ƕȱ�׼������
	void  move(int x, int y);	//�ƶ�
	CPoint setscale(CPoint pt, float f);	//���ŵ�
	void setscale(float f);			//����ͼ��
	void scaleshape(float s, bool ba = false);	//����
	void  onfill(bool bl,COLORREF c);		//���
	void setrgn(bool bc=false);	//ͼ����������
	void setpoints();		//�ƶ���ת���ź�����
	static  void OnLButtonDown(CPoint point);  //��갴��
	static  void OnLButtonUp(CPoint point,bool bs=false);	//��굯��
	static void OnMouseMove(CPoint point, CDC*pDC);		//����ƶ�
	static void OnRButtonUp(CPoint point);		//�Ҽ�����
	static void drawtmptriangle(CDC*pDC);		//��ʱ�����λ���
	static void drawshape(vector<CPoint>pvec, CDC*pDC);  //ͼ�λ���
	static void drawtri2(CPoint p1, CPoint p2, CDC*pDC);  //���������λ���
	static void drawtri3(CPoint p1, CPoint p2, CDC*pDC);	//ֱ�������λ���
	static void drawtri4(CPoint p1, CPoint p2, CDC*pDC);	//�ȱ������λ���
	static void clear();	//���
	static void calculateIntersections(); //���㽻��
	static bool checkIntersect(CShape* s1, CShape* s2); //����Ƿ��ཻ
	static void fillIntersections(CDC* pDC); //��佻������
	static COLORREF blendColors(COLORREF color1, COLORREF color2); // ��ɫ��Ϻ���
	static void setRotationAngle(float angleDegrees); // ������ת�Ƕ�
	static float getRotationAngle(); // ��ȡ��ת�Ƕ�
	
	CShape &operator = (const CShape & tmp);
	CShape(const CShape  & tmp);
	void Serialize(CArchive& ar);
	DECLARE_SERIAL(CShape)
};