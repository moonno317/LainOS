#include <stdbool.h>
#include <kernel/tty.h>
#include <stdint.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "GDTandIDT.h"

#define PAGE_SIZE 4096
#define NUM_PAGES 1024

typedef struct {
    bool allocated; } PageEntry;

PageEntry pageTable[NUM_PAGES];

void initializePageTable() {
	for (int i = 0; i < NUM_PAGES; i++) {
	pageTable[i].allocated = false; } }

void* allocatePage() {
	for (int i = 0; i < NUM_PAGES; i++) {
        if (!pageTable[i].allocated) {
	pageTable[i].allocated = true;
	void* physicalAddress = (void*)(i * PAGE_SIZE);
	return physicalAddress; } }
	return NULL; }

void freePage(void* physicalAddress) {
    int pageNumber = (int)physicalAddress / PAGE_SIZE;
    if (pageNumber >= 0 && pageNumber < NUM_PAGES) {
        pageTable[pageNumber].allocated = false; } }


void kernel_main(void) {
    init_gdt();
    init_idt();
    terminal_initialize();
    printf("Hi, I got GDT working\n");
    initializePageTable();
    void* page1 = allocatePage();
    void* page2 = allocatePage();
	printf("Allocated page 1 at physical address: %p\n", (void*)page1);
	printf("Allocated page 2 at physical address: %p\n", (void*)page2);
    freePage(page1);
    freePage(page2);
    while (1) {
        kbd(); } }
