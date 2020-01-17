#if !defined(AFX_CACHEFRM_H__58C162CB_8BE7_4677_AC11_37C9D9D14D56__INCLUDED_)
#define AFX_CACHEFRM_H__58C162CB_8BE7_4677_AC11_37C9D9D14D56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// cacheFrm.h : header file
//
#include "cachestatic.h"

/////////////////////////////////////////////////////////////////////////////
// cacheFrm frame

class cacheFrm : public CFrameWnd
{
	//DECLARE_DYNCREATE(cacheFrm)
public:
	cacheFrm();           // protected constructor used by dynamic creation (not anymore)

// Attributes
public:

	CListCtrl clistctrl;
	cachestatic text_cache;
	
	

// Operations
public:
	
	void updateOneWayNoBack();
	void updateOneWayBack();
	void updateMoreWaysNoBack();
	void updateMoreWaysBack();
	void updateFullyNoBack();
	void updateFullyBack();
	void updateStatistics();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cacheFrm)
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~cacheFrm();

	// Generated message map functions
	//{{AFX_MSG(cacheFrm)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CACHEFRM_H__58C162CB_8BE7_4677_AC11_37C9D9D14D56__INCLUDED_)
