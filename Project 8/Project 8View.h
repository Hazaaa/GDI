
// Project 8View.h : interface of the CProject8View class
//

#pragma once
#include "DImage.h"

class CProject8View : public CView
{
protected: // create from serialization only
	CProject8View() noexcept;
	DECLARE_DYNCREATE(CProject8View)

// Attributes
public:
	CProject8Doc* GetDocument() const;
	CRect rect;
	DImage* border;
	DImage* table;
	float ballX;
	float ballY;
	int ballR;
	float stickAngle;
	int stickDistance;
// Operations
public:
	void Translate(CDC* pdc, float x, float y, bool rightMultiply);
	void Rotate(CDC* pdc, float angle, bool rightMultiply);
	void DrawBall(CDC* pdc, int w);
	void DrawBorder(CDC* pdc, CRect rect, int w);
	void DrawTable(CDC* pdc, CRect rect);
	void DrawHoles(CDC* pdc, CRect rect, int size);
	void DrawStick(CDC* pdc, int w);
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
	virtual ~CProject8View();
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

#ifndef _DEBUG  // debug version in Project 8View.cpp
inline CProject8Doc* CProject8View::GetDocument() const
   { return reinterpret_cast<CProject8Doc*>(m_pDocument); }
#endif

