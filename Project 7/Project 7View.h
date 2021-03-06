
// Project 7View.h : interface of the CProject7View class
//

#pragma once
#include "DImage.h"

class CProject7View : public CView
{
protected: // create from serialization only
	CProject7View() noexcept;
	DECLARE_DYNCREATE(CProject7View)

// Attributes
public:
	CProject7Doc* GetDocument() const;
	CRect clientRect;
	DImage* body;
	DImage* leg1;
	DImage* leg2;
	DImage* leg3;
	DImage* back;

	float bgX;
	float bgY;
	float positionX;
	float positionY;
	float scale;
	float leg1Angle;
	float leg2Angle;
	float leg3Angle;
	float leg4Angle;
// Operations
public:
	void Translate(CDC* pdc, float x, float y, bool rightMultiply);
	void Rotate(CDC* pdc, float angle, bool rightMultiply);
	void Scale(CDC* pdc, float x, float y, bool rightMultiply);
	void DrawLeg(CDC* pdc, double alpha, double x, double y);
	void DrawScene(CDC* pdc, CRect rect);
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
	virtual ~CProject7View();
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

#ifndef _DEBUG  // debug version in Project 7View.cpp
inline CProject7Doc* CProject7View::GetDocument() const
   { return reinterpret_cast<CProject7Doc*>(m_pDocument); }
#endif

