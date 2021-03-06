
// Project 3View.h : interface of the CProject3View class
//

#pragma once


class CProject3View : public CView
{
protected: // create from serialization only
	CProject3View() noexcept;
	DECLARE_DYNCREATE(CProject3View)

// Attributes
public:
	CProject3Doc* GetDocument() const;
	float smallPointAngle;
	float bigPointAngle;
	float klatnoAngle;
	int smallMinutes;
	int bigMinutes;
	const double PI = 3.14159265358979323846;
// Operations
public:
	void DrawWalls(CDC* pDC);
	void DrawWindow(CDC* pDC);
	void DrawCloset(CDC* pDC);
	void DrawDoor(CDC* pDC);
	void DrawInventory(CDC* pDC);
	void DrawClock(CDC* pDC);
	void PrimeniTransformaciju(CDC* pDC, float cx, float cy, float rx, float ry, float alfa, XFORM* oldXForm);
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
	virtual ~CProject3View();
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

#ifndef _DEBUG  // debug version in Project 3View.cpp
inline CProject3Doc* CProject3View::GetDocument() const
   { return reinterpret_cast<CProject3Doc*>(m_pDocument); }
#endif

