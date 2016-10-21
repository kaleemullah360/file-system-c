/*
 * \file
 *         disk-emu-lib.h
 * \author
 *         Kaleem Ullah    <MSCS14059@ITU.EDU.PK>
 *
 * \Short Description:
 *
 *    File System i.e FAT, FAT32, ExFat, NTFS, HPFS, GPT, EXT1,2,3,4
 * are storage representation to Operating System of physical unformatted RAW Disk.
 * using LBA(Logical Block Addressing) scheme, storage cluster size and formatting method OS stores our file on disk media.
 * 
 * this library is design to emulate disk operations performed by OS.
 *
 * \What it does:
 *
 *    There are seven operations: 
 *
 *      1. Open Disk:   to open disk for reading & writing
 *      2. Read Disk:   read disk content on specific location (cluster)
 *      3. Write Disk:  Write to disk on specific location (cluster)
 *      4. Format Disk: Erase existing disk 
 *      5. Close Disk:  close disk after read write operations
 *      6. Sync Disk:   complete pending read write operations
 * 		7. View File:   view whole file written on disk
 *
 *
 * \Why it does so ?
 *  just to simulate real hardisk and check to see how it works :)
 *
 *
 * \Assumptions:
 *  max file size is 1024KB i.e 1MB
 *  disk cluster or BLOCK SIZE (in our case) is 4096Bytes i.e 4KB
 *  allocating BLOCK_SIZE memory in read_buffer, write_buffer containg data to be process
 *  write_buffer is then use to write data to disk, read_buffer is used to display data to user.
 *
 * \Intimation:
 *    some parts of the assignments are created taking help from [1]
 * for helping and educational purposes to get familarity with syntax and other libs
 *
 * [1] https://github.com/jmelai/Project.git
 *
 * Copyright 2016
 */

/* ============== include libraries ============== */
#include <stdio.h>		// standard IO operations
#include <string.h>		// string operations
#include <stdlib.h>		// for clearing screen // memory allocation, process control, conversions and others
#include <unistd.h>		// Unix/POSIX operating system API
#include <fcntl.h>		// O_RDWR | O_CREAT // Open file for reading and writing .
#include <sys/types.h>	// Used for some file attributes. with access rights i.e (mode_t)0600)
#include <sys/stat.h>	// mode of file mode_t
#include <ctype.h>     	// for tolower
/* =========== end include libraries ============= */

int main(); // one thread -> main()

#define BLOCK_SIZE 4096 // 4 KB block size
#define FILE_SIZE 1024 * 1024 // 1024 KB or 1MB file size
static int file_descriptor;

/* some prototyping for our disk operations */
int openDisk(char *file_name, int n_Bytes);
int readBlock(int disk, int blockNr, void *block);
int writeBlock(int disk, int blockNr, void *block);
int formatDisk(char *fileName);
int closeDisk();
int syncDisk();
/* end disk operations functions prototyping */
