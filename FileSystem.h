/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileSystem.h
 * Author: marioandre
 *
 * Created on 29 de Junho de 2017, 15:40
 */

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "VirtualDisk.h"
#include <string.h>
#include <iostream>
#include <stdint.h>
using namespace std;

//--------------------------------------------------------------
///*
#define MAX_F_NAME 64
#define MAX_FILES 40
#define MAX_FILEDES 32
#define MAX_FILE_SIZE 16384 // expressed in KB 16MB file which will occupy 4096 blocks of 4 KB each
#define READ 0
#define WRITE 1

//--------------------------------------------------------------
struct super_block{
 
  // FAT information
  int32_t fat_inicio; // Inicio da tabela FAT no bloco
  int32_t fat_tamanho; // Tamanho da tabela FAT
  // directory information
  int32_t dir_inicio; //
  int32_t dir_tamanho; //
  // data information
  int32_t data_inicio; //
};
//*/
//--------------------------------------------------------------

struct tabela_diretorio	//it stores the information of a file
{
  int usado;

  char nome[MAX_F_NAME + 1];	//file name
  //char * nome;
  int tamanho;	//file size

  int head;	//first data block of this file
  int ref_cnt;	//how many file descriptors this entry is using, if ref_cnt > 0 we cannot delete this file
};
//--------------------------------------------------------------
/*struct file_descriptor
{
  int used;	// file descriptor is in use
  int file;		// the first block of current file who uses this file descriptor
  off_t offset;	
};
//--------------------------------------------------------------
struct super_block * fs;
struct file_descriptor fildes[MAX_FILEDES];		//MAX_FILDES=32
struct dir_entry * DIR;	// a queue of directories
int *FAT;		// a queue
*/
//--------------------------------------------------------------

//struct super_block * fs;



class FileSystem {
private:
    FileSystem(char * disk_name);

public:
    //FileSystem();
    static int create_file_system(char * disk_name);

    ~FileSystem();

    int create_file(char * file_name);
    int delete_file(char * file_name);

    static FileSystem * instance() { return _fs; }

    VirtualDisk * disk() { return &_disk; }
    

private:
    VirtualDisk _disk;
    static FileSystem * _fs;
    
};

#endif /* FILESYSTEM_H */

