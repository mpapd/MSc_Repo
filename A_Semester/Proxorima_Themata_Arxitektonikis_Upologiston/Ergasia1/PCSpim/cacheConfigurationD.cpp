// cacheConfigurationD.cpp : implementation file
//

#include "stdafx.h"
#include "PCSpim.h"
#include "cacheConfigurationD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// cacheConfigurationD dialog


cacheConfigurationD::cacheConfigurationD(CWnd* pParent /*=NULL*/)
	: CDialog(cacheConfigurationD::IDD, pParent)
{
	//{{AFX_DATA_INIT(cacheConfigurationD)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void cacheConfigurationD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(cacheConfigurationD)
	DDX_Control(pDX, IDOK, m_buttonDok);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(cacheConfigurationD, CDialog)
	//{{AFX_MSG_MAP(cacheConfigurationD)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// cacheConfigurationD message handlers

BOOL cacheConfigurationD::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	this->m_list1.InsertString(0,"Harvard Architecture");
	this->m_list1.InsertString(1,"Data Cache Only");
	this->m_list1.InsertString(2,"Instruction Cache Only");
	if(data_simulation){
		switch(inst_simulation){
			case 0:
				this->m_list1.SetCurSel(1);
				break;
			case 1:
				this->m_list1.SetCurSel(0);
				break;
		}
	}
	else
		if(inst_simulation)
			this->m_list1.SetCurSel(2);
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void cacheConfigurationD::OnOK() 
{
	// TODO: Add extra validation here
	int sel=this->m_list1.GetCurSel();
	switch(sel){
		case 0:
			data_simulation=1;
			inst_simulation=1;
			break;
		case 1:
			data_simulation=1;
			inst_simulation=0;
			break;
		case 2:
			data_simulation=0;
			inst_simulation=1;
			break;
	}
	CDialog::OnOK();
}
