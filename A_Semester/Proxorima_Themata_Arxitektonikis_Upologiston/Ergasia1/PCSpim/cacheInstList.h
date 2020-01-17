#if !defined(AFX_CACHEINSTLIST_H__DA734072_E1A8_418D_9AED_D04CBBB8C900__INCLUDED_)
#define AFX_CACHEINSTLIST_H__DA734072_E1A8_418D_9AED_D04CBBB8C900__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// cacheInstList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// cacheInstList window

class cacheInstList : public CListCtrl
{
// Construction
public:
	cacheInstList();

// Attributes
public:
protected:
	int colAcc;   //indicates which column is the Acc one
	int lastAcc;  //indicates the result of the last access
	int rowAcc;	  //indicates the row accessed
// Operations
public:
	void InitializeList();
	void initListOneWayNoBack();
	void initListOneWayBack();
	void initListMoreWaysNoBack();
	void initListMoreWaysBack();
	void initFullyNoBack();
	void initFullyBack();

	void SizeList();
	void sizeListOneWayNoBack();
	void sizeListOneWayBack();
	void sizeListMoreWaysNoBack();
	void sizeListMoreWaysBack();
	void sizeListFullyNoBack();
	void sizeListFullyBack();

	void updateListOneWayNoBack();
	void updateListOneWayBack();
	void updateListMoreWaysNoBack();
	void updateListMoreWaysBack();
	void updateListFullyNoBack();
	void updateListFullyBack();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cacheInstList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~cacheInstList();

	// Generated message map functions
protected:
	//{{AFX_MSG(cacheInstList)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnCustomDraw(NMHDR * pNMHDR, LRESULT *pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CACHEINSTLIST_H__DA734072_E1A8_418D_9AED_D04CBBB8C900__INCLUDED_)
