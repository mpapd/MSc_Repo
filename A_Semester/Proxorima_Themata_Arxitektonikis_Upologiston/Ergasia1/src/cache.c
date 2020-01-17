// cache.c: implementation of the cache class.
//
//////////////////////////////////////////////////////////////////////

#include "spim.h"
#include "string-stream.h"
#include "spim-utils.h"
#include "inst.h"
#include "reg.h"
#include "mem.h"
#include "cache.h"
#include <math.h>


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cache * initialize_cache(cache *c,unsigned int bytes_cache,unsigned int bytes_bloc,unsigned int n_vies,unsigned int m_algorithm,int inst)
{
	int i,j;
	unsigned int C_size;
	
	c=(cache *)malloc(sizeof(cache));
	c->cache_size=bytes_cache;
	c->block_size=bytes_bloc;
	c->num_ways=n_vies;
	
	c->num_sets=calculate_sets(bytes_cache,bytes_bloc,n_vies);
	
	//initialize the cache structs
	c->set=(struct cache_set *)malloc(c->num_sets*sizeof(struct cache_set));
	for(i=0;i<(int)c->num_sets;i++)
		c->set[i].way=(struct cache_way *)malloc(c->num_ways*sizeof(struct cache_way));
	for(i=0;i<(int)c->num_sets;i++){
		for(j=0;j<(int)c->num_ways;j++){
			c->set[i].way[j].block=(int *)malloc((c->block_size/4)*sizeof(int));
		}
	}
	c->full=c->num_sets*c->num_ways;   //initialize to total num_ways in cache
	for(i=0;i<(int)c->num_sets;i++){
		c->set[i].full_s=c->num_ways;   //initialize to num_ways; when full=0 -> full set
		for(j=0;j<(int)c->num_ways;j++){
			c->set[i].way[j].acc=-1;
			c->set[i].way[j].valid=0;
			c->set[i].way[j].modified=0;
			c->set[i].way[j].tag=NULL;
			c->set[i].way[j].block[0]=NULL;
		}
	}
	if(c->num_sets==1)
		c->fully_associ=1;   //it is fully associative
	else
		c->fully_associ=0;   //it isn't

	c->instruction=inst;   //inst cache
		
	c->addr_fields.block_bits=calculate_block_bits(bytes_bloc);
	c->addr_fields.set_bits=calculate_bits(c->num_sets);
	c->addr_fields.tag_bits=32-(c->addr_fields.block_bits+c->addr_fields.set_bits);
	if(!inst){
		c->wr_policy.hit_policy=cache_wrHit;
		c->wr_policy.miss_policy=cache_wrMiss;
	}
	else{
		c->wr_policy.hit_policy=0;
		c->wr_policy.miss_policy=0;
	}

	c->algorithm=m_algorithm;
	c->acces=0;
	c->miss_step=0;
	c->postmiss_way=-1;
	c->statistics.accesses=0;
	c->statistics.hits=0;
	if(!inst)
		c->statistics.show=show_rate;
	else
		c->statistics.show=show_rateI;
	C_size=8192/(c->block_size/4);
	c->statistics.three_Cs=(unsigned int *)malloc(C_size*sizeof(unsigned int));
	for(i=0;i<(int)C_size;i++){
		c->statistics.three_Cs[i]=0;
	}
	c->statistics.compulsory=0;
	c->statistics.conflict=0;
	c->statistics.capacity=0;
	c->instNull=0;
	
	return c;
}

void free_cache(cache *c){
	int i,j;
	for(i=0;i<(int)c->num_sets;i++)
		for(j=0;j<(int)c->num_ways;j++)
			free(c->set[i].way[j].block);
	for(i=0;i<(int)c->num_sets;i++)
		free(c->set[i].way);
	free(c->set);
	free(c);
		
		
	
}



void write_cache_word(cache *c,unsigned int addr,int word){
	int via;
	unsigned int conj=set_value(c,addr);
	unsigned int et=tag_value(c,addr);
	unsigned int bloc=block_value(c,addr);
	unsigned int addr_base=calculate_addr_base(c,addr);
	if(!checkAddrWord(byte_value(c,addr))){
		RAISE_EXCEPTION (ExcCode_AdES, CP0_BadVAddr = addr)
	}
	else{
		via=hit_way(c,conj,et);
		if(c->miss_step==0)
			c->statistics.accesses++;
		
		if(via!=-1 && c->miss_step==0){
			
			c->set[conj].way[via].acc=1;
			c->set[conj].way[via].block[bloc]=word;
			c->acces=1;
			if(c->num_ways>1 && c->algorithm==LRU)   //update LRU counters
				hit_lru(c,conj,via);

			if(c->wr_policy.hit_policy==through)
				set_mem_word(addr,word);   //write through
			else
				c->set[conj].way[via].modified=1;
			c->statistics.hits++;
		}
		else{
			if(c->miss_step==0){
				check_Cs(c,conj,et);   //for the three C's
				mark_miss(c,conj);
				if(c->wr_policy.miss_policy==allocate)
					c->miss_step=1;
				else 
					c->miss_step=2; //write in main memory with no write allocate 
			}
			
			else{   
				// only if it isn't no write allocate
					c->postmiss_way=load_block(c,conj,et,addr_base);
					c->miss_step=2;
				
			}
		}
	}
	
}

void write_word_postmiss(cache *c,unsigned int addr,int word){
	unsigned int conj=set_value(c,addr);
	unsigned int bloc=block_value(c,addr);
	if(c->wr_policy.miss_policy==allocate){
		c->set[conj].way[c->postmiss_way].block[bloc]=word;
		if(c->wr_policy.hit_policy!=back)
			set_mem_word(addr,word);
		else
			c->set[conj].way[c->postmiss_way].modified=1;
	}
	else
		set_mem_word(addr,word);
		
}


void write_cache_byte(cache *c,unsigned int addr,int word){
	int wordaux,mask=0xffffff00,via;
	unsigned int conj=set_value(c,addr);
	unsigned int et=tag_value(c,addr);
	unsigned int bloc=block_value(c,addr);
	unsigned int addr_base=calculate_addr_base(c,addr);
	unsigned int byte=byte_value(c,addr);
	wordaux=word & 0xff;
	wordaux=wordaux<<(8*byte);
	left_ones(&mask,(8*byte));
	via=hit_way(c,conj,et);
	if(c->miss_step==0)
		c->statistics.accesses++;
	
	if(via!=-1 && c->miss_step==0){
		
		c->set[conj].way[via].acc=1;
		c->set[conj].way[via].block[bloc]&=mask; //set the lower byte to zero
		c->set[conj].way[via].block[bloc]|=wordaux;//write the byte in memory
		c->acces=1;
		if(c->num_ways>1 && c->algorithm==LRU)   //update LRU counters
				hit_lru(c,conj,via);

		if(c->wr_policy.hit_policy==through)
			set_mem_byte(addr,word);   //write through
		else
			c->set[conj].way[via].modified=1;
		c->statistics.hits++;
	}
	else{
		if(c->miss_step==0){
			check_Cs(c,conj,et);   //for the three C's
			mark_miss(c,conj);
			if(c->wr_policy.miss_policy==allocate)
				c->miss_step=1;
			else
				c->miss_step=2;
		}
		
		else{
			//only if it isn't no write allocate
				c->postmiss_way=load_block(c,conj,et,addr_base);
				c->miss_step=2;
			
		}
	}
	
}


void write_byte_postmiss(cache *c,unsigned int addr,int word){
	int wordaux,mask=0xffffff00;
	unsigned int conj=set_value(c,addr);
	unsigned int bloc=block_value(c,addr);
	unsigned int byte=byte_value(c,addr);
	wordaux=word & 0xff;
	wordaux=wordaux<<(8*byte);
	left_ones(&mask,(8*byte));
	if(c->wr_policy.miss_policy==allocate){
		c->set[conj].way[c->postmiss_way].block[bloc]&=mask;
		c->set[conj].way[c->postmiss_way].block[bloc]|=wordaux;
	
		if(c->wr_policy.hit_policy!=back)
			set_mem_byte(addr,word);
		else
			c->set[conj].way[c->postmiss_way].modified=1;
	}
	else
		set_mem_byte(addr,word);
}


void write_cache_half(cache *c,unsigned int addr,int word){
	int wordaux,mask=0xffff0000,via;
	unsigned int conj=set_value(c,addr);
	unsigned int et=tag_value(c,addr);
	unsigned int bloc=block_value(c,addr);
	unsigned int addr_base=calculate_addr_base(c,addr);
	unsigned int byte=byte_value(c,addr);
	wordaux=word & 0xffff;
	wordaux=wordaux<<(8*byte);
	left_ones(&mask,(8*byte));
	if(!checkAddrHalf(byte)){
		RAISE_EXCEPTION (ExcCode_AdES, CP0_BadVAddr = addr)
	}
	else{
		via=hit_way(c,conj,et);
		if(c->miss_step==0)
		c->statistics.accesses++;
		
		if(via!=-1 && c->miss_step==0){
			
			c->set[conj].way[via].acc=1;
			c->set[conj].way[via].block[bloc]&=mask;
			c->set[conj].way[via].block[bloc]|=wordaux;
			c->acces=1;
			if(c->num_ways>1 && c->algorithm==LRU)   //update LRU counters
				hit_lru(c,conj,via);

			if(c->wr_policy.miss_policy==through)
				set_mem_half(addr,word);   //write through
			else
				c->set[conj].way[via].modified=1;
			c->statistics.hits++;
		}
		else{
			if(c->miss_step==0){
				check_Cs(c,conj,et);   //for the three C's
				mark_miss(c,conj);
				if(c->wr_policy.miss_policy==allocate)
					c->miss_step=1;
				else
					c->miss_step=2;
			}
		
			else{
				//only if it isn't no write allocate
					c->postmiss_way=load_block(c,conj,et,addr_base);
					c->miss_step=2;
				
			}
		}
	}
	
}


void write_half_postmiss(cache *c,unsigned int addr,int word){
	int wordaux,mask=0xffff0000;
	unsigned int conj=set_value(c,addr);
	unsigned int bloc=block_value(c,addr);
	unsigned int byte=byte_value(c,addr);
	wordaux=word & 0xffff;
	wordaux=wordaux<<(8*byte);
	left_ones(&mask,(8*byte));
	if(c->wr_policy.miss_policy==allocate){
		c->set[conj].way[c->postmiss_way].block[bloc]&=mask;
		c->set[conj].way[c->postmiss_way].block[bloc]|=wordaux;
	
		if(c->wr_policy.hit_policy!=back)
			set_mem_half(addr,word);
		else
			c->set[conj].way[c->postmiss_way].modified=1;
	}
	else
		set_mem_half(addr,word);
}

int read_cache_inst(cache *c,int dat_step,unsigned int addr){
	int i,via;
	unsigned int conj=set_value(c,addr);
	unsigned int et=tag_value(c,addr);
	unsigned int bloc=block_value(c,addr);
	unsigned int addr_base=calculate_addr_base(c,addr);
	if(addr==0)
		return NULL;
	if(!checkAddrWord(byte_value(c,addr))){
		RAISE_EXCEPTION (ExcCode_AdEL, CP0_BadVAddr = addr)
		return NULL;
	}
	else{
	
		via=hit_way(c,conj,et);
		if(c->miss_step==0 && dat_step==0)
			c->statistics.accesses++;
		if(via!=-1 && c->miss_step==0){	
			if(dat_step==0){
				c->set[conj].way[via].acc=1;   //the element we are accesing is the one set to 1
				if(c->num_ways>1 && c->algorithm==LRU)   //update LRU counters
					hit_lru(c,conj,via);
				c->statistics.hits++;				
			} //update the hit/miss if not in a step of a lw/sw of the data cache
			//else 
				//c->set[conj].way[via].acc=0;  //keep miss if in a step of a lw/sw of the data cache
			c->acces=1;					   //read hit, we read in one step
			return c->set[conj].way[via].block[bloc];
			
		}
		else {
			if(c->miss_step==0){
				//check_Cs(c,conj,et);   
				mark_miss(c,conj);
				c->miss_step=1;
				return NULL;
			}
			
			else{
				i=load_block(c,conj,et,addr_base);
				c->miss_step=2;
				return c->set[conj].way[i].block[bloc];
			}
		}
	}
	
}





int read_cache_word(cache *c,unsigned int addr){
	int i,via;
	unsigned int conj=set_value(c,addr);
	unsigned int et=tag_value(c,addr);
	unsigned int bloc=block_value(c,addr);
	unsigned int addr_base=calculate_addr_base(c,addr);
	
	if(!checkAddrWord(byte_value(c,addr))){
		RAISE_EXCEPTION (ExcCode_AdEL, CP0_BadVAddr = addr)
		return NULL;
	}
	else{
	
		via=hit_way(c,conj,et);
		if(c->miss_step==0)
			c->statistics.accesses++;
		if(via!=-1 && c->miss_step==0){	
			
			c->set[conj].way[via].acc=1;   //the element we are accesing is the one set to 1
			c->acces=1;					   //read hit, we read in one step	
			if(c->num_ways>1 && c->algorithm==LRU)   //update LRU counters
				hit_lru(c,conj,via);
			c->statistics.hits++;
			
			return c->set[conj].way[via].block[bloc];
			
		}
		else {
			if(c->miss_step==0){
				check_Cs(c,conj,et);   //for the three C's
				mark_miss(c,conj);
				c->miss_step=1;
				return NULL;
			}
			
			else{
				i=load_block(c,conj,et,addr_base);
				c->miss_step=2;
				return c->set[conj].way[i].block[bloc];
			}
		}
	}
	
}


int read_cache_byte(cache *c,unsigned int addr,int extsigne){
	int i,word,via;
	unsigned int conj=set_value(c,addr);
	unsigned int et=tag_value(c,addr);
	unsigned int bloc=block_value(c,addr);
	unsigned int addr_base=calculate_addr_base(c,addr);
	unsigned int byte=byte_value(c,addr);
	via=hit_way(c,conj,et);
	if(c->miss_step==0)
		c->statistics.accesses++;
	
	if(via!=-1 && c->miss_step==0){	
		
		c->set[conj].way[via].acc=1;   
		c->acces=1;
		if(c->num_ways>1 && c->algorithm==LRU)   
			hit_lru(c,conj,via);
		word=c->set[conj].way[via].block[bloc];
		word=word>>(8*byte);
		word&=0xff;
		if((word & 0x80) && extsigne)
			word=word+0xffffff00;   //extend the sign 
		c->statistics.hits++;
		return word;
	}
	else {
		if(c->miss_step==0){
			check_Cs(c,conj,et);   //for the three C's
			mark_miss(c,conj);
			c->miss_step=1;
			return NULL;
		}
			
		
		else{
			i=load_block(c,conj,et,addr_base);
			c->miss_step=2;
			word=c->set[conj].way[i].block[bloc];
			word=word>>(8*byte);
			word&=0xff;
			if((word & 0x80) && extsigne)
				word=word+0xffffff00;   //extend the sign
			return word;
		}
	}
}


int read_cache_half(cache *c,unsigned int addr,int extsigne){
	int i,word,via;
	unsigned int conj=set_value(c,addr);
	unsigned int et=tag_value(c,addr);
	unsigned int bloc=block_value(c,addr);
	unsigned int addr_base=calculate_addr_base(c,addr);
	unsigned int byte=byte_value(c,addr);
	if(!checkAddrHalf(byte)){
		RAISE_EXCEPTION (ExcCode_AdEL, CP0_BadVAddr = addr)
		return NULL;
	}
	else{
		via=hit_way(c,conj,et);
		if(c->miss_step==0)
			c->statistics.accesses++;
	
		if(via!=-1 && c->miss_step==0){
			
			c->set[conj].way[via].acc=1;   
			c->acces=1;
			if(c->num_ways>1 && c->algorithm==LRU)   
				hit_lru(c,conj,via);
			word=c->set[conj].way[via].block[bloc];
			word=word>>(8*byte);
			word&=0xffff;   
			if((word & 0x8000) && extsigne)
				word=word+0xffff0000;   //extend the sign
			c->statistics.hits++;
			return word;
		}
		else {
			if(c->miss_step==0){
				check_Cs(c,conj,et);   //for the three C's
				mark_miss(c,conj);
				c->miss_step=1;
				return NULL;
			}

			
			else{
				i=load_block(c,conj,et,addr_base);
				c->miss_step=2;
				word=c->set[conj].way[i].block[bloc];
				word=word>>(8*byte);
				word&=0xffff;
				if((word & 0x8000)  && extsigne)
					word=word+0xffff0000;   //extend the sign
				return word;
			}
		}
	}
}

void mark_miss(cache *c,unsigned int conj){
	int i,j;
	for(i=0;i<(int)c->num_sets;i++){
		for(j=0;j<(int)c->num_ways;j++){
			if(i!=(int)conj)
				c->set[i].way[j].acc=-1;
			else
				c->set[i].way[j].acc=0;
		}
	}
}


int load_block(cache *c,unsigned int conj,unsigned int et,unsigned int addr_base){
	int i,j;
	
	for(i=0;i<(int)c->num_sets;i++)
		for(j=0;j<(int)c->num_ways;j++)
			c->set[i].way[j].acc=-1;
	for(j=0;j<(int)c->num_ways;j++)
		if(!(c->set[conj].way[j].valid))
			break;   //j keeps the value of the first free way
	if(j>=(int)c->num_ways)
		if(c->num_ways>1)
			j=substitute_way(c,conj);
		else
			j--;
	if(c->wr_policy.hit_policy==back && c->set[conj].way[j].modified){
		int et_dest=c->set[conj].way[j].tag;
		int addr_dest=rebuild_addr_base(c,conj,et_dest);
		for(i=0;i<(int)c->block_size/4;i++){
			set_mem_word(addr_dest,c->set[conj].way[j].block[i]);
			addr_dest+=4;
		}
	}   //write the block in memory if it is writeback

	c->set[conj].way[j].acc=0;
	c->set[conj].way[j].tag=et;

	if(!c->instruction){
		for(i=0;i<(int)(c->block_size/4);i++)   //load the block from memory
			c->set[conj].way[j].block[i]=read_mem_word(addr_base+(i*4));
	}
	else{   //inst cache
		instruction *in;
		for(i=0;i<(int)(c->block_size/4);i++){
			in=read_mem_inst(addr_base+(i*4));
			if(in==NULL)
				c->set[conj].way[j].block[i]=NULL;	
			else	
				c->set[conj].way[j].block[i]=in->encoding;
		}
	}

	c->set[conj].way[j].valid=1;
	c->acces=0; 
	c->set[conj].way[j].modified=0;
	for(i=0;i<(int)c->num_ways;i++){
		if(i==j)
			c->set[conj].way[i].counter=0;
		else
			c->set[conj].way[i].counter++;
	}//update the counters. If there's only one way, always to zero
	return j;   //return which way to store the block
}


int substitute_way(cache *c,unsigned int conj){
	int via_contador=c->set[conj].way[0].counter;
	int i,j=0;
	for(i=1;i<(int)c->num_ways;i++){
		if(c->set[conj].way[i].counter>via_contador){
			via_contador=c->set[conj].way[i].counter;
			j=i;
		}
	}
	
	return j;   //return the way with the highest counter
}



int hit_way(cache *c,unsigned int conj,unsigned int et){
	int i;
	for(i=0;i<(int)c->num_ways;i++){
		
		if(c->set[conj].way[i].valid && et==c->set[conj].way[i].tag){	
			int j,k;
			for(j=0;j<(int)c->num_sets;j++){
				for(k=0;k<(int)c->num_ways;k++)					
					c->set[j].way[k].acc=-1;
			}
			return i;
		}
		
	}
	if(c->set[conj].full_s && c->miss_step==0){
		c->set[conj].full_s--;   // for the three C's
		c->full--;
	}
	return -1;
}


void hit_lru(cache *c,unsigned int conj,int via){
	int i;
	for(i=0;i<(int)c->num_ways;i++){
		if(c->set[conj].way[i].counter<c->set[conj].way[via].counter)
			c->set[conj].way[i].counter++;
	}
	c->set[conj].way[via].counter=0;
}

void check_Cs(cache *c,unsigned int conj, unsigned int et){
	unsigned int addr=rebuild_addr_base(c,conj,et),offset;
	if(addr>= 0x10000000 && addr<0x10040000){
	addr-=0x10000000;
	addr/=c->block_size;
	offset=addr%32;//(32*(c->block_size/4));
	addr/=32;//(32*(c->block_size/4));
	if(!((c->statistics.three_Cs[addr]>>offset)&1)){
		unsigned int status=c->statistics.three_Cs[addr];
		c->statistics.three_Cs[addr]=c->statistics.three_Cs[addr]>>offset;
		c->statistics.three_Cs[addr]|=1;
		c->statistics.three_Cs[addr]=c->statistics.three_Cs[addr]<<offset;
		c->statistics.three_Cs[addr]|=status;
		c->statistics.compulsory++;
	}
	else if(!c->set[conj].full_s && c->full)
		c->statistics.conflict++;
	else
		c->statistics.capacity++;
	}
}
	

unsigned int calculate_sets(unsigned int t_cache,unsigned int t_bloc,unsigned int n_vies)
{
	return t_cache/(n_vies*t_bloc);
}

unsigned int set_value(cache *c,unsigned int a){
	a=a<<c->addr_fields.tag_bits;
	a=a>>c->addr_fields.tag_bits;
	a=a>>c->addr_fields.block_bits;
	return a;
	
}

unsigned int tag_value(cache *c,unsigned int a){
	a=a>>(c->addr_fields.set_bits+c->addr_fields.block_bits);
	return a;
}

unsigned int block_value(cache *c,unsigned int a){
	a=a<<(c->addr_fields.set_bits+c->addr_fields.tag_bits);
	a=a>>(c->addr_fields.set_bits+c->addr_fields.tag_bits);
	a=a>>2;   //+2 que son els bits de byte
	return a;
}

unsigned int byte_value(cache *c,unsigned int a){
	a&=0x3;
	return a;
}

unsigned int calculate_bits(unsigned int a)
{
	
	unsigned int n=0;
	unsigned int b=a;
	while(a!=1){
		a=a>>1;
		n++;
	}
	if(pow(2,n)<b)
		return n+1;
	else
		return n;
}

unsigned int calculate_block_bits(unsigned int a){
	a/=4;
	return calculate_bits(a)+2;   //2 bits for the word offset
}

void left_ones(int *p,int num){
	int i;
	
	for(i=0;i<num;i++){
		*p=*p<<1;
		*p|=1;
	}
}

unsigned int calculate_addr_base(cache *c,unsigned int a){
	unsigned int bits=calculate_block_bits((c->block_size));
	unsigned int addr_b=a>>bits;
	addr_b=addr_b<<bits;
	return addr_b;
}

unsigned int rebuild_addr_base(cache *c,unsigned int conj,unsigned int et){
	int addr=et<<(32-(c->addr_fields.tag_bits));
	conj=conj<<c->addr_fields.block_bits;
	addr=addr|conj;
	return addr;
}


int checkAddrWord(unsigned int byte_offset){
	if(byte_offset)
		return 0;
	else
		return 1;  //if the byte offset is 0, the addres is ok
		
}


int checkAddrHalf(unsigned int byte_offset){
	if(byte_offset==0 || byte_offset==2)
		return 1;
	else return 0;
}