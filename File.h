/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   File.h
 * Author: marioandre
 *
 * Created on 29 de Junho de 2017, 15:57
 */

#ifndef FILE_H
#define FILE_H


#include <string.h>

//#include "FileSystem.h"

class File {
    public:
    File(char * file_name); // para ser chamado apenas pelo FileSystem
    ~File(); // deve fechar o arquivo

    int read(void * buf, size_t bytes); // lê no máximo 'bytes' bytes do arquivo e armazena em 'buf'
    int write(void * buf, size_t bytes); // escreve 'bytes' bytes de 'buf' para o arquivo
    int size(); // retorna o tamanho do arquivo
    int lseek(int offset); // move o apontador do arquivo de acordo com o parâmetro offset (offset pode ser negativo)
    private:

};

#endif /* FILE_H */

