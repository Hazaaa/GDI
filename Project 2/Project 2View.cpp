
// Project 2View.cpp : implementation of the CProject2View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Project 2.h"
#endif

#include "Project 2Doc.h"
#include "Project 2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProject2View

IMPLEMENT_DYNCREATE(CProject2View, CView)

BEGIN_MESSAGE_MAP(CProject2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CProject2View construction/destruction

CProject2View::CProject2View()
{
	// TODO: add construction code here
	this->clickedOnClosetDoor = false;
	this->clickedOnDoor = false;
	this->keyIsInInventroy = false;
}

CProject2View::~CProject2View()
{
}

BOOL CProject2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CProject2View drawing

void CProject2View::DrawWalls(CDC * pDC)
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

void CProject2View::DrawWindow(CDC * pDC)
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

void CProject2View::DrawCloset(CDC * pDC)
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

	if (this->clickedOnClosetDoor)
	{
		CPoint openedClosetDoor[] = { {10, 126 }, {48, 136}, { 48 ,420}, {10, 430} };
		pDC->Polygon(openedClosetDoor, 4);

		pDC->SelectStockObject(BLACK_BRUSH);
		pDC->Rectangle(48, 136, 98, 420);

		pDC->SelectObject(closetBrush);

		if (!this->keyIsInInventroy)
		{
			//L is added for LPCWSTR type
			HENHMETAFILE key = GetEnhMetaFile(L"./res/key.emf");

			if (key != NULL)
			{
				pDC->PlayMetaFile(key, CRect(60, 385, 90, 410));
			}

			DeleteEnhMetaFile(key);
		}
	}
	else
	{
		pDC->Rectangle(48, 136, 98, 420);
	}

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

	if (!this->clickedOnClosetDoor)
	{
		pDC->Ellipse(79, 277, 91, 288);
	}
	
	pDC->Ellipse(106, 277, 118, 288);
	pDC->Ellipse(90, 460, 102, 470);
	pDC->Ellipse(90, 533, 102, 543);

#pragma endregion

	pDC->SelectObject(oldBrush);
	closetBrush->DeleteObject();
	handleBrush->DeleteObject();
}

void CProject2View::DrawDoor(CDC * pDC)
{
	CBrush* oldBrush;

	CBrush* doorBrush = new CBrush(RGB(133, 101, 68));
	oldBrush = pDC->SelectObject(doorBrush);

#pragma region Door

	CPoint door[] = { { 708, 124 }, { 773, 94 }, { 773, 595 }, { 708, 555 } };

	if (!this->clickedOnDoor)
	{
		pDC->Polygon(door, 4);
	}
	else
	{
		pDC->Rectangle(580, 124, 708, 555);

		pDC->SelectStockObject(BLACK_BRUSH);

		pDC->Polygon(door, 4);
	}

#pragma endregion

#pragma region Handle
	
	CBrush* handleBrush = new CBrush(RGB(244, 152, 66));

	if (!this->clickedOnDoor)
	{
		pDC->SelectObject(handleBrush);

		pDC->Ellipse(757, 354, 766, 363);
		pDC->Ellipse(744, 351, 763, 366);
	}
	
#pragma endregion

#pragma region Hole

	pDC->SelectStockObject(BLACK_BRUSH);

	pDC->Ellipse(761,369,766,378);

#pragma endregion

	pDC->SelectObject(oldBrush);
	handleBrush->DeleteObject();
	doorBrush->DeleteObject();
}

void CProject2View::DrawInventory(CDC * pDC)
{
	CBrush* oldBrush;
	oldBrush = (CBrush*) pDC->SelectStockObject(LTGRAY_BRUSH);

#pragma region Inventory

	pDC->RoundRect(8, 8, 72, 59, 15, 15);

	if (this->keyIsInInventroy)
	{
		//L is added for LPCWSTR type
		HENHMETAFILE key = GetEnhMetaFile(L"./res/key.emf");

		if (key != NULL)
		{
			pDC->PlayMetaFile(key, CRect(24, 20, 54, 45));
		}

		DeleteEnhMetaFile(key);
	}

#pragma endregion

	pDC->SelectObject(oldBrush);
}

void CProject2View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	//Create region for hit test
	CRgn regionClosetDoor, regionKeyInCloset, regionDoor, regionOpenedDoor, regionOpenedClosetDoor, regionKeyInInventory;
	regionClosetDoor.CreateRectRgn(48, 136, 98, 420);
	regionKeyInCloset.CreateRectRgn(60, 385, 90, 410);
	regionDoor.CreateEllipticRgn(744, 351, 763, 366);
	regionOpenedDoor.CreateRectRgn(580, 124, 708, 555);
	regionKeyInInventory.CreateRectRgn(24, 20, 54, 45);

	CPoint openedClosetDoor[] = { {10, 126 }, {48, 136}, { 48 ,420}, {10, 430} };
	regionOpenedClosetDoor.CreatePolygonRgn(openedClosetDoor, 4, ALTERNATE);
	
	if (this->clickedOnClosetDoor && !this->keyIsInInventroy) //Mean that left closet door is open and key is not in inventory
	{
		if (regionKeyInCloset.PtInRegion(point))
		{
			this->keyIsInInventroy = true;
			Invalidate();
		}
		else if (regionOpenedClosetDoor.PtInRegion(point))
		{
			this->clickedOnClosetDoor = false;
			Invalidate();
		}
	}
	else if (regionClosetDoor.PtInRegion(point))
	{
		this->clickedOnClosetDoor = true;
		Invalidate();
	}
	else if (regionOpenedClosetDoor.PtInRegion(point))
	{
		this->clickedOnClosetDoor = false;
		Invalidate();
	}
	else if (this->keyIsInInventroy)
	{
		if (regionDoor.PtInRegion(point))
		{
			this->clickedOnDoor = true;
			Invalidate();
		}
		else if (regionOpenedDoor.PtInRegion(point))
		{
			this->clickedOnDoor = false;
			Invalidate();
		}
		else if (regionKeyInInventory.PtInRegion(point))
		{
			this->keyIsInInventroy = false;
			Invalidate();
		}
	}


	CView::OnLButtonDown(nFlags, point);
}

void CProject2View::OnDraw(CDC* pDC)
{
	CProject2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	DrawWalls(pDC);
	DrawWindow(pDC);
	DrawCloset(pDC);
	DrawDoor(pDC);
	DrawInventory(pDC);
}


// CProject2View printing

BOOL CProject2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CProject2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CProject2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CProject2View diagnostics

#ifdef _DEBUG
void CProject2View::AssertValid() const
{
	CView::AssertValid();
}

void CProject2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProject2Doc* CProject2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProject2Doc)));
	return (CProject2Doc*)m_pDocument;
}
#endif //_DEBUG
