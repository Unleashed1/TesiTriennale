#pragma once
#include "linked_list.h"
#include "disastrOS_pcb.h"
#include "disstrOS_mqueue.h"

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

