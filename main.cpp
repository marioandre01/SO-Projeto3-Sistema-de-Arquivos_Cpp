/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: marioandre
 *
 * Created on 7 de Junho de 2017, 08:44
 */

#include <iostream>
//#include "VirtualDisk.h"
#include "FileSystem.h"

using namespace std;

/*
 * 
 */
int main() {
    char * fs1 = (char *) "Disco_1"; //utilizando Typecast para converter string em char *
    FileSystem::create_file_system(fs1);
    
    FileSystem * f1 = FileSystem::instance();
    char * arq1 = (char * )"arq1";
    f1->create_file(arq1);
    
    
    return 0;
}

