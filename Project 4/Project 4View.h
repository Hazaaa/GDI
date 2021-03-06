
// Project 4View.h : interface of the CProject4View class
//

#pragma once


class CProject4View : public CView
{
protected: // create from serialization only
	CProject4View() noexcept;
	DECLARE_DYNCREATE(CProject4View)

// Attributes
public:
	CProject4Doc* GetDocument() const;
	const float PI = 3.14159265359;
	bool r;
	bool g;
	bool b;
// Operations
public:
	//Drawings
	void DrawWalls(CDC* pDC);
	void DrawWindow(CDC* pDC);
	void DrawCloset(CDC* pDC);
	void DrawDoor(CDC* pDC);
	void DrawInventory(CDC* pDC);
	void DrawPicture(CDC* pDC);

	//Transformations
	void Translate(CDC* pDC, int x, int y, bool leftMultiply);
	void Scale(CDC* pDC, float sx, float sy, bool leftMultiply);
	void Rotate(CDC* pDC, float alpha, bool leftMultiply);

	//Needed functions
	void SetBitmapTransformation(CDC* pDC, float cx, float cy, float bw, float bh, float scale, float alpha, bool mirror, XFORM* oldXForm);
	void SetBitmapRGBFilter(CBitmap*bmp, bool r, bool g, bool b);
	void DrawBitmap(CDC* pDC, int x, int y, float scale, CString name);
	void DrawTransparentBitmap(CDC* pDC, int x, int y, float scale, bool r, bool g, bool b, CString name);
	void DrawPuzzlePart(CDC* pDC, int x, int y, float scale, float angle, bool mirror, bool r, bool g, bool b, CString name);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CProject4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in Project 4View.cpp
inline CProject4Doc* CProject4View::GetDocument() const
   { return reinterpret_cast<CProject4Doc*>(m_pDocument); }
#endif

