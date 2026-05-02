/*
 * contraseña.c
 *
 *  Created on: 19 mar 2026
 *      Author: j.li
 */

#include "contrasena.h"
#include <stdio.h>

unsigned long hash_djb2(const char *str) {
    unsigned long h = 5381;
    int c;
    while ((c = *str++))
        h = ((h << 5) + h) + c;
    return h;
}

void hashear_password(const char *pw, char *dest, size_t n){
    unsigned long h = hash_djb2(pw);
    snprintf(dest, n, "%016lx", h);
}
