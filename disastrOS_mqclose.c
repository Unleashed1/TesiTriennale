#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "disastrOS.h"
#include "disastrOS_syscalls.h"
#include "disastrOS_mqueue.h"
#include "disastrOS_mqdescriptor.h"
#include "disastrOS_globals.h"
#include "disastrOS_constants.h"

void internal_mqClose(){
  //First of all take the fd of the mqDescriptor that we wants to close(check the list)


  int myfd = running->syscall_args[0];

  MqDescriptor* mq_desc = MqDescriptorList_byFd(&running->mq_descriptors,myfd);
  if(!mq_desc){
	running->syscall_retvalue = DSOS_EMQCLOSE_MQDESC_IS_NOT_IN_PROCESS;
	return;
  }

  //Now remove it from the list, remove the ptr fom the list of descriptors && free resources
  List_detach(&running->mq_descriptors, (ListItem*)mq_desc);
  Mqueue* m = mq_desc->mqueue;
  assert(m);
  MqDescriptorPtr* mq_desc_ptr = (MqDescriptorPtr*)List_detach(&m->descriptors, (ListItem*)(mq_desc->ptr));
  assert(mq_desc_ptr);
  MqDescriptorPtr_free(mq_desc_ptr);
  MqDescriptor_free(mq_desc);

  //Before return the syscall success(0),check if there are another process that could be on mq
  if(m->descriptors.size==0) {
	  //cast
	  m = (Mqueue*)List_detach(&mq_list,(ListItem*)m);
	  assert(m);
	  Mqueue_free(m);
  }
  running->syscall_retvalue = 0;
}
