#pragma once

typedef struct msgList {
  struct msgtem* prev;
  struct msgItem* next;
  char msg[32];
} msgItem;

typedef struct msgHead {
  msgItem* first;
  msgItem* last;
  int size;
} msgHead;
