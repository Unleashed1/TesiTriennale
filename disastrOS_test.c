
#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include <assert.h>
#include "disastrOS_mqueue.h"
#include "disastrOS_mqdescriptor.h"
#include "disastrOS.h"
#include "disastrOS_globals.h"


// we need this to handle the sleep state
void sleeperFunction(void* args){
  printf("Hello, I am the sleeper, and I sleep %d\n",disastrOS_getpid());
  while(1) {
    getc(stdin);
    disastrOS_printStatus();
  }
}


void childFunction(void* args){
//first and second for test the open and close and the rest of this func is going to test the shared sem situation
  printf("Hello, I am the child function %d\n",disastrOS_getpid());
  for (int i=0; i<(disastrOS_getpid()+1); i++){
    int fs = disastrOS_semOpen(i);
    printf("%d : Hello i am the semaphore!\n",disastrOS_getpid());
    assert(fs >= 0);
  }
  disastrOS_printStatus();
  for (int i=0; i<disastrOS_getpid()+1; i++){
    int fs = disastrOS_semClose(i);
    printf("%d : My job here is done\n",disastrOS_getpid());
    assert(!fs);
  }
  disastrOS_printStatus();
  int fd = disastrOS_semOpen(sh_sem);
  assert(fd >= 0);
  printf("sem open, pid%d\n",disastrOS_getpid());
  int fs = disastrOS_semWait(fd);
  assert(!fs);
  printf("Red Light \n");
  disastrOS_preempt();
  fs = disastrOS_semPost(fd);
  assert(!fs);
  printf("Green Light\n");
  disastrOS_printStatus();
  fs = disastrOS_semClose(fd);
  assert(!fs);
  printf("sem %d closed \n",disastrOS_getpid());

printf("***********************************************\n\n");

for (int i=0; i<(disastrOS_getpid()+1); i++){
    int mq = disastrOS_mqOpen(i);
    assert(mq>=0);
    printf("%d : Hello i am the mqueue!\n",disastrOS_getpid());
}
for (int i=0; i<(disastrOS_getpid()+1); i++){
    disastrOS_mqWrite(i);
    printf("%d : I write a message!\n",disastrOS_getpid());
    MqDescriptor* mq_desc = MqDescriptorList_byFd(&running->mq_descriptors,i);
    if(mq_desc->mqueue->id != i) break;
    for(int j = 0 ; j<19 ;j++){
        printf("%c",mq_desc->mqueue->msg[j]);
    }
    printf("\n");
}
  for (int i=0; i<disastrOS_getpid()+1; i++){
    int mq = disastrOS_mqClose(i);
    assert(!mq);
    printf("%d : I leave the terminal, bye bye \n", disastrOS_getpid());
}
  disastrOS_exit(disastrOS_getpid()+1);
}


void initFunction(void* args) {
  disastrOS_printStatus();
  printf("hello, I am init and I just started\n");
  disastrOS_spawn(sleeperFunction, 0);

  printf("I feel like to spawn 5 nice threads\n");
  int alive_children=0;
  for (int i=0; i<4; ++i) {
    int type=0;
    int mode=DSOS_CREATE;
    printf("mode: %d\n", mode);
    printf("opening resource (and creating if necessary)\n");
    int fd=disastrOS_openResource(i,type,mode);
    printf("fd=%d\n", fd);
    disastrOS_spawn(childFunction, 0);
    alive_children++;
  }

  disastrOS_printStatus();
  int retval;
  int pid;
  sh_mq= 2* ready_list.size;
  sh_sem = 2 * ready_list.size;
  while(alive_children>0 && (pid=disastrOS_wait(0, &retval))>=0){
    disastrOS_printStatus();
    printf("initFunction, child: %d terminated, retval:%d, alive: %d \n",
	   pid, retval, alive_children);
    --alive_children;
  }
  printf("shutdown!");
  disastrOS_shutdown();
}

int main(int argc, char** argv){
  char* logfilename=0;
  if (argc>1) {
    logfilename=argv[1];
  }
  // we create the init process processes
  // the first is in the running variable
  // the others are in the ready queue
  printf("the function pointer is: %p", childFunction);
  // spawn an init process
  printf("start\n");
  disastrOS_start(initFunction, 0, logfilename);
  return 0;
}
