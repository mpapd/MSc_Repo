// cacheList.cpp : implementation file
//

#include "stdafx.h"
#include "PCSpim.h"
#include "cacheList.h"

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
#define AUT_SCR	3
/////////////////////////////////////////////////////////////////////////////
// cacheList

cacheList::cacheList()
{
}

cacheList::~cacheList()
{
}

void cacheList::InsertarColumna(int index,LPCSTR name){
	this->InsertColumn(index,name);
	this->num_columns++;
}

void cacheList::deleteAllColumns(){
	int tries=0;  //number of tries to delete the columns
	while(this->num_columns || tries!=10000){
	int count=this->num_columns;
	for(int i=0;i<count;i++){
		if(this->DeleteColumn(i))
			this->num_columns--;
	}
	tries++;
	}
}

void cacheList::fitColumns(int ncol,int offset){
	RECT r;
	int length1=0;
	this->GetClientRect(&r);
	for(int i=0;i<this->num_columns || i<9;i++)
		length1+=this->GetColumnWidth(i);
	if(r.right<length1)
		this->SetColumnWidth(0,30-(length1-(r.right-15)));
}		


void cacheList::InitializeList(){
	
	int count=this->GetItemCount();
	if(count)
		this->DeleteAllItems();   
	this->deleteAllColumns();

	if(c_dat->num_ways==1){		//one way
		if(c_dat->wr_policy.hit_policy!=1)   //write-through
			this->initListOneWayNoBack();
		else
			this->initListOneWayBack();   //write-back
	}
	else if(c_dat->num_ways>1 && !c_dat->fully_associ){
		if(c_dat->wr_policy.hit_policy!=1)
			this->initListMoreWaysNoBack();
		else
			this->initListMoreWaysBack();
	}
	else{
		if(c_dat->wr_policy.hit_policy!=1)
			this->initFullyNoBack();
		else
			this->initFullyBack();
	}

	
	CHeaderCtrl *col=this->GetHeaderCtrl();
	col->BeginModalState();   //to fix the columns
	
}

void cacheList::initListOneWayNoBack(){
	RECT r;
	this->GetClientRect(&r);
	r.right-=15;
	this->InsertarColumna(0,"Set");
	this->InsertarColumna(1,"V");
	this->InsertarColumna(2,"Tag (h)");
	this->InsertarColumna(3,"Data (h)");
	this->InsertarColumna(4,"Acc");
	r.right=r.right-SET_W-BIT_W-TAG_W-ACC_W;
	this->SetColumnWidth(0,SET_W);
	this->SetColumnWidth(1,BIT_W);
	this->SetColumnWidth(2,TAG_W);//(int)(r.right*.2));
	this->SetColumnWidth(3,r.right);//(int)(r.right*.7));
	this->SetColumnWidth(4,ACC_W);//(int)(r.right*.1));
	//this->fitColumns(3,4);
	for(int i=0;i<(int)c_dat->num_sets;i++){
		char frase[5];
		sprintf(frase,"%d",i);
		this->InsertItem(i,frase);
		this->SetItemText(i,1,"0");
	}
	this->colAcc=4;
}

void cacheList::initListOneWayBack(){
	RECT r;
	this->GetClientRect(&r);
	r.right-=15;
	this->InsertarColumna(0,"Set");
	this->InsertarColumna(1,"V");
	this->InsertarColumna(2,"M");
	this->InsertarColumna(3,"Tag (h)");
	this->InsertarColumna(4,"Data (h)");
	this->InsertarColumna(5,"Acc");
	r.right=r.right-SET_W-2*BIT_W-TAG_W-ACC_W;
	this->SetColumnWidth(0,SET_W);
	this->SetColumnWidth(1,BIT_W);
	this->SetColumnWidth(2,BIT_W);
	this->SetColumnWidth(3,TAG_W);//(int)(r.right*.2));
	this->SetColumnWidth(4,r.right);//(int)(r.right*.7));
	this->SetColumnWidth(5,ACC_W);//(int)(r.right*.1));
	//this->fitColumns(4,5);
	for(int i=0;i<(int)c_dat->num_sets;i++){
		char frase[5];
		sprintf(frase,"%d",i);
		this->InsertItem(i,frase);
		this->SetItemText(i,1,"0");
		this->SetItemText(i,2,"0");
	}
	this->colAcc=5;
}

void cacheList::initListMoreWaysNoBack(){
	RECT r;
	char dataway[25];
	this->GetClientRect(&r);
	this->InsertarColumna(0,"Set");
	this->SetColumnWidth(0,SET_W);
	r.right-=15;   //size of the vscroll-bar?
	r.right=r.right-SET_W-2*(BIT_W+ALG_W+TAG_W+ACC_W)-10;
	r.right/=2;
	for(int j=0;j<(int)c_dat->num_ways;j++){
		this->InsertarColumna(1+(j*6),"V");
		c_dat->algorithm?this->InsertarColumna(2+(j*6),"FIFO"):this->InsertarColumna(2+(j*6),"LRU");
		this->InsertarColumna(3+(j*6),"Tag (h)");
		sprintf(dataway,"Data (h)   Way %d",j);
		this->InsertarColumna(4+(j*6),dataway);
		this->InsertarColumna(5+(j*6),"Acc");
		if(j!=(int)c_dat->num_ways-1){
			this->InsertarColumna(6+(j*6),"");
			this->SetColumnWidth(6+(j*6),10);
		}
		this->SetColumnWidth(1+(j*6),BIT_W);
		this->SetColumnWidth(2+(j*6),ALG_W);
		this->SetColumnWidth(3+(j*6),TAG_W);//(int)((r.right/2)*.2));
		this->SetColumnWidth(4+(j*6),r.right);//(int)((r.right/2)*.7));
		this->SetColumnWidth(5+(j*6),ACC_W);//(int)((r.right/2)*.1));
	}
	//this->fitColumns(4,6);
	for(int i=0;i<(int)c_dat->num_sets;i++){
		char frase[5];
		sprintf(frase,"%d",i);
		this->InsertItem(i,frase);
		for(int k=0;k<(int)c_dat->num_ways;k++){
			this->SetItemText(i,1+(k*6),"0");
			this->SetItemText(i,2+(k*6),"0");
		}
	}
	this->colAcc=5;
}

void cacheList::initListMoreWaysBack(){
	RECT r;
	char dataway[25];
	this->GetClientRect(&r);
	this->InsertarColumna(0,"Set");
	this->SetColumnWidth(0,SET_W);
	r.right-=15;   //size of the vscroll-bar?
	r.right=r.right-SET_W-10-2*(2*BIT_W+ALG_W+TAG_W+ACC_W);
	r.right/=2;
	for(int j=0;j<(int)c_dat->num_ways;j++){
		this->InsertarColumna(1+(j*7),"V");
		c_dat->algorithm?this->InsertarColumna(2+(j*7),"FIFO"):this->InsertarColumna(2+(j*7),"LRU");
		this->InsertarColumna(3+(j*7),"M");
		this->InsertarColumna(4+(j*7),"Tag (h)");
		sprintf(dataway,"Data (h)   Way %d",j);
		this->InsertarColumna(5+(j*7),dataway);
		this->InsertarColumna(6+(j*7),"Acc");
		if(j!=(int)c_dat->num_ways-1){
			this->InsertarColumna(7+(j*7),"");
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
	for(int i=0;i<(int)c_dat->num_sets;i++){
		char frase[5];
		sprintf(frase,"%d",i);
		this->InsertItem(i,frase);
		for(int k=0;k<(int)c_dat->num_ways;k++){
			this->SetItemText(i,1+(k*7),"0");
			this->SetItemText(i,2+(k*7),"0");
			this->SetItemText(i,3+(k*7),"0");
		}
	}
	this->colAcc=6;
}

void cacheList::initFullyNoBack(){
	RECT r;
	this->GetClientRect(&r);
	r.right-=15;
	this->InsertarColumna(0,"Way");  
	this->InsertarColumna(1,"V");
	c_dat->algorithm?this->InsertarColumna(2,"FIFO"):this->InsertarColumna(2,"LRU");
	this->InsertarColumna(3,"Tag (h)");
	this->InsertarColumna(4,"Data (h)");
	this->InsertarColumna(5,"Acc");
	r.right=r.right-SET_W-BIT_W-ALG_W-TAG_W-ACC_W;
	this->SetColumnWidth(0,SET_W);
	this->SetColumnWidth(1,BIT_W);
	this->SetColumnWidth(2,ALG_W);
	this->SetColumnWidth(3,TAG_W);
	this->SetColumnWidth(4,r.right);
	this->SetColumnWidth(5,ACC_W);
	for(int j=0;j<(int)c_dat->num_ways;j++){
		char frase[5];
		sprintf(frase,"%d",j);
		this->InsertItem(j,"");
		this->SetItemText(j,0,frase);
		this->SetItemText(j,1,"0");
		this->SetItemText(j,2,"0");
	}
	this->colAcc=5;
}

void cacheList::initFullyBack(){
	RECT r;
	this->GetClientRect(&r);
	r.right-=15;
	this->InsertarColumna(0,"Way");  
	this->InsertarColumna(1,"V");
	c_dat->algorithm?this->InsertarColumna(2,"FIFO"):this->InsertarColumna(2,"LRU");
	this->InsertarColumna(3,"M");
	this->InsertarColumna(4,"Tag (h)");
	this->InsertarColumna(5,"Data (h)");
	this->InsertarColumna(6,"Acc");
	r.right=r.right-SET_W-2*BIT_W-ALG_W-TAG_W-ACC_W;
	this->SetColumnWidth(0,SET_W);
	this->SetColumnWidth(1,BIT_W);
	this->SetColumnWidth(2,ALG_W);
	this->SetColumnWidth(3,BIT_W);
	this->SetColumnWidth(4,TAG_W);
	this->SetColumnWidth(5,r.right);
	this->SetColumnWidth(6,ACC_W);
	for(int j=0;j<(int)c_dat->num_ways;j++){
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


void cacheList::SizeList(){
	if(c_dat->num_ways==1){		//one way
		if(c_dat->wr_policy.hit_policy!=1)   //write-through
			this->sizeListOneWayNoBack();
		else
			this->sizeListOneWayBack();   //write-back
	}
	else if(c_dat->num_ways>1 && !c_dat->fully_associ){
		if(c_dat->wr_policy.hit_policy!=1)
			this->sizeListMoreWaysNoBack();
		else
			this->sizeListMoreWaysBack();
	}
	else{
		if(c_dat->wr_policy.hit_policy!=1)
			this->sizeListFullyNoBack();
		else
			this->sizeListFullyBack();
	}
}




void cacheList::sizeListOneWayNoBack(){
	RECT r;
	this->GetClientRect(&r);
	r.right=r.right-SET_W-BIT_W-TAG_W-ACC_W;
	this->SetColumnWidth(0,SET_W);
	this->SetColumnWidth(1,BIT_W);
	this->SetColumnWidth(2,TAG_W);//(int)(r.right*.2));
	this->SetColumnWidth(3,r.right);//(int)(r.right*.7));
	this->SetColumnWidth(4,ACC_W);//(int)(r.right*.1));
	//this->fitColumns(3,4);
}

void cacheList::sizeListOneWayBack(){
	RECT r;
	this->GetClientRect(&r);
	r.right=r.right-SET_W-(2*BIT_W)-TAG_W-ACC_W;
	this->SetColumnWidth(0,SET_W);
	this->SetColumnWidth(1,BIT_W);
	this->SetColumnWidth(2,BIT_W);
	this->SetColumnWidth(3,TAG_W);//(int)(r.right*.2));
	this->SetColumnWidth(4,r.right);//(int)(r.right*.7));
	this->SetColumnWidth(5,ACC_W);//(int)(r.right*.1));
	//this->fitColumns(4,5);
}

void cacheList::sizeListMoreWaysNoBack(){
	RECT r;
	this->GetClientRect(&r);
	this->SetColumnWidth(0,SET_W);
	r.right=r.right-SET_W-2*(BIT_W+ALG_W+TAG_W+ACC_W)-10;
	r.right/=2;
	for(int j=0;j<(int)c_dat->num_ways;j++){
		if(j!=(int)c_dat->num_ways-1)
			this->SetColumnWidth(6+(j*6),10);
		this->SetColumnWidth(1+(j*6),BIT_W);
		this->SetColumnWidth(2+(j*6),ALG_W);
		this->SetColumnWidth(3+(j*6),TAG_W);//(int)(r.right*.2));
		this->SetColumnWidth(4+(j*6),r.right);//(int)(r.right*.7));
		this->SetColumnWidth(5+(j*6),ACC_W);//(int)(r.right*.1));
	}
	//this->fitColumns(4,6);
}

void cacheList::sizeListMoreWaysBack(){
	RECT r;
	this->GetClientRect(&r);
	this->SetColumnWidth(0,SET_W);
	r.right=r.right-SET_W-2*(2*BIT_W+ALG_W+TAG_W+ACC_W)-10;
	r.right/=2;
	for(int j=0;j<(int)c_dat->num_ways;j++){
		if(j!=(int)c_dat->num_ways-1)
			this->SetColumnWidth(7+(j*7),10);
		this->SetColumnWidth(1+(j*7),BIT_W);
		this->SetColumnWidth(2+(j*7),ALG_W);
		this->SetColumnWidth(3+(j*7),BIT_W);
		this->SetColumnWidth(4+(j*7),TAG_W);//(int)(r.right*.2));
		this->SetColumnWidth(5+(j*7),r.right);//(int)(r.right*.7));
		this->SetColumnWidth(6+(j*7),ACC_W);//(int)(r.right*.1));
	}
	//this->fitColumns(5,7);
}

void cacheList::sizeListFullyNoBack(){
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

void cacheList::sizeListFullyBack(){
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





void cacheList::updateListOneWayNoBack(){
	for(int i=0;i<(int)c_dat->num_sets;i++){
		char frase[10];
		for(int v=0;v<(int)c_dat->num_ways;v++){

			if(c_dat->set[i].way[v].acc!=-1){
				int pos=this->GetScrollPos(SB_VERT);
				if(pos+AUT_SCR<=i)
					for(int k=0;k<i-pos-AUT_SCR+1;k++)
						this->SendMessage(WM_VSCROLL,SB_LINEDOWN,0);
				else if(pos>i+AUT_SCR)
					for(int k=0;k<pos-i;k++)
						this->SendMessage(WM_VSCROLL,SB_LINEUP,0);
			}   //   set the scroll bar in the right position

						
			if(c_dat->set[i].way[v].tag==NULL){
				this->SetItemText(i,1,"0");
				this->SetItemText(i,2,"");
				this->SetItemText(i,3,"");
				if(c_dat->set[i].way[v].acc==0){
					this->SetItemText(i,4,"miss");
					this->lastAcc=0;
					this->rowAcc=i;
				}
					
				else
					this->SetItemText(i,4,"");
			}
			else{
						
				
				sprintf(frase,"%d",c_dat->set[i].way[v].valid);
				this->SetItemText(i,1,frase);
				sprintf(frase,"%x",c_dat->set[i].way[v].tag);
				this->SetItemText(i,2,frase);
				CString dada("");
				for(int k=0;k<(int)(c_dat->block_size/4);k++){   //mirem cada paraula del bloc
					sprintf(frase,"%x",c_dat->set[i].way[v].block[k]);
					CString dada1(frase);
					int l=dada1.GetLength();
					for(int j=0;j<8-l;j++)
					dada1="0"+dada1;
					dada=dada+dada1+"   ";
				}
				//dada="0x"+dada;
				this->SetItemText(i,3,dada);
				
				if(c_dat->set[i].way[v].acc==-1)
					this->SetItemText(i,4,"");
				else if(c_dat->set[i].way[v].acc==0){
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

void cacheList::updateListOneWayBack(){
	for(int i=0;i<(int)c_dat->num_sets;i++){
		char frase[10];
		for(int v=0;v<(int)c_dat->num_ways;v++){
			
			if(c_dat->set[i].way[v].acc!=-1){
					int pos=this->GetScrollPos(SB_VERT);
					if(pos+AUT_SCR<=i)
						for(int k=0;k<i-pos-AUT_SCR+1;k++)
							this->SendMessage(WM_VSCROLL,SB_LINEDOWN,0);
					else if(pos>i+AUT_SCR)
						for(int k=0;k<pos-i;k++)
							this->SendMessage(WM_VSCROLL,SB_LINEUP,0);
				}   //   col·loquem la scroll bar en la posició adequada			
			
			
			if(c_dat->set[i].way[v].tag==NULL){
				this->SetItemText(i,1,"0");
				this->SetItemText(i,2,"0");
				this->SetItemText(i,3,"");
				this->SetItemText(i,4,"");
				if(c_dat->set[i].way[v].acc==0){
					this->SetItemText(i,5,"miss");
					this->lastAcc=0;
					this->rowAcc=i;
				}
				else
					this->SetItemText(i,5,"");
			}
			else{
				
				sprintf(frase,"%d",c_dat->set[i].way[v].valid);
				this->SetItemText(i,1,frase);
				sprintf(frase,"%d",c_dat->set[i].way[v].modified);
				this->SetItemText(i,2,frase);
				sprintf(frase,"%x",c_dat->set[i].way[v].tag);
				this->SetItemText(i,3,frase);
				CString dada("");
				for(int k=0;k<(int)(c_dat->block_size/4);k++){   //mirem cada paraula del bloc
					sprintf(frase,"%x",c_dat->set[i].way[v].block[k]);
					CString dada1(frase);
					int l=dada1.GetLength();
					for(int j=0;j<8-l;j++)
					dada1="0"+dada1;
					dada=dada+dada1+"   ";
				}
				//dada="0x"+dada;
				this->SetItemText(i,4,dada);
				if(c_dat->set[i].way[v].acc==-1)
					this->SetItemText(i,5,"");
				else if(c_dat->set[i].way[v].acc==0){
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

void cacheList::updateListMoreWaysNoBack(){
	for(int i=0;i<(int)c_dat->num_sets;i++){
		char frase[10];
		for(int v=0;v<(int)c_dat->num_ways;v++){
				
			if(c_dat->set[i].way[v].acc!=-1){
					int pos=this->GetScrollPos(SB_VERT);
					if(pos+AUT_SCR<=i)
						for(int k=0;k<i-pos-AUT_SCR+1;k++)
							this->SendMessage(WM_VSCROLL,SB_LINEDOWN,0);
					else if(pos>i+AUT_SCR)
						for(int k=0;k<pos-i;k++)
							this->SendMessage(WM_VSCROLL,SB_LINEUP,0);
					if(c_dat->num_ways>2){
						pos=this->GetScrollPos(SB_HORZ);
						int lim=this->GetScrollLimit(SB_HORZ);
						
						if((c_dat->miss_step==2 || c_dat->set[i].way[v].acc==1) && (v==2 || v==3))
							for(int k=pos;k<lim;k++)
								this->SendMessage(WM_HSCROLL,SB_LINERIGHT,0);
						else if((c_dat->miss_step==2 || c_dat->set[i].way[v].acc==1) && (v==0 || v==1))
							for(int k=pos;k>0;k--)
								this->SendMessage(WM_HSCROLL,SB_LINELEFT,0);
					}
							
				}   //   col·loquem la scroll bar en la posició adequada
			
			
			if(c_dat->set[i].way[v].tag==NULL){
				this->SetItemText(i,1+(v*6),"0");
				this->SetItemText(i,3+(v*6),"");
				this->SetItemText(i,4+(v*6),"");
				if(c_dat->set[i].way[v].acc==0){
					this->SetItemText(i,5+(v*6),"miss");
					this->lastAcc=0;
					this->rowAcc=i;
				}
				else
					this->SetItemText(i,5+(v*6),"");
			}
			
			else{
				
					
				sprintf(frase,"%d",c_dat->set[i].way[v].valid);
				this->SetItemText(i,1+(v*6),frase);
				sprintf(frase,"%d",c_dat->set[i].way[v].counter);
				this->SetItemText(i,2+(v*6),frase);
				sprintf(frase,"%x",c_dat->set[i].way[v].tag);
				this->SetItemText(i,3+(v*6),frase);
				CString dada("");
				for(int k=0;k<(int)(c_dat->block_size/4);k++){   //mirem cada paraula del bloc
					sprintf(frase,"%x",c_dat->set[i].way[v].block[k]);
					CString dada1(frase);
					int l=dada1.GetLength();
					for(int j=0;j<8-l;j++)
					dada1="0"+dada1;
					dada=dada+dada1+"   ";
				}
				//dada="0x"+dada;
				this->SetItemText(i,4+(v*6),dada);
				
				if(c_dat->set[i].way[v].acc==-1)
					this->SetItemText(i,5+(v*6),"");
				else if(c_dat->set[i].way[v].acc==0){
					this->SetItemText(i,5+(v*6),"miss");
					this->lastAcc=0;
					this->rowAcc=i;
				}
				else{
					this->SetItemText(i,5+(v*6),"hit");
					this->lastAcc=1;
					this->rowAcc=i;
				}
			}
		}
	}
}

void cacheList::updateListMoreWaysBack(){
	for(int i=0;i<(int)c_dat->num_sets;i++){
		char frase[10];
		for(int v=0;v<(int)c_dat->num_ways;v++){
			
			if(c_dat->set[i].way[v].acc!=-1){
					int pos=this->GetScrollPos(SB_VERT);
					if(pos+AUT_SCR<=i)
						for(int k=0;k<i-pos-AUT_SCR+1;k++)
							this->SendMessage(WM_VSCROLL,SB_LINEDOWN,0);
					else if(pos>i+AUT_SCR)
						for(int k=0;k<pos-i;k++)
							this->SendMessage(WM_VSCROLL,SB_LINEUP,0);
					if(c_dat->num_ways>2){
						pos=this->GetScrollPos(SB_HORZ);
						int lim=this->GetScrollLimit(SB_HORZ);
						
						if((c_dat->miss_step==2 || c_dat->set[i].way[v].acc==1) && (v==2 || v==3))
							for(int k=pos;k<lim;k++)
								this->SendMessage(WM_HSCROLL,SB_LINERIGHT,0);
						else if((c_dat->miss_step==2 || c_dat->set[i].way[v].acc==1) && (v==0 || v==1))
							for(int k=pos;k>0;k--)
								this->SendMessage(WM_HSCROLL,SB_LINELEFT,0);
					}
				}   //   col·loquem la scroll bar en la posició adequada
			
			
			if(c_dat->set[i].way[v].tag==NULL){
				this->SetItemText(i,1+(v*7),"0");
				this->SetItemText(i,3+(v*7),"0");
				this->SetItemText(i,4+(v*7),"");
				this->SetItemText(i,5+(v*7),"");
				if(c_dat->set[i].way[v].acc==0){
					this->SetItemText(i,6+(v*7),"miss");
					this->lastAcc=0;
					this->rowAcc=i;
				}
				else
					this->SetItemText(i,6+(v*7),"");
			}
			else{
				

				sprintf(frase,"%d",c_dat->set[i].way[v].valid);
				this->SetItemText(i,1+(v*7),frase);
				sprintf(frase,"%d",c_dat->set[i].way[v].counter);
				this->SetItemText(i,2+(v*7),frase);
				sprintf(frase,"%d",c_dat->set[i].way[v].modified);
				this->SetItemText(i,3+(v*7),frase);
				sprintf(frase,"%x",c_dat->set[i].way[v].tag);
				this->SetItemText(i,4+(v*7),frase);
				CString dada("");
				for(int k=0;k<(int)(c_dat->block_size/4);k++){   //mirem cada paraula del bloc
					sprintf(frase,"%x",c_dat->set[i].way[v].block[k]);
					CString dada1(frase);
					int l=dada1.GetLength();
					for(int j=0;j<8-l;j++)
					dada1="0"+dada1;
					dada=dada+dada1+"   ";
				}
				//dada="0x"+dada;
				this->SetItemText(i,5+(v*7),dada);
				if(c_dat->set[i].way[v].acc==-1)
					this->SetItemText(i,6+(v*7),"");
				else if(c_dat->set[i].way[v].acc==0){
					this->SetItemText(i,6+(v*7),"miss");
					this->lastAcc=0;
					this->rowAcc=i;
				}
				else{
					this->SetItemText(i,6+(v*7),"hit");
					this->lastAcc=1;
					this->rowAcc=i;
				}
			}
		}
	}
}

void cacheList::updateListFullyNoBack(){
	for(int i=0;i<(int)c_dat->num_sets;i++){
		char frase[10];
		for(int v=0;v<(int)c_dat->num_ways;v++){
			
			if(c_dat->set[i].way[v].acc!=-1){
					int pos=this->GetScrollPos(SB_VERT);
					if(pos+AUT_SCR<=v)
						for(int k=0;k<v-pos;k++)
							this->SendMessage(WM_VSCROLL,SB_LINEDOWN,0);
					else if(pos>v+AUT_SCR)
						for(int k=0;k<pos-v+AUT_SCR-1;k++)
							this->SendMessage(WM_VSCROLL,SB_LINEUP,0);
				}   //   col·loquem la scroll bar en la posició adequada
			
			
			if(c_dat->set[i].way[v].tag==NULL){
				this->SetItemText(v,1,"0");
				this->SetItemText(v,3,"");
				this->SetItemText(v,4,"");
				if(c_dat->set[i].way[v].acc==0){
					this->SetItemText(v,5,"miss");
					this->lastAcc=0;
					this->rowAcc=v;
				}
				else
					this->SetItemText(v,5,"");
			}
			else{
				
				
				sprintf(frase,"%d",c_dat->set[i].way[v].valid);
				this->SetItemText(v,1,frase);
				sprintf(frase,"%d",c_dat->set[i].way[v].counter);
				this->SetItemText(v,2,frase);
				sprintf(frase,"%x",c_dat->set[i].way[v].tag);
				this->SetItemText(v,3,frase);
				CString dada("");
				for(int k=0;k<(int)(c_dat->block_size/4);k++){   //mirem cada paraula del bloc
					sprintf(frase,"%x",c_dat->set[i].way[v].block[k]);
					CString dada1(frase);
					int l=dada1.GetLength();
					for(int j=0;j<8-l;j++)
					dada1="0"+dada1;
					dada=dada+dada1+"   ";
				}
				//dada="0x"+dada;
				this->SetItemText(v,4,dada);
				
				if(c_dat->set[i].way[v].acc==-1)
					this->SetItemText(v,5,"");
				else if(c_dat->set[i].way[v].acc==0){
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

void cacheList::updateListFullyBack(){
	for(int i=0;i<(int)c_dat->num_sets;i++){
		char frase[10];
		for(int v=0;v<(int)c_dat->num_ways;v++){
			
			if(c_dat->set[i].way[v].acc!=-1){
					int pos=this->GetScrollPos(SB_VERT);
					if(pos+AUT_SCR<=v)
						for(int k=0;k<v-pos;k++)
							this->SendMessage(WM_VSCROLL,SB_LINEDOWN,0);
					else if(pos>v+AUT_SCR)
						for(int k=0;k<pos-v+AUT_SCR-1;k++)
							this->SendMessage(WM_VSCROLL,SB_LINEUP,0);
				}   //   col·loquem la scroll bar en la posició adequada
			
			
			if(c_dat->set[i].way[v].tag==NULL){
				this->SetItemText(v,1,"0");
				this->SetItemText(v,3,"0");
				this->SetItemText(v,4,"");
				this->SetItemText(v,5,"");
				if(c_dat->set[i].way[v].acc==0){
					this->SetItemText(v,6,"miss");
					this->lastAcc=0;
					this->rowAcc=v;
				}
				else
					this->SetItemText(v,6,"");
			}
			else{
				

				sprintf(frase,"%d",c_dat->set[i].way[v].valid);
				this->SetItemText(v,1,frase);
				sprintf(frase,"%d",c_dat->set[i].way[v].counter);
				this->SetItemText(v,2,frase);
				sprintf(frase,"%d",c_dat->set[i].way[v].modified);
				this->SetItemText(v,3,frase);
				sprintf(frase,"%x",c_dat->set[i].way[v].tag);
				this->SetItemText(v,4,frase);
				CString dada("");
				for(int k=0;k<(int)(c_dat->block_size/4);k++){   //mirem cada paraula del bloc
					sprintf(frase,"%x",c_dat->set[i].way[v].block[k]);
					CString dada1(frase);
					int l=dada1.GetLength();
					for(int j=0;j<8-l;j++)
					dada1="0"+dada1;
					dada=dada+dada1+"   ";
				}
				//dada="0x"+dada;
				this->SetItemText(v,5,dada);
				if(c_dat->set[i].way[v].acc==-1)
					this->SetItemText(v,6,"");
				else if(c_dat->set[i].way[v].acc==0){
					this->SetItemText(v,6,"miss");
					this->lastAcc=0;
					this->rowAcc=v;
				}
				else{
					this->SetItemText(v,6,"hit");
					this->lastAcc=1;
					this->rowAcc=v;
				}
			}
		}
	}
}


BEGIN_MESSAGE_MAP(cacheList, CListCtrl)
	//{{AFX_MSG_MAP(cacheList)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW,OnCustomDraw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// cacheList message handlers

int cacheList::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	this->num_columns=0;
	this->SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	
	
	//fonteta.CreateFont(7,6,0,0,0,0,0,0,0,0,0,0,0,0);
	//this->SetFont(&fonteta,TRUE);
	return 0;
}

void cacheList::OnSize(UINT nType, int cx, int cy) 
{
	CListCtrl::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	/*if(nType==SIZE_MAXIMIZED){
		RECT r;
		this->GetClientRect(&r);
		r.right-=50;
		this->SetColumnWidth(0,30);
		this->SetColumnWidth(1,20);
		this->SetColumnWidth(2,(int)(cx*.2));
		this->SetColumnWidth(3,(int)(cx*.7));
		this->SetColumnWidth(4,(int)(cx*.1));
		this->fitColumns(3);
	}*/
}

void cacheList::OnCustomDraw(NMHDR *pNMHDR,LRESULT *pResult){
	
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



