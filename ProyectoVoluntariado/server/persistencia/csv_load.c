

#include "csv_load.h"
#include "repo_usuario.h"
#include "repo_actividad.h"
#include "repo_reserva.h"
#include "repo_noticia.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <limits.h>
#include <unistd.h>

#include "shared/modelo_noticia.h"
#include "shared/modelo_reserva.h"
#include "shared/modelo_actividad.h"
#include "shared/modelo_user.h"


//----------------------- CARGAR USUARIOS -----------------------
void cargar_usuarios_csv(sqlite3 *db, const char *ruta) {
//	printf("Intentando abrir: %s\n", ruta);
//	fflush(stdout);


	FILE *f = fopen(ruta, "r");
    if (!f) {
    	printf("No se pudo abrir %s\n", ruta);
    	fflush(stdout);

        return;
    }

    char linea[512];
    fgets(linea, sizeof(linea), f); //saltar cabecera

    while (fgets(linea, sizeof(linea), f)) {

//    	printf("LINEA LEIDA RAW: [%s]\n", linea);

    	linea[strcspn(linea, "\r\n")] = 0;
//
//    	int len = strlen(linea);
//    	while (len > 0 && (linea[len-1] == ' ' || linea[len-1] == '\t' || linea[len-1] == '\r')) {
//    	    linea[--len] = 0;
//    	}

    	if (strlen(linea) == 0) continue;

        char *campos[7] = {0};
        int idx = 0;

        char *p = linea;
        char *inicio = p;

        while (*p && idx < 7) {
            if (*p == ',') {
                *p = 0;
                campos[idx++] = inicio;
                inicio = p + 1;
            }
            p++;
        }
        campos[idx++] = inicio;

        char *nombre = campos[0];
        char *tlf    = campos[1];
        char *mail   = campos[2];
        char *pw     = campos[3];
        char *rol    = campos[4];
        char *estado = campos[5];
        char *fecha  = campos[6];

    	if (!nombre || !mail || !pw || !rol || !estado) {
    	    printf("ERROR: línea CSV mal formada: %s\n",  nombre ? nombre : "(sin nombre)");
    	    continue;
    	}

        User u;
        strcpy(u.nombre, nombre);
        strcpy(u.tlf, tlf);
        strcpy(u.mail, mail);
        strcpy(u.pw, pw);
        u.rol = atoi(rol);
        u.estado_cuenta = atoi(estado);
        strcpy(u.fecha_reg, fecha);

        repo_usuario_insert(db, &u);
    }
//    printf("usuarios.csv abierto y cargado");

    fclose(f);
}


//----------------------- CARGAR ACTIVIDADES -----------------------
void cargar_actividades_csv(sqlite3 *db, const char *ruta) {
//	printf("Intentando abrir: %s\n", ruta);
//	fflush(stdout);

	FILE *f = fopen(ruta, "r");
    if (!f) {
        printf("No se pudo abrir %s\n", ruta);
        return;
    }

    char linea[512];
    fgets(linea, sizeof(linea), f);

    while (fgets(linea, sizeof(linea), f)) {

    	char *titulo = strtok(linea, ",");
        char *max_plazas = strtok(NULL, ",");
        char *ubicacion = strtok(NULL, ",");
        char *descripcion = strtok(NULL, ",");
        char *hora_init = strtok(NULL, ",");
        char *hora_fin = strtok(NULL, ",");
        char *tipo = strtok(NULL, ",");
        char *fecha = strtok(NULL, "\n");

        Actividad a;
        strcpy(a.titulo, titulo);
        a.max_plazas = atoi(max_plazas);
        strcpy(a.ubicacion, ubicacion);
        strcpy(a.descripcion, descripcion);
        strcpy(a.hora_init, hora_init);
        strcpy(a.hora_fin, hora_fin);
        strcpy(a.tipo, tipo);
        strcpy(a.fecha, fecha);

        repo_actividad_insert(db, &a);
    }
//    printf("actividades.csv abierto y cargado");
    fclose(f);
}


//----------------------- CARGAR RESERVAS -----------------------
void cargar_reservas_csv(sqlite3 *db, const char *ruta) {
    FILE *f = fopen(ruta, "r");
    if (!f) {
        printf("No se pudo abrir %s\n", ruta);
        return;
    }

    char linea[512];
    fgets(linea, sizeof(linea), f);

    while (fgets(linea, sizeof(linea), f)) {

    	char *estado = strtok(linea, ",");
        char *fecha = strtok(NULL, ",");
        char *id_usuario = strtok(NULL, ",");
        char *id_actividad = strtok(NULL, "\n");

        Reserva r;
        r.estado = atoi(estado);
        strcpy(r.fecha, fecha);
        r.id_usuario = atoi(id_usuario);
        r.id_actividad = atoi(id_actividad);

        repo_reserva_insert(db, &r);
    }

    fclose(f);
}


//----------------------- CARGAR NOTICIAS -----------------------
void cargar_noticias_csv(sqlite3 *db, const char *ruta) {
    FILE *f = fopen(ruta, "r");
    if (!f) {
        printf("No se pudo abrir %s\n", ruta);
        return;
    }

    char linea[512];
    fgets(linea, sizeof(linea), f);

    while (fgets(linea, sizeof(linea), f)) {

        char *titulo = strtok(linea, ",");
        char *descripcion = strtok(NULL, ",");
        char *fecha = strtok(NULL, ",");
        char *id_usuario = strtok(NULL, "\n");

        Noticia n;
        strcpy(n.titulo, titulo);
        strcpy(n.contenido, descripcion);
        strcpy(n.fecha_pub, fecha);
        n.id_usuario = atoi(id_usuario);

        repo_noticia_insert(db, &n);
    }

    fclose(f);
}

