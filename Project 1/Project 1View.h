
// Project 1View.h : interface of the CProject1View class
//

#pragma once


class CProject1View : public CView
{
protected: // create from serialization only
	CProject1View();
	DECLARE_DYNCREATE(CProject1View)

// Attributes
public:
	CProject1Doc* GetDocument() const;

// Operations
public:

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
	virtual ~CProject1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Project 1View.cpp
inline CProject1Doc* CProject1View::GetDocument() const
   { return reinterpret_cast<CProject1Doc*>(m_pDocument); }
#endif

