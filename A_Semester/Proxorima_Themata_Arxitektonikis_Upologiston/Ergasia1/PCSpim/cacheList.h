#if !defined(AFX_CACHELIST_H__A8CA415F_CBC8_43EC_9A6F_0C5FE2770076__INCLUDED_)
#define AFX_CACHELIST_H__A8CA415F_CBC8_43EC_9A6F_0C5FE2770076__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// cacheList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// cacheList window

class cacheList : public CListCtrl
{
// Construction
public:
	cacheList();

// Attributes
public:
protected:
	int colAcc;   //indicates which column is the Acc one
	int lastAcc;  //indicates the result of the last access
	int rowAcc;	  //indicates the row accessed
private:
	int num_columns;
	CFont fonteta;
	
	
// Operations
public:
	void InsertarColumna(int index,LPCSTR name);
	void InitializeList();
	void updateListOneWayNoBack();
	void updateListOneWayBack();
	void updateListMoreWaysNoBack();
	void updateListMoreWaysBack();
	void updateListFullyNoBack();
	void updateListFullyBack();
	void deleteAllColumns();
	void initListOneWayNoBack();
	void initListOneWayBack();
	void initListMoreWaysNoBack();
	void initListMoreWaysBack();
	void initFullyNoBack();
	void initFullyBack();
	void fitColumns(int ncol,int offset);
	void SizeList();
	void sizeListOneWayNoBack();
	void sizeListOneWayBack();
	void sizeListMoreWaysNoBack();
	void sizeListMoreWaysBack();
	void sizeListFullyNoBack();
	void sizeListFullyBack();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cacheList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~cacheList();

	// Generated message map functions
protected:
	//{{AFX_MSG(cacheList)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnCustomDraw(NMHDR * pNMHDR, LRESULT *pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CACHELIST_H__A8CA415F_CBC8_43EC_9A6F_0C5FE2770076__INCLUDED_)
