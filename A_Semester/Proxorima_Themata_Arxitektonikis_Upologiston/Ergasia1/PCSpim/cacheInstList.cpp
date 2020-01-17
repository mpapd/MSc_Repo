// cacheInstList.cpp : implementation file
//

#include "stdafx.h"
#include "PCSpim.h"
#include "cacheInstList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define	BIT_W	20   //column width for the valid and modified bit
#define ALG_W	40	 //column width for the algorithm column
#define	SET_W	38	
#define	ACC_W	33
#define	TAG_W	60
#define AUT_SCR	3	//for the automatic vertical scroll
/////////////////////////////////////////////////////////////////////////////
// cacheInstList

cacheInstList::cacheInstList()
{
}

cacheInstList::~cacheInstList()
{
}


void cacheInstList::InitializeList(){
	
	
	if(c_inst->num_ways==1){		//one way
		if(c_inst->wr_policy.hit_policy!=1)   //write-through
			this->initListOneWayNoBack();
		else
			this->initListOneWayBack();   //write-back
	}
	else if(c_inst->num_ways>1 && !c_inst->fully_associ){
		if(c_inst->wr_policy.hit_policy!=1)
			this->initListMoreWaysNoBack();
		else
			this->initListMoreWaysBack();
	}
	else{
		if(c_inst->wr_policy.hit_policy!=1)
			this->initFullyNoBack();
		else
			this->initFullyBack();
	}

	
	CHeaderCtrl *col=this->GetHeaderCtrl();
	col->BeginModalState();   //to fix the columns
	
}

void cacheInstList::initListOneWayNoBack(){
	RECT r;
	this->GetClientRect(&r);
	r.right-=15;
	this->InsertColumn(0,"Set");
	this->InsertColumn(1,"V");
	this->InsertColumn(2,"Tag (h)");
	this->InsertColumn(3,"Instructions (h)");
	this->InsertColumn(4,"Acc");
	r.right=r.right-SET_W-BIT_W-TAG_W-ACC_W;
	this->SetColumnWidth(0,SET_W);
	this->SetColumnWidth(1,BIT_W);
	this->SetColumnWidth(2,TAG_W);//(int)(r.right*.2));
	this->SetColumnWidth(3,r.right);//(int)(r.right*.7));
	this->SetColumnWidth(4,ACC_W);//(int)(r.right*.1));
	//this->fitColumns(3,4);
	for(int i=0;i<(int)c_inst->num_sets;i++){
		char frase[5];
		sprintf(frase,"%d",i);
		this->InsertItem(i,frase);
		this->SetItemText(i,1,"0");
	}

	this->colAcc=4;
}


void cacheInstList::initListOneWayBack(){
	RECT r;
	this->GetClientRect(&r);
	r.right-=15;
	this->InsertColumn(0,"Set");
	this->InsertColumn(1,"V");
	this->InsertColumn(2,"M");
	this->InsertColumn(3,"Tag (h)");
	this->InsertColumn(4,"Instructions (h)");
	this->InsertColumn(5,"Acc");
	r.right=r.right-SET_W-2*BIT_W-TAG_W-ACC_W;
	this->SetColumnWidth(0,SET_W);
	this->SetColumnWidth(1,BIT_W);
	this->SetColumnWidth(2,BIT_W);
	this->SetColumnWidth(3,TAG_W);//(int)(r.right*.2));
	this->SetColumnWidth(4,r.right);//(int)(r.right*.7));
	this->SetColumnWidth(5,ACC_W);//(int)(r.right*.1));
	//this->fitColumns(4,5);
	for(int i=0;i<(int)c_inst->num_sets;i++){
		char frase[5];
		sprintf(frase,"%d",i);
		this->InsertItem(i,frase);
		this->SetItemText(i,1,"0");
		this->SetItemText(i,2,"0");
	}

	this->colAcc=5;

}


void cacheInstList::initListMoreWaysNoBack(){
	RECT r;
	char dataway[25];
	this->GetClientRect(&r);
	this->InsertColumn(0,"Set");
	this->SetColumnWidth(0,SET_W);
	r.right-=15;   //size of the vscroll-bar?
	r.right=r.right-SET_W-2*(BIT_W+ALG_W+TAG_W+ACC_W)-10;
	r.right/=2;
	for(int j=0;j<(int)c_inst->num_ways;j++){
		this->InsertColumn(1+(j*6),"V");
		c_inst->algorithm?this->InsertColumn(2+(j*6),"FIFO"):this->InsertColumn(2+(j*6),"LRU");
		this->InsertColumn(3+(j*6),"Tag (h)");
		sprintf(dataway,"Instructions (h)   Way %d",j);
		this->InsertColumn(4+(j*6),dataway);
		this->InsertColumn(5+(j*6),"Acc");
		if(j!=(int)c_inst->num_ways-1){
			this->InsertColumn(6+(j*6),"");
			this->SetColumnWidth(6+(j*6),10);
		}
		this->SetColumnWidth(1+(j*6),BIT_W);
		this->SetColumnWidth(2+(j*6),ALG_W);
		this->SetColumnWidth(3+(j*6),TAG_W);//(int)((r.right/2)*.2));
		this->SetColumnWidth(4+(j*6),r.right);//(int)((r.right/2)*.7));
		this->SetColumnWidth(5+(j*6),ACC_W);//(int)((r.right/2)*.1));
	}
	//this->fitColumns(4,6);
	for(int i=0;i<(int)c_inst->num_sets;i++){
		char frase[5];
		sprintf(frase,"%d",i);
		this->InsertItem(i,frase);
		for(int k=0;k<(int)c_inst->num_ways;k++){
			this->SetItemText(i,1+(k*6),"0");
			this->SetItemText(i,2+(k*6),"0");
		}
	}

	this->colAcc=5;
}


void cacheInstList::initListMoreWaysBack(){
	RECT r;
	char dataway[25];
	this->GetClientRect(&r);
	this->InsertColumn(0,"Set");
	this->SetColumnWidth(0,SET_W);
	r.right-=15;   //size of the vscroll-bar?
	r.right=r.right-SET_W-10-2*(2*BIT_W+ALG_W+TAG_W+ACC_W);
	r.right/=2;
	for(int j=0;j<(int)c_inst->num_ways;j++){
		this->InsertColumn(1+(j*7),"V");
		c_inst->algorithm?this->InsertColumn(2+(j*7),"FIFO"):this->InsertColumn(2+(j*7),"LRU");
		this->InsertColumn(3+(j*7),"M");
		this->InsertColumn(4+(j*7),"Tag (h)");
		sprintf(dataway,"Instructions (h)   Way %d",j);
		this->InsertColumn(5+(j*7),dataway);
		this->InsertColumn(6+(j*7),"Acc");
		if(j!=(int)c_inst->num_ways-1){
			this->InsertColumn(7+(j*7),"");
			this->SetColumnWidth(7+(j*7),10);
		}
		this->SetColumnWidth(1+(j*7),BIT_W);
		this->SetColumnWidth(2+(j*7),ALG_W);
		this->SetColumnWidth(3+(j*7),BIT_W);
		this->SetColumnWidth(4+(j*7),TAG_W);//(int)((r.right/2)*.2));
		this->SetColumnWidth(5+(j*7),r.right);//(int)((r.right/2)*.7));
		this->SetColumnWidth(6+(j*7),ACC_W);//(int)((r.right/2)*.1));
	}
	//this->fitColumns(5,7);
	for(int i=0;i<(int)c_inst->num_sets;i++){
		char frase[5];
		sprintf(frase,"%d",i);
		this->InsertItem(i,frase);
		for(int k=0;k<(int)c_inst->num_ways;k++){
			this->SetItemText(i,1+(k*7),"0");
			this->SetItemText(i,2+(k*7),"0");
			this->SetItemText(i,3+(k*7),"0");
		}
	}

	this->colAcc=6;
}


void cacheInstList::initFullyNoBack(){
	RECT r;
	this->GetClientRect(&r);
	r.right-=15;
	this->InsertColumn(0,"Way");  
	this->InsertColumn(1,"V");
	c_inst->algorithm?this->InsertColumn(2,"FIFO"):this->InsertColumn(2,"LRU");
	this->InsertColumn(3,"Tag (h)");
	this->InsertColumn(4,"Instructions (h)");
	this->InsertColumn(5,"Acc");
	r.right=r.right-SET_W-BIT_W-ALG_W-TAG_W-ACC_W;
	this->SetColumnWidth(0,SET_W);
	this->SetColumnWidth(1,BIT_W);
	this->SetColumnWidth(2,ALG_W);
	this->SetColumnWidth(3,TAG_W);
	this->SetColumnWidth(4,r.right);
	this->SetColumnWidth(5,ACC_W);
	for(int j=0;j<(int)c_inst->num_ways;j++){
		char frase[5];
		sprintf(frase,"%d",j);
		this->InsertItem(j,"");
		this->SetItemText(j,0,frase);
		this->SetItemText(j,1,"0");
		this->SetItemText(j,2,"0");
	}

	this->colAcc=5;
}


void cacheInstList::initFullyBack(){
	RECT r;
	this->GetClientRect(&r);
	r.right-=15;
	this->InsertColumn(0,"Way");  
	this->InsertColumn(1,"V");
	c_inst->algorithm?this->InsertColumn(2,"FIFO"):this->InsertColumn(2,"LRU");
	this->InsertColumn(3,"M");
	this->InsertColumn(4,"Tag (h)");
	this->InsertColumn(5,"Instructions (h)");
	this->InsertColumn(6,"Acc");
	r.right=r.right-SET_W-2*BIT_W-ALG_W-TAG_W-ACC_W;
	this->SetColumnWidth(0,SET_W);
	this->SetColumnWidth(1,BIT_W);
	this->SetColumnWidth(2,ALG_W);
	this->SetColumnWidth(3,BIT_W);
	this->SetColumnWidth(4,TAG_W);
	this->SetColumnWidth(5,r.right);
	this->SetColumnWidth(6,ACC_W);
	for(int j=0;j<(int)c_inst->num_ways;j++){
		char frase[5];
		sprintf(frase,"%d",j);
		this->InsertItem(j,"");
		this->SetItemText(j,0,frase);
		this->SetItemText(j,1,"0");
		this->SetItemText(j,2,"0");
		this->SetItemText(j,3,"0");
	}

	this->colAcc=6;
}

void cacheInstList::SizeList(){
	if(c_inst->num_ways==1){		//one way
		if(c_inst->wr_policy.hit_policy!=1)   //write-through
			this->sizeListOneWayNoBack();
		else
			this->sizeListOneWayBack();   //write-back
	}
	else if(c_inst->num_ways>1 && !c_inst->fully_associ){
		if(c_inst->wr_policy.hit_policy!=1)
			this->sizeListMoreWaysNoBack();
		else
			this->sizeListMoreWaysBack();
	}
	else{
		if(c_inst->wr_policy.hit_policy!=1)
			this->sizeListFullyNoBack();
		else
			this->sizeListFullyBack();
	}
}


void cacheInstList::sizeListOneWayNoBack(){
	RECT r;
	this->GetClientRect(&r);
	r.right=r.right-SET_W-BIT_W-TAG_W-ACC_W;
	this->SetColumnWidth(0,SET_W);
	this->SetColumnWidth(1,BIT_W);
	this->SetColumnWidth(2,TAG_W);//(int)(r.right*.2));
	this->SetColumnWidth(3,r.right);//(int)(r.right*.7));
	this->SetColumnWidth(4,ACC_W);//(int)(r.right*.1));
}


void cacheInstList::sizeListOneWayBack(){
	RECT r;
	this->GetClientRect(&r);
	r.right=r.right-SET_W-(2*BIT_W)-TAG_W-ACC_W;
	this->SetColumnWidth(0,SET_W);
	this->SetColumnWidth(1,BIT_W);
	this->SetColumnWidth(2,BIT_W);
	this->SetColumnWidth(3,TAG_W);//(int)(r.right*.2));
	this->SetColumnWidth(4,r.right);//(int)(r.right*.7));
	this->SetColumnWidth(5,ACC_W);//(int)(r.right*.1));
}


void cacheInstList::sizeListMoreWaysNoBack(){
	RECT r;
	this->GetClientRect(&r);
	this->SetColumnWidth(0,SET_W);
	r.right=r.right-SET_W-2*(BIT_W+ALG_W+TAG_W+ACC_W)-10;
	r.right/=2;
	for(int j=0;j<(int)c_inst->num_ways;j++){
		if(j!=(int)c_inst->num_ways-1)
			this->SetColumnWidth(6+(j*6),10);
		this->SetColumnWidth(1+(j*6),BIT_W);
		this->SetColumnWidth(2+(j*6),ALG_W);
		this->SetColumnWidth(3+(j*6),TAG_W);//(int)(r.right*.2));
		this->SetColumnWidth(4+(j*6),r.right);//(int)(r.right*.7));
		this->SetColumnWidth(5+(j*6),ACC_W);//(int)(r.right*.1));
	}
}


void cacheInstList::sizeListMoreWaysBack(){
	RECT r;
	this->GetClientRect(&r);
	this->SetColumnWidth(0,SET_W);
	r.right=r.right-SET_W-2*(2*BIT_W+ALG_W+TAG_W+ACC_W)-10;
	r.right/=2;
	for(int j=0;j<(int)c_inst->num_ways;j++){
		if(j!=(int)c_inst->num_ways-1)
			this->SetColumnWidth(7+(j*7),10);
		this->SetColumnWidth(1+(j*7),BIT_W);
		this->SetColumnWidth(2+(j*7),ALG_W);
		this->SetColumnWidth(3+(j*7),BIT_W);
		this->SetColumnWidth(4+(j*7),TAG_W);//(int)(r.right*.2));
		this->SetColumnWidth(5+(j*7),r.right);//(int)(r.right*.7));
		this->SetColumnWidth(6+(j*7),ACC_W);//(int)(r.right*.1));
	}
}


void cacheInstList::sizeListFullyNoBack(){
	RECT r;
	this->GetClientRect(&r);
	r.right=r.right-SET_W-BIT_W-ALG_W-TAG_W-ACC_W;
	this->SetColumnWidth(0,SET_W);
	this->SetColumnWidth(1,BIT_W);
	this->SetColumnWidth(2,ALG_W);
	this->SetColumnWidth(3,TAG_W);
	this->SetColumnWidth(4,r.right);
	this->SetColumnWidth(5,ACC_W);
}


void cacheInstList::sizeListFullyBack(){
	RECT r;
	this->GetClientRect(&r);
	r.right=r.right-SET_W-(2*BIT_W)-ALG_W-TAG_W-ACC_W;
	this->SetColumnWidth(0,SET_W);
	this->SetColumnWidth(1,BIT_W);
	this->SetColumnWidth(2,ALG_W);
	this->SetColumnWidth(3,BIT_W);
	this->SetColumnWidth(4,TAG_W);
	this->SetColumnWidth(5,r.right);
	this->SetColumnWidth(6,ACC_W);
}

void cacheInstList::updateListOneWayNoBack(){
	for(int i=0;i<(int)c_inst->num_sets;i++){
		char frase[100];
		for(int v=0;v<(int)c_inst->num_ways;v++){

			if(c_inst->set[i].way[v].acc!=-1){
				int pos=this->GetScrollPos(SB_VERT);
				if(pos+AUT_SCR<=i)
					for(int k=0;k<i-pos-AUT_SCR+1;k++)
						this->SendMessage(WM_VSCROLL,SB_LINEDOWN,0);
				else if(pos>i+AUT_SCR)
					for(int k=0;k<pos-i;k++)
						this->SendMessage(WM_VSCROLL,SB_LINEUP,0);
			}   //   set the scroll bar in the right position

						
			if(c_inst->set[i].way[v].tag==NULL){
				this->SetItemText(i,1,"0");
				this->SetItemText(i,2,"");
				this->SetItemText(i,3,"");
				if(c_inst->set[i].way[v].acc==0){
					this->SetItemText(i,4,"miss");
					this->lastAcc=0;
					this->rowAcc=i;
				}
				else
					this->SetItemText(i,4,"");
			}
			else{
						
				
				sprintf(frase,"%d",c_inst->set[i].way[v].valid);
				this->SetItemText(i,1,frase);
				sprintf(frase,"%x",c_inst->set[i].way[v].tag);
				this->SetItemText(i,2,frase);
				CString dada("");
				for(int k=0;k<(int)(c_inst->block_size/4);k++){   //mirem cada paraula del bloc
					if(c_inst->set[i].way[v].block[k]==NULL)
						sprintf(frase,"  NULL  ");
					else
						format_cache_instruction(c_inst->set[i].way[v].block[k],frase);
						//sprintf(frase,"%x",c_inst->set[i].way[v].block[k]);
					CString dada1(frase);
					/*int l=dada1.GetLength();
					for(int j=0;j<8-l;j++)
					dada1="0"+dada1;*/
					dada=dada+dada1+"     ";
					
				}
				//dada="0x"+dada;
				this->SetItemText(i,3,dada);
				
				if(c_inst->set[i].way[v].acc==-1)
					this->SetItemText(i,4,"");
				else if(c_inst->set[i].way[v].acc==0){
					this->SetItemText(i,4,"miss");
					this->lastAcc=0;
					this->rowAcc=i;
				}
				else{
					this->SetItemText(i,4,"hit");
					this->lastAcc=1;
					this->rowAcc=i;
				}
			}
		}
	}
}


void cacheInstList::updateListOneWayBack(){
	for(int i=0;i<(int)c_inst->num_sets;i++){
		char frase[100];
		for(int v=0;v<(int)c_inst->num_ways;v++){
			
			if(c_inst->set[i].way[v].acc!=-1){
					int pos=this->GetScrollPos(SB_VERT);
					if(pos+AUT_SCR<=i)
						for(int k=0;k<i-pos-AUT_SCR+1;k++)
							this->SendMessage(WM_VSCROLL,SB_LINEDOWN,0);
					else if(pos>i+AUT_SCR)
						for(int k=0;k<pos-i;k++)
							this->SendMessage(WM_VSCROLL,SB_LINEUP,0);
				}   //   col·loquem la scroll bar en la posició adequada			
			
			
			if(c_inst->set[i].way[v].tag==NULL){
				this->SetItemText(i,1,"0");
				this->SetItemText(i,2,"0");
				this->SetItemText(i,3,"");
				this->SetItemText(i,4,"");
				if(c_inst->set[i].way[v].acc==0){
					this->SetItemText(i,5,"miss");
					this->lastAcc=0;
					this->rowAcc=i;
				}
				else
					this->SetItemText(i,5,"");
			}
			else{
				
				sprintf(frase,"%d",c_inst->set[i].way[v].valid);
				this->SetItemText(i,1,frase);
				sprintf(frase,"%d",c_inst->set[i].way[v].modified);
				this->SetItemText(i,2,frase);
				sprintf(frase,"%x",c_inst->set[i].way[v].tag);
				this->SetItemText(i,3,frase);
				CString dada("");
				for(int k=0;k<(int)(c_inst->block_size/4);k++){   //mirem cada paraula del bloc
					if(c_inst->set[i].way[v].block[k]==NULL)
						sprintf(frase,"  NULL  ");
					else
						format_cache_instruction(c_inst->set[i].way[v].block[k],frase);
					//sprintf(frase,"%x",c_inst->set[i].way[v].block[k]);
					CString dada1(frase);
					//int l=dada1.GetLength();
					//for(int j=0;j<8-l;j++)
					//dada1="0"+dada1;
					dada=dada+dada1+"     ";
				}
				//dada="0x"+dada;
				this->SetItemText(i,4,dada);
				if(c_inst->set[i].way[v].acc==-1)
					this->SetItemText(i,5,"");
				else if(c_inst->set[i].way[v].acc==0){
					this->SetItemText(i,5,"miss");
					this->lastAcc=0;
					this->rowAcc=i;
				}
				else{
					this->SetItemText(i,5,"hit");
					this->lastAcc=1;
					this->rowAcc=i;
				}
			}
		}
	}
}


void cacheInstList::updateListMoreWaysNoBack(){
	for(int i=0;i<(int)c_inst->num_sets;i++){
		char frase[100];
		for(int v=0;v<(int)c_inst->num_ways;v++){
				
			if(c_inst->set[i].way[v].acc!=-1){
					int pos=this->GetScrollPos(SB_VERT);
					if(pos+AUT_SCR<=i)
						for(int k=0;k<i-pos-AUT_SCR+1;k++)
							this->SendMessage(WM_VSCROLL,SB_LINEDOWN,0);
					else if(pos>i+AUT_SCR)
						for(int k=0;k<pos-i;k++)
							this->SendMessage(WM_VSCROLL,SB_LINEUP,0);
					if(c_inst->num_ways>2){
						pos=this->GetScrollPos(SB_HORZ);
						int lim=this->GetScrollLimit(SB_HORZ);
						
						if((c_inst->miss_step==2 || c_inst->set[i].way[v].acc==1) && (v==2 || v==3))
							for(int k=pos;k<lim;k++)
								this->SendMessage(WM_HSCROLL,SB_LINERIGHT,0);
						else if((c_inst->miss_step==2 || c_inst->set[i].way[v].acc==1) && (v==0 || v==1))
							for(int k=pos;k>0;k--)
								this->SendMessage(WM_HSCROLL,SB_LINELEFT,0);
					}
							
				}   //   col·loquem la scroll bar en la posició adequada
			
			
			if(c_inst->set[i].way[v].tag==NULL){
				this->SetItemText(i,1+(v*6),"0");
				this->SetItemText(i,3+(v*6),"");
				this->SetItemText(i,4+(v*6),"");
				if(c_inst->set[i].way[v].acc==0){
					this->lastAcc=0;
					this->rowAcc=i;
					this->SetItemText(i,5+(v*6),"miss");					
				}
				else
					this->SetItemText(i,5+(v*6),"");
			}
			
			else{
				
					
				sprintf(frase,"%d",c_inst->set[i].way[v].valid);
				this->SetItemText(i,1+(v*6),frase);
				sprintf(frase,"%d",c_inst->set[i].way[v].counter);
				this->SetItemText(i,2+(v*6),frase);
				sprintf(frase,"%x",c_inst->set[i].way[v].tag);
				this->SetItemText(i,3+(v*6),frase);
				CString dada("");
				for(int k=0;k<(int)(c_inst->block_size/4);k++){   //mirem cada paraula del bloc
					if(c_inst->set[i].way[v].block[k]==NULL)
						sprintf(frase,"  NULL  ");
					else
						format_cache_instruction(c_inst->set[i].way[v].block[k],frase);
					//sprintf(frase,"%x",c_inst->set[i].way[v].block[k]);
					CString dada1(frase);
					//int l=dada1.GetLength();
					//for(int j=0;j<8-l;j++)
					//dada1="0"+dada1;
					dada=dada+dada1+"     ";
				}
				//dada="0x"+dada;
				this->SetItemText(i,4+(v*6),dada);
				
				if(c_inst->set[i].way[v].acc==-1)
					this->SetItemText(i,5+(v*6),"");
				else if(c_inst->set[i].way[v].acc==0){
					this->lastAcc=0;
					this->rowAcc=i;
					this->SetItemText(i,5+(v*6),"miss");					
				}
				else{
					this->lastAcc=1;
					this->rowAcc=i;
					this->SetItemText(i,5+(v*6),"hit");					
				}
			}
		}
	}
}


void cacheInstList::updateListMoreWaysBack(){
	for(int i=0;i<(int)c_inst->num_sets;i++){
		char frase[100];
		for(int v=0;v<(int)c_inst->num_ways;v++){
			
			if(c_inst->set[i].way[v].acc!=-1){
					int pos=this->GetScrollPos(SB_VERT);
					if(pos+AUT_SCR<=i)
						for(int k=0;k<i-pos-AUT_SCR+1;k++)
							this->SendMessage(WM_VSCROLL,SB_LINEDOWN,0);
					else if(pos>i+AUT_SCR)
						for(int k=0;k<pos-i;k++)
							this->SendMessage(WM_VSCROLL,SB_LINEUP,0);
					if(c_inst->num_ways>2){
						pos=this->GetScrollPos(SB_HORZ);
						int lim=this->GetScrollLimit(SB_HORZ);
						
						if((c_inst->miss_step==2 || c_inst->set[i].way[v].acc==1) && (v==2 || v==3))
							for(int k=pos;k<lim;k++)
								this->SendMessage(WM_HSCROLL,SB_LINERIGHT,0);
						else if((c_inst->miss_step==2 || c_inst->set[i].way[v].acc==1) && (v==0 || v==1))
							for(int k=pos;k>0;k--)
								this->SendMessage(WM_HSCROLL,SB_LINELEFT,0);
					}
				}   //   col·loquem la scroll bar en la posició adequada
			
			
			if(c_inst->set[i].way[v].tag==NULL){
				this->SetItemText(i,1+(v*7),"0");
				this->SetItemText(i,3+(v*7),"0");
				this->SetItemText(i,4+(v*7),"");
				this->SetItemText(i,5+(v*7),"");
				if(c_inst->set[i].way[v].acc==0)
					this->SetItemText(i,6+(v*7),"miss");
				else
					this->SetItemText(i,6+(v*7),"");
			}
			else{
				

				sprintf(frase,"%d",c_inst->set[i].way[v].valid);
				this->SetItemText(i,1+(v*7),frase);
				sprintf(frase,"%d",c_inst->set[i].way[v].counter);
				this->SetItemText(i,2+(v*7),frase);
				sprintf(frase,"%d",c_inst->set[i].way[v].modified);
				this->SetItemText(i,3+(v*7),frase);
				sprintf(frase,"%x",c_inst->set[i].way[v].tag);
				this->SetItemText(i,4+(v*7),frase);
				CString dada("");
				for(int k=0;k<(int)(c_inst->block_size/4);k++){   //mirem cada paraula del bloc
					if(c_inst->set[i].way[v].block[k]==NULL)
						sprintf(frase,"  NULL  ");
					else
						format_cache_instruction(c_inst->set[i].way[v].block[k],frase);
					//sprintf(frase,"%x",c_inst->set[i].way[v].block[k]);
					CString dada1(frase);
					//int l=dada1.GetLength();
					//for(int j=0;j<8-l;j++)
					//dada1="0"+dada1;
					dada=dada+dada1+"     ";
				}
				//dada="0x"+dada;
				this->SetItemText(i,5+(v*7),dada);
				if(c_inst->set[i].way[v].acc==-1)
					this->SetItemText(i,6+(v*7),"");
				else if(c_inst->set[i].way[v].acc==0)
					this->SetItemText(i,6+(v*7),"miss");
				else
					this->SetItemText(i,6+(v*7),"hit");
			}
		}
	}
}


void cacheInstList::updateListFullyNoBack(){
	for(int i=0;i<(int)c_inst->num_sets;i++){
		char frase[100];
		for(int v=0;v<(int)c_inst->num_ways;v++){
			
			if(c_inst->set[i].way[v].acc!=-1){
					int pos=this->GetScrollPos(SB_VERT);
					if(pos+AUT_SCR<=v)
						for(int k=0;k<v-pos;k++)
							this->SendMessage(WM_VSCROLL,SB_LINEDOWN,0);
					else if(pos>v+AUT_SCR)
						for(int k=0;k<pos-v+AUT_SCR-1;k++)
							this->SendMessage(WM_VSCROLL,SB_LINEUP,0);
				}   //   col·loquem la scroll bar en la posició adequada
			
			
			if(c_inst->set[i].way[v].tag==NULL){
				this->SetItemText(v,1,"0");
				this->SetItemText(v,3,"");
				this->SetItemText(v,4,"");
				if(c_inst->set[i].way[v].acc==0){
					this->SetItemText(v,5,"miss");
					this->lastAcc=0;
					this->rowAcc=v;
				}
				else
					this->SetItemText(v,5,"");
			}
			else{
				
				
				sprintf(frase,"%d",c_inst->set[i].way[v].valid);
				this->SetItemText(v,1,frase);
				sprintf(frase,"%d",c_inst->set[i].way[v].counter);
				this->SetItemText(v,2,frase);
				sprintf(frase,"%x",c_inst->set[i].way[v].tag);
				this->SetItemText(v,3,frase);
				CString dada("");
				for(int k=0;k<(int)(c_inst->block_size/4);k++){   //mirem cada paraula del bloc
					if(c_inst->set[i].way[v].block[k]==NULL)
						sprintf(frase,"  NULL  ");
					else
						format_cache_instruction(c_inst->set[i].way[v].block[k],frase);
					//sprintf(frase,"%x",c_inst->set[i].way[v].block[k]);
					CString dada1(frase);
					//int l=dada1.GetLength();
					//for(int j=0;j<8-l;j++)
					//dada1="0"+dada1;
					dada=dada+dada1+"     ";
				}
				//dada="0x"+dada;
				this->SetItemText(v,4,dada);
				
				if(c_inst->set[i].way[v].acc==-1)
					this->SetItemText(v,5,"");
				else if(c_inst->set[i].way[v].acc==0){
					this->SetItemText(v,5,"miss");
					this->lastAcc=0;
					this->rowAcc=v;
				}
				else{
					this->SetItemText(v,5,"hit");
					this->lastAcc=1;
					this->rowAcc=v;
				}
			}
		}
	}
}


void cacheInstList::updateListFullyBack(){
	for(int i=0;i<(int)c_inst->num_sets;i++){
		char frase[100];
		for(int v=0;v<(int)c_inst->num_ways;v++){
			
			if(c_inst->set[i].way[v].acc!=-1){
					int pos=this->GetScrollPos(SB_VERT);
					if(pos+AUT_SCR<=v)
						for(int k=0;k<v-pos;k++)
							this->SendMessage(WM_VSCROLL,SB_LINEDOWN,0);
					else if(pos>v+AUT_SCR)
						for(int k=0;k<pos-v+AUT_SCR-1;k++)
							this->SendMessage(WM_VSCROLL,SB_LINEUP,0);
				}   //   col·loquem la scroll bar en la posició adequada
			
			
			if(c_inst->set[i].way[v].tag==NULL){
				this->SetItemText(v,1,"0");
				this->SetItemText(v,3,"0");
				this->SetItemText(v,4,"");
				this->SetItemText(v,5,"");
				if(c_inst->set[i].way[v].acc==0)
					this->SetItemText(v,6,"miss");
				else
					this->SetItemText(v,6,"");
			}
			else{
				

				sprintf(frase,"%d",c_inst->set[i].way[v].valid);
				this->SetItemText(v,1,frase);
				sprintf(frase,"%d",c_inst->set[i].way[v].counter);
				this->SetItemText(v,2,frase);
				sprintf(frase,"%d",c_inst->set[i].way[v].modified);
				this->SetItemText(v,3,frase);
				sprintf(frase,"%x",c_inst->set[i].way[v].tag);
				this->SetItemText(v,4,frase);
				CString dada("");
				for(int k=0;k<(int)(c_inst->block_size/4);k++){   //mirem cada paraula del bloc
					if(c_inst->set[i].way[v].block[k]==NULL)
						sprintf(frase,"  NULL  ");
					else
						format_cache_instruction(c_inst->set[i].way[v].block[k],frase);
					//sprintf(frase,"%x",c_inst->set[i].way[v].block[k]);
					CString dada1(frase);
					//int l=dada1.GetLength();
					//for(int j=0;j<8-l;j++)
					//dada1="0"+dada1;
					dada=dada+dada1+"     ";
				}
				//dada="0x"+dada;
				this->SetItemText(v,5,dada);
				if(c_inst->set[i].way[v].acc==-1)
					this->SetItemText(v,6,"");
				else if(c_inst->set[i].way[v].acc==0)
					this->SetItemText(v,6,"miss");
				else
					this->SetItemText(v,6,"hit");
			}
		}
	}
}


BEGIN_MESSAGE_MAP(cacheInstList, CListCtrl)
	//{{AFX_MSG_MAP(cacheInstList)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW,OnCustomDraw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// cacheInstList message handlers

int cacheInstList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	this->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	this->colAcc=-1;
	this->lastAcc=-1;
	this->rowAcc=0;
	
	return 0;
}


void cacheInstList::OnCustomDraw(NMHDR *pNMHDR,LRESULT *pResult){
	
	//NMLVCUSTOMDRAW *pCustomDraw = reinterpret_cast<NMLVCUSTOMDRAW *> (pNMHDR);
	int draw;
	NMLVCUSTOMDRAW *pCustomDraw = (NMLVCUSTOMDRAW *) pNMHDR;
	if(pCustomDraw->iSubItem>this->colAcc){
		if(pCustomDraw->iSubItem%this->colAcc==1 || pCustomDraw->iSubItem%this->colAcc==0)
			draw=1;
		else
			draw=0;
	}
	else{
		if(pCustomDraw->iSubItem==this->colAcc || pCustomDraw->iSubItem==this->colAcc-1)
			draw=1;
		else
			draw=0;
	}

	switch(pCustomDraw->nmcd.dwDrawStage){
		case CDDS_PREPAINT:
			*pResult=CDRF_NOTIFYSUBITEMDRAW;
			break;
		
		case CDDS_PREPAINT|CDDS_ITEM:
			*pResult=CDRF_NOTIFYSUBITEMDRAW;
			break;
		case CDDS_SUBITEM|CDDS_ITEM|CDDS_PREPAINT:
			if((pCustomDraw->nmcd.dwItemSpec==(unsigned int)this->rowAcc) && draw){
				if(this->lastAcc==0)
					pCustomDraw->clrText=RGB(255,0,0);
				else if(this->lastAcc==1)
					pCustomDraw->clrText=RGB(0,0,255);
				*pResult=CDRF_NEWFONT;
			}
			else{
				pCustomDraw->clrText=RGB(0,0,0);
				*pResult=CDRF_NEWFONT;
			}
			break;
			
		default:
			*pResult=CDRF_DODEFAULT;
			break;
	}
	
	

}
