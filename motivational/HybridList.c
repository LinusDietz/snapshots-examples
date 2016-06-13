#include <stdlib.h>
#include <stdio.h>


struct HybridList
{
  struct HybridList *sll_next;
  struct HybridList *dll_next;
  struct HybridList *dll_prev;
  int payload;
};

void traverse_sll(struct HybridList * entry)
{
  printf("Traversing the SLL beginning with node %d:\n", entry->payload);
  printf("Nodes: [%d", entry->payload);
  while(entry->sll_next != 0)
  {
    entry = entry->sll_next;
    printf(", %d", entry->payload);
  }
  printf("]\n");
}

void traverse_dll_forward(struct HybridList * entry)
{
  printf("Traversing the DLL forwards beginning with node %d:\n", entry->payload);
  printf("Nodes: [%d", entry->payload);
  while(entry->dll_next != 0)
  {
    entry = entry->dll_next;
    printf(", %d", entry->payload);
  }
  printf("]\n");
}

void traverse_dll_backward(struct HybridList * entry)
{
  printf("Traversing backwards the DLL beginning with node %d:\n", entry->payload);
  printf("Nodes: [%d", entry->payload);
  while(entry->dll_prev!= 0)
  {
    entry = entry->dll_prev;
    printf(", %d", entry->payload);
  }
  printf("]\n");
}

int main()
{

  struct HybridList *root;

  root = (struct HybridList *) malloc(sizeof(struct HybridList));
  root->payload = 1;
  root->sll_next = (struct HybridList *) malloc(sizeof(struct HybridList));
  root->sll_next->payload = 21;





  root->dll_next = (struct HybridList *) malloc(sizeof(struct HybridList));
  root->dll_next->payload = 12;
  root->dll_next->dll_prev = root;

  printf("payload root:\t%d\n" , root->payload);
  printf("payload 2nd:\t%d\n" , root->dll_next->payload);
  printf("payload root_via_2nd:\t%d\n" , root->dll_next->dll_prev->payload);

  //printf("payload sll2nd\t%d\n" , root->sll_next->payload);
  traverse_sll(root);
  traverse_dll_forward(root);
  traverse_dll_backward(root->dll_next);




  return 0;
}
