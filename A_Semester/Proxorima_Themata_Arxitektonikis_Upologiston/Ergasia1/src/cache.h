
struct cache_way{
	int *block;
	unsigned int tag;
	unsigned int valid;
	int acc;
	int modified;
	int counter;
};


struct cache_set{
	struct cache_way *way;
	int full_s;   //when full_s=0 -> full set
};


typedef struct mem_cache{
	unsigned int cache_size; //in bytes
	unsigned int block_size;  //in bytes
	unsigned int num_sets;  //calculated from the two above
	unsigned int num_ways;
	
	int fully_associ;
	
	int instruction;
	
	struct cache_set *set;
	int full;   //when full=0 -> full cache
	struct {
		unsigned int block_bits;
		unsigned int set_bits;
		unsigned int tag_bits;
	}addr_fields;
	struct {
		enum {allocate,noallocate}miss_policy;
		enum {through,back}hit_policy;
	}wr_policy;
	int acces;   //indicates hit/miss in reading/writing
	int miss_step; //indicates the miss step of the read/write instruction with values 0, 1, 2
	int postmiss_way;   //way where to write the block after a write miss
	int word;		   //word to load to the processor's register after a read
	int instNull;
	struct {
		int accesses;
		int hits;
		int show;
		unsigned int *three_Cs;
		unsigned int compulsory;
		unsigned int conflict;
		unsigned int capacity;
	}statistics;
	enum {LRU,FIFO} algorithm;
}cache;

unsigned int calculate_sets(unsigned int t_cache,unsigned int t_bloc,unsigned int n_vies);
unsigned int calculate_block_bits(unsigned int a);
unsigned int calculate_bits(unsigned int a);
unsigned int set_value(cache *c,unsigned int a); //calcula el valor dels bits corresponents al conjunt 
unsigned int tag_value(cache *c,unsigned int a); //calcula el valor de la etiqueta per a comparar
unsigned int block_value(cache *c,unsigned int a);
unsigned int byte_value(cache *c,unsigned int a);
unsigned int calculate_addr_base(cache *c,unsigned int a);
unsigned int rebuild_addr_base(cache *c,unsigned int conj,unsigned int et);
void left_ones(int *p,int num);
int checkAddrWord(unsigned int byte);
int checkAddrHalf(unsigned int byte);

cache * initialize_cache(cache *c,unsigned int bytes_cache,unsigned int bytes_bloc,unsigned int n_vies,unsigned int m_algorithm,int inst);
void free_cache(cache *c);
int read_cache_word(cache *c,unsigned int addr);
int read_cache_byte(cache *c,unsigned int addr,int extsigne);
int read_cache_half(cache *c,unsigned int addr,int extsigne);
void write_cache_word(cache *c,unsigned int addr,int word);
void write_word_postmiss(cache *c,unsigned int conj,int word);
void write_cache_byte(cache *c,unsigned int addr,int word);
void write_byte_postmiss(cache *c,unsigned int addr,int word);
void write_cache_half(cache *c,unsigned int addr,int word);
void write_half_postmiss(cache *c,unsigned int addr,int word);
void mark_miss(cache *c,unsigned int conj);
int load_block(cache *c,unsigned int conj,unsigned int et,unsigned int addr_base);
int substitute_way(cache *c,unsigned int conj);
int hit_way(cache *c,unsigned int conj,unsigned int et);
void hit_lru(cache *c,unsigned int conj,int via);
void check_Cs(cache *c,unsigned int conj, unsigned int et);
int read_cache_inst(cache *c,int dat_step,unsigned int addr);