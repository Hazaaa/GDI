
// Project 1View.cpp : implementation of the CProject1View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Project 1.h"
#endif

#include "Project 1Doc.h"
#include "Project 1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProject1View

IMPLEMENT_DYNCREATE(CProject1View, CView)

BEGIN_MESSAGE_MAP(CProject1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CProject1View construction/destruction

CProject1View::CProject1View()
{
	// TODO: add construction code here

}

CProject1View::~CProject1View()
{
}

BOOL CProject1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CProject1View drawing

void CProject1View::OnDraw(CDC* pDC)
{
	CProject1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CGdiObject* oldObject;
	CBrush *frontBrickBrush, *topBrickBrush, *sideBrickBrush;
	CPoint topBrickPolygon[4], sideBrickPolygon[4];

#pragma region Background

	//Background rectangle (black pen & light gray brush)
	oldObject = pDC->SelectStockObject(LTGRAY_BRUSH);
	pDC->Rectangle(100, 0, 1000, 450); // x - width, y - height

	//Side polygon
	CPoint sidePolygonPoints[4];
	sidePolygonPoints[0] = CPoint(0, 50);
	sidePolygonPoints[1] = CPoint(100, 0);
	sidePolygonPoints[2] = CPoint(100, 450);
	sidePolygonPoints[3] = CPoint(0, 500);

	pDC->Polygon(sidePolygonPoints, 4);

	//Return to original brush
	pDC->SelectObject(oldObject);

	//Bottom polygon
	oldObject = pDC->SelectStockObject(GRAY_BRUSH);

	CPoint bottomPolygonPoints[4];
	bottomPolygonPoints[0] = CPoint(100, 450);
	bottomPolygonPoints[1] = CPoint(1000, 450);
	bottomPolygonPoints[2] = CPoint(900, 500);
	bottomPolygonPoints[3] = CPoint(0, 500);

	pDC->Polygon(bottomPolygonPoints, 4);

	//Return to original brush
	pDC->SelectObject(oldObject);

	//Drawing lines
	for (int i = 75; i < 450; i = i + 75)
	{
		pDC->MoveTo(100, i);
		pDC->LineTo(1000, i);
	}

	for (int j = 0; j < 425; j = j + 75)
	{
		pDC->MoveTo(0, j + 50);
		pDC->LineTo(100, j);
	}

#pragma endregion

#pragma region First brick

	frontBrickBrush = new CBrush(RGB(140, 80, 237));
	oldObject = pDC->SelectObject(frontBrickBrush);
	pDC->Rectangle(120, 320, 200, 485);

	topBrickBrush = new CBrush(RGB(119, 66, 206));
	frontBrickBrush = pDC->SelectObject(topBrickBrush);
	delete frontBrickBrush;

	topBrickPolygon[4];
	topBrickPolygon[0] = CPoint(135, 300);
	topBrickPolygon[1] = CPoint(215, 300);
	topBrickPolygon[2] = CPoint(200, 320);
	topBrickPolygon[3] = CPoint(120, 320);
	pDC->Polygon(topBrickPolygon, 4);

	sideBrickBrush = new CBrush(RGB(97, 41, 188));
	topBrickBrush = pDC->SelectObject(sideBrickBrush);
	delete topBrickBrush;

	sideBrickPolygon[4];
	sideBrickPolygon[0] = CPoint(200, 320);
	sideBrickPolygon[1] = CPoint(215, 300);
	sideBrickPolygon[2] = CPoint(215, 465);
	sideBrickPolygon[3] = CPoint(200, 485);
	pDC->Polygon(sideBrickPolygon, 4);

	sideBrickBrush = (CBrush*)pDC->SelectObject(oldObject);
	delete sideBrickBrush;

#pragma endregion

#pragma region Second brick

	frontBrickBrush = new CBrush(RGB(140, 80, 237));
	oldObject = pDC->SelectObject(frontBrickBrush);
	pDC->Rectangle(300, 225, 380, 485); // x + 180

	topBrickBrush = new CBrush(RGB(119, 66, 206));
	frontBrickBrush = pDC->SelectObject(topBrickBrush);
	delete frontBrickBrush;

	topBrickPolygon[4];
	topBrickPolygon[0] = CPoint(315, 205); // x + 80
	topBrickPolygon[1] = CPoint(395, 205);
	topBrickPolygon[2] = CPoint(380, 225);
	topBrickPolygon[3] = CPoint(300, 225);
	pDC->Polygon(topBrickPolygon, 4);

	sideBrickBrush = new CBrush(RGB(97, 41, 188));
	topBrickBrush = pDC->SelectObject(sideBrickBrush);
	delete topBrickBrush;

	sideBrickPolygon[4];
	sideBrickPolygon[0] = CPoint(380, 225);
	sideBrickPolygon[1] = CPoint(395, 205);
	sideBrickPolygon[2] = CPoint(395, 465);
	sideBrickPolygon[3] = CPoint(380, 485);
	pDC->Polygon(sideBrickPolygon, 4);

	sideBrickBrush = (CBrush*)pDC->SelectObject(oldObject);
	delete sideBrickBrush;

#pragma endregion

#pragma region Third brick

	frontBrickBrush = new CBrush(RGB(140, 80, 237));
	oldObject = pDC->SelectObject(frontBrickBrush);
	pDC->Rectangle(480, 100, 560, 485); // x + 180

	topBrickBrush = new CBrush(RGB(119, 66, 206));
	frontBrickBrush = pDC->SelectObject(topBrickBrush);
	delete frontBrickBrush;

	topBrickPolygon[4];
	topBrickPolygon[0] = CPoint(495, 75); // x + 80
	topBrickPolygon[1] = CPoint(575, 75);
	topBrickPolygon[2] = CPoint(560, 100);
	topBrickPolygon[3] = CPoint(480, 100);
	pDC->Polygon(topBrickPolygon, 4);

	sideBrickBrush = new CBrush(RGB(97, 41, 188));
	topBrickBrush = pDC->SelectObject(sideBrickBrush);
	delete topBrickBrush;

	sideBrickPolygon[4];
	sideBrickPolygon[0] = CPoint(560, 100);
	sideBrickPolygon[1] = CPoint(575, 75);
	sideBrickPolygon[2] = CPoint(575, 465);
	sideBrickPolygon[3] = CPoint(560, 485);
	pDC->Polygon(sideBrickPolygon, 4);

	sideBrickBrush = (CBrush*)pDC->SelectObject(oldObject);
	delete sideBrickBrush;

#pragma endregion

#pragma region Forth brick

	frontBrickBrush = new CBrush(RGB(140, 80, 237));
	oldObject = pDC->SelectObject(frontBrickBrush);
	pDC->Rectangle(660, 175, 740, 485); // x + 180

	topBrickBrush = new CBrush(RGB(119, 66, 206));
	frontBrickBrush = pDC->SelectObject(topBrickBrush);
	delete frontBrickBrush;

	topBrickPolygon[4];
	topBrickPolygon[0] = CPoint(675, 150); 
	topBrickPolygon[1] = CPoint(755, 150);  // x + 80
	topBrickPolygon[2] = CPoint(740, 175);	// x - 15
	topBrickPolygon[3] = CPoint(660, 175); // x - 80
	pDC->Polygon(topBrickPolygon, 4);

	sideBrickBrush = new CBrush(RGB(97, 41, 188));
	topBrickBrush = pDC->SelectObject(sideBrickBrush);
	delete topBrickBrush;

	sideBrickPolygon[4];
	sideBrickPolygon[0] = CPoint(740, 175);
	sideBrickPolygon[1] = CPoint(755, 150);
	sideBrickPolygon[2] = CPoint(755, 465);
	sideBrickPolygon[3] = CPoint(740, 485);
	pDC->Polygon(sideBrickPolygon, 4);

	sideBrickBrush = (CBrush*)pDC->SelectObject(oldObject);
	delete sideBrickBrush;

#pragma endregion

}


// CProject1View printing

BOOL CProject1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CProject1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CProject1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CProject1View diagnostics

#ifdef _DEBUG
void CProject1View::AssertValid() const
{
	CView::AssertValid();
}

void CProject1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProject1Doc* CProject1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProject1Doc)));
	return (CProject1Doc*)m_pDocument;
}
#endif //_DEBUG


// CProject1View message handlers
