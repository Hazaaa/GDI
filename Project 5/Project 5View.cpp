
// Project 5View.cpp : implementation of the CProject5View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Project 5.h"
#endif

#include "Project 5Doc.h"
#include "Project 5View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define Degres 3.1415926535897932384626433832795/180


// CProject5View

IMPLEMENT_DYNCREATE(CProject5View, CView)

BEGIN_MESSAGE_MAP(CProject5View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CProject5View construction/destruction

CProject5View::CProject5View() noexcept
{
	// TODO: add construction code here
	angle = 10.0f;
	position = 0.0f;

	tocak = new DImage();
	tocak->Load(L"Wheel.png");
	clio = GetEnhMetaFile(L"clio.emf");
}

CProject5View::~CProject5View()
{
	delete tocak;
	DeleteEnhMetaFile(clio);
}

BOOL CProject5View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CProject5View drawing

void CProject5View::DrawGround(CDC * pdc, float angle)
{

	CPen* oldPen;
	CBrush* oldBrush;

	//Background
	CBrush* backgroundBrush = new CBrush(RGB(200, 220, 255));
	oldBrush = pdc->SelectObject(backgroundBrush);

	pdc->Rectangle(CRect(clientRect.TopLeft(), clientRect.BottomRight()));

	//Ground
	CBrush* groundBrush = new CBrush(HS_FDIAGONAL, RGB(128, 32, 32));
	CPen* groundPen = new CPen(PS_SOLID, 3, RGB(128, 64, 0));

	pdc->SelectObject(groundBrush);
	oldPen = pdc->SelectObject(groundPen);
	
	POINT pts[3];

	pts[0].x = clientRect.left;
	pts[0].y = clientRect.bottom;
	pts[1].x = clientRect.right;
	pts[1].y = clientRect.bottom;
	pts[2].x = clientRect.right;
	pts[2].y = clientRect.bottom - clientRect.Width()*tan(angle*Degres);

	COLORREF oldBKColor = pdc->SetBkColor(RGB(200, 255, 192));

	pdc->Polygon(pts, 3);

	//Destroying objects
	pdc->SetBkColor(oldBKColor);
	pdc->SelectObject(oldBrush);
	pdc->SelectObject(oldPen);
	oldBrush->DeleteObject();
	oldPen->DeleteObject();
	groundBrush->DeleteObject();
	backgroundBrush->DeleteObject();
}

void CProject5View::Translate(CDC * pdc, float x, float y, bool rightMultiply)
{
	XFORM translate;

	translate.eM11 = 1.0;
	translate.eM12 = 0.0;
	translate.eM21 = 0.0;
	translate.eM22 = 1.0;
	translate.eDx = x;
	translate.eDy = y;

	if (rightMultiply)
	{
		pdc->ModifyWorldTransform(&translate, MWT_RIGHTMULTIPLY);
	}
	else
	{
		pdc->ModifyWorldTransform(&translate, MWT_LEFTMULTIPLY);
	}
}

void CProject5View::Rotate(CDC * pdc, float angle, bool rightMultiply)
{
	XFORM rotate;

	rotate.eM11 = cos(angle*Degres);
	rotate.eM12 = sin(angle*Degres);
	rotate.eM21 = -sin(angle*Degres);
	rotate.eM22 = cos(angle*Degres);
	rotate.eDx = 0;
	rotate.eDy = 0;

	if (rightMultiply)
	{
		pdc->ModifyWorldTransform(&rotate, MWT_RIGHTMULTIPLY);
	}
	else
	{
		pdc->ModifyWorldTransform(&rotate, MWT_LEFTMULTIPLY);
	}
}

void CProject5View::Scale(CDC * pdc, float x, float y, bool rightMultiply)
{
	XFORM scale;

	scale.eM11 = x;
	scale.eM12 = 0.0;
	scale.eM21 = 0.0;
	scale.eM22 = y;
	scale.eDx = 0;
	scale.eDy = 0;

	if (rightMultiply)
	{
		pdc->ModifyWorldTransform(&scale, MWT_RIGHTMULTIPLY);
	}
	else
	{
		pdc->ModifyWorldTransform(&scale, MWT_LEFTMULTIPLY);
	}
}

void CProject5View::DrawCar(CDC * pdc, int x, int y, int w, int h)
{
	pdc->PlayMetaFile(clio, CRect(x + w / 2, y - h / 2, x - w / 2, y + h / 2));
}

void CProject5View::DrawWheel(CDC * pdc, int x, int y, int r, float angle)
{
	XFORM oldTransform;
	pdc->GetWorldTransform(&oldTransform); //We save old transform (in this case Car translation and rotation) but it will still effect wheel

	//Left coordinate of wheel in wheel.png file
	int wx = 52, wy = 15, ww = 376;
	CRect wheelRect(wx, wy, wx + ww, wy + ww);

	CRect destRect(-r, -r, r, r); //Because we draw wheel in 0,0 koordinates

	Translate(pdc, x, y, false);
	Rotate(pdc, angle, false);
	tocak->DrawTransparent(pdc, wheelRect, destRect, RGB(255, 255, 255)); // RGB is for white background of wheel.png

	pdc->SetWorldTransform(&oldTransform);
}

void CProject5View::OnDraw(CDC* pDC)
{
	CProject5Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	GetClientRect(&clientRect);

#pragma region Flicker

	CDC* pdc = new CDC();
	pdc->CreateCompatibleDC(pDC);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, clientRect.Width(), clientRect.Height());
	pdc->SelectObject(bmp);

#pragma endregion

	

	int oldGMode = pdc->SetGraphicsMode(GM_ADVANCED);
	XFORM oldTransform;
	pdc->GetWorldTransform(&oldTransform);

	DrawGround(pdc, angle);

	int carWidth = 450;
	int carHeight = carWidth / 2.5;
	int wheelR = 38;
	int xPosition = 0 + position;
	int yPosition = 0;
	float alpha = Degres * position / (2 * 3.1415926535);

	//First place car on 0.0 and clientHeight coordinate
	//Then rotate car
	//And then translate it on the ground
	Translate(pdc, carWidth / 2.0, -carHeight / 2.0 - wheelR /2.0, true);
	Rotate(pdc, -angle, true); //Because car is different rotated in emf file
	Translate(pdc, 0.0, clientRect.Height(), true);

	DrawCar(pdc, xPosition, yPosition, carWidth, carHeight);

	DrawWheel(pdc, xPosition - 155, yPosition + 70, wheelR, alpha);
	DrawWheel(pdc, xPosition + 135, yPosition + 70, wheelR, alpha);


	pdc->SetWorldTransform(&oldTransform);
	pdc->SetGraphicsMode(oldGMode);

	pDC->BitBlt(0, 0, clientRect.Width(), clientRect.Height(), pdc, 0, 0, SRCCOPY);

	pdc->DeleteDC();
	delete pdc;
}


// CProject5View printing

BOOL CProject5View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CProject5View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CProject5View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CProject5View diagnostics

#ifdef _DEBUG
void CProject5View::AssertValid() const
{
	CView::AssertValid();
}

void CProject5View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProject5Doc* CProject5View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProject5Doc)));
	return (CProject5Doc*)m_pDocument;
}
#endif //_DEBUG


// CProject5View message handlers


BOOL CProject5View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true;
}


void CProject5View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	if (nChar == VK_DOWN)
	{
		position = 0.0;
		angle -= 10.0f;
		if (angle < -10.0f)
			angle = -10.0f;
		Invalidate();
	}

	if (nChar == VK_UP)
	{
		position = 0.0;
		angle += 10.0f;
		if (angle > 80.0f)
			angle = 80.0f;
		Invalidate();
	}

	if (nChar == VK_LEFT)
	{
		position -= 10.0;
		if (position < 0.0)
			position = 0.0;
		Invalidate();
	}

	if (nChar == VK_RIGHT)
	{
		position += 10.0;
		Invalidate();
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
