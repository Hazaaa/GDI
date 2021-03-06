
// Project 6View.h : interface of the CProject6View class
//

#include "DImage.h"
#pragma once

class CProject6View : public CView
{
protected: // create from serialization only
	CProject6View() noexcept;
	DECLARE_DYNCREATE(CProject6View)

// Attributes
public:
	CProject6Doc* GetDocument() const;
	CRect clientRect;
	DImage* sky;
	DImage* wood;
	int position;
	float angle;
	int maxDistance;
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	void DrawBlade(CDC* pdc, int size);
	void Translate(CDC* pdc, int x, int y, bool rightMultiply);
	void Rotate(CDC* pdc, float angle, bool rightMultiply);
	void DrawStar(CDC* pdc, int size);
	void DrawPictures(CDC* pdc);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CProject6View();
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

#ifndef _DEBUG  // debug version in Project 6View.cpp
inline CProject6Doc* CProject6View::GetDocument() const
   { return reinterpret_cast<CProject6Doc*>(m_pDocument); }
#endif

