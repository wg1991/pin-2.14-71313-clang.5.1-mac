#include <stdlib.h>
#include <math.h>
#include <memory.h>
#define BLOCK_SIZE 12 /* 由于存在虚拟的data字段，sizeof不能正确计算meta长度，这里手工设置 */


void *firstaddr = NULL;
char blockmap[131072];
typedef struct s_block *t_block;
typedef struct block_link *b_link;

struct block_link {
    int block_size;
    void *block;
    b_link next;
};

b_link block = NULL;

struct s_block {
    int padding;  /* 填充4字节，保证meta块长度为8的倍数 */
    t_block next; /* 指向下个块的指针 */
};


b_link init_blink(b_link t){
    for (int i = 5; i < 20; ++i)
    {
        printf("%d\n", i);
        b_link b;
        b = (b_link)malloc(sizeof(struct block_link));
        b->block_size = pow(2,i);
        printf("blocksize:%d\n", b->block_size);
        b->next = NULL;
        b->block = NULL;
        if (t == NULL)
        {
            t = b;
            printf("%p,%p\n", t->block_size,t);
        }
        else{
            b->next = t;
            t = b;
            printf("%p,%p\n", t->block_size,t);
        }
    }
    return t;
}

/* First fit */
t_block find_block(t_block first) {
    t_block b = first;
    first = first->next;
    return b;
}

/* Initialize list */
void init_block(void *first_block,size_t s){
    if (firstaddr == NULL)
    {
        firstaddr = malloc(1024*1024*1024*4);
        memset(blockmap,0,131072);
        void *t;
        firstaddr = (void*)((((unsigned long long)firstaddr>>16)+1)<<16);
    }
    void *first_addr;
    first_addr = firstaddr;
    int i;
    i = s/(64*1024) + 1;
    while(i > 0){
        firstaddr = firstaddr + 1024*64;
        blockmap[((unsigned long long)first_addr) >> 16] = (char)(log(s)/log(2));
        i--;
    }

    t_block last;
    last = (t_block)first_addr;
    for (int j = 0; j < s; j = j + 64*1024)
    {
        while(last < firstaddr){
            t_block b;
            b = last;
            if (first_block == NULL)
            {
                first_block = b;   
            }
            last = last + s;
            b->next = last;
        }
        
    }
}

size_t align8(size_t s) {
    if(s & 0x7 == 0)
        return s;
    return ((s >> 3) + 1) << 3;
}


void *mymalloc(size_t size) {
    printf("mymalloc,size:%d\n",size);
    if (block == NULL){
        printf("initblock\n");
        for (int i = 5; i < 20; ++i)
        {
            b_link b;
            b = (b_link)malloc(sizeof(struct block_link));
            b->block_size = pow(2,i);
            b->next = NULL;
            b->block = NULL;
            if (block == NULL)
            {
                block = b;
            }
            else{
                b->next = block;
                block = b;
            }
            printf("%p , %p\n", block,block->next);
        }
        b_link t;
        t = block;
        while(t->next != NULL){
            printf("%d,%p\n", t->block_size,t);
            t = t->next;
        }
        printf("init blink success\n");
    }
    b_link cur;
    cur = block;
    void *first_block;
    while(cur != NULL){
        if (cur->next == NULL)
        {
            break;
        }
        if (cur->next->block_size < size)
            break;
        cur = cur->next;
    }
    printf("cursize:%d\n", cur->block_size);
    if (cur->block == NULL)
    {
        init_block(cur->block,cur->block_size);
        printf("init_block success\n");
    }
    else
        first_block = cur->block;

    t_block b;

    b = find_block(first_block);

    return b + BLOCK_SIZE;
}


void myfree(void *p) {
    int blocksize;
    blocksize = blockmap[((unsigned long long)p>>16)];
    t_block first_block;
    b_link firstblock;
    firstblock = block;
    while(firstblock->next != NULL){
        if (firstblock->block_size == blocksize)
        {
            first_block = firstblock->block;
            while(first_block->next != NULL){
                first_block = first_block->next; 
            }
            t_block b;
            b = p - BLOCK_SIZE;
            b->next = NULL;
            first_block->next = b;
        }
    }
}
