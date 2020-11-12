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
    if(!mq_desc){
        running->syscall_retvalue = DSOS_EMQWRITE_MQDESC_IS_NOT_IN_PROCESS;
        return;
    }
    for(int i = 0 ; i<array_size;i++){
// controllo se la coda è libera lo inserisco come primo messaggio
// dopo di che vad o a scalare e la insert in coda la faccio con funzione aux di linked list
// fino ad un max di 32
//implementa controllo sulla lunghezza del messaggio
//implementa controllo sul max num di messaggi
        mq_desc->mqueue->msg[i][31]
}
