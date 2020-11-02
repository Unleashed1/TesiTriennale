#pragma once
#include "linked_list.h"
#include "disastrOS_pcb.h"
#include "disastrOS_mqueue.h"

struct MqDescriptorPtr;

typedef struct MqDescriptor{
    ListItem list ;
    PCB* pcb;
    Mqueue* queue;
    int fd ;
    struct MqDescriptorPtr* ptr ;
} MqDescriptor;

typedef struct MqDescriptorPtr{
    ListItem list ;
    ListItem DescriptorPtr;
    MqDescriptor* descriptor;
}MqDescriptorPtr;


void MqDescriptor_init();
MqDescriptor* MqDescriptor_alloc(int fd, Mqueue* res, PCB* pcb);
int MqDescriptor_free(MqDescriptor* d);
MqDescriptor*  MqDescriptorList_byFd(ListHead* l, int fd);
void MqDescriptorList_print(ListHead* l);

MqDescriptorPtr* MqDescriptorPtr_alloc(MqDescriptor* descriptor);
int MqDescriptorPtr_free(MqDescriptorPtr* d);
void MqDescriptorPtrList_print(ListHead* l);
