// cacheSettings.cpp : implementation file
//

#include "stdafx.h"
#include "PCSpim.h"
#include "cacheSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// cacheSettings dialog


cacheSettings::cacheSettings(CWnd* pParent /*=NULL*/)
	: CDialog(cacheSettings::IDD, pParent)
{
	//{{AFX_DATA_INIT(cacheSettings)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void cacheSettings::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(cacheSettings)
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_CHECK1, m_checkshowrate);
	DDX_Control(pDX, IDC_LIST5, m_listalgor);
	DDX_Control(pDX, IDC_LIST4, m_listwrpolitics);
	DDX_Control(pDX, IDC_LIST3, m_listcorres);
	DDX_Control(pDX, IDC_LIST2, m_listblocksize);
	DDX_Control(pDX, IDOK, m_buttonok);
	DDX_Control(pDX, IDC_LIST1, m_listcachesize);
	//}}AFX_DATA_MAP
}

void cacheSettings::dataDisplay(){
	if(Dshow_rate)
		this->m_checkshowrate.SetCheck(1);
	else
		this->m_checkshowrate.SetCheck(0);
	
	switch(Dcache_bytesize){
		
		case 128:
			this->m_listcachesize.SetCurSel(0);
			break;
		case 256:
			this->m_listcachesize.SetCurSel(1);
			break;
		case 512:
			this->m_listcachesize.SetCurSel(2);
			break;
		case 1024:
			this->m_listcachesize.SetCurSel(3);
			break;
	}
	switch(Dcache_block_bytesize){
		case 4:
			this->m_listblocksize.SetCurSel(0);
			break;
		case 8:
			this->m_listblocksize.SetCurSel(1);
			break;
		case 16:
			this->m_listblocksize.SetCurSel(2);
			break;
	}
	switch(Dcache_ways){
		case 1:
			this->m_listcorres.SetCurSel(0);
			break;
		case 2:
			this->m_listcorres.SetCurSel(1);
			break;
		case 4:
			this->m_listcorres.SetCurSel(2);
			break;
		default:
			this->m_listcorres.SetCurSel(3);
			break;
	}
	this->m_listwrpolitics.EndModalState();
	switch(Dcache_wrHit){
		case 0:
			!Dcache_wrMiss?this->m_listwrpolitics.SetCurSel(0):this->m_listwrpolitics.SetCurSel(1);
			break;
		case 1:
			!Dcache_wrMiss?this->m_listwrpolitics.SetCurSel(2):this->m_listwrpolitics.SetCurSel(3);
			break;
		
	}
	switch(Dcache_algorithm){
		case 0:
			this->m_listalgor.SetCurSel(0);
			break;
		case 1:
			this->m_listalgor.SetCurSel(1);
			break;
	}
}

void cacheSettings::instructionDisplay(){
	if(Dshow_rateI)
		this->m_checkshowrate.SetCheck(1);
	else
		this->m_checkshowrate.SetCheck(0);
	
	switch(Dcache_instbytesize){
		
		case 128:
			this->m_listcachesize.SetCurSel(0);
			break;
		case 256:
			this->m_listcachesize.SetCurSel(1);
			break;
		case 512:
			this->m_listcachesize.SetCurSel(2);
			break;
		case 1024:
			this->m_listcachesize.SetCurSel(3);
			break;
	}
	switch(Dcache_instblock_bytesize){
		case 4:
			this->m_listblocksize.SetCurSel(0);
			break;
		case 8:
			this->m_listblocksize.SetCurSel(1);
			break;
		case 16:
			this->m_listblocksize.SetCurSel(2);
			break;
	}
	switch(Dcache_instways){
		case 1:
			this->m_listcorres.SetCurSel(0);
			break;
		case 2:
			this->m_listcorres.SetCurSel(1);
			break;
		case 4:
			this->m_listcorres.SetCurSel(2);
			break;
		default:
			this->m_listcorres.SetCurSel(3);
			break;
	}
	
	this->m_listwrpolitics.SetCurSel(-1);
	this->m_listwrpolitics.BeginModalState();
	
	switch(Dcache_instalgorithm){
		case 0:
			this->m_listalgor.SetCurSel(0);
			break;
		case 1:
			this->m_listalgor.SetCurSel(1);
			break;
	}
}

void cacheSettings::dataGetValues(){
	int selsize=this->m_listcachesize.GetCurSel();
	int selblocksize=this->m_listblocksize.GetCurSel();
	int selways=this->m_listcorres.GetCurSel();
	int selwrpolitics=this->m_listwrpolitics.GetCurSel();
	int selalgor=this->m_listalgor.GetCurSel();
	Dshow_rate=this->m_checkshowrate.GetCheck();
	//c_dat->statistics.show=show_rate;
	
	switch(selsize){
		
		case 0:
			Dcache_bytesize=128;
			break;
		case 1:
			Dcache_bytesize=256;
			break;
		case 2:
			Dcache_bytesize=512;
			break;
		case 3:
			Dcache_bytesize=1024;
			break;
	}
	switch(selblocksize){
		case 0:
			Dcache_block_bytesize=4;
			break;
		case 1:
			Dcache_block_bytesize=8;
			break;
		case 2:
			Dcache_block_bytesize=16;
			break;
	}
	switch(selways){
		case 0:
			Dcache_ways=1;
			break;
		case 1:
			Dcache_ways=2;
			break;
		case 2:
			Dcache_ways=4;
			break;
		case 3:
			Dcache_ways=Dcache_bytesize/Dcache_block_bytesize;
			break;
	}
	switch(selwrpolitics){
		case 0:
			Dcache_wrHit=0;
			Dcache_wrMiss=0;
			break;
		case 1:
			Dcache_wrHit=0;
			Dcache_wrMiss=1;
			break;
		case 2:
			Dcache_wrHit=1;
			Dcache_wrMiss=0;
			break;
		case 3:
			Dcache_wrHit=1;
			Dcache_wrMiss=1;
			break;
	}
	switch(selalgor){
		case 0:
			Dcache_algorithm=0;
			break;
		case 1:
			Dcache_algorithm=1;
			break;
	}
}

void cacheSettings::instructionGetValues(){
	int selsize=this->m_listcachesize.GetCurSel();
	int selblocksize=this->m_listblocksize.GetCurSel();
	int selways=this->m_listcorres.GetCurSel();
	int selwrpolitics=this->m_listwrpolitics.GetCurSel();
	int selalgor=this->m_listalgor.GetCurSel();
	this->Dshow_rateI=this->m_checkshowrate.GetCheck();
	//c_inst->statistics.show=show_rate;
	
	switch(selsize){
		
		case 0:
			Dcache_instbytesize=128;
			break;
		case 1:
			Dcache_instbytesize=256;
			break;
		case 2:
			Dcache_instbytesize=512;
			break;
		case 3:
			Dcache_instbytesize=1024;
			break;
	}
	switch(selblocksize){
		case 0:
			Dcache_instblock_bytesize=4;
			break;
		case 1:
			Dcache_instblock_bytesize=8;
			break;
		case 2:
			Dcache_instblock_bytesize=16;
			break;
	}
	switch(selways){
		case 0:
			Dcache_instways=1;
			break;
		case 1:
			Dcache_instways=2;
			break;
		case 2:
			Dcache_instways=4;
			break;
		case 3:
			Dcache_instways=Dcache_instbytesize/Dcache_instblock_bytesize;
			break;
	}
	/*switch(selwrpolitics){
		case 0:
			cache_wrHit=0;
			cache_wrMiss=0;
			break;
		case 1:
			cache_wrHit=0;
			cache_wrMiss=1;
			break;
		case 2:
			cache_wrHit=1;
			cache_wrMiss=0;
			break;
		case 3:
			cache_wrHit=1;
			cache_wrMiss=1;
			break;
	}*/
	switch(selalgor){
		case 0:
			Dcache_instalgorithm=0;
			break;
		case 1:
			Dcache_instalgorithm=1;
			break;
	}
}


BEGIN_MESSAGE_MAP(cacheSettings, CDialog)
	//{{AFX_MSG_MAP(cacheSettings)
	ON_LBN_SELCHANGE(IDC_LIST3, OnSelchangeList3)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// cacheSettings message handlers

BOOL cacheSettings::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	this->Dcache_bytesize=cache_bytesize;
	this->Dcache_block_bytesize=cache_block_bytesize;
	this->Dcache_ways=cache_ways;
	this->Dcache_wrHit=cache_wrHit;
	this->Dcache_wrMiss=cache_wrMiss;
	this->Dcache_algorithm=cache_algorithm;
	this->Dshow_rate=show_rate;
	this->Dcache_instbytesize=cache_instbytesize;
	this->Dcache_instblock_bytesize=cache_instblock_bytesize;
	this->Dcache_instways=cache_instways;
	this->Dcache_instalgorithm=cache_instalgorithm;
	this->Dshow_rateI=show_rateI;
	this->m_listcachesize.InsertString(0,"128B");
	this->m_listcachesize.InsertString(1,"256B");
	this->m_listcachesize.InsertString(2,"512B");
	this->m_listcachesize.InsertString(3,"1024B");
	this->m_listblocksize.InsertString(0,"4B");
	this->m_listblocksize.InsertString(1,"8B");
	this->m_listblocksize.InsertString(2,"16B");
	this->m_listcorres.InsertString(0,"Direct Mapping");
	this->m_listcorres.InsertString(1,"2 Ways Set-Associative");
	this->m_listcorres.InsertString(2,"4 Ways Set-Associative");
	this->m_listcorres.InsertString(3,"Fully Associative");
	this->m_listwrpolitics.InsertString(0,"WriteThrough-Allocate");
	this->m_listwrpolitics.InsertString(1,"WriteThrough-NoAllocate");
	this->m_listwrpolitics.InsertString(2,"WriteBack-Allocate");
	this->m_listwrpolitics.InsertString(3,"WriteBack-NoAllocate");
	this->m_listalgor.InsertString(0,"LRU");
	this->m_listalgor.InsertString(1,"FIFO");
	if(data_simulation){
		this->m_combo1.SetCurSel(0);
		this->comboSel=0;
	}
	else{
		this->m_combo1.SetCurSel(1);
		this->comboSel=1;
	}
	if(!comboSel)
		dataDisplay();
	else
		instructionDisplay();

	
	if(this->m_listcorres.GetCurSel()==0)
		this->m_listalgor.BeginModalState();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void cacheSettings::OnOK() 
{
	// TODO: Add extra validation here
	if(this->m_combo1.GetCurSel())
		this->instructionGetValues();
	else
		this->dataGetValues();
	
	cache_bytesize=this->Dcache_bytesize;
	cache_block_bytesize=this->Dcache_block_bytesize;
	cache_ways=this->Dcache_ways;
	cache_wrHit=this->Dcache_wrHit;
	cache_wrMiss=this->Dcache_wrMiss;
	cache_algorithm=this->Dcache_algorithm;
	show_rate=this->Dshow_rate;
	cache_instbytesize=this->Dcache_instbytesize;
	cache_instblock_bytesize=this->Dcache_instblock_bytesize;
	cache_instways=this->Dcache_instways;
	cache_instalgorithm=this->Dcache_instalgorithm;
	show_rateI=this->Dshow_rateI;
	
	
	
	CDialog::OnOK();
}

void cacheSettings::OnSelchangeList3() 
{
	// TODO: Add your control notification handler code here
	if(this->m_listcorres.GetCurSel()==0)
		this->m_listalgor.BeginModalState();
	else 
		this->m_listalgor.EndModalState();
}

void cacheSettings::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	int sel=this->m_combo1.GetCurSel();
	if(sel!=this->comboSel){
		if(!sel){
			if(data_simulation){
				this->instructionGetValues();
				this->dataDisplay();
			}
			else{
				MessageBox("Data cache simulation is not enabled");
				this->m_combo1.SetCurSel(1);
			}
		}
		else{
			if(inst_simulation){
				this->dataGetValues();
				instructionDisplay();
			}
			else{
				MessageBox("Instruction cache is not enabled");
				this->m_combo1.SetCurSel(0);
			}
		}
		this->comboSel=this->m_combo1.GetCurSel();
	}
		
		
	
}
