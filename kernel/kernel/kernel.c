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
#include "schedule.h"

void kernel_main(void) {
    init_gdt();
    init_idt();
    terminal_initialize();
    printf("Hi, I got GDT working\n");
    init_dynamic_mem();
    
    size_t allocation_size = 1024;
    void* allocated_memory;
    int allocation_count = 0;

    while ((allocated_memory = malloc(allocation_size)) != NULL) {
        allocation_count++;
        allocation_size *= 2; }

    if (allocated_memory != NULL) {
        *(int*)allocated_memory = 42; }

   	free(allocated_memory);
    while (1) {
	schedule();
        kbd(); } }