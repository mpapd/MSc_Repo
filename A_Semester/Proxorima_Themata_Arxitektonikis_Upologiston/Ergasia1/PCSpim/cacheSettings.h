#if !defined(AFX_CACHESETTINGS_H__84D32381_D778_4117_8270_1E69094A11B5__INCLUDED_)
#define AFX_CACHESETTINGS_H__84D32381_D778_4117_8270_1E69094A11B5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// cacheSettings.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// cacheSettings dialog

class cacheSettings : public CDialog
{
// Construction
public:
	cacheSettings(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(cacheSettings)
	enum { IDD = IDD_DIALOG1 };
	CComboBox	m_combo1;
	CButton	m_checkshowrate;
	CListBox	m_listalgor;
	CListBox	m_listwrpolitics;
	CListBox	m_listcorres;
	CListBox	m_listblocksize;
	CButton	m_buttonok;
	CListBox	m_listcachesize;
	//}}AFX_DATA
private:
	int comboSel;
	unsigned int Dcache_bytesize;
	unsigned int Dcache_block_bytesize;
	unsigned int Dcache_ways;
	unsigned int Dcache_wrHit;
	unsigned int Dcache_wrMiss;
	unsigned int Dcache_algorithm;
	int Dshow_rate;
	unsigned int Dcache_instbytesize;
	unsigned int Dcache_instblock_bytesize;
	unsigned int Dcache_instways;
	unsigned int Dcache_instalgorithm;
	int Dshow_rateI;
	void dataDisplay();
	void instructionDisplay();
	void dataGetValues();
	void instructionGetValues();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cacheSettings)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

protected:

	// Generated message map functions
	//{{AFX_MSG(cacheSettings)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeList3();
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CACHESETTINGS_H__84D32381_D778_4117_8270_1E69094A11B5__INCLUDED_)
