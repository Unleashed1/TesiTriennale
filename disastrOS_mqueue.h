#pragma once
#include "linked_list.h"
#include "disastrOS_pcb.h"
#include "disastrOS_constants.h"

typedef struct {
    int id ;
    int count;
    //list di descrittori
    ListHead descriptors;
    //lista di descrittori in attesa
    ListHead waiting_descriptors;
    ListItem list;
   // char mq_curmsgs[MAX_MSG_SIZE] ;
} Mqueue;

void MqueueInit();


Mqueue* Mqueue_alloc(int id,int type);
int Mqueue_free(Mqueue* mqueue);


typedef ListHead MqueueList ;

Mqueue* MqueueList_byId(MqueueList* l, int id) ;

void MqueueList_print(ListHead* l);



