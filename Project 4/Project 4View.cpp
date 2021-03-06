
// Project 4View.cpp : implementation of the CProject4View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Project 4.h"
#endif

#include "Project 4Doc.h"
#include "Project 4View.h"
#include "DImage.h"
#include "CDIB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProject4View

IMPLEMENT_DYNCREATE(CProject4View, CView)

BEGIN_MESSAGE_MAP(CProject4View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CProject4View construction/destruction

CProject4View::CProject4View() noexcept
{
	// TODO: add construction code here
	this->b = true;
	this->g = true;
	this->r = true;
}

CProject4View::~CProject4View()
{
}

BOOL CProject4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Draw functions implementation

void CProject4View::DrawWalls(CDC * pDC)
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

void CProject4View::DrawWindow(CDC * pDC)
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

void CProject4View::DrawCloset(CDC * pDC)
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

void CProject4View::DrawDoor(CDC * pDC)
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

void CProject4View::DrawInventory(CDC * pDC)
{
	CBrush* oldBrush;
	oldBrush = (CBrush*)pDC->SelectStockObject(LTGRAY_BRUSH);

#pragma region Inventory

	pDC->RoundRect(8, 8, 72, 59, 15, 15);

#pragma endregion

	pDC->SelectObject(oldBrush);
}

void CProject4View::DrawPicture(CDC * pDC)
{
	float scalef = 0.4;

	CRect clientRect;
	GetClientRect(&clientRect);

	int width = clientRect.Width();
	int height = clientRect.Height();

	DrawBitmap(pDC, width*0.64, height*0.22, scalef, CString("./res/Ram.bmp"));
	DrawPuzzlePart(pDC, width*0.645, height*0.24, scalef, 0, false, r, g, b, CString("./res/part1.bmp"));
	DrawPuzzlePart(pDC, width*0.768, height*0.117, scalef, -35, false, r, g, b, CString("./res/part2.bmp"));
	DrawPuzzlePart(pDC, width*0.323, height*0.305, scalef, 115, false, r, g, b, CString("./res/part3.bmp"));
	DrawPuzzlePart(pDC, width*0.629, height*0.47, scalef, 120, true, r, g, b, CString("./res/part4.bmp"));
}


// Transformations implementation

void CProject4View::Translate(CDC* pDC, int x, int y, bool leftMultiply)
{
	XFORM translate;

	translate.eM11 = (FLOAT)1.0;
	translate.eM12 = (FLOAT)0.0;
	translate.eM21 = (FLOAT)0.0;
	translate.eM22 = (FLOAT)1.0;
	translate.eDx = (FLOAT)x;
	translate.eDy = (FLOAT)y;

	//Need to set transform before this function so this transform is used first
	if (leftMultiply)
	{
		pDC->ModifyWorldTransform(&translate, MWT_LEFTMULTIPLY);
	}
	else
	{
		pDC->ModifyWorldTransform(&translate, MWT_RIGHTMULTIPLY);
	}
}

void CProject4View::Scale(CDC* pDC, float sx, float sy, bool leftMultiply)
{
	XFORM scale;

	scale.eM11 = (FLOAT)sx; //If is -sx then this is also reflection on x
	scale.eM12 = (FLOAT)0.0;
	scale.eM21 = (FLOAT)0.0;
	scale.eM22 = (FLOAT)sy; //If is -sy then this is also reflection on y
	scale.eDx = (FLOAT)0;
	scale.eDy = (FLOAT)0;

	//Need to set transform before this function so this transform is used first
	if (leftMultiply)
	{
		pDC->ModifyWorldTransform(&scale, MWT_LEFTMULTIPLY);
	}
	else
	{
		pDC->ModifyWorldTransform(&scale, MWT_RIGHTMULTIPLY);
	}
}

void CProject4View::Rotate(CDC* pDC, float alpha, bool leftMultiply)
{
	XFORM rotate;

	rotate.eM11 = (FLOAT)cos(alpha);
	rotate.eM12 = (FLOAT)sin(alpha);
	rotate.eM21 = (FLOAT)-sin(alpha);
	rotate.eM22 = (FLOAT)cos(alpha);
	rotate.eDx = (FLOAT)0;
	rotate.eDy = (FLOAT)0;

	//Need to set transform before this function so this transform is used first
	if (leftMultiply)
	{
		pDC->ModifyWorldTransform(&rotate, MWT_LEFTMULTIPLY);
	}
	else
	{
		pDC->ModifyWorldTransform(&rotate, MWT_RIGHTMULTIPLY);
	}
}


// Help functions implementation

void CProject4View::SetBitmapTransformation(CDC * pDC, float cx, float cy, float bw, float bh, float scale, float alpha, bool mirror, XFORM * oldXForm)
{
	XFORM translate, rotate, reflect, scaling;
	GetWorldTransform(pDC->m_hDC, oldXForm);

	translate.eM11 = 1;
	translate.eM12 = 0;
	translate.eM21 = 0;
	translate.eM22 = 1;
	translate.eDx = -(cx + bw / 2);
	translate.eDy = -(cy + bh / 2);

	SetWorldTransform(pDC->m_hDC, &translate);

	if (mirror)
	{
		reflect.eM11 = 1;
		reflect.eM12 = 0;
		reflect.eM21 = 0;
		reflect.eM22 = -1;
		reflect.eDx = 0;
		reflect.eDy = 0;

		ModifyWorldTransform(pDC->m_hDC, &reflect, MWT_RIGHTMULTIPLY);
	}

	scaling.eM11 = scale;
	scaling.eM12 = 0;
	scaling.eM21 = 0;
	scaling.eM22 = scale;
	scaling.eDx = 0;
	scaling.eDy = 0;

	ModifyWorldTransform(pDC->m_hDC, &scaling, MWT_RIGHTMULTIPLY);

	rotate.eM11 = cos((3.14159265*alpha) / 180);
	rotate.eM12 = sin((3.14159265*alpha) / 180);
	rotate.eM21 = -sin((3.14159265*alpha) / 180);
	rotate.eM22 = cos((3.14159265*alpha) / 180);
	rotate.eDx = cx + (bw*scale / 2);
	rotate.eDy = cy + (bh*scale / 2);

	ModifyWorldTransform(pDC->m_hDC, &rotate, MWT_RIGHTMULTIPLY);
}

void CProject4View::SetBitmapRGBFilter(CBitmap * bmp, bool r, bool g, bool b)
{
	unsigned rgbMask = 0;

	if (r)
		rgbMask |= 0x0000ff00;
	if (g)
		rgbMask |= 0x00ff0000;
	if (b)
		rgbMask |= 0xff000000;

	BITMAP info;
	bmp->GetBitmap(&info);

	unsigned byteCount = info.bmWidthBytes * info.bmHeight;
	unsigned char *bitmapData = new unsigned char[byteCount];

	bmp->GetBitmapBits(byteCount, bitmapData);

	for (unsigned char *ptr = bitmapData; ptr < bitmapData + byteCount; ptr += 4)
	{
		unsigned pixelRaw = *(reinterpret_cast<unsigned *>(ptr));
		unsigned pixel = ((pixelRaw & 0xff000000) >> 24) | ((pixelRaw & 0x00ff0000) >> 8)
			| ((pixelRaw & 0x0000ff00) << 8) | ((pixelRaw & 0x000000ff) << 24);
		pixel &= rgbMask;

		ptr[0] = pixel >> 24;
		ptr[1] = pixel >> 16;
		ptr[2] = pixel >> 8;
		ptr[3] = pixel;
	}

	bmp->SetBitmapBits(byteCount, bitmapData);

	delete[] bitmapData;
}

void CProject4View::DrawBitmap(CDC * pDC, int x, int y, float scale, CString name)
{
	DImage* img = new DImage();
	img->Load(name);

	int width = img->Width();
	int height = img->Height();

	CBitmap placeholder;
	placeholder.CreateBitmap(width, height, 1, 32, NULL);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap* oldBm = memDC->SelectObject(&placeholder);
	img->Draw(memDC, CRect(0, 0, width*2.5, height*2.5), CRect(0, 0, width, height));
	pDC->BitBlt(x, y, width*scale, height*scale, memDC, 0, 0, SRCCOPY);

	memDC->SelectObject(oldBm);
	memDC->DeleteDC();
	delete memDC;
	delete img;
}

void CProject4View::DrawTransparentBitmap(CDC * pDC, int x, int y, float scale, bool r, bool g, bool b, CString name)
{
	DImage* img = new DImage();
	img->Load(name);

	int width = img->Width();
	int height = img->Height();

	CBitmap placeholder, bmpMask;
	placeholder.CreateBitmap(width, height, 1, 32, NULL);
	bmpMask.CreateBitmap(width, height, 1, 1, NULL);

	CDC* srcDC = new CDC();
	srcDC->CreateCompatibleDC(pDC);
	CDC* dstDC = new CDC();
	dstDC->CreateCompatibleDC(pDC);

	CBitmap* pOldSrcBmp = srcDC->SelectObject(&placeholder);
	CBitmap* pOldDstBmp = dstDC->SelectObject(&bmpMask);
	img->Draw(srcDC, CRect(0, 0, width, height), CRect(0, 0, width, height));

	COLORREF clrTopLeft = srcDC->GetPixel(0, 0);
	COLORREF clrSaveBk = srcDC->SetBkColor(clrTopLeft);
	dstDC->BitBlt(0, 0, width, height, srcDC, 0, 0, SRCCOPY);

	COLORREF clrSaveSrcTxt = srcDC->SetTextColor(RGB(255, 255, 255));
	srcDC->SetBkColor(RGB(0, 0, 0));
	srcDC->BitBlt(0, 0, width, height, dstDC, 0, 0, SRCAND);

	srcDC->SetTextColor(clrSaveSrcTxt);
	srcDC->SetBkColor(clrSaveBk);
	srcDC->SelectObject(pOldSrcBmp);
	dstDC->SelectObject(pOldDstBmp);
	srcDC->DeleteDC();
	delete srcDC;
	dstDC->DeleteDC();
	delete dstDC;

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);
	CBitmap* bmpOld = memDC->SelectObject(&bmpMask);
	COLORREF oldBkPdc = pDC->SetBkColor(RGB(255, 255, 255));
	COLORREF oldTxtPdc = pDC->SetTextColor(RGB(0, 0, 0));
	pDC->StretchBlt(x, y, width*scale, height*scale, memDC, 0, 0, width, height, SRCAND);
	SetBitmapRGBFilter(&placeholder, r, g, b);
	memDC->SelectObject(&placeholder);
	pDC->StretchBlt(x, y, width*scale, height*scale, memDC, 0, 0, width, height, SRCPAINT);

	memDC->SelectObject(bmpOld);
	memDC->DeleteDC();
	delete memDC;
	delete img;
}

void CProject4View::DrawPuzzlePart(CDC * pDC, int x, int y, float scale, float angle, bool mirror, bool r, bool g, bool b, CString name)
{
	XFORM* oldXform = new XFORM();
	DImage* img = new DImage();
	img->Load(name);

	int width = img->Width();
	int height = img->Height();

	SetBitmapTransformation(pDC, x, y, width, height, 1, angle, mirror, oldXform);
	DrawTransparentBitmap(pDC, x, y, scale, r, g, b, name);
	pDC->SetWorldTransform(oldXform);

	delete img;
}

void CProject4View::OnDraw(CDC* pDC)
{
	CProject4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	int oldGMode = pDC->SetGraphicsMode(GM_ADVANCED);

	DrawWalls(pDC);
	DrawWindow(pDC);
	DrawCloset(pDC);
	DrawDoor(pDC);
	DrawInventory(pDC);
	DrawPicture(pDC);

	pDC->SetGraphicsMode(oldGMode);


#pragma region TransformationTest

	/*CRect rect;
	GetClientRect(rect);

	XFORM oldForm;
	pDC->GetWorldTransform(&oldForm);

	Translate(pDC, rect.CenterPoint().x, rect.CenterPoint().y, true);
	Scale(pDC, 1, -1, true);
	Rotate(pDC, (PI / 180) * 60, true);
	pDC->Rectangle(0, 0, 40, 40);*/

#pragma endregion

}


// CProject4View printing

BOOL CProject4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CProject4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CProject4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CProject4View diagnostics

#ifdef _DEBUG
void CProject4View::AssertValid() const
{
	CView::AssertValid();
}

void CProject4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CProject4Doc* CProject4View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProject4Doc)));
	return (CProject4Doc*)m_pDocument;
}
#endif //_DEBUG


// CProject4View message handlers


void CProject4View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	if (nChar == 'R')
	{
		r = true;
		g = false;
		b = false;
		Invalidate();
	}
	else if (nChar == 'G')
	{
		r = false;
		b = false;
		g = true;
		Invalidate();
	}
	else if (nChar == 'B')
	{
		r = false;
		g = false;
		b = true;
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
