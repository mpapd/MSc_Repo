#if !defined(AFX_CACHECONFIGURATIOND_H__84CD1A76_DC46_4A36_B17D_05AE26874D4E__INCLUDED_)
#define AFX_CACHECONFIGURATIOND_H__84CD1A76_DC46_4A36_B17D_05AE26874D4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// cacheConfigurationD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// cacheConfigurationD dialog

class cacheConfigurationD : public CDialog
{
// Construction
public:
	cacheConfigurationD(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(cacheConfigurationD)
	enum { IDD = IDD_DIALOG2 };
	CButton	m_buttonDok;
	CListBox	m_list1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cacheConfigurationD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(cacheConfigurationD)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CACHECONFIGURATIOND_H__84CD1A76_DC46_4A36_B17D_05AE26874D4E__INCLUDED_)
