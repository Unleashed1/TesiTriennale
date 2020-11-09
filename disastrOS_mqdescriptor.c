#include <assert.h>
#include <stdio.h>
#include "disastrOS_mqdescriptor.h"
#include "pool_allocator.h"
#include "disastrOS_constants.h"

#define MQDESCRIPTOR_SIZE sizeof(MqDescriptor)
#define MQDESCRIPTOR_MEMSIZE (sizeof(MqDescriptor)+sizeof(int))
#define MAX_NUM_MQDESCRIPTORS (MAX_NUM_MQDESCRIPTORS_PER_PROCESS*MAX_NUM_PROCESSES)
#define MQDESCRIPTOR_BUFFER_SIZE MAX_NUM_MQDESCRIPTORS*MQDESCRIPTOR_MEMSIZE

#define MQDESCRIPTORPTR_SIZE sizeof(MqDescriptorPtr)
#define MQDESCRIPTORPTR_MEMSIZE (sizeof(MqDescriptorPtr)+sizeof(int))
#define MQDESCRIPTORPTR_BUFFER_SIZE MAX_NUM_MQDESCRIPTORS*MQDESCRIPTORPTR_MEMSIZE

static char _mq_descriptor_buffer[MQDESCRIPTOR_BUFFER_SIZE];
static PoolAllocator _mq_descriptor_allocator;

static char _mq_descriptor_ptr_buffer[MQDESCRIPTORPTR_BUFFER_SIZE];
static PoolAllocator _mq_descriptor_ptr_allocator;

void MqDescriptor_init(){
  int result=PoolAllocator_init(& _mq_descriptor_allocator,
				MQDESCRIPTOR_SIZE,
				MAX_NUM_PROCESSES,
				_mq_descriptor_buffer,
				MQDESCRIPTOR_BUFFER_SIZE);
  assert(! result);

  result=PoolAllocator_init(& _mq_descriptor_ptr_allocator,
			    MQDESCRIPTORPTR_SIZE,
			    MAX_NUM_PROCESSES,
			    _mq_descriptor_ptr_buffer,
			    MQDESCRIPTORPTR_BUFFER_SIZE);
  assert(! result);
}

MqDescriptor* MqDescriptor_alloc(int fd, Mqueue* res, PCB* pcb) {
  MqDescriptor* d=(MqDescriptor*)PoolAllocator_getBlock(&_mq_descriptor_allocator);
  if (!d)
    return 0;
  d->list.prev=d->list.next=0;
  d->fd=fd;
  d->mqueue=res;
  d->pcb=pcb;
  return d;
}

int MqDescriptor_free(MqDescriptor* d) {
  return PoolAllocator_releaseBlock(&_mq_descriptor_allocator, d);
}

MqDescriptor*  MqDescriptorList_byFd(ListHead* l, int fd){
  ListItem* aux=l->first;
  while(aux){
    MqDescriptor* d=(MqDescriptor*)aux;
    if (d->fd==fd)
      return d;
    aux=aux->next;
  }
  return 0;
}

MqDescriptorPtr* MqDescriptorPtr_alloc(MqDescriptor* descriptor) {
  MqDescriptorPtr* d=PoolAllocator_getBlock(&_mq_descriptor_ptr_allocator);
  if (!d)
    return 0;
  d->list.prev=d->list.next=0;
  d->descriptor=descriptor;
  return d;
}

int MqDescriptorPtr_free(MqDescriptorPtr* d){
  return PoolAllocator_releaseBlock(&_mq_descriptor_ptr_allocator, d);
}

void MqDescriptorList_print(ListHead* l){
  ListItem* aux=l->first;
  printf("[");
  while(aux){
    MqDescriptor* d=(MqDescriptor*)aux;
    printf("(fd: %d, rid:%d)",
	   d->fd,
	   d->mqueue->id);
    if(aux->next)
      printf(", ");
    aux=aux->next;
  }
  printf("]");
}


void MqDescriptorPtrList_print(ListHead* l){
  ListItem* aux=l->first;
  printf("[");
  while(aux){
    MqDescriptorPtr* d=(MqDescriptorPtr*)aux;
    printf("(pid: %d, fd: %d, rid:%d)",
	   d->descriptor->fd,
	   d->descriptor->pcb->pid,
	   d->descriptor->mqueue->id);
    if(aux->next)
      printf(", ");
    aux=aux->next;
  }
  printf("]");
}
