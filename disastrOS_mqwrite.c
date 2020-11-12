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
    char msg[]= running->syscall_args[1];
    int array_size = sizeof(msg)/sizeof(char);
    // prelevo fd per prendere la queue e nella lista al suo interno metto
    // i messaggi e li prelevo con select dalla linked list
    MqDescriptor* mq_desc = MqDescriptorList_byFd(&running->mq_descriptors,fd);
    int pos = mq_desc->mqueue->pos;
    if(!mq_desc){
        running->syscall_retvalue = DSOS_EMQWRITE_MQDESC_IS_NOT_IN_PROCESS;
        return;
    }
    if(pos == 0){
        running->syscall_retvalue = DSOS_EMQWRITE_OUT_OF_BOUND;
        return;
    for(;pos>=0;pos--){
    //da capire come prelevare la stringa
        if( ""== ""){
            for(int i =0 ; i<array_size ; i++){
                mq_desc->mqueue->msg[pos][i] == msg[i];
            }
        }
    }
    running->syscall_retvalue = 0;
    }
}
