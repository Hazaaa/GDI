
// Project 9View.h : interface of the CProject9View class
//

#pragma once
#include "DImage.h"

class CProject9View : public CView
{
protected: // create from serialization only
	CProject9View() noexcept;
	DECLARE_DYNCREATE(CProject9View)

// Attributes
public:
	CProject9Doc* GetDocument() const;
	CRect rect;
	DImage* backgroud;
	bool openMouth;
	float packmanAngle;
	float positionX;
	float positionY;
	float mirrorX;
	float mirrorY;
	bool theEnd;
// Operations
public:
	void DrawScene(CDC* pdc);
	void Translate(CDC* pdc, float x, float y, bool right);
	void Rotate(CDC* pdc, float angle, bool right);
	void Mirror(CDC* pdc, float x, float y, bool right);
	void DrawPackman(CDC* pdc, CRect rect, float angle);
	void DrawGhost(CDC* pdc, CRect rect);
	void DetectColision();
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
	virtual ~CProject9View();
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

#ifndef _DEBUG  // debug version in Project 9View.cpp
inline CProject9Doc* CProject9View::GetDocument() const
   { return reinterpret_cast<CProject9Doc*>(m_pDocument); }
#endif

