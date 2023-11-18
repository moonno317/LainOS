#ifndef FS_H
#define FS_H


#define FS_FILE        0x01
#define FS_DIRECTORY   0x02
#define FS_CHARDEVICE  0x03
#define FS_BLOCKDEVICE 0x04
#define FS_PIPE        0x05
#define FS_SYMLINK     0x06
#define FS_MOUNTPOINT  0x08

struct fs_node;

typedef unsigned int (*read_type_t)(struct fs_node*,unsigned int,unsigned int,unsigned char*);
typedef unsigned int (*write_type_t)(struct fs_node*,unsigned int,unsigned int,unsigned char*);
typedef void (*open_type_t)(struct fs_node*);
typedef void (*close_type_t)(struct fs_node*);
typedef struct dirent * (*readdir_type_t)(struct fs_node*,unsigned int);
typedef struct fs_node * (*finddir_type_t)(struct fs_node*,char *name);

typedef struct fs_node{
    char name[128]; 
    unsigned int mask;    
    unsigned int uid;      
    unsigned int gid;      
    unsigned int flags;      
    unsigned int inode;     
    unsigned int length;   
    unsigned int impl;      
    read_type_t read;
    write_type_t write;
    open_type_t open;
    close_type_t close;
    readdir_type_t readdir;
    finddir_type_t finddir;
    struct fs_node *ptr; } fs_node_t;

struct dirent {
    char name[128];
    unsigned int ino; };

extern fs_node_t *fs_root;

unsigned int read_fs(fs_node_t *node, unsigned int offset, unsigned int size, unsigned char *buffer);
unsigned int write_fs(fs_node_t *node, unsigned int offset, unsigned int size, unsigned char *buffer);
void open_fs(fs_node_t *node, unsigned char read, unsigned char write);
void close_fs(fs_node_t *node);
struct dirent *readdir_fs(fs_node_t *node, unsigned int index);
fs_node_t *finddir_fs(fs_node_t *node, char *name);

#endif
