
// Project 8View.cpp : implementation of the CProject8View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Project 8.h"
#endif

#include "Project 8Doc.h"
#include "Project 8View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ToRad 3.1415926535897932384626433832795/180

// CProject8View

IMPLEMENT_DYNCREATE(CProject8View, CView)

BEGIN_MESSAGE_MAP(CProject8View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CProject8View construction/destruction

CProject8View::CProject8View() noexcept
{
	// TODO: add construction code here
	border = new DImage();
	border->Load(L"wood.jpg");

	table = new DImage();
	table->Load(L"felt2.jpg");

	ballX = 600;
	ballY = 400;

	ballR = 30;
	stickAngle = 60;
	stickDistance = ballR;
}

CProject8View::~CProject8View()
{
	delete border;
	delete table;
}

BOOL CProject8View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CProject8View drawing

void CProject8View::Translate(CDC * pdc, float x, float y, bool rightMultiply)
{
	XFORM translate;

	translate.eM11 = 1.0;
	translate.eM12 = 0.0;
	translate.eM21 = 0.0;
	translate.eM22 = 1.0;
	translate.eDx = x;
	translate.eDy = y;

	if (rightMultiply)
		pdc->ModifyWorldTransform(&translate, MWT_RIGHTMULTIPLY);
	else
		pdc->ModifyWorldTransform(&translate, MWT_LEFTMULTIPLY);
}

void CProject8View::Rotate(CDC * pdc, float angle, bool rightMultiply)
{
	XFORM rotate;

	rotate.eM11 = cos(angle*ToRad);
	rotate.eM12 = sin(angle*ToRad);
	rotate.eM21 = -sin(angle*ToRad);
	rotate.eM22 = cos(angle*ToRad);
	rotate.eDx = 0;
	rotate.eDy = 0;

	if (rightMultiply)
		pdc->ModifyWorldTransform(&rotate, MWT_RIGHTMULTIPLY);
	else
		pdc->ModifyWorldTransform(&rotate, MWT_LEFTMULTIPLY);
}

void CProject8View::DrawBall(CDC * pdc, int w)
{
	CPen* oldPen;
	CBrush* oldBrush;

	CPen* ballPen = new CPen(PS_SOLID, 1, RGB(120, 0, 0));
	CBrush* ballBrush = new CBrush(RGB(150, 0, 0));

	oldPen = pdc->SelectObject(ballPen);
	oldBrush = pdc->SelectObject(ballBrush);

	pdc->Ellipse(-w/2, -w/2, w/2, w/2);

	pdc->SelectObject(oldPen);
	pdc->SelectObject(oldBrush);

	pdc->Ellipse(0, 0, w/8 + w/5, w/8 + w/5);

	ballPen->DeleteObject();
	ballBrush->DeleteObject();

}

void CProject8View::DrawBorder(CDC * pdc, CRect rect, int w)
{
	border->Draw(pdc, CRect(0, 0, border->Width(), border->Height()), CRect(0, 0, rect.Width(), rect.Height()));
}

void CProject8View::DrawTable(CDC * pdc, CRect rect)
{
	XFORM oldForm;
	pdc->GetWorldTransform(&oldForm);

	for (int i = 0; i < 5; i++)
	{
		Translate(pdc, 40 + (table->Width() * i), 40, false);
		table->Draw(pdc, CRect(0, 0, table->Width(), table->Height()), CRect(0, 0, table->Width(), table->Height()));
		pdc->SetWorldTransform(&oldForm);
	}

	for (int i = 0; i < 5; i++)
	{
		Translate(pdc, 40 + (table->Width() * i), 40 + table->Height(), false);
		table->Draw(pdc, CRect(0, 0, table->Width(), table->Height()), CRect(0, 0, table->Width(), table->Height()));
		pdc->SetWorldTransform(&oldForm);
	}

	pdc->SetWorldTransform(&oldForm);
}

void CProject8View::DrawHoles(CDC * pdc, CRect rect, int size)
{
	XFORM oldForm;
	pdc->GetWorldTransform(&oldForm);

	CBrush* oldBrush;

	oldBrush = (CBrush*)pdc->SelectStockObject(BLACK_BRUSH);

	for (int i = 0; i < 3; i++)
	{
		Translate(pdc, size / 2 + (rect.Width()/2.16 * i), size / 4, false);
		pdc->Ellipse(CRect(0, 0, size, size));
		pdc->SetWorldTransform(&oldForm);
	}

	for (int i = 0; i < 3; i++)
	{
		Translate(pdc, size / 2 + (rect.Width() / 2.16 * i), size / 4 + table->Height()*2, false);
		pdc->Ellipse(CRect(0, 0, size, size));
		pdc->SetWorldTransform(&oldForm);
	}

	pdc->SetWorldTransform(&oldForm);
	pdc->SelectObject(oldBrush);
}

void CProject8View::DrawStick(CDC * pdc, int w)
{
	CBrush* oldBrush;
	CPen* oldPen;

	CBrush* frontStickBrush = new CBrush(RGB(255, 190, 128));
	CBrush* backStrickBrush = new CBrush(RGB(64, 32, 0));
	CPen* stickPen = new CPen(PS_SOLID, 1, RGB(64, 32, 0));

	oldBrush = pdc->SelectObject(frontStickBrush);
	oldPen = pdc->SelectObject(stickPen);
	
	CPoint pts[4];
	
	pts[0].x = -w / 100; pts[0].y = 0;
	pts[1].x = w / 100; pts[1].y = 0;
	pts[2].x = w / 66; pts[2].y = w * 2 / 3;
	pts[3].x = -w / 66; pts[3].y = w * 2 / 3;

	pdc->Polygon(pts, 4);

	pdc->SelectObject(backStrickBrush);

	pts[0].x = -w / 66; pts[0].y = w * 2 / 3;
	pts[1].x = w / 66; pts[1].y = w * 2 / 3;
	pts[2].x = w / 50; pts[2].y = w;
	pts[3].x = -w / 50; pts[3].y = w;

	pdc->Polygon(pts, 4);

	pdc->SelectStockObject(BLACK_BRUSH);

	pdc->Ellipse(-w / 50, w - 4, w / 50, w + 4);

	pdc->SelectStockObject(WHITE_PEN);
	pdc->MoveTo(-w / 100 + 2, 0);
	pdc->LineTo(-w / 50 + 2 * 2, w);

	pdc->SelectObject(oldPen);
	pdc->SelectObject(oldBrush);
	frontStickBrush->DeleteObject();
	backStrickBrush->DeleteObject();
	stickPen->DeleteObject();
}

void CProject8View::OnDraw(CDC* pDC)
{
	CProject8Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	GetClientRect(&rect);

	CDC* pdc = new CDC();
	pdc->CreateCompatibleDC(pDC);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	pdc->SelectObject(&bmp);

	int oldMode = pdc->SetGraphicsMode(GM_ADVANCED);
	XFORM oldForm;
	pdc->GetWorldTransform(&oldForm);

	//DRAW
	DrawBorder(pdc, rect, 100);
	DrawTable(pdc, rect);
	DrawHoles(pdc, rect, 50);

	Translate(pdc, ballX, ballY, false);
	DrawBall(pdc, ballR);

	pdc->SetWorldTransform(&oldForm);

	Translate(pdc, 0, stickDistance, true);
	Rotate(pdc, stickAngle, true);
	Translate(pdc, ballX, ballY, true);
	DrawStick(pdc, 400);

	pdc->SetWorldTransform(&oldForm);
	pdc->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), pdc, 0, 0, SRCCOPY);

	pdc->DeleteDC();
	delete pdc;
}


// CProject8View printing

BOOL CProject8View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CProject8View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CProject8View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CProject8View diagnostics

#ifdef _DEBUG
void CProject8View::AssertValid() const
{
	CView::AssertValid();
}

void CProject8View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProject8Doc* CProject8View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProject8Doc)));
	return (CProject8Doc*)m_pDocument;
}
#endif //_DEBUG


// CProject8View message handlers


BOOL CProject8View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true;
}


void CProject8View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	if (nChar == VK_LEFT)
	{
		stickAngle -= 10;
		if (stickAngle < 0)
			stickAngle = 360;
		Invalidate();
	}

	if (nChar == VK_RIGHT)
	{
		stickAngle += 10;
		if (stickAngle > 360)
			stickAngle = 0;
		Invalidate();
	}

	if (nChar == VK_UP)
	{
		stickDistance -= 10;
		if (stickDistance < ballR / 2)
		{
			stickDistance = ballR / 2;
			Invalidate();
			return;
		}
		Invalidate();
	}

	if (nChar == VK_DOWN)
	{
		stickDistance += 10;
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
