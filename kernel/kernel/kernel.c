#include <stdbool.h>
#include <kernel/tty.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "GDTandIDT.h"
#include "mm.h"


void kernel_main(void) {
   	init_gdt();
   	init_idt();
   	terminal_initialize();
   	printf("Hi, I got GDT working\n");
   	init_paging();
   	init_dynamic_mem();
   	size_t allocation_size = 8096;
   	void *allocated_memory;
   	int allocation_count = 0;
   	while ((allocated_memory = malloc(allocation_size)) != NULL) {
        allocation_count++;
        allocation_size *= 2; }
	printf("Total memory allocated: %d bytes\n", allocation_count * allocation_size);
   	while (1) {
        kbd(); } }
