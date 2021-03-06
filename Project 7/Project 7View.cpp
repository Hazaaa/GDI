
// Project 7View.cpp : implementation of the CProject7View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Project 7.h"
#endif

#include "Project 7Doc.h"
#include "Project 7View.h"
#include "DImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PI 3.1415926535897932384626433832795
#define ToRad PI/180

// CProject7View

IMPLEMENT_DYNCREATE(CProject7View, CView)

BEGIN_MESSAGE_MAP(CProject7View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CProject7View construction/destruction

CProject7View::CProject7View() noexcept
{
	// TODO: add construction code here
	body = new DImage();
	body->Load(L"Body.png");

	leg1 = new DImage();
	leg1->Load(L"Leg1.png");

	leg2 = new DImage();
	leg2->Load(L"Leg2.png");

	leg3 = new DImage();
	leg3->Load(L"Leg3.png");

	back = new DImage();
	back->Load(L"Back2.jpg");

	bgX = 0.0;
	bgY = 0.0;
	positionX = 100.0;
	positionY = 100.0;
	scale = 1.0;
	
	leg1Angle = -20.0;
	leg2Angle = -10.0;
	leg3Angle = 0.0;
	leg4Angle = 10.0;
}

CProject7View::~CProject7View()
{
	delete body;
	delete leg1;
	delete leg2;
	delete leg3;
	delete back;
}

BOOL CProject7View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CProject7View drawing

void CProject7View::Translate(CDC * pdc, float x, float y, bool rightMultiply)
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

void CProject7View::Rotate(CDC * pdc, float angle, bool rightMultiply)
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

void CProject7View::Scale(CDC * pdc, float x, float y, bool rightMultiply)
{
	XFORM scale;

	scale.eM11 = x;
	scale.eM12 = 0.0;
	scale.eM21 = 0.0;
	scale.eM22 = y;
	scale.eDx = 0;
	scale.eDy = 0;

	if (rightMultiply)
		pdc->ModifyWorldTransform(&scale, MWT_RIGHTMULTIPLY);
	else
		pdc->ModifyWorldTransform(&scale, MWT_LEFTMULTIPLY);
}

void CProject7View::DrawLeg(CDC * pdc, double alpha, double x, double y)
{
	XFORM oldForm;
	pdc->GetWorldTransform(&oldForm);

	Translate(pdc, (float)x+28, (float)y+28, false);
	Rotate(pdc, (float)alpha, false);
	leg1->DrawTransparent(pdc, CRect(0, 0, leg1->Width(), leg1->Height()), CRect(0, 0, leg1->Width(), leg1->Height()), RGB(255,255,255));

	leg2->DrawTransparent(pdc, CRect(0, 0, leg2->Width(), leg2->Height()), CRect(0, leg1->Height()-50, leg2->Width(), leg2->Height() + leg1->Height()-50),RGB(255, 255, 255));

	leg3->DrawTransparent(pdc, CRect(0, 0, leg3->Width(), leg3->Height()), CRect(-35, leg1->Height() + 40, leg3->Width()-35, leg3->Height()+leg1->Height() + 40), RGB(255, 255, 255));

	pdc->SetWorldTransform(&oldForm);
}

void CProject7View::DrawScene(CDC * pdc, CRect rect)
{

	XFORM oldForm;

	pdc->GetWorldTransform(&oldForm);

	back->Draw(pdc, CRect(0, 0, back->Width(), back->Height()), CRect(bgX, bgY, back->Width() + bgX, back->Height() + bgY));

	Scale(pdc, scale, scale, false);
	body->DrawTransparent(pdc, CRect(0, 0, body->Width(), body->Height()), CRect(positionX, positionY, positionX + body->Width(), positionY + body->Height()), RGB(255,255,255));

	DrawLeg(pdc, leg1Angle, positionX + 17, positionY + 160);
	DrawLeg(pdc, leg2Angle, positionX + 17, positionY + 160);

	DrawLeg(pdc, leg3Angle, positionX + 240, positionY + 150);
	DrawLeg(pdc, leg4Angle, positionX + 240, positionY + 150);

	pdc->SetWorldTransform(&oldForm);
}

void CProject7View::OnDraw(CDC* pDC)
{
	CProject7Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	GetClientRect(&clientRect);

	CDC* pdc = new CDC();
	pdc->CreateCompatibleDC(pDC);

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, clientRect.Width(), clientRect.Height());
	pdc->SelectObject(&bmp);

	XFORM oldForm;
	int oldGM = pdc->SetGraphicsMode(GM_ADVANCED);

	pdc->GetWorldTransform(&oldForm);
	
	//Draw
	DrawScene(pdc, clientRect);
	

	pDC->BitBlt(0, 0, clientRect.Width(), clientRect.Height(), pdc, 0, 0, SRCCOPY);

	pdc->SetGraphicsMode(oldGM);
	pdc->SetWorldTransform(&oldForm);

	pdc->DeleteDC();
	delete pdc;
}


// CProject7View printing

BOOL CProject7View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CProject7View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CProject7View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CProject7View diagnostics

#ifdef _DEBUG
void CProject7View::AssertValid() const
{
	CView::AssertValid();
}

void CProject7View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProject7Doc* CProject7View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProject7Doc)));
	return (CProject7Doc*)m_pDocument;
}
#endif //_DEBUG


// CProject7View message handlers


BOOL CProject7View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return true;
}


void CProject7View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
