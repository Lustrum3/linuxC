
#include <stdio.h>
#include <stdlib.h>

typedef enum {
LOCK,
SENSOR,
LIGHT,
}device_type_t;

typedef struct {
        char offset;
        device_type_t type;
}port_t;

//Logical slot definition
typedef struct {
        char slot_id;
        char number_of_ports;    //2
        port_t port[];
}slot_t;

typedef struct {
        char total_slots;     // 2 
        slot_t *slots[];
}layout_t;

int main()
{

layout_t *mlayout = (layout_t *)malloc(sizeof(layout_t)  + 2*sizeof(slot_t));

      slot_t *mslot[2] = {NULL};

      mslot[0]  = (slot_t *)malloc(sizeof(slot_t)+2*sizeof(port_t));
      mslot[1]  = (slot_t *)malloc(sizeof(slot_t)+2*sizeof(port_t));

      



      printf("szieof(device_type_t) : %x\r\n", sizeof(device_type_t));
      printf("szieof(port_t) : %x\r\n", sizeof(port_t));
      printf("szieof(slot_t) : %x\r\n", sizeof(slot_t));
      printf("szieof(layout_t) : %x\r\n", sizeof(layout_t));

      printf("\r\n");

      printf("mlayout addr: %p\n",(mlayout));
      printf("mlayout->total_slots addr: %p\n",(&mlayout->total_slots));


      printf("\r\n");
      printf("mslot1 addr: %p\n",(mslot[0]));
      printf("mslot2 addr: %p\n",(mslot[1]));

#if 1 
	
     mlayout->slots[0] = mslot[0];
     mlayout->slots[1] = mslot[1];

      printf("mlayout->slots[0] addr: %p\n",(mlayout->slots[0]));
      printf("mlayout->slots[1] addr: %p\n",(mlayout->slots[1]));

	ptintf("\r\n");

      printf("mlayout->slots[0]->slot_id addr: %p\n",(&mlayout->slots[0]->slot_id));
      printf("mlayout->slots[1]->slot_id addr: %p\n",(&mlayout->slots[1]->slot_id));

      printf("\r\n");
      printf("mlayout->slots[0]->port[0] addr: %p\n",&(mlayout->slots[0]->port[0]));
      printf("mlayout->slots[0]->port[1] addr: %p\n",&(mlayout->slots[0]->port[1]));
     

      printf("\r\n");
      
      printf("mlayout->slots[1]->port[0] addr: %p\n",(&mlayout->slots[1]->port[0]));
      printf("mlayout->slots[1]->port[1] addr: %p\n",(&mlayout->slots[1]->port[1]));


      printf("\r\n");
      
      printf("mlayout->slots[0]->port[0].offset addr: %p\n",(&mlayout->slots[0]->port[0].offset));
      printf("mlayout->slots[0]->port[1].offset addr: %p\n",(&mlayout->slots[0]->port[1].offset));

      printf("\r\n");
      
      printf("mlayout->slots[1]->port[0].offset addr: %p\n",(&mlayout->slots[1]->port[0].offset));
      printf("mlayout->slots[1]->port[1].offset addr: %p\n",(&mlayout->slots[1]->port[1].offset));

#endif


        return 1;

}
