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
 *    7. View File:   view whole file written on disk
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

#include "disk-emu-lib.c"
/* ================== Main Function =================== */
int main(int argc, char *argv[]){

  /* User inputs */

  // dynamically allocating memory to hold require byte.
  int *block = malloc(sizeof(int) * 10);             // use to store block number
  char *fileName = malloc(sizeof(char) * 10);       // use to store file name
  char *file_data = malloc(sizeof(char) * 1);       // use to store file data
  char *disk_operation = malloc(sizeof(char) * 1);  // use to store disk operation
  //char *fileName = "sample.txt";

  /* User inputs */

  char *read_buffer;
  char *write_buffer;
  read_buffer = (char*)malloc(sizeof(char)*BLOCK_SIZE);
  write_buffer = (char*)malloc(sizeof(char)*BLOCK_SIZE);

  void clrscr()
  {
    system("@cls||clear");
  }

  void switch_reading(){
    printf("=================== File Reading ================================\n");
    printf("Enter File name (Max 10 Bytes long)\n");
    scanf("%10s", fileName); // If file_name holds a memory of 10 bytes

    printf("Enter Block Number\n");
    scanf("%10d", block); // If file_data holds a memory of 1 byte
    clrscr();
    int diskFile = openDisk(fileName, FILE_SIZE * 1);

    if(diskFile != -1){

      printf("Reading '%s' from Block %d\n", fileName, *block);
      readBlock(diskFile, *block, read_buffer);
      printf("\n\n\n+++++++++++++++++++ Begin ++++++++++++++++++++\n\n\n");
      for (int i=0; i <= BLOCK_SIZE; i++) {
        //printf("buffread[%d] = %c\n", i, read_buffer[i]);  
        printf("%c", read_buffer[i]);
      }
      printf("\n\n\n+++++++++++++++++++ EndOF ++++++++++++++++++++\n");
      syncDisk();
      closeDisk();
    }else{
      printf("Info: Exiting main thread.\n");
      exit(-1);
    }
  }
  void switch_writing(){
    printf("=================== File Writing ================================\n");

    printf("Enter File name (Max 10 Bytes long)\n");
    scanf("%10s", fileName); // If file_name holds a memory of 10 bytes

    printf("Enter Block Number\n");
    scanf("%10d", block); // If file_data holds a memory of 1 byte

    printf("Enter character to be written in file\n");
    scanf("%1s", file_data); // If file_data holds a memory of 1 byte

    int diskFile = openDisk(fileName, FILE_SIZE * 1);

    if(diskFile != -1){

      printf("File %s opened for writing\n\n\n", fileName);
      printf("Filling buffer into memory for writing\n\n\n");
      for(int i=0; i <= BLOCK_SIZE; i++){
        write_buffer[i] = *file_data;
      }

      printf("Writing %s to File %s on Block %d\n\n\n",file_data ,fileName, *block);
      writeBlock(diskFile, *block, write_buffer);

      syncDisk();
      closeDisk();

      printf("Writing Finish.\n\n\n");
    }else{
      printf("Info: Exiting main thread.\n");
      exit(-1);
    }
  }
  void switch_formating(){

    printf("=================== File Formating ================================\n");
    printf("Enter File name (Max 10 Bytes long)\n");
    scanf("%10s", fileName); // If file_name holds a memory of 10 bytes

    int diskFile = openDisk(fileName, FILE_SIZE * 1);

    if(diskFile != -1){
      printf("File %s opened for formatting\n\n\n", fileName);
      formatDisk(fileName);
      syncDisk();
      closeDisk(); 
      printf("Formatting completed.\n\n\n");
    }else{
      printf("Info: Exiting main thread.\n");
      exit(-1);
    }
  }
  void switch_viewing(){

    printf("=================== View File ================================\n");
    printf("Enter File name (Max 10 Bytes long)\n");
    scanf("%10s", fileName); // If file_name holds a memory of 10 bytes

    int c;
    FILE *file;
    file = fopen(fileName, "r");
    if (file) {
      printf("\n\n\n+++++++++++++++++++ Begin ++++++++++++++++++++\n\n\n");
      while ((c = getc(file)) != EOF)
        putchar(c);
      fclose(file);
      printf("\n\n\n+++++++++++++++++++ EndOF ++++++++++++++++++++\n");
    }else{
      printf("Info: Exiting main thread.\n");
      exit(-1);
    }
  }

  void switch_exiting(){

    printf("=================== Nothing to Do ================================\n");
    printf("You made no selection therefor exiting.\n");
    exit(-1);
  }

  printf("main thread started..!\n");

  printf("'R' for Reading\n'W' for Writing\n'F' for Formatting\n'V' for View whole file\n");
  scanf("%1s", disk_operation); // If disk_operation holds a memory of 1 byte
  clrscr(); // clear screen after user enter section
  switch(tolower(*disk_operation)) {

    case 'r' :	/* switch to reading mode */
      switch_reading();
      break; 

    case 'w' :	/* switch to writing mode */
      switch_writing();
      break; 

    case 'f' :	/* switch to format mode */
      switch_formating();
      break; 

    case 'v' :	/* switch to view file mode */
      switch_viewing();
      break; 

      /* you can have any number of case statements */
    default : 
      switch_exiting();
  }
  return 0;
}
/* ================ End Main Function ================ */
