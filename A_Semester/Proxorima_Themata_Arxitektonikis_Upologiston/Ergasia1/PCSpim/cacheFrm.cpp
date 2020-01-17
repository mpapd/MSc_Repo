// cacheFrm.cpp : implementation file
//

#include "stdafx.h"
#include "PCSpim.h"
#include "cacheFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// cacheFrm

//IMPLEMENT_DYNCREATE(cacheFrm, CFrameWnd)

cacheFrm::cacheFrm()
{
	int i,ancho;
	char algo[5],info_cache[38];
	RECT mainr;
	mainr.top=mainr.left=0;
	mainr.bottom=495;
	(c_dat->num_ways>1 && !c_dat->fully_associ)?mainr.right=938:mainr.right=600;
	if(c_dat->num_ways==1)
		sprintf(info_cache,"Cache Window: %d B, %d Way, %d B",c_dat->cache_size,c_dat->num_ways,c_dat->block_size);
	else
		sprintf(info_cache,"Cache Window: %d B, %d Ways, %d B",c_dat->cache_size,c_dat->num_ways,c_dat->block_size);
	Create(NULL,info_cache,WS_CAPTION|WS_HSCROLL,mainr);
	RECT r,info;
	info.top=5;//mainr.bottom-30;
	info.bottom=20;
	info.left=20;
	info.right=mainr.right-30;
	
	text_cache.Create("",SS_LEFT,info,this);
	text_cache.ShowWindow(SW_SHOW);
	if(show_rate)
		text_cache.SetWindowText("Accesses:0   Hits:0   Hit Rate:0.000000   Compulsory:0   Conflict:0   Capacity:0");
	
	this->GetClientRect(&r);
	r.top=r.top+30;
	if(c_dat->num_ways>1 && !c_dat->fully_associ)
		r.right/=2;
	ancho=r.right;
	//r.bottom=r.bottom-46;
	
	if(c_dat->num_ways==1){   //només una via 
		if(c_dat->wr_policy.hit_policy!=1){   //no es escriptura posterior
			
			//for(i=0;i<(int)c_dat->num_ways;i++){
				int j;
				clistctrl.Create(LVS_REPORT|WS_BORDER,r,this,1);
				clistctrl.ShowWindow(SW_SHOW);
				clistctrl.InsertColumn(0,"Set");  
				clistctrl.InsertColumn(1,"V");
				clistctrl.InsertColumn(2,"Tag (h)");
				clistctrl.InsertColumn(3,"Data (h)");
				clistctrl.InsertColumn(4,"Acc");
				//clistctrl[i].GetClientRect(&r);
				clistctrl.SetColumnWidth(0,40);
				clistctrl.SetColumnWidth(1,25);
				clistctrl.SetColumnWidth(2,50);
				clistctrl.SetColumnWidth(3,(ancho-165));
				clistctrl.SetColumnWidth(4,33);
				for(j=0;j<(int)c_dat->num_sets;j++){
					char frase[5];
					sprintf(frase,"%d",j);
					clistctrl.InsertItem(j,"");
					clistctrl.SetItemText(j,0,frase);
					clistctrl.SetItemText(j,1,"0");
				}
				r.left=r.right;
				r.right=r.right+ancho;
				clistctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
				CHeaderCtrl *col=clistctrl.GetHeaderCtrl();
				col->BeginModalState();   //per fixar les columnes
		//	}
		}
		else{   //escriptura posterior
			
			//for(i=0;i<(int)c_dat->num_ways;i++){
				int j;
				clistctrl.Create(LVS_REPORT|WS_BORDER,r,this,1);
				clistctrl.ShowWindow(SW_SHOW);
				clistctrl.InsertColumn(0,"Set");
				clistctrl.InsertColumn(1,"V");
				clistctrl.InsertColumn(2,"M");
				clistctrl.InsertColumn(3,"Tag (h)");
				clistctrl.InsertColumn(4,"Data (h)");
				clistctrl.InsertColumn(5,"Acc");
				//clistctrl[i].GetClientRect(&r);
				clistctrl.SetColumnWidth(0,40);
				clistctrl.SetColumnWidth(1,25);
				clistctrl.SetColumnWidth(2,25);
				clistctrl.SetColumnWidth(3,60);
				clistctrl.SetColumnWidth(4,(ancho-200));
				clistctrl.SetColumnWidth(5,33);
				for(j=0;j<(int)c_dat->num_sets;j++){
					char frase[5];
					sprintf(frase,"%d",j);
					clistctrl.InsertItem(j,"");
					clistctrl.SetItemText(j,0,frase);
					clistctrl.SetItemText(j,1,"0");
					clistctrl.SetItemText(j,2,"0");
				}
				r.left=r.right;
				r.right=r.right+ancho;
				clistctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
				CHeaderCtrl *col=clistctrl.GetHeaderCtrl();
				col->BeginModalState();   //per fixar les columnes
		//	}
		}
		this->SetScrollRange(SB_HORZ,0,r.right-(2*ancho));
	}
	else if(c_dat->num_ways>1 && !c_dat->fully_associ){   //més d'una via pero no totalment associativa
		c_dat->algorithm?sprintf(algo,"FIFO"):sprintf(algo,"LRU");
		r.right*=2;//(r.right*c_dat->num_vies)-(48*(c_dat->num_vies/4));//amb més de dos vies, sobra rectangle
		int ancho2=(ancho*2);//+63*(c_dat->num_vies/4);
		if(c_dat->wr_policy.hit_policy!=1){   //no es escriptura posterior
			//for(i=0;i<(int)c_dat->num_vies/2;i++){
				int j;
				
				clistctrl.Create(LVS_REPORT|WS_BORDER,r,this,1);
				clistctrl.ShowWindow(SW_SHOW);
				clistctrl.InsertColumn(0,"Set");
				clistctrl.SetColumnWidth(0,40);
				for(j=0;j<(int)c_dat->num_ways;j++){
					char numv[25];
					sprintf(numv,"Data (h)   Way %d",j);
					clistctrl.InsertColumn(1+(j*6),"V");
					clistctrl.InsertColumn(2+(j*6),algo);
					//clistctrl[0].InsertColumn(2+(j*6),"R");
					clistctrl.InsertColumn(3+(j*6),"Tag (h)");
					clistctrl.InsertColumn(4+(j*6),numv);
					clistctrl.InsertColumn(5+(j*6),"Acc");
				//clistctrl[i].GetClientRect(&r);
					if(j!=(int)c_dat->num_ways-1){
						clistctrl.InsertColumn(6+(j*6),"");
						clistctrl.SetColumnWidth(6+(j*6),10);
					}
						
				
					clistctrl.SetColumnWidth(1+(j*6),25);
					clistctrl.SetColumnWidth(2+(j*6),40);
					//clistctrl[0].SetColumnWidth(2+(j*6),25);
					clistctrl.SetColumnWidth(3+(j*6),60);
					//if(c_dat->tamany_bloc==4 && c_dat->num_vies>2)
						//clistctrl[0].SetColumnWidth(4+(j*6),(ancho-192));
						//clistctrl[0].SetColumnWidth(4+(j*6),80);   //per a veure 4 vies sense scroll amb una paraula
					//else
					clistctrl.SetColumnWidth(4+(j*6),(ancho-192));
					clistctrl.SetColumnWidth(5+(j*6),33);
					
				}
				for(i=0;i<(int)c_dat->num_sets;i++){
					char frase[5];
					sprintf(frase,"%d",i);
					clistctrl.InsertItem(i,"");
					clistctrl.SetItemText(i,0,frase);
					for(j=0;j<(int)c_dat->num_ways;j++){
						clistctrl.SetItemText(i,1+(j*6),"0");
						clistctrl.SetItemText(i,2+(j*6),"0");
					}
						//clistctrl[i].SetItemText(j,6,"|");
						//clistctrl[0].SetItemText(i,1+(j*6),"0");
					}
				
				
				//r.left=r.right;
				//r.right=r.right+ancho2;
				clistctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
				CHeaderCtrl *col=clistctrl.GetHeaderCtrl();
				col->BeginModalState();   //per fixar les columnes
			//}
		}
		else{   //escriptura posterior
			//for(i=0;i<(int)c_dat->num_vies/2;i++){
				int j;
				
				clistctrl.Create(LVS_REPORT|WS_BORDER,r,this,1);
				clistctrl.ShowWindow(SW_SHOW);
				clistctrl.InsertColumn(0,"Set");
				clistctrl.SetColumnWidth(0,40);
				for(j=0;j<(int)c_dat->num_ways;j++){
					char numv[25];
					sprintf(numv,"Data (h)   Way %d",j);
					clistctrl.InsertColumn(1+(j*7),"V");
					clistctrl.InsertColumn(2+(j*7),algo);
					//clistctrl[0].InsertColumn(2+(j*7),"R");
					clistctrl.InsertColumn(3+(j*7),"M");
					clistctrl.InsertColumn(4+(j*7),"Tag (h)");
					clistctrl.InsertColumn(5+(j*7),numv);
					clistctrl.InsertColumn(6+(j*7),"Acc");
				//clistctrl[i].GetClientRect(&r);
					if(j!=(int)c_dat->num_ways-1){
						clistctrl.InsertColumn(7+(j*7),"");
						clistctrl.SetColumnWidth(7+(j*7),10);
					}
				
					clistctrl.SetColumnWidth(1+(j*7),25);
					clistctrl.SetColumnWidth(2+(j*7),40);
					//clistctrl[0].SetColumnWidth(2+(j*7),25);
					clistctrl.SetColumnWidth(3+(j*7),25);
					clistctrl.SetColumnWidth(4+(j*7),60);
					//if(c_dat->tamany_bloc==4 && c_dat->num_vies>2)
						//clistctrl[0].SetColumnWidth(5+(j*7),(ancho-202));
						//clistctrl[0].SetColumnWidth(5+(j*7),80);
					//else
					clistctrl.SetColumnWidth(5+(j*7),(ancho-217));
					clistctrl.SetColumnWidth(6+(j*7),33);
					
				}
				for(i=0;i<(int)c_dat->num_sets;i++){
					char frase[5];
					sprintf(frase,"%d",i);
					clistctrl.InsertItem(i,"");
					clistctrl.SetItemText(i,0,frase);
					for(j=0;j<(int)c_dat->num_ways;j++){
						clistctrl.SetItemText(i,1+(7*j),"0");
						//clistctrl[i].SetItemText(j,1+7,"0");
						clistctrl.SetItemText(i,2+(7*j),"0");
						//clistctrl[i].SetItemText(j,2+7,"0");
						clistctrl.SetItemText(i,3+(7*j),"0");
					}
				}
				
				//r.left=r.right;
				//r.right=r.right+ancho2;
				clistctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
				CHeaderCtrl *col=clistctrl.GetHeaderCtrl();
				col->BeginModalState();   //per fixar les columnes
			//}
		}
		this->SetScrollRange(SB_HORZ,0,r.right-ancho2);//-2*ancho2);//-(3*ancho));
	}

	else{   //totalment associativa
		c_dat->algorithm?sprintf(algo,"FIFO"):sprintf(algo,"LRU");
		if(c_dat->wr_policy.hit_policy!=1){   //no es escriptura posterior
			
			//for(i=0;i<(int)c_dat->num_sets;i++){
				int j;
				clistctrl.Create(LVS_REPORT|WS_BORDER,r,this,1);
				clistctrl.ShowWindow(SW_SHOW);
				clistctrl.InsertColumn(0,"Way");  
				clistctrl.InsertColumn(1,"V");
				clistctrl.InsertColumn(2,algo);
				clistctrl.InsertColumn(3,"Tag (h)");
				clistctrl.InsertColumn(4,"Data (h)");
				clistctrl.InsertColumn(5,"Acc");
				//clistctrl[i].GetClientRect(&r);
				clistctrl.SetColumnWidth(0,40);
				clistctrl.SetColumnWidth(1,25);
				clistctrl.SetColumnWidth(2,40);
				clistctrl.SetColumnWidth(3,80);
				clistctrl.SetColumnWidth(4,(ancho-235));
				clistctrl.SetColumnWidth(5,33);
				for(j=0;j<(int)c_dat->num_ways;j++){
					char frase[5];
					sprintf(frase,"%d",j);
					clistctrl.InsertItem(j,"");
					clistctrl.SetItemText(j,0,frase);
					clistctrl.SetItemText(j,1,"0");
					clistctrl.SetItemText(j,2,"0");
				}
				r.left=r.right;
				r.right=r.right+ancho;
				clistctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
				CHeaderCtrl *col=clistctrl.GetHeaderCtrl();
				col->BeginModalState();   //per fixar les columnes
			//}
		}
		else{   //escriptura posterior
			
			//for(i=0;i<(int)c_dat->num_sets;i++){
				int j;
				clistctrl.Create(LVS_REPORT|WS_BORDER,r,this,1);
				clistctrl.ShowWindow(SW_SHOW);
				clistctrl.InsertColumn(0,"Way");
				clistctrl.InsertColumn(1,"V");
				clistctrl.InsertColumn(2,algo);
				clistctrl.InsertColumn(3,"M");
				clistctrl.InsertColumn(4,"Tag (h)");
				clistctrl.InsertColumn(5,"Data (h)");
				clistctrl.InsertColumn(6,"Acc");
				//clistctrl[i].GetClientRect(&r);
				clistctrl.SetColumnWidth(0,40);
				clistctrl.SetColumnWidth(1,25);
				clistctrl.SetColumnWidth(2,40);
				clistctrl.SetColumnWidth(3,25);
				clistctrl.SetColumnWidth(4,80);
				clistctrl.SetColumnWidth(5,(ancho-260));
				clistctrl.SetColumnWidth(6,33);
				for(j=0;j<(int)c_dat->num_ways;j++){
					char frase[5];
					sprintf(frase,"%d",j);
					clistctrl.InsertItem(j,"");
					clistctrl.SetItemText(j,0,frase);
					clistctrl.SetItemText(j,1,"0");
					clistctrl.SetItemText(j,2,"0");
					clistctrl.SetItemText(j,3,"0");
				}
				r.left=r.right;
				r.right=r.right+ancho;
				clistctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
				CHeaderCtrl *col=clistctrl.GetHeaderCtrl();
				col->BeginModalState();   //per fixar les columnes
			//}
		}
		this->SetScrollRange(SB_HORZ,0,r.right-(2*ancho));
	}

	
	
	/*if(c_dat->num_vies>1)
		this->SetScrollRange(SB_HORZ,0,r.right-(3*ancho));
	else
		this->SetScrollRange(SB_HORZ,0,r.right-(2*ancho));*/
}

cacheFrm::~cacheFrm()
{
}

void cacheFrm::updateOneWayNoBack(){
	for(int i=0;i<(int)c_dat->num_sets;i++){
		char frase[10];
		for(int v=0;v<(int)c_dat->num_ways;v++){

			if(c_dat->set[i].way[v].acc!=-1){
				int pos=this->clistctrl.GetScrollPos(SB_VERT);
				if(pos+25<i)
					for(int k=0;k<i-pos;k++)
						this->clistctrl.SendMessage(WM_VSCROLL,SB_LINEDOWN,0);
				else if(pos>i+25)
					for(int k=0;k<pos-i;k++)
						this->clistctrl.SendMessage(WM_VSCROLL,SB_LINEUP,0);
			}   //   col·loquem la scroll bar en la posició adequada

						
			if(c_dat->set[i].way[v].tag==NULL){
				this->clistctrl.SetItemText(i,1,"0");
				this->clistctrl.SetItemText(i,2,"");
				this->clistctrl.SetItemText(i,3,"");
				if(c_dat->set[i].way[v].acc==0)
					this->clistctrl.SetItemText(i,4,"miss");
				else
					this->clistctrl.SetItemText(i,4,"");
			}
			else{
						
				
				sprintf(frase,"%d",c_dat->set[i].way[v].valid);
				this->clistctrl.SetItemText(i,1,frase);
				sprintf(frase,"%x",c_dat->set[i].way[v].tag);
				this->clistctrl.SetItemText(i,2,frase);
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
				this->clistctrl.SetItemText(i,3,dada);
				
				if(c_dat->set[i].way[v].acc==-1)
					this->clistctrl.SetItemText(i,4,"");
				else if(c_dat->set[i].way[v].acc==0)
					this->clistctrl.SetItemText(i,4,"miss");
				else
					this->clistctrl.SetItemText(i,4,"hit");
			}
		}
	}
}
void cacheFrm::updateOneWayBack(){
	for(int i=0;i<(int)c_dat->num_sets;i++){
		char frase[10];
		for(int v=0;v<(int)c_dat->num_ways;v++){
			
			if(c_dat->set[i].way[v].tag==NULL){
				this->clistctrl.SetItemText(i,1,"0");
				this->clistctrl.SetItemText(i,2,"0");
				this->clistctrl.SetItemText(i,3,"");
				this->clistctrl.SetItemText(i,4,"");
				if(c_dat->set[i].way[v].acc==0)
					this->clistctrl.SetItemText(i,5,"miss");
				else
					this->clistctrl.SetItemText(i,5,"");
			}
			else{
				if(c_dat->set[i].way[v].acc!=-1){
					int pos=this->clistctrl.GetScrollPos(SB_VERT);
					if(pos+25<i)
						for(int k=0;k<i-pos;k++)
							this->clistctrl.SendMessage(WM_VSCROLL,SB_LINEDOWN,0);
					else if(pos>i+25)
						for(int k=0;k<pos-i;k++)
							this->clistctrl.SendMessage(WM_VSCROLL,SB_LINEUP,0);
				}   //   col·loquem la scroll bar en la posició adequada

				sprintf(frase,"%d",c_dat->set[i].way[v].valid);
				this->clistctrl.SetItemText(i,1,frase);
				sprintf(frase,"%d",c_dat->set[i].way[v].modified);
				this->clistctrl.SetItemText(i,2,frase);
				sprintf(frase,"%x",c_dat->set[i].way[v].tag);
				this->clistctrl.SetItemText(i,3,frase);
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
				this->clistctrl.SetItemText(i,4,dada);
				if(c_dat->set[i].way[v].acc==-1)
					this->clistctrl.SetItemText(i,5,"");
				else if(c_dat->set[i].way[v].acc==0)
					this->clistctrl.SetItemText(i,5,"miss");
				else
					this->clistctrl.SetItemText(i,5,"hit");
			}
		}
	}
}
void cacheFrm::updateMoreWaysNoBack(){
	for(int i=0;i<(int)c_dat->num_sets;i++){
		char frase[10];
		for(int v=0;v<(int)c_dat->num_ways;v++){
				
			if(c_dat->set[i].way[v].tag==NULL){
				this->clistctrl.SetItemText(i,1+(v*6),"0");
				this->clistctrl.SetItemText(i,3+(v*6),"");
				this->clistctrl.SetItemText(i,4+(v*6),"");
				if(c_dat->set[i].way[v].acc==0)
					this->clistctrl.SetItemText(i,5+(v*6),"miss");
				else
					this->clistctrl.SetItemText(i,5+(v*6),"");
			}
			
			else{
				if(c_dat->set[i].way[v].acc!=-1){
					int pos=this->clistctrl.GetScrollPos(SB_VERT);
					
					if(pos+25<i)
						for(int k=0;k<i-pos;k++)
							this->clistctrl.SendMessage(WM_VSCROLL,SB_LINEDOWN,0);
					else if(pos>i+25)
						for(int k=0;k<pos-i;k++)
							this->clistctrl.SendMessage(WM_VSCROLL,SB_LINEUP,0);
							
				}   //   col·loquem la scroll bar en la posició adequada
					
				sprintf(frase,"%d",c_dat->set[i].way[v].valid);
				this->clistctrl.SetItemText(i,1+(v*6),frase);
				sprintf(frase,"%d",c_dat->set[i].way[v].counter);
				this->clistctrl.SetItemText(i,2+(v*6),frase);
				sprintf(frase,"%x",c_dat->set[i].way[v].tag);
				this->clistctrl.SetItemText(i,3+(v*6),frase);
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
				this->clistctrl.SetItemText(i,4+(v*6),dada);
				
				if(c_dat->set[i].way[v].acc==-1)
					this->clistctrl.SetItemText(i,5+(v*6),"");
				else if(c_dat->set[i].way[v].acc==0)
					this->clistctrl.SetItemText(i,5+(v*6),"miss");
				else
					this->clistctrl.SetItemText(i,5+(v*6),"hit");
			}
		}
	}
}
void cacheFrm::updateMoreWaysBack(){
	for(int i=0;i<(int)c_dat->num_sets;i++){
		char frase[10];
		for(int v=0;v<(int)c_dat->num_ways;v++){
			
			if(c_dat->set[i].way[v].tag==NULL){
				this->clistctrl.SetItemText(i,1+(v*7),"0");
				this->clistctrl.SetItemText(i,3+(v*7),"0");
				this->clistctrl.SetItemText(i,4+(v*7),"");
				this->clistctrl.SetItemText(i,5+(v*7),"");
				if(c_dat->set[i].way[v].acc==0)
					this->clistctrl.SetItemText(i,6+(v*7),"miss");
				else
					this->clistctrl.SetItemText(i,6+(v*7),"");
			}
			else{
				if(c_dat->set[i].way[v].acc!=-1){
					int pos=this->clistctrl.GetScrollPos(SB_VERT);
					if(pos+25<i)
						for(int k=0;k<i-pos;k++)
							this->clistctrl.SendMessage(WM_VSCROLL,SB_LINEDOWN,0);
					else if(pos>i+25)
						for(int k=0;k<pos-i;k++)
							this->clistctrl.SendMessage(WM_VSCROLL,SB_LINEUP,0);
				}   //   col·loquem la scroll bar en la posició adequada

				sprintf(frase,"%d",c_dat->set[i].way[v].valid);
				this->clistctrl.SetItemText(i,1+(v*7),frase);
				sprintf(frase,"%d",c_dat->set[i].way[v].counter);
				this->clistctrl.SetItemText(i,2+(v*7),frase);
				sprintf(frase,"%d",c_dat->set[i].way[v].modified);
				this->clistctrl.SetItemText(i,3+(v*7),frase);
				sprintf(frase,"%x",c_dat->set[i].way[v].tag);
				this->clistctrl.SetItemText(i,4+(v*7),frase);
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
				this->clistctrl.SetItemText(i,5+(v*7),dada);
				if(c_dat->set[i].way[v].acc==-1)
					this->clistctrl.SetItemText(i,6+(v*7),"");
				else if(c_dat->set[i].way[v].acc==0)
					this->clistctrl.SetItemText(i,6+(v*7),"miss");
				else
					this->clistctrl.SetItemText(i,6+(v*7),"hit");
			}
		}
	}
}
void cacheFrm::updateFullyNoBack(){
	for(int i=0;i<(int)c_dat->num_sets;i++){
		char frase[10];
		for(int v=0;v<(int)c_dat->num_ways;v++){
			
			
			if(c_dat->set[i].way[v].tag==NULL){
				this->clistctrl.SetItemText(v,1,"0");
				this->clistctrl.SetItemText(v,3,"");
				this->clistctrl.SetItemText(v,4,"");
				if(c_dat->set[i].way[v].acc==0)
					this->clistctrl.SetItemText(v,5,"miss");
				else
					this->clistctrl.SetItemText(v,5,"");
			}
			else{
				
				if(c_dat->set[i].way[v].acc!=-1){
					int pos=this->clistctrl.GetScrollPos(SB_VERT);
					if(pos+25<v)
						for(int k=0;k<v-pos;k++)
							this->clistctrl.SendMessage(WM_VSCROLL,SB_LINEDOWN,0);
					else if(pos>v+25)
						for(int k=0;k<pos-v;k++)
							this->clistctrl.SendMessage(WM_VSCROLL,SB_LINEUP,0);
				}   //   col·loquem la scroll bar en la posició adequada

				sprintf(frase,"%d",c_dat->set[i].way[v].valid);
				this->clistctrl.SetItemText(v,1,frase);
				sprintf(frase,"%d",c_dat->set[i].way[v].counter);
				this->clistctrl.SetItemText(v,2,frase);
				sprintf(frase,"%x",c_dat->set[i].way[v].tag);
				this->clistctrl.SetItemText(v,3,frase);
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
				this->clistctrl.SetItemText(v,4,dada);
				
				if(c_dat->set[i].way[v].acc==-1)
					this->clistctrl.SetItemText(v,5,"");
				else if(c_dat->set[i].way[v].acc==0)
					this->clistctrl.SetItemText(v,5,"miss");
				else
					this->clistctrl.SetItemText(v,5,"hit");
			}
		}
	}
}
void cacheFrm::updateFullyBack(){
	for(int i=0;i<(int)c_dat->num_sets;i++){
		char frase[10];
		for(int v=0;v<(int)c_dat->num_ways;v++){
			
			if(c_dat->set[i].way[v].tag==NULL){
				this->clistctrl.SetItemText(v,1,"0");
				this->clistctrl.SetItemText(v,3,"0");
				this->clistctrl.SetItemText(v,4,"");
				this->clistctrl.SetItemText(v,5,"");
				if(c_dat->set[i].way[v].acc==0)
					this->clistctrl.SetItemText(v,6,"miss");
				else
					this->clistctrl.SetItemText(v,6,"");
			}
			else{
				if(c_dat->set[i].way[v].acc!=-1){
					int pos=this->clistctrl.GetScrollPos(SB_VERT);
					if(pos+25<v)
						for(int k=0;k<v-pos;k++)
							this->clistctrl.SendMessage(WM_VSCROLL,SB_LINEDOWN,0);
					else if(pos>v+25)
						for(int k=0;k<pos-v;k++)
							this->clistctrl.SendMessage(WM_VSCROLL,SB_LINEUP,0);
				}   //   col·loquem la scroll bar en la posició adequada

				sprintf(frase,"%d",c_dat->set[i].way[v].valid);
				this->clistctrl.SetItemText(v,1,frase);
				sprintf(frase,"%d",c_dat->set[i].way[v].counter);
				this->clistctrl.SetItemText(v,2,frase);
				sprintf(frase,"%d",c_dat->set[i].way[v].modified);
				this->clistctrl.SetItemText(v,3,frase);
				sprintf(frase,"%x",c_dat->set[i].way[v].tag);
				this->clistctrl.SetItemText(v,4,frase);
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
				this->clistctrl.SetItemText(v,5,dada);
				if(c_dat->set[i].way[v].acc==-1)
					this->clistctrl.SetItemText(v,6,"");
				else if(c_dat->set[i].way[v].acc==0)
					this->clistctrl.SetItemText(v,6,"miss");
				else
					this->clistctrl.SetItemText(v,6,"hit");
			}
		}
	}
}

void cacheFrm::updateStatistics(){
	char frase2[100];
	double taxa=0.0;
	double acce=1.0*c_dat->statistics.accesses;
	double ence=1.0*c_dat->statistics.hits;
	if(c_dat->statistics.accesses && c_dat->statistics.hits)
		taxa=ence/acce;
	sprintf(frase2,"Accesses:%d   Hits:%d   Hit Rate:%f   Compulsory:%d   Conflict:%d   Capacity:%d",c_dat->statistics.accesses,c_dat->statistics.hits,taxa,c_dat->statistics.compulsory,c_dat->statistics.conflict,c_dat->statistics.capacity);
	if(c_dat->statistics.show)
		this->text_cache.SetWindowText(frase2);
}

BEGIN_MESSAGE_MAP(cacheFrm, CFrameWnd)
	//{{AFX_MSG_MAP(cacheFrm)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// cacheFrm message handlers

void cacheFrm::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	static int pos=0;
	int max,min;
	//char frase[10];
	//RECT r;
	//this->GetClientRect(&r);
	this->GetScrollRange(SB_HORZ,&min,&max);
	//sprintf(frase,"%d   %d",min,max);
	//MessageBox(frase);
	
	
	if(nSBCode==SB_LINEDOWN || nSBCode==SB_PAGEDOWN){
		if(!(pos>=max)){
			pos+=1;
			this->ScrollWindow(-1,0);
			this->SetScrollPos(SB_HORZ,pos);
		}
		
	}
	else if(nSBCode==SB_LINEUP || nSBCode==SB_PAGEUP){
		if(!(pos<=min)){
			pos-=1;
			this->ScrollWindow(1,0);
			this->SetScrollPos(SB_HORZ,pos);
		}
		
	}
	else if(nSBCode==SB_THUMBPOSITION || nSBCode==SB_THUMBTRACK){
		if(nPos<=3032 || nPos>=0){
			this->ScrollWindow((pos-nPos),0);
			this->SetScrollPos(SB_HORZ,nPos);
			pos=nPos;
		}
	}
	
	CFrameWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL cacheFrm::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	LPNMLISTVIEW nmlv=(LPNMLISTVIEW) lParam;
	if(nmlv->hdr.code==NM_RCLICK){
		if(nmlv->iItem==-1){
			if(c_dat->num_ways==1){
				if(c_dat->wr_policy.hit_policy!=1)
					MessageBox("V:Valid Bit\nTag:Tag for the Block in hex\nData:Data stored in the Cache\nAcc:Indicates last access to the Cache (hit/miss)","INFO");
				else
					MessageBox("V:Valid Bit\nM:Modified Bit\nTag:Tag for the Block in hex\nData:Data stored in the Cache\nAcc:Indicates last access to the Cache (hit/miss)","INFO");
			}
			else if(c_dat->num_ways>1 && !c_dat->fully_associ){
				if(c_dat->wr_policy.hit_policy!=1)
					MessageBox("V:Valid Bit\nR:Counter for the Replacement algorithm (FIFO/LRU)\nTag:Tag for the Block in hex\nData:Data stored in the Cache\nAcc:Indicates last access to the Cache (hit/miss)","INFO");
				else
					MessageBox("V:Valid Bit\nR:Counter for the Replacement algorithm (FIFO/LRU)\nM:Modified Bit\nTag:Tag for the Block in hex\nData:Data stored in the Cache\nAcc:Indicates last access to the Cache (hit/miss)","INFO");
			}
			else{
				if(c_dat->wr_policy.hit_policy!=1)
					MessageBox("Way:Number of Way in the single Set\nV:Valid Bit\nR:Counter for the Replacement algorithm (FIFO/LRU)\nTag:Tag for the Block in hex\nData:Data stored in the Cache\nAcc:Indicates last access to the Cache (hit/miss)","INFO");
				else
					MessageBox("Way:Number of Way in the single Set\nV:Valid Bit\nR:Counter for the Replacement algorithm (FIFO/LRU)\nM:Modified Bit\nTag:Tag for the Block in hex\nData:Data stored in the Cache\nAcc:Indicates last access to the Cache (hit/miss)","INFO");
			}

		}
		else{
			unsigned int eti,conju,w;
			if(!c_dat->fully_associ){
				//c_dat->politica_wr==2?eti=c_dat->conjunt[nmlv->iItem].via[nmlv->iSubItem/7].etiqueta:eti=c_dat->conjunt[nmlv->iItem].via[nmlv->iSubItem/6].etiqueta;
				c_dat->wr_policy.hit_policy==1?w=nmlv->iSubItem/7:w=nmlv->iSubItem/6;
				conju=nmlv->iItem;
				eti=c_dat->set[conju].way[w].tag;
			}
			else{
				w=nmlv->iItem;
				conju=0;
				eti=c_dat->set[conju].way[w].tag;
			}
			if(c_dat->set[conju].way[w].valid){	
				unsigned int dir=rebuild_addr_base(c_dat,conju,eti);
				char resultado[38];
				sprintf(resultado,"Block Base Address\n   0x%x",dir);
				MessageBox(resultado);
			}
			else
				MessageBox("Empty Address");
		}
		return 0;
	}
	else
		return CFrameWnd::OnNotify(wParam, lParam, pResult);
}
