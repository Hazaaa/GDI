
// Project 3View.cpp : implementation of the CProject3View class
//

#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <math.h>
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Project 3.h"
#endif

#include "Project 3Doc.h"
#include "Project 3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProject3View

IMPLEMENT_DYNCREATE(CProject3View, CView)

BEGIN_MESSAGE_MAP(CProject3View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CProject3View construction/destruction

CProject3View::CProject3View() noexcept
{
	// TODO: add construction code here
	this->smallPointAngle = M_PI;
	this->bigPointAngle = M_PI;
	this->klatnoAngle = PI; // desno 1.06 levo -1.06
	this->smallMinutes = 1;
	this->bigMinutes = 1;
}

CProject3View::~CProject3View()
{
}

BOOL CProject3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CProject3View drawing

void CProject3View::DrawWalls(CDC * pDC)
{
	//Old pens and brushes
	CPen* oldPen;
	CBrush* oldBrush;

	CPen* wallPen = new CPen(PS_GEOMETRIC, 2, RGB(129, 101, 64));

#pragma region Front wall

	CBrush* frontWallBrush = new CBrush(RGB(255, 192, 128));

	oldPen = pDC->SelectObject(wallPen);
	oldBrush = pDC->SelectObject(frontWallBrush);
	pDC->Rectangle(80, 65, 700, 550);

	pDC->SelectObject(oldBrush);
	frontWallBrush->DeleteObject();

#pragma endregion

	CBrush* sideWallsBrush = new CBrush(RGB(197, 147, 94));
	oldBrush = pDC->SelectObject(sideWallsBrush);

#pragma region Side walls

	CPoint sideLeftWall[] = { {0,0}, {80, 65}, {80, 550}, {0,600} };
	pDC->Polygon(sideLeftWall, 4);

	CPoint sideRightWall[] = { { 700, 65 }, { 780, 0 }, { 780, 600 }, { 700, 550 } };
	pDC->Polygon(sideRightWall, 4);

#pragma endregion

#pragma region Floor

	CBrush* floorBrush = new CBrush(RGB(199, 199, 199));
	oldBrush = pDC->SelectObject(floorBrush);

	CPoint floor[] = { { 80, 550 }, { 700, 550 }, { 780, 600 }, { 0, 600 } };
	pDC->Polygon(floor, 4);

#pragma endregion

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
	wallPen->DeleteObject();
	sideWallsBrush->DeleteObject();
	floorBrush->DeleteObject();
}

void CProject3View::DrawWindow(CDC * pDC)
{
	CBrush* oldBrush;

#pragma region Window frame

	CBrush* windowBrush = new CBrush(RGB(133, 101, 68));
	oldBrush = pDC->SelectObject(windowBrush);

	pDC->Rectangle(290, 320, 490, 400);

	pDC->SelectObject(oldBrush);
	windowBrush->DeleteObject();

#pragma endregion

#pragma region Small windows

	CBrush* smallWindowsBrush = new CBrush(RGB(4, 184, 216));
	oldBrush = pDC->SelectObject(smallWindowsBrush);

	pDC->Rectangle(300, 340, 388, 385);
	pDC->Rectangle(395, 340, 480, 385);

	pDC->SelectObject(oldBrush);
	smallWindowsBrush->DeleteObject();

#pragma endregion

#pragma region Courtain holder

	CBrush* courtainHolderBrush = new CBrush(RGB(133, 101, 68));
	oldBrush = pDC->SelectObject(courtainHolderBrush);

	pDC->RoundRect(274, 93, 509, 124, 36, 36);

	pDC->SelectObject(oldBrush);
	courtainHolderBrush->DeleteObject();

#pragma endregion

#pragma region Courtain

	CBrush* courtainBrush = new CBrush(RGB(251, 251, 160));
	oldBrush = pDC->SelectObject(courtainBrush);

	//Starting path
	pDC->BeginPath();

	pDC->MoveTo(284, 123);
	pDC->LineTo(284, 366);

	CPoint courtainLine[] = { {350, 340}, {425, 395} , {496,366} };
	pDC->PolyBezierTo(courtainLine, 3);

	pDC->LineTo(496, 123);
	pDC->LineTo(284, 123);

	pDC->EndPath();
	pDC->StrokeAndFillPath();

	pDC->SelectObject(oldBrush);
	courtainBrush->DeleteObject();

#pragma endregion
}

void CProject3View::DrawCloset(CDC * pDC)
{
	CBrush* oldBrush;

	CBrush* closetBrush = new CBrush(RGB(133, 101, 68));
	oldBrush = pDC->SelectObject(closetBrush);

#pragma region Big front rectangle

	pDC->Rectangle(40, 123, 157, 579);

#pragma endregion

#pragma region Closet side

	CPoint closetSide[] = { { 157, 123 }, { 195, 154}, { 195, 550}, { 157, 579 } };
	pDC->Polygon(closetSide, 4);

#pragma endregion

#pragma region Left door

	pDC->Rectangle(48, 136, 98, 420);	

#pragma endregion

#pragma region Right door

	pDC->Rectangle(98, 136, 148, 420);

#pragma endregion

#pragma region First drawer

	pDC->Rectangle(48, 433, 148, 494);

#pragma endregion

#pragma region Second drawer

	pDC->Rectangle(48, 506, 148, 566);

#pragma endregion

#pragma region Handles

	CBrush* handleBrush = new CBrush(RGB(244, 152, 66));
	pDC->SelectObject(handleBrush);

	pDC->Ellipse(79, 277, 91, 288);
	pDC->Ellipse(106, 277, 118, 288);
	pDC->Ellipse(90, 460, 102, 470);
	pDC->Ellipse(90, 533, 102, 543);

#pragma endregion

	pDC->SelectObject(oldBrush);
	closetBrush->DeleteObject();
	handleBrush->DeleteObject();
}

void CProject3View::DrawDoor(CDC * pDC)
{
	CBrush* oldBrush;

	CBrush* doorBrush = new CBrush(RGB(133, 101, 68));
	oldBrush = pDC->SelectObject(doorBrush);

#pragma region Door

	CPoint door[] = { { 708, 124 }, { 773, 94 }, { 773, 595 }, { 708, 555 } };
	
	pDC->Polygon(door, 4);

#pragma endregion

#pragma region Handle

	CBrush* handleBrush = new CBrush(RGB(244, 152, 66));
	pDC->SelectObject(handleBrush);

	pDC->Ellipse(757, 354, 766, 363);
	pDC->Ellipse(744, 351, 763, 366);

#pragma endregion

#pragma region Hole

	pDC->SelectStockObject(BLACK_BRUSH);

	pDC->Ellipse(761, 369, 766, 378);

#pragma endregion

	pDC->SelectObject(oldBrush);
	handleBrush->DeleteObject();
	doorBrush->DeleteObject();

}

void CProject3View::DrawInventory(CDC * pDC)
{
	CBrush* oldBrush;
	oldBrush = (CBrush*)pDC->SelectStockObject(LTGRAY_BRUSH);

#pragma region Inventory

	pDC->RoundRect(8, 8, 72, 59, 15, 15);

#pragma endregion

	pDC->SelectObject(oldBrush);
}

void CProject3View::DrawClock(CDC * pDC)
{

	CBrush* oldBrush;
	CPen* oldPen;

	XFORM oldXForm;
	pDC->GetWorldTransform(&oldXForm);

#pragma region Clock down body

	CBrush* clockBackBrush = new CBrush(RGB(133, 101, 68));
	oldBrush = pDC->SelectObject(clockBackBrush);

	pDC->RoundRect(565, 151, 642, 302, 15, 15);

	pDC->SelectStockObject(BLACK_BRUSH);
	pDC->RoundRect(570, 156, 637, 297, 15, 15);

	pDC->SelectObject(oldBrush);

#pragma endregion

#pragma region Klatno

	CBrush* klatnoBrush = new CBrush(RGB(255, 200, 1));
	oldBrush = pDC->SelectObject(klatnoBrush);

	PrimeniTransformaciju(pDC, 607, 147, 0, -135, this->klatnoAngle, &oldXForm);
	pDC->Rectangle(0, 0, 7, 119);
	pDC->Ellipse(-9, 0, 16, 25);

	pDC->SetWorldTransform(&oldXForm);
	pDC->SelectObject(oldBrush);

#pragma endregion

#pragma region Clock head

	oldBrush = pDC->SelectObject(clockBackBrush);

	//Brown back circle
	pDC->Ellipse(552, 95, 657, 200);

	pDC->SelectObject(klatnoBrush);

	//Gold back circle
	pDC->Ellipse(559, 102, 650, 193);

	pDC->SelectStockObject(WHITE_BRUSH);

	//First white circle
	pDC->Ellipse(572, 115, 637, 180); //+13

	//Second white circle
	pDC->Ellipse(578, 121, 631, 174); //+6

	pDC->SelectObject(oldBrush);

#pragma region Lines

	CPen* bolderPen = new CPen(PS_SOLID, 2, RGB(0, 0, 0));
	for (int i = 0; i < 60; i++)
	{
		if ((i % 5) == 0)
			oldPen = pDC->SelectObject(bolderPen);
		else
			pDC->SelectObject(oldPen);

		PrimeniTransformaciju(pDC, 604, 147, 0, 0, i * (2 * M_PI / 60), &oldXForm);
		pDC->MoveTo(0, 27);
		pDC->LineTo(0, 32);
	}

	pDC->SelectObject(oldPen);
	pDC->SetWorldTransform(&oldXForm);

#pragma endregion

#pragma region Numbers

	CPen* circlePen = new CPen(PS_SOLID, 1, RGB(255, 217, 127));
	oldPen = pDC->SelectObject(circlePen);

	CBrush* circleBrush = new CBrush(RGB(255, 217, 125));
	oldBrush = pDC->SelectObject(circleBrush);

	CFont font;
	font.CreateFont(8, 0, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, L"Arial");
	CFont *oldFont = pDC->SelectObject(&font);

	pDC->SetBkMode(TRANSPARENT);

	PrimeniTransformaciju(pDC, 604, 147, 0, -39, 0, &oldXForm);
	pDC->Ellipse(-5, -5, 5, 5);
	pDC->TextOutW(-4, -3, L"XII");

	PrimeniTransformaciju(pDC, 604, 147, 0, -39, M_PI / 6, &oldXForm); //30
	pDC->Ellipse(-5, -5, 5, 5);
	pDC->TextOutW(-1, -5, L"I");

	PrimeniTransformaciju(pDC, 604, 147, 0, -39, M_PI / 3, &oldXForm); //60
	pDC->Ellipse(-5, -5, 5, 5);
	pDC->TextOutW(-1, -5, L"II");

	PrimeniTransformaciju(pDC, 604, 147, 0, -39, M_PI / 2, &oldXForm); //90
	pDC->Ellipse(-5, -5, 5, 5);
	pDC->TextOutW(-3, -5, L"III");

	PrimeniTransformaciju(pDC, 604, 147, 0, -39, M_PI / 1.5, &oldXForm); //120
	pDC->Ellipse(-5, -5, 5, 5);
	pDC->TextOutW(-3, -5, L"IV");

	PrimeniTransformaciju(pDC, 604, 147, 0, -39, M_PI / 1.20, &oldXForm); //150
	pDC->Ellipse(-5, -5, 5, 5);
	pDC->TextOutW(-2, -5, L"V");

	PrimeniTransformaciju(pDC, 604, 147, 0, -39, M_PI, &oldXForm); //180
	pDC->Ellipse(-5, -5, 5, 5);
	pDC->TextOutW(-4, -5, L"VI");

	PrimeniTransformaciju(pDC, 604, 147, 0, -39, M_PI / 0.85, &oldXForm); //210
	pDC->Ellipse(-5, -5, 5, 5);
	pDC->TextOutW(-5, -5, L"VII");

	PrimeniTransformaciju(pDC, 604, 147, 0, -39, M_PI / 0.75, &oldXForm); //230
	pDC->Ellipse(-5, -5, 5, 5);
	pDC->TextOutW(-6, -5, L"VIII");

	PrimeniTransformaciju(pDC, 604, 147, 0, -39, M_PI / 0.66, &oldXForm); //260
	pDC->Ellipse(-5, -5, 5, 5);
	pDC->TextOutW(-5, -5, L"IX");

	PrimeniTransformaciju(pDC, 604, 147, 0, -39, M_PI / 0.60, &oldXForm); //260
	pDC->Ellipse(-5, -5, 5, 5);
	pDC->TextOutW(-3, -5, L"X");

	PrimeniTransformaciju(pDC, 604, 147, 0, -39, M_PI / 0.55, &oldXForm); //260
	pDC->Ellipse(-5, -5, 5, 5);
	pDC->TextOutW(-4, -5, L"XI");

	pDC->SetWorldTransform(&oldXForm);

#pragma endregion

#pragma region Pointers

	HENHMETAFILE smallPointer = GetEnhMetaFile(L"./res/MalaKazaljka.emf");
	HENHMETAFILE bigPointer = GetEnhMetaFile(L"./res/VelikaKazaljka.emf");

	PrimeniTransformaciju(pDC, 604, 147, 6, 32, this->bigPointAngle, &oldXForm);
	pDC->PlayMetaFile(bigPointer, CRect(0,0, -10, -40));

	PrimeniTransformaciju(pDC, 604, 147, 10, 32, this->smallPointAngle, &oldXForm);
	pDC->PlayMetaFile(smallPointer, CRect(0, 0, -20, -40));

	pDC->SetWorldTransform(&oldXForm);

	DeleteEnhMetaFile(smallPointer);
	DeleteEnhMetaFile(bigPointer);

#pragma endregion

#pragma endregion

	circlePen->DeleteObject();
	clockBackBrush->DeleteObject();
	klatnoBrush->DeleteObject();
	bolderPen->DeleteObject();
	circleBrush->DeleteObject();
}

void CProject3View::PrimeniTransformaciju(CDC * pDC, float cx, float cy, float rx, float ry, float alfa, XFORM * oldXForm)
{

	XFORM firstTransf, secondTransf;

	firstTransf.eM11 = (FLOAT)1.0;
	firstTransf.eM12 = (FLOAT)0.0;
	firstTransf.eM21 = (FLOAT)0.0;
	firstTransf.eM22 = (FLOAT)1.0;
	firstTransf.eDx = (FLOAT)rx;
	firstTransf.eDy = (FLOAT)ry;

	pDC->SetWorldTransform(&firstTransf);

	secondTransf.eM11 = (FLOAT)cos(alfa);
	secondTransf.eM12 = (FLOAT)sin(alfa);
	secondTransf.eM21 = (FLOAT)-sin(alfa);
	secondTransf.eM22 = (FLOAT)cos(alfa);
	secondTransf.eDx = (FLOAT)cx;
	secondTransf.eDy = (FLOAT)cy;

	pDC->ModifyWorldTransform(&secondTransf, MWT_RIGHTMULTIPLY);
}

void CProject3View::OnDraw(CDC* pDC)
{
	CProject3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	int oldGraphicMode = pDC->SetGraphicsMode(GM_ADVANCED); //Needed for transformations

	DrawWalls(pDC);
	DrawWindow(pDC);
	DrawCloset(pDC);
	DrawDoor(pDC);
	DrawInventory(pDC);
	DrawClock(pDC);

	pDC->SetGraphicsMode(oldGraphicMode);
}


// CProject3View printing

BOOL CProject3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CProject3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CProject3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CProject3View diagnostics

#ifdef _DEBUG
void CProject3View::AssertValid() const
{
	CView::AssertValid();
}

void CProject3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProject3Doc* CProject3View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProject3Doc)));
	return (CProject3Doc*)m_pDocument;
}
#endif //_DEBUG


// CProject3View message handlers


void CProject3View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == 86)
	{
		this->bigMinutes++;
		this->bigPointAngle = bigMinutes * (2 * M_PI / 60);
		if (this->klatnoAngle >= PI)
		{
			this->klatnoAngle = M_PI / 1.06;
		}
		else
		{
			this->klatnoAngle = -this->klatnoAngle;
		}
		Invalidate();
	}
	else if(nChar == 77)
	{
		this->smallMinutes++;
		this->smallPointAngle = smallMinutes * (2 * M_PI / 60);
		if (this->klatnoAngle == M_PI)
		{
			this->klatnoAngle = M_PI / 1.06;
		}
		else
		{
			this->klatnoAngle = -this->klatnoAngle;
		}
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
