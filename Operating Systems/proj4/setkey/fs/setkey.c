#include <stdio.h>
#include <unistd.h>

typedef struct key {
	//uid_t user_id;
	unsigned int e_key;
	unsigned int d_key;
} key;

key keys[8];
int next_slot = 0;

void fs_setkey (unsigned int k0, unsigned int k1) {
	keys[next_slot].e_key = k0;
	keys[next_slot].d_key = k1;
	next_slot += next_slot % 8;
}