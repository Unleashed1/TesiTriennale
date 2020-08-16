#include <assert.h>
#include <stdio.h>
#include "disastrOS_descriptor.h"
#include "pool_allocator.h"
#include "linked_list.h"
#include "disastrOS_mqueue.h"


#define MQUEUE_SIZE sizeof(Mqueue)
#define MQUEUE_MEMSIZE (sizeof(Mqueue)+sizeof(int))
#define MQUEUE_BUFFER_SIZE MAX_NUM_MQUEUE*MQUEUE_MEMSIZE

static char _mqueue_buffer[MQUEUE_BUFFER_SIZE];
static PoolAllocator _mqueue_allocator;

void Mqueue_init(){
    // la init deve inizializare la queue
    int res = PoolAllocator_init(& _mqueue_allocator,
            MQUEUE_SIZE,
            MAX_NUM_MQUEUE,
            _mqueue_buffer,
            MQUEUE_SIZE);
    assert(! result);
}
//promemoria per la alloc
/// utilizza una lista di n elementi per implementare la queue
Mqueue* Mqueue_alloc(int mq_flags, int mq_maxmsg, int mq_msgsize, int mq_curmsgs){
    Mqueue* m=(Mqueue*) PoolAllocator_getBlock(&_mqueue_allocator);
    if(!m) return 0 ;
    m->list.prev = m->list.next = 0;
    m->mq_flags = mq_flags;
    m->mq_maxmsg = maxmsg;
    m->mq_msgsize = mq_msgsize;
    m->mq_curmsgs = mq_curmsgs;
    List_init(&m->descriptors);
    return m ;
}
int Mqueue_free(Mqueue* m){
    assert(m->descriptors.first == 0);
    assert(m->descriptors.last == 0);
    return PoolAllocator_relaseBlock(&_mqueue_allocator, m);
}
