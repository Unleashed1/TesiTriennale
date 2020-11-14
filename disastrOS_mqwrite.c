#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "disastrOS.h"
#include "disastrOS_syscalls.h"
#include "disastrOS_mqueue.h"
#include "disastrOS_mqdescriptor.h"
#include "disastrOS_globals.h"

void internal_mqWrite(){
   int fd = running->syscall_args[0];

    // prelevo fd per prendere la queue e nella lista al suo interno metto
    // i messaggi e li prelevo con select dalla linked list
    MqDescriptor* mq_desc = MqDescriptorList_byFd(&running->mq_descriptors,fd);
    if(!mq_desc){
        running->syscall_retvalue = DSOS_EMQWRITE_MQDESC_IS_NOT_IN_PROCESS;
        return;
    }
    if(sizeof(mq_desc->mqueue->msg) == 32*32){
        running->syscall_retvalue = DSOS_EMQWRITE_OUT_OF_BOUND;
        return;
    }

    char aux[19] ={'m','e','s','s','a','g','g','i','o',' ','d','i',' ','p','r','o','v','a','\0'};
    for(int i = 0; i<sizeof(aux)/sizeof(char);i++){
        mq_desc->mqueue->msg[1][i] = aux[i];
    }
    running->syscall_retvalue = 0;

}
