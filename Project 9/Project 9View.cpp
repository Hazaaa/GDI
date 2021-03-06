
// Project 9View.cpp : implementation of the CProject9View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Project 9.h"
#endif

#include "Project 9Doc.h"
#include "Project 9View.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "DImage.h"
#define ToRad 3.1415926535897932384626433832795/180


// CProject9View

IMPLEMENT_DYNCREATE(CProject9View, CView)

BEGIN_MESSAGE_MAP(CProject9View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CProject9View construction/destruction

CProject9View::CProject9View() noexcept
{
	// TODO: add construction code here
	backgroud = new DImage();
	backgroud->Load(L"blue.png");

	openMouth = true;
	packmanAngle = 0;
	positionX = 400;
	positionY = 400;
	mirrorX = 1.0;
	mirrorY = 1.0;
	theEnd = false;
}

CProject9View::~CProject9View()
{
	delete backgroud;
}

BOOL CProject9View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CProject9View drawing

void CProject9View::DrawScene(CDC * pdc)
{
	backgroud->Draw(pdc, CRect(0, 0, backgroud->Width(), backgroud->Height()), CRect(0, 0, rect.Width(), rect.Height()));
}

void CProject9View::Translate(CDC * pdc, float x, float y, bool right)
{
	XFORM translate;

	translate.eM11 = 1.0;
	translate.eM12 = 0.0;
	translate.eM21 = 0.0;
	translate.eM22 = 1.0;
	translate.eDx = x;
	translate.eDy = y;

	if (right)
		pdc->ModifyWorldTransform(&translate, MWT_RIGHTMULTIPLY);
	else
		pdc->ModifyWorldTransform(&translate, MWT_LEFTMULTIPLY);
}

void CProject9View::Rotate(CDC * pdc, float angle, bool right)
{
	XFORM rotate;

	rotate.eM11 = cos(angle*ToRad);
	rotate.eM12 = sin(angle*ToRad);
	rotate.eM21 = -sin(angle*ToRad);
	rotate.eM22 = cos(angle*ToRad);
	rotate.eDx = 0;
	rotate.eDy = 0;

	if (right)
		pdc->ModifyWorldTransform(&rotate, MWT_RIGHTMULTIPLY);
	else
		pdc->ModifyWorldTransform(&rotate, MWT_LEFTMULTIPLY);
}

void CProject9View::Mirror(CDC * pdc, float x, float y, bool right)
{
	XFORM mirror;

	mirror.eM11 = x;
	mirror.eM12 = 0.0;
	mirror.eM21 = 0.0;
	mirror.eM22 = y;
	mirror.eDx = 0;
	mirror.eDy = 0;

	if (right)
		pdc->ModifyWorldTransform(&mirror, MWT_RIGHTMULTIPLY);
	else
		pdc->ModifyWorldTransform(&mirror, MWT_LEFTMULTIPLY);
}

void CProject9View::DrawPackman(CDC * pdc, CRect rect, float angle)
{
	CBrush* oldBrush;
	
	CBrush* packmanBrush = new CBrush(RGB(255,242,0));

	oldBrush = pdc->SelectObject(packmanBrush);

	POINT pt1, pt2;

	if (openMouth)
	{
		pt1.x = rect.right;
		pt1.y = rect.Height() / 2 - 30;
		pt2.x = rect.right;
		pt2.y = rect.Height() / 2 + 20;
	}
	else
	{
		pt1.x = rect.right;
		pt1.y = rect.Height() / 2;
		pt2.x = rect.right;
		pt2.y = rect.Height() / 2;
	}
	
	pdc->Pie(rect, pt1, pt2);

	pdc->SelectStockObject(BLACK_BRUSH);

	pdc->Ellipse(rect.Width() / 2 + 10, rect.Height() / 2 - 20, rect.Width() / 2 + 20, rect.Height() / 2 - 30);

	pdc->SelectObject(oldBrush);
	packmanBrush->DeleteObject();
}

void CProject9View::DrawGhost(CDC * pdc, CRect rect)
{
	//CRect(100,120,196,216) 96

	CBrush* oldBrush;

	CBrush* redBrush = new CBrush(RGB(255, 0, 0));
	CBrush* blueBrush = new CBrush(RGB(0, 0, 255));

	oldBrush = pdc->SelectObject(redBrush);

	pdc->SetArcDirection(AD_CLOCKWISE);
	pdc->BeginPath();
	pdc->Arc(rect.right, rect.bottom, rect.left, rect.top, rect.left, rect.top + 48, rect.right, rect.top + 48);
	pdc->MoveTo(rect.right, rect.bottom - 48);
	pdc->LineTo(rect.right, rect.bottom);
	pdc->LineTo(rect.left, rect.bottom);
	pdc->LineTo(rect.left, rect.bottom - 48);
	pdc->EndPath();

	pdc->StrokeAndFillPath();

	pdc->SetArcDirection(AD_COUNTERCLOCKWISE);

	pdc->SelectStockObject(WHITE_BRUSH);

	pdc->Ellipse(rect.right - 30, rect.top + 28, rect.right - 10, rect.top + 48);
	pdc->Ellipse(rect.right - 60, rect.top + 28, rect.right - 40, rect.top + 48);

	pdc->SelectObject(blueBrush);

	pdc->Ellipse(rect.right - 20, rect.top + 33, rect.right - 10, rect.top + 43);
	pdc->Ellipse(rect.right - 50, rect.top + 33, rect.right - 40, rect.top + 43);

	pdc->SelectObject(oldBrush);
	redBrush->DeleteObject();
	blueBrush->DeleteObject();
}

void CProject9View::DetectColision()
{
	CRgn ghostRegion;
	ghostRegion.CreateEllipticRgn(100, 120, 196, 216);

	if (ghostRegion.PtInRegion(positionX - 100, positionY))
	{
		theEnd = true;
	}
	
	if (ghostRegion.PtInRegion(positionX, positionY + 100))
	{
		theEnd = true;
	}
}

void CProject9View::OnDraw(CDC* pDC)
{
	CProject9Doc* pDoc = GetDocument();
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

	XFORM oldForm;
	int oldMode = pdc->SetGraphicsMode(GM_ADVANCED);
	pdc->GetWorldTransform(&oldForm);

	//DRAW
	DrawScene(pdc);

	if (!theEnd)
	{
		DrawGhost(pdc, CRect(100,120,196,216));

		Translate(pdc, positionX, positionY, false);
		Rotate(pdc, packmanAngle, false);
		Mirror(pdc, mirrorX, mirrorY, false);
		DrawPackman(pdc, CRect(0, 0, 100, 100), 30);
	}
	else
	{
		COLORREF oldBkColor = pdc->SetTextColor(RGB(255, 255, 255));
		pdc->SetBkMode(TRANSPARENT);
		CFont font;
		font.CreateFont(72, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"Arial");
		CFont* oldFont = pdc->SelectObject(&font);

		pdc->TextOut(rect.Width() / 2.5, rect.Height() / 2.40, L"THE END");

		pdc->SetTextColor(oldBkColor);
	}

	pdc->SetWorldTransform(&oldForm);
	pdc->SetGraphicsMode(oldMode);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), pdc, 0, 0, SRCCOPY);

	pdc->DeleteDC();
	delete pdc;
}


// CProject9View printing

BOOL CProject9View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CProject9View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CProject9View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CProject9View diagnostics

#ifdef _DEBUG
void CProject9View::AssertValid() const
{
	CView::AssertValid();
}

void CProject9View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProject9Doc* CProject9View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProject9Doc)));
	return (CProject9Doc*)m_pDocument;
}
#endif //_DEBUG


// CProject9View message handlers


BOOL CProject9View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true;
}


void CProject9View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (!theEnd)
	{
		if (nChar == VK_UP)
		{
			mirrorX = 1.0;
			mirrorY = 1.0;
			packmanAngle = -90;
			positionY -= 10;
			openMouth = !openMouth;
			if (positionY < 100)
				positionY = 100;
			DetectColision();
			Invalidate();
		}

		if (nChar == VK_DOWN)
		{
			mirrorX = 1.0;
			mirrorY = 1.0;
			packmanAngle = 90;
			positionY += 10;
			openMouth = !openMouth;
			if (positionY > rect.Height() - 100)
				positionY = rect.Height() - 100;
			DetectColision();
			Invalidate();
		}

		if (nChar == VK_LEFT)
		{
			mirrorX = -1.0;
			packmanAngle = 0;
			openMouth = !openMouth;
			positionX -= 10;
			if (positionX < 100)
				positionX = 100;
			DetectColision();
			Invalidate();
		}

		if (nChar == VK_RIGHT)
		{
			mirrorX = 1.0;
			mirrorY = 1.0;
			packmanAngle = 0;
			positionX += 10;
			openMouth = !openMouth;
			if (positionX > rect.Width() - 100)
				positionX = rect.Width() - 100;
			DetectColision();
			Invalidate();
		}
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
