#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "disastrOS.h"
#include "disastrOS_syscalls.h"
#include "disastrOS_mqueue.h"
#include "disastrOS_mqdescriptor.h"
#include "disastrOS_globals.h"
#include "disastrOS_constants.h"

void internal_mqOpen(){
	//Looking for some possible errors
	// Check if the num. of the mqdescriptors has been reached, probably no xp
	if(running->mq_descriptors.size >= MAX_NUM_MQDESCRIPTORS_PER_PROCESS){
		running->syscall_retvalue = DSOS_EMQOPEN_OUT_OF_BOUND;
		return;
	}
	//get an id for the mq from pcb
	int id = running->syscall_args[0];


	if(id<0) {
		running->syscall_retvalue = DSOS_EMQOPEN_MQNUMVALUE;
		return;
	}
	// Check if the mqueue is already open  if not we add it in the list (we alloc first obv.)
	Mqueue* mq = MqueueList_byId((MqueueList*)&mq_list, id);
	if(!mq) {
		mq = Mqueue_alloc(id,1);
		assert(mq);
		List_insert(&mq_list, mq_list.last, (ListItem*)mq);
	}

	//Now alloc the MqDescriptor
	MqDescriptor* mq_desc = MqDescriptor_alloc(running->last_mq_fd,mq,running);
	assert(mq_desc);


	//Then alloc mqDescriptorPtr for mq_desc && update fd amd ptr
    running->last_mq_fd++;
	MqDescriptorPtr* mq_d_ptr = MqDescriptorPtr_alloc(mq_desc);
	assert(mq_d_ptr);
	mq_desc->ptr = mq_d_ptr;

	//Add mq_desc to the mq_descriptors list && link the ptr && insert mq
	List_insert(&running->mq_descriptors, running->mq_descriptors.last, (ListItem*)mq_desc);
	List_insert(&mq->descriptors, mq->descriptors.last, (ListItem*)mq_d_ptr);

	//Finally return the value of the syscall
	running->syscall_retvalue = mq_desc->fd;
}
