
// Project 6View.cpp : implementation of the CProject6View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Project 6.h"
#endif

#include "Project 6Doc.h"
#include "Project 6View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PI 3.1415926535897932384626433832795
#define ToRad PI/180


// CProject6View

IMPLEMENT_DYNCREATE(CProject6View, CView)

BEGIN_MESSAGE_MAP(CProject6View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CProject6View construction/destruction

CProject6View::CProject6View() noexcept
{
	// TODO: add construction code here
	sky = new DImage();
	wood = new DImage();
	position = 0.0f;
	angle = 0.0f;

	sky->Load(L"sky.jpg");
	wood->Load(L"bark.jpg");
}

CProject6View::~CProject6View()
{
	delete sky;
	delete wood;
}

BOOL CProject6View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CProject6View::DrawBlade(CDC * pdc, int size)
{

	CBrush* oldBrush;
	CPen* oldPen;
	CFont* oldFont;
	
	CBrush* lightGrayBrush = new CBrush(RGB(195, 195, 195));
	CBrush* darkGrayBrush = new CBrush(RGB(150, 150, 150));
	CPen* grayPen = new CPen(PS_SOLID, 1, RGB(127, 127, 127));

	//Left side
	oldBrush = pdc->SelectObject(lightGrayBrush);
	oldPen = pdc->SelectObject(grayPen);

	POINT pts[3];

	pts[0].x = 0;
	pts[0].y = 0;
	pts[1].x = 4 * size;
	pts[1].y = 0;
	pts[2].x = size;
	pts[2].y = -size;

	pdc->Polygon(pts, 3);


	//Right side
	pdc->SelectObject(darkGrayBrush);

	POINT ptsr[3];

	ptsr[0].x = 0;
	ptsr[0].y = 0;
	ptsr[1].x = 4 * size;
	ptsr[1].y = 0;
	ptsr[2].x = size;
	ptsr[2].y = size;

	pdc->Polygon(ptsr, 3);

	//Text
	CFont font;
	font.CreateFont(0.7*size, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"Monotype Corsiva");
	oldFont = pdc->SelectObject(&font);
	COLORREF oldCOlor = pdc->SetTextColor(RGB(127, 127, 127));
	int oldBKMode = pdc->SetBkMode(TRANSPARENT);
	pdc->TextOut(size, -size/2.5, CString("Shuricane"));


	//Return old
	pdc->SetTextColor(oldCOlor);
	pdc->SelectObject(oldPen);
	pdc->SelectObject(oldBrush);
	pdc->SelectObject(oldFont);
	pdc->SetBkMode(oldBKMode);
	lightGrayBrush->DeleteObject();
	darkGrayBrush->DeleteObject();
	grayPen->DeleteObject();
}

void CProject6View::Translate(CDC * pdc, int x, int y, bool rightMultiply)
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

void CProject6View::Rotate(CDC * pdc, float angle, bool rightMultiply)
{
	XFORM rotate;

	rotate.eM11 = cos(angle*ToRad);
	rotate.eM12 = sin(angle*ToRad);
	rotate.eM21 = -sin(angle*ToRad);
	rotate.eM22 = cos(angle*ToRad);
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

void CProject6View::DrawStar(CDC * pdc, int size)
{
	XFORM oldTransform;
	pdc->GetWorldTransform(&oldTransform);

	//First translate then rotate each blade
	Translate(pdc, 100 + position, 200, false);

	Rotate(pdc, angle, false);
	for (int i = 0; i < 4; i++)
	{
		Rotate(pdc, i*90, false);
		DrawBlade(pdc, size);
	}
	
	pdc->SetWorldTransform(&oldTransform);
}

void CProject6View::DrawPictures(CDC * pdc)
{
	sky->Draw(pdc, CRect(0, 0, sky->Width(), sky->Height()), CRect(clientRect.TopLeft(), clientRect.BottomRight()));
}

// CProject6View drawing

void CProject6View::OnDraw(CDC* pDC)
{
	CProject6Doc* pDoc = GetDocument();
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
	pdc->SelectObject(&bmp);

#pragma endregion
	XFORM oldForm;
	int oldGM = pdc->SetGraphicsMode(GM_ADVANCED);
	pdc->GetWorldTransform(&oldForm);

	//DRAW
	DrawPictures(pdc);
	DrawStar(pdc, 40);
	wood->Draw(pdc, CRect(0, 0, wood->Width(), wood->Height()), CRect(clientRect.right - wood->Width(), 0, clientRect.right, clientRect.bottom));
	maxDistance = clientRect.right - wood->Width() - 40*5.1;

	pdc->SetGraphicsMode(oldGM);
	pdc->SetWorldTransform(&oldForm);

	pDC->BitBlt(0, 0, clientRect.Width(), clientRect.Height(), pdc, 0, 0, SRCCOPY);

	pdc->DeleteDC();
	delete pdc;

}


// CProject6View printing

BOOL CProject6View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CProject6View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CProject6View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CProject6View diagnostics

#ifdef _DEBUG
void CProject6View::AssertValid() const
{
	CView::AssertValid();
}

void CProject6View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProject6Doc* CProject6View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProject6Doc)));
	return (CProject6Doc*)m_pDocument;
}
#endif //_DEBUG


// CProject6View message handlers


BOOL CProject6View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true;
}


void CProject6View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	if (nChar == 'W')
	{
		if (position > maxDistance)
			return;

		position += 20;
		angle += 10;
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
