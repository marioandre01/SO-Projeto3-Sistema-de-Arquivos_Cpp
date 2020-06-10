/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileSystem.cpp
 * Author: marioandre
 * 
 * Created on 29 de Junho de 2017, 15:40
 */

#include "FileSystem.h"
//#include "VirtualDisk.h"

//FileSystem::FileSystem() {
//}

//FileSystem::FileSystem(){
    
//}

FileSystem * FileSystem::_fs;

FileSystem::FileSystem(char * disk_name): _disk(disk_name){ 
    _disk.create_disk(disk_name); //monta o disco
}

int FileSystem::create_file_system(char * disk_name){
    
    int disk_blocks = VirtualDisk::BLOCK_SIZE;
    int block_size = VirtualDisk::DISK_BLOCKS;
    
    char buf[VirtualDisk::BLOCK_SIZE];
    
    VirtualDisk::create_disk(disk_name); //Criar disco virtual
    
    _fs = new FileSystem(disk_name); //instanciar um objeto FileSystem e fazer _fs apontar para ele
    
    //VirtualDisk dv(disk_name); // Abri o Disco Virtual
   
    
    super_block * sp = new super_block;
    
	sp->dir_inicio = 1;
	sp->dir_tamanho = 64;//BLOCK_SIZE/4 + 1;
	sp->fat_inicio = 64;
        sp->fat_tamanho = 8;
        sp->data_inicio = 4096; 
        
        
        
        // write super block to block 0 of the disk
	memset(buf,0,sizeof(buf));
        memcpy(buf,&sp,sizeof(sp));
        //cout << "sp: " << sizeof(sp) << endl;
        
        
        //ler conteudo do buffer
        /*super_block * s;
        //cout << "fat-ini: " << s->fat_inicio << endl;
        memcpy(&s,&buf,sizeof(s));
        cout << "fat-ini2: " << s->fat_inicio << endl;
        cout << "fat-tam2: " << s->fat_tamanho << endl;
        */
        //#################################################
        //escrever super bloco no bloco 0 do disco
	_fs->_disk.write_block(0,buf);
        
    tabela_diretorio * td = new tabela_diretorio; 
    
    td->usado = 0;
    //fsd->nome = "arq";
    td->tamanho = 0;
    td->head = 0;
    td->ref_cnt = 0;
    
    // Escreve tabela de diretorios nos blocos 1 a 64 do disco
	memset(buf,0,sizeof(buf));
        memcpy(buf,&td,sizeof(td));
        //cout << "td: " << sizeof(sp) << endl;
	for(int i = sp->dir_inicio; i < sp->dir_tamanho; i++){
            _fs->_disk.write_block(i,buf);
        }
    
    //-1:free
    //-2:Eof
    //-3:Sistema
    //Criando tabela FAT    
    int32_t fat[VirtualDisk::DISK_BLOCKS];
    //cout << sizeof(fat) << endl;
    
    //setando posições que representam arquivos do sistema
    int bloc_fimArqSys = sp->fat_inicio +sp->fat_tamanho;
    
    for(int j=0; j < bloc_fimArqSys; j++){
        fat[j] = -3; // -3 representa bloco com configuração do sistema
    }
    
    //setando blocos restantes como livres
    int bloc_comecoArqLivres = sp->fat_inicio +sp->fat_tamanho;
     
    for(int k=bloc_comecoArqLivres; k < VirtualDisk::DISK_BLOCKS; k++){
        fat[k] = -1; // -1 representa bloco livre - free
    }
    
    //Escrevendo a fat no disco
    //cout << "t:" << sizeof(int32_t) << endl;
        
	for(int l = 0; l < sp->fat_tamanho; l++){
            memset(buf,0,sizeof(buf));
            memcpy(buf,&fat[l*sizeof(buf)/sizeof(int32_t)],sizeof(buf));
            _fs->_disk.write_block(sp->fat_inicio + l,buf);
            //cout << l << endl;
        }
    
    
	//dv.~VirtualDisk();
	cout << "file system created successfully" << endl;
	return 0;
     //*/
    
   
   
}

int FileSystem::create_file(char * file_name){
    char buf[VirtualDisk::BLOCK_SIZE];
    
    memset(buf,0,sizeof(buf));
    _fs->_disk.read_block(0,buf);
    
    super_block * s;
        
    memcpy(&s,&buf,sizeof(buf));
    cout << "dir-ini: " << s->dir_inicio << endl;
    int ibd = s->dir_inicio;
    
    memset(buf,0,sizeof(buf));
    _fs->_disk.read_block(ibd,buf);
    
    tabela_diretorio * td1;
        
    memcpy(&td1,&buf,sizeof(buf));
    cout << "td1-nome: " << td1->nome << endl;
    //td1->nome = file_name;
    strcpy(td1->nome,file_name);
    
    
    cout << "nome arq1: " << file_name << endl;
    cout << "td1-nome: " << td1->nome << endl;
        
    
    
}

int FileSystem::delete_file(char * file_name){
    
}

FileSystem::~FileSystem() {
}

