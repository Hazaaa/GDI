
// Project 5View.h : interface of the CProject5View class
//

#pragma once
#include "DImage.h"

class CProject5View : public CView
{

	

protected: // create from serialization only
	CProject5View() noexcept;
	DECLARE_DYNCREATE(CProject5View)

// Attributes
public:
	CProject5Doc* GetDocument() const;

	DImage* tocak;
	HENHMETAFILE clio;

	CRect clientRect;
	float angle;
	float position;
// Operations
public:
	void DrawGround(CDC* pdc, float angle);
	void Translate(CDC* pdc, float x, float y, bool rightMultiply);
	void Rotate(CDC* pdc, float angle, bool rightMultiply);
	void Scale(CDC* pdc, float x, float y, bool rightMultiply);
	void DrawCar(CDC* pdc, int x, int y, int w, int h);
	void DrawWheel(CDC* pdc, int x, int y, int r, float angle);
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
	virtual ~CProject5View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in Project 5View.cpp
inline CProject5Doc* CProject5View::GetDocument() const
   { return reinterpret_cast<CProject5Doc*>(m_pDocument); }
#endif

