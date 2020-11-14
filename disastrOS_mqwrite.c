#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "disastrOS.h"
#include "disastrOS_syscalls.h"
#include "disastrOS_mqueue.h"
#include "disastrOS_mqdescriptor.h"
#include "disastrOS_globals.h"
#include "msg_list.h"

void internal_mqWrite(){
   int fd = running->syscall_args[0];

    // prelevo fd per prendere la queue e nella lista al suo interno metto
    // i messaggi e li prelevo con select dalla linked list
    MqDescriptor* mq_desc = MqDescriptorList_byFd(&running->mq_descriptors,fd);
    if(!mq_desc){
        running->syscall_retvalue = DSOS_EMQWRITE_MQDESC_IS_NOT_IN_PROCESS;
        return;
    }
    if(mq_desc->mqueue->msg.size == 32){
        running->syscall_retvalue = DSOS_EMQWRITE_OUT_OF_BOUND;
        return;
    }

    char aux[19] ={'m','e','s','s','a','g','g','i','o',' ','d','i',' ','p','r','o','v','a','\0'};
    for(int i = sizeof(aux)/sizeof(char)-1; i>=0;i--){
        mq_desc->mqueue->msg.first->msg[i] = aux[i];
    }
    int size = sizeof(aux)/sizeof(char)-1;
    for(int i = 0; i<size;i++){
        printf("il messaggio è : %c",mq_desc->mqueue->msg.first->msg[i]);
    }


    running->syscall_retvalue = 0;

}
