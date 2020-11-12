#include <assert.h>
#include <stdio.h>
#include "disastrOS_descriptor.h"
#include "pool_allocator.h"
#include "linked_list.h"
#include "disastrOS_mqueue.h"
#include "disastrOS_constants.h"


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
            MQUEUE_BUFFER_SIZE);
    assert(! res);
   printf("%d",res);

}
//promemoria per la alloc
/// utilizza una lista di n elementi per implementare la queue
Mqueue* Mqueue_alloc(int id, int count){
    Mqueue* m=(Mqueue*) PoolAllocator_getBlock(&_mqueue_allocator);
    if(!m) return 0 ;
    m->id = id ;
    m->list.prev = m->list.next = 0;
    m->count = count;
    List_init(&m->descriptors);
    return m ;
}
int Mqueue_free(Mqueue* m){
    assert(m->descriptors.first == 0);
    assert(m->descriptors.last == 0);
    return PoolAllocator_releaseBlock(&_mqueue_allocator, m);
}

Mqueue* MqueueList_byId(MqueueList* l , int id ){
    ListItem* aux = l-> first ;
    while(aux){
        Mqueue* r =(Mqueue*)aux;
        if(r->id == id){
            return r ;
        }
        aux = aux->next;
    }
    return 0 ;
}

void Mqueue_print(Mqueue* r){
  printf("id: %d, count:%d, pids:", r->id, r->count);
  DescriptorPtrList_print(&r->descriptors);
  printf("waiting: ");
  DescriptorPtrList_print(&r->waiting_descriptors);
}

void MqueueList_print(ListHead* l){
  ListItem* aux=l->first;
  printf("{\n");
  while(aux){
    Mqueue* r=(Mqueue*)aux;
    printf("\t");
    Mqueue_print(r);
    if(aux->next)
      printf(",");
    printf("\n");
    aux=aux->next;
    }
}
