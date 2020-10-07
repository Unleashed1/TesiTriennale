#pragma once
#include "linked_list.h"
#include "disastrOS_pcb.h"

typedef struct {
    int id ;
    int count;
    int mq_flags;
    int mq_maxmsg;
    int mq_msgsize;
    int mq_curmsgs;
    //list di descrittori
    ListHead descriptors;
    //lista di descrittori in attesa
    ListHead waiting_descriptors;
    ListItem list;
} Mqueue;

//DA IMPLEMENTARE
void mqueueInit();


Mqueue* Mqueue_alloc(int mq_flags, int mq_maxmsg, int mq_msgsize, int mq_curmsgs);
int Mqueue_free(Mqueue* queue);


typedef ListHead MqueueList ;

Mqueue* MqueueList_byId(MqueueList* l, int id) ;

void MqueueList_print(ListHead* l);



