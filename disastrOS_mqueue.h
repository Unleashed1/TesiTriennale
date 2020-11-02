#pragma once
#include "linked_list.h"
#include "disastrOS_pcb.h"
#include "disastrOS_constants.h"

typedef struct {
    int id ;
    int count;
    char mq_msg_list[MAX_MSG_SIZE][MAX_MSG_NUM];
    //list di descrittori
    ListHead descriptors;
    //lista di descrittori in attesa
    ListHead waiting_descriptors;
    ListItem list;
    char mq_curmsgs[MAX_MSG_SIZE] ;
} Mqueue;

//DA IMPLEMENTARE
void mqueueInit();


Mqueue* Mqueue_alloc(int id, char mq_curmsgs[]);
int Mqueue_free(Mqueue* queue);


typedef ListHead MqueueList ;

Mqueue* MqueueList_byId(MqueueList* l, int id) ;

void MqueueList_print(ListHead* l);



