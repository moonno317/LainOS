#ifndef INITRD_H
#define INITRD_H

#include "fs.h"

typedef struct {
    unsigned int nfiles; } initrd_header_t;

typedef struct {
    unsigned char magic;  
    char name[64];  
    unsigned int offset;  
    unsigned int length; } initrd_file_header_t;

fs_node_t *initialise_initrd(unsigned int location);

#endif
