/*
 * \file
 *         disk-emu-lib.c
 * \author
 *         Kaleem Ullah    <MSCS14059@ITU.EDU.PK>
 *
 * \Short Description:
 *
 *    File System i.e FAT, FAT32, ExFat, NTFS, HPFS, GPT, EXT1,2,3,4
 * are storage representation to Operating System of physical unformatted RAW Disk.
 * using using LBA(Logical Block Addressing) scheme, storage cluster size and formatting method OS stores our file on disk media.
 * 
 * this library is design to emulate disk operations performed by OS.
 *
 * \What it does:
 *
 *    There are four operations: 
 *
 *      1. Open Disk:   to open disk for reading & writing
 *      2. Read Disk:   read disk content on specific location (cluster)
 *      3. Write Disk:  Write to disk on specific location (cluster)
 *      4. Format Disk: Erase existing disk 
 *      4. Close Disk:  close disk after read write operations
 *      4. Sync Disk:   complete pending read write operations
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
 */

#include "disk-emu-lib.h"
/* ================ openDisk operation ================ */

int openDisk(char *file_name, int n_Bytes){
  // open or creat a new file with full permission for reading writing and return its descriptor.
  // http://man7.org/linux/man-pages/man2/open.2.html
  file_descriptor = open(file_name, O_RDWR | O_CREAT, (mode_t)0600);

  // file descriptor will return -1 in case of error
  if(file_descriptor == -1){
    perror("Error: something went wrong on creating / opening file\n");
    return -1; // return -1 to caller function
  }

  // when file is open then we need to set file size i.e 1024KB
  // http://man7.org/linux/man-pages/man2/lseek.2.html
  // SEEK_SET:  The file offset is set to offset bytes.

  lseek(file_descriptor, n_Bytes - 1, SEEK_SET);  // set file descriptor to the end of file i.e file size 1024KB
  write(file_descriptor, "\0", 1); // file descriptor is at the end of file now write NULL i.e "\0" string of length 1, not character

  // we opened a file of required size. now return the file descriptor to caller function

  return file_descriptor;
}
/* ============== end openDisk operation ============== */


/* ================ readBlock operation ================ */
// Reading from given block number
int readBlock(int disk, int blockNr, void *block){
  int file_pointer;
  file_pointer = lseek(disk, blockNr * BLOCK_SIZE, SEEK_SET); // set file descriptor to the end of file i.e file size 1024KB
  if(file_pointer == -1){ // something went wrong seeking block, may be that block not exist
    perror("Error Reading: Could not resolved disk pointer status at specified location.");
    return -1;
  }
  // reading from specified pointer position
  file_pointer = read(disk, block, BLOCK_SIZE);
  if(file_pointer == -1){
    perror("Error Reading: Unable to read from specified location");
    return -1;
  }
  return 0;
}
/* ============== end readBlock operation ============== */


/* ================ writeBlock operation ================ */

int writeBlock(int disk, int blockNr, void *block){
  int file_pointer;
  file_pointer = lseek(disk, blockNr * BLOCK_SIZE, SEEK_SET); // set file descriptor to the end of file i.e file size 1024KB
  if(file_pointer == -1){ // something went wrong seeking block, may be that block not exist
    perror("Error: Could not resolved disk pointer status at specified location.");
    return -1;
  }
  // now writing to disk on given block size and position
  file_pointer = write(disk, block, BLOCK_SIZE);
  if(file_pointer == -1){
    perror("Error: Unable to write at specified location");
    return -1;
  }
  return 0;
}
/* ============== end writeBlock operation ============== */

/* ================ Erase (Format) Disk ================ */
// Completely erasing or formatting disk
int formatDisk(char *fileName){
  fclose(fopen(fileName, "w"));
  return 0;
}
/* ============== end  Erase (Format) Disk  ============== */

/* ================ closeDisk operation ================ */
// close already opened file
int closeDisk(){
  if(close(file_descriptor) == -1){ // if close function returns an error the throw this error
    perror("Error: unable to close disk, some operations are still accessing it.");
    return -1;
  }else{
    return 0;
  }
}
/* ============== end closeDisk operation ============== */

/* ================ syncDisk operation ================ */
// there may some writes or disk operations pending.
// we need to force'em before leaving
// syncDisk will perform outstanding operations forecfully 
int syncDisk(){
  if(fsync(file_descriptor) == -1){ // incase of fsync() fails to do job.
    perror("Error: Sync disk fail !");
    return -1;
  }else{
    return 0;
  }
}
/* ============== end syncDisk operation ============== */
