#include <stdlib.h>
#include <math.h>
#define BLOCK_SIZE 12 /* 由于存在虚拟的data字段，sizeof不能正确计算meta长度，这里手工设置 */

b_link block = NULL;

typedef struct block_link *b_link;
{
    int block_size;
    void *block;
    b_link next;
};

typedef struct s_block *t_block;
struct s_block {
    int padding;  /* 填充4字节，保证meta块长度为8的倍数 */
    t_block next; /* 指向下个块的指针 */
};

int init_blink(b_link block){
    for (int i = 4; i < 20; ++i)
    {
        b_link b;
        b = (b_link)malloc(sizeof(block_link));
        b->block_size = pow(2,i);
        b->next = NULL;
        b->block = NULL;
        if (block == NULL)
            block = b;
        else{
            b_link tmp;
            tmp = block;
            while(tmp->next != NULL){
                tmp = tmp->next;
            }
            tmp->next = b;
        }
    }
    return 1;
}

/* First fit */
t_block find_block(t_block first) {
    t_block b = first;
    first = first->next;
    return b;
}

/* Initialize list */
t_block init_block(void *first_block,size_t s){
    printf("0 num:%d\n",num);
    void *first_addr;
    int i = (int)s/(64*1024);
    first_addr = malloc(64*1024*i);

    t_block b;
    b = (t_block)first_addr;

    if(sbrk(BLOCK_SIZE + s) == (void *)-1)
      return NULL;
    b->size = s;
    b->next = NULL;
    b->free = 1;
    first_block = b;
    printf("2\n");
    t_block last;
    int i;
    printf("3\n");
    for (i = 0; i < num; ++i)
    {
        printf("%d\n", i);
        last = first_block;
        while(last->next != NULL)
            last = last->next;
        t_block t;
        t = extend_heap(last,s);
        last->next = t;
        //printf("size:%d,data:%s,padding:%d,free:%d\n",last->size,last->data,last->padding,last->free );
    }
    printf("4\n");
    return first_block;
}

size_t align8(size_t s) {
    if(s & 0x7 == 0)
        return s;
    return ((s >> 3) + 1) << 3;
}


void *mymalloc(size_t size) {
    printf("mymalloc,size:%d\n",size);
    if (block == NULL)
        if (!init_blink(block))
            return NULL;
    b_link cur;
    cur = block;
    void *first_block;
    while(cur->next != NULL){
        if (cur->size > size)
            break;
        cur = cur->next;
    }
    if (cur->block == NULL)
    {
        first_block = init_block(cur->block,cur->size);
    }
    else
        first_block = cur->block;

    t_block b

    b = find_block(first_block);

    return b + BLOCK_SIZE;
}


void myfree(void *p) {
    t_block first_block;
    if (p > block_16 && p < (block_16 + 32 * (BLOCK_SIZE + 16)))
        first_block = block_16;
    else if(p > block_64 && p < (block_64 + 32 * (BLOCK_SIZE + 64)))
        first_block = block_64;
    else if(p > block_256 && p < (block_256 + 32 * (BLOCK_SIZE + 256)))
        first_block = block_256;
    else if(p > block_1024 && p < (block_1024 + 32 * (BLOCK_SIZE + 1024)))
        first_block = block_1024;
    else if(p > block_4096 && p < (block_4096 + 32 * (BLOCK_SIZE + 4096)))
        first_block = block_4096;
    else if(p > block_16384 && p < (block_16384 + 32 * (BLOCK_SIZE + 16384)))
        first_block = block_16384;
    t_block b = first_block;
    while(b){
        if(b->data == (char*)p){
            b->free = 1;
            break;
        }
        b = b->next;
    }
}
