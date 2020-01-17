// cachestatic.cpp : implementation file
//

#include "stdafx.h"
#include "PCSpim.h"
#include "cachestatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// cachestatic

cachestatic::cachestatic()
{
	this->texto=RGB(0,0,0);
	this->fondo=RGB(255,255,255);
	llapis.CreateSolidBrush(fondo);
}

cachestatic::~cachestatic()
{
}

void cachestatic::updateInst(){
	char frase2[200];
	double taxa=0.0;
	double acce=1.0*c_inst->statistics.accesses;
	double ence=1.0*c_inst->statistics.hits;
	if(c_inst->statistics.accesses && c_inst->statistics.hits)
		taxa=ence/acce;
	sprintf(frase2," Instruction Cache   Accesses:%d   Hits:%d   Hit Rate:%f",c_inst->statistics.accesses,c_inst->statistics.hits,taxa);
	if(c_inst->statistics.show)
		this->SetWindowText(frase2);
}


void cachestatic::update(){
	char frase2[200];
	double taxa=0.0;
	double acce=1.0*c_dat->statistics.accesses;
	double ence=1.0*c_dat->statistics.hits;
	if(c_dat->statistics.accesses && c_dat->statistics.hits)
		taxa=ence/acce;
	sprintf(frase2," Data Cache   Accesses:%d   Hits:%d   Hit Rate:%f         Misses:   Compulsory:%d   Conflict:%d   Capacity:%d",c_dat->statistics.accesses,c_dat->statistics.hits,taxa,c_dat->statistics.compulsory,c_dat->statistics.conflict,c_dat->statistics.capacity);
	if(c_dat->statistics.show)
		this->SetWindowText(frase2);
}

BEGIN_MESSAGE_MAP(cachestatic, CStatic)
	//{{AFX_MSG_MAP(cachestatic)
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// cachestatic message handlers

HBRUSH cachestatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	pDC->SetTextColor(texto);
	pDC->SetBkColor(fondo);
	return llapis;
	
	// TODO: Return a non-NULL brush if the parent's handler should not be called
	//return NULL;
}
