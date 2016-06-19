# file-system-c
Disk Emulation to Study Operating System File System -C Language -Linux OS
==============================
## SYNOPSIS

\file

        my-disk.c


\author

        Kaleem Ullah    <MSCS14059@ITU.EDU.PK>


\Short Description:

   File System i.e FAT, FAT32, ExFat, NTFS, HPFS, GPT, EXT1,2,3,4
are storage representation to Operating System of physical unformatted RAW Disk.
using using LBA(Logical Block Addressing) scheme, storage cluster size and formatting method OS stores our file on disk media.
this library is design to emulate disk operations performed by OS.


\What it does:

   There are six operations: 

     1. Open Disk:   to open disk for reading & writing

     2. Read Disk:   read disk content on specific location (cluster)

     3. Write Disk:  Write to disk on specific location (cluster)

     4. Format Disk: Erase existing disk 

     5. Close Disk:  close disk after read write operations

     6. Sync Disk:   complete pending read write operations


\Why it does so ?
 just to simulate real hardisk and check to see how it works :)


\Assumptions:

 max file size is 1024KB i.e 1MB
 disk cluster or BLOCK SIZE (in our case) is 4096Bytes i.e 4KB
 allocating BLOCK_SIZE memory in read_buffer, write_buffer containg data to be process
 write_buffer is then use to write data to disk, read_buffer is used to display data to user.


\Intimation:

   some parts of the assignments are created taking help from [1]
for helping and educational purposes to get familarity with syntax and other libs
[1] https://github.com/jmelai/Project.git


**Rquired Dependencies**

1. stdio.h
2. string.h
3. stdlib.h
4. unistd.h
5. fcntl.h
6. sys/types.h
7. sys/stat.h
8. ctype.h
9. stdlib.h

## Running Program on Ubuntu

compile program.

```sh
make compile
```
Then, to run the program do,

```sh
make run
```
for clean-up,

```sh
make clean
```
