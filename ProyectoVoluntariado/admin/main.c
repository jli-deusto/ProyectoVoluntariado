/*
 * main.c
 *
 *  Created on: 19 mar 2026
 *      Author: j.li
 */

#include <stdio.h>
#include <stdlib.h>
#include "config/config_sistema.h" // to read admin.conf
#include "guardar/admin_data_manager.h" // to open DB
#include "ui/menu.h"
#include "shared/constantes.h"
// 1. read admin.conf

//2. open data base

// 3. create database if tables do not exist

// 4. show the principal menu


int main() {
    menu_principal();
    return 0;
}
