#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "disastrOS.h"
#include "disastrOS_syscalls.h"
#include "disastrOS_mqueue.h"
#include "disastrOS_mqdescriptor.h"
#include "disastrOS_globals.h"

void internal_mqRead(){
   int fd = running->syscall_args[0];

    MqDescriptor* mq_desc = MqDescriptorList_byFd(&running->mq_descriptors,fd);
    if(!mq_desc){
        running->syscall_retvalue = DSOS_EMQREAD_MQDESC_IS_NOT_IN_PROCESS;
        return;
    }
    char msg[32];
    for(int i = 0;i<19;i++){
        msg[i] = mq_desc->mqueue->msg[i];
    }

    running->syscall_retvalue =0 ;

}
