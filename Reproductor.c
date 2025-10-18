// Este codigo es un reworked del proyecto que realizamos mi compañero Neftalí y yo
// El codigo consiste en un "Reproductor de musica" donde pudes guardar, mostrar o eliminar canciones
// El codigo se puede optimizar mas, yo se.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LONTITULO 100
#define LONINTERPRETE 100
#define MAXDISCOS 1000

void mostrarMenu();
int AltaDisc(struct Coleccion *);
void MostrarDiscs(struct Coleccion *);
void MostrarDiscMayorDuracion(struct Coleccion *);
void BuscarPorTitulo(struct Coleccion *);
void MostrarDiscosArtista(struct Coleccion *);
void EliminarCdPorTitulo(struct Coleccion *);
void AbrirArchivo(struct Coleccion *);
void GuardarArchivo(struct Coleccion *);

struct Tiempo {
    int horas;
    int minutos;
};

struct CompactDisc{
    char titulo[LONTITULO+1];
    char interprete[LONINTERPRETE+1];
    struct Tiempo duracion;
    int anio;
};

struct Coleccion{
    struct CompactDisc cd[MAXDISCOS];
    int cantidad;
};

int main() {
    struct Coleccion mis_cds = { .cantidad = 0 };
    int opcion = 0;
    AbrirArchivo(&mis_cds);
    mostrarMenu();
    while (opcion != 7){
        printf("Elige una opcion: ");
        scanf("%d", &opcion);
        getchar();
        switch(opcion){
            case 1:
                if (AltaDisc(&mis_cds))
                    printf("Disco guardado correctamente\n");
                else
                    printf("Error al guardar el disco\n");
                break;
            case 2:
                MostrarDiscs(&mis_cds);
                break;
            case 3:
                MostrarDiscMayorDuracion(&mis_cds);
                break;
            case 4:
                BuscarPorTitulo(&mis_cds);
                break;
            case 5:
                MostrarDiscosArtista(&mis_cds);
                break;
            case 6:
                break;
            case 7:
                GuardarArchivo(&mis_cds);
                printf("Hasta Pronto :D\n");
                break;
            default:
                printf("Elige una opcion valida\n");
                break;
        }
    }
    return 0;
}

void mostrarMenu(){
    printf("\t\t\tMenu\t\t\t\n"); 
    printf("1. Dar de alta un disco\n");
    printf("2. Mostrar discos en la collecion\n");
    printf("3. Mostrar el disco con mayor duracion\n");
    printf("4. Buscar un disco por titulo\n");
    printf("5. Mostrar discos de un artista\n");
    printf("6. Eliminar un disco\n");
    printf("7. Salir del programa\n");
}

int AltaDisc(struct Coleccion *mis_cds){
    char titulo[LONTITULO + 1];
    char interprete[LONINTERPRETE + 1];
    int lon_titulo = 0, lon_interprete = 0;
    if (mis_cds->cantidad == MAXDISCOS){
        printf("La coleccion de cds esta llena\n");
        return 0;
    }

    printf("Ingrese el titulo del disco: ");
    if (fgets(titulo, sizeof(titulo),stdin) == NULL){
        printf("El titulo no pude estar vacio\n");
        return 0;
    }
    lon_titulo = strlen(titulo);
    if(titulo[lon_titulo - 1] == '\n')
        titulo[lon_titulo - 1] = '\0';
    strcpy(mis_cds->cd[mis_cds->cantidad].titulo, titulo);

    printf("Ingrese el interprete del disco: ");
    if (fgets(interprete, sizeof(interprete), stdin) == NULL) {
        printf("El interprete no puede estar vacio\n");
        return 0;
    }
    lon_interprete = strlen(interprete);
    if(interprete[lon_interprete - 1] == '\n')
        interprete[lon_interprete - 1] = '\0';
    strcpy(mis_cds->cd[mis_cds->cantidad].interprete, interprete);

    printf("Ingrese la duracion del album en horas y minutos: ");
    scanf("%d %d", &mis_cds->cd[mis_cds->cantidad].duracion.horas, &mis_cds->cd[mis_cds->cantidad].duracion.minutos);
    printf("Ingrese el anio del album: ");
    scanf("%d", &mis_cds->cd[mis_cds->cantidad].anio);
    getchar();
    mis_cds->cantidad++;
    return 1;
}

void MostrarDiscs(struct Coleccion *mis_cds){
    int cantidad = mis_cds->cantidad;
    cantidad--;
    for(cantidad; cantidad >= 0; cantidad--){
        printf("Titulo del album: %s\n", mis_cds->cd[cantidad].titulo);
        printf("Interprete del album: %s\n", mis_cds->cd[cantidad].interprete);
        printf("Duracion del album: %d horas %d minutos\n", mis_cds->cd[cantidad].duracion.horas, mis_cds->cd[cantidad].duracion.minutos);
        printf("Anio de lanzamiento del album: %d\n", mis_cds->cd[cantidad].anio);
        printf("\n");
    }
}

void MostrarDiscMayorDuracion(struct Coleccion *mis_cds){
    int indice = -1;
    int mayor_duracion = 0;
    int duracion_total;

    for (int i = 0; i < mis_cds->cantidad; i++) {
        duracion_total = (mis_cds->cd[i].duracion.horas * 60) + mis_cds->cd[i].duracion.minutos;
        if (duracion_total > mayor_duracion) {
            mayor_duracion = duracion_total;
            indice = i;
        }
    }
    if(indice != -1){
        printf("Album con mayor duracion:\n");
        printf("Titulo del album: %s\n", mis_cds->cd[indice].titulo);
        printf("Interprete del album: %s\n", mis_cds->cd[indice].interprete);
        printf("Duracion del album: %d horas %d minutos\n", mis_cds->cd[indice].duracion.horas, mis_cds->cd[indice].duracion.minutos);
        printf("Anio de lanzamiento del album: %d\n", mis_cds->cd[indice].anio);
    }else
        printf("No hay albumes en la coleccion\n");
}

void BuscarPorTitulo(struct Coleccion *mis_cds){
    char titulo[LONTITULO + 1];
    printf("Ingrese el nombre del album a buscar: ");
    fgets(titulo, sizeof(titulo), stdin);
    int lon_titulo = strlen(titulo);
    if(titulo[lon_titulo - 1] == '\n')
        titulo[lon_titulo - 1] = '\0';
    int indice = mis_cds->cantidad;
    int indice_album = -1;
    for (int i = 0; i < indice; i++){
        if(strcmp(titulo, mis_cds->cd[i].titulo) == 0){
            indice_album = i;
            break;
        }
    }
    if (indice_album != -1){
        printf("Album encontrado:\n");
        printf("Titulo del album: %s\n", mis_cds->cd[indice_album].titulo);
        printf("Interprete del album: %s\n", mis_cds->cd[indice_album].interprete);
        printf("Duracion del album: %d horas %d minutos\n", mis_cds->cd[indice_album].duracion.horas, mis_cds->cd[indice_album].duracion.minutos);
        printf("Anio de lanzamiento del album: %d\n", mis_cds->cd[indice_album].anio);
    }else{
        printf("No se encontro el album");
    }
}

void MostrarDiscosArtista(struct Coleccion *mis_cds){
    int albumes_del_artista[20];
    int j = 0;
    int cantidad = mis_cds->cantidad;
    char nombre[LONINTERPRETE + 1];
    printf("Ingrese el nombre del artista a buscar: ");
    fgets(nombre, sizeof(nombre), stdin);
    int lon_nombre = strlen(nombre);
    if (nombre[lon_nombre - 1] == '\n')
        nombre[lon_nombre - 1] = '\0';
    for(int i = 0; i < cantidad; i++){
        if (strcmp(nombre, mis_cds->cd[i].interprete) == 0){
            albumes_del_artista[j] = i;
            j++;
        }
    }
    if (j != 0){
        for (int i = 0; i < j; i++) {
            int idx = albumes_del_artista[i];
            printf("Titulo del album: %s\n", mis_cds->cd[idx].titulo);
            printf("Interprete del album: %s\n", mis_cds->cd[idx].interprete);
            printf("Duracion del album: %d horas %d minutos\n", mis_cds->cd[idx].duracion.horas, mis_cds->cd[idx].duracion.minutos);
            printf("Anio de lanzamiento del album: %d\n", mis_cds->cd[idx].anio);
        }
    }else
        printf("No se encontraron albumes del artista");
}

void EliminarCdPorTitulo(struct Coleccion *mis_cds) {
    char titulo_a_eliminar[LONTITULO + 1];
    int indice_encontrado = -1;
    printf("Ingrese el titulo del disco que desea eliminar: ");
    fgets(titulo_a_eliminar, sizeof(titulo_a_eliminar), stdin);
    int longitud = strlen(titulo_a_eliminar);
    if (titulo_a_eliminar[longitud - 1] == '\n') {
        titulo_a_eliminar[longitud - 1] = '\0';
    }
    for (int i = 0; i < mis_cds->cantidad; i++) {
        if (strcmp(titulo_a_eliminar, mis_cds->cd[i].titulo) == 0) {
            indice_encontrado = i;
            break;               
        }
    }
    if (indice_encontrado != -1) {
        for (int i = indice_encontrado; i < mis_cds->cantidad - 1; i++) {
            mis_cds->cd[i] = mis_cds->cd[i + 1];
        }
        mis_cds->cantidad--;
        printf("El disco '%s' ha sido eliminado correctamente.\n", titulo_a_eliminar);
    } else {
        printf("No se encontro ningun disco con el titulo '%s'.\n", titulo_a_eliminar);
    }
}

void AbrirArchivo(struct Coleccion *mis_cds) {
    FILE *biblioteca = fopen("Biblioteca.txt", "r");
    if (biblioteca == NULL) {
        printf("Archivo Biblioteca.txt no encontrado. Se iniciara una coleccion vacia.\n");
        return;
    }
    fscanf(biblioteca, "%d\n", &mis_cds->cantidad);
    if (mis_cds->cantidad == 0) {
        fclose(biblioteca);
        return;
    }
    for (int i = 0; i < mis_cds->cantidad; i++) {
        fgets(mis_cds->cd[i].titulo, LONTITULO, biblioteca);
        mis_cds->cd[i].titulo[strcspn(mis_cds->cd[i].titulo, "\n")] = 0;
        fgets(mis_cds->cd[i].interprete, LONINTERPRETE, biblioteca);
        mis_cds->cd[i].interprete[strcspn(mis_cds->cd[i].interprete, "\n")] = 0;
        fscanf(biblioteca, "%d %d", &mis_cds->cd[i].duracion.horas, &mis_cds->cd[i].duracion.minutos);
        fscanf(biblioteca, "%d\n", &mis_cds->cd[i].anio);
    }
    fclose(biblioteca);
    printf("Coleccion cargada correctamente desde Biblioteca.txt (%d discos).\n", mis_cds->cantidad);
}

void GuardarArchivo(struct Coleccion *mis_cds) {
    FILE *biblioteca = fopen("Biblioteca.txt", "w"); 

    if (biblioteca == NULL) {
        printf("Error: No se pudo abrir el archivo para guardar.\n");
        return;
    }
    fprintf(biblioteca, "%d\n", mis_cds->cantidad);
    for (int i = 0; i < mis_cds->cantidad; i++) {
        fprintf(biblioteca, "%s\n", mis_cds->cd[i].titulo);
        fprintf(biblioteca, "%s\n", mis_cds->cd[i].interprete);
        fprintf(biblioteca, "%d %d\n", mis_cds->cd[i].duracion.horas, mis_cds->cd[i].duracion.minutos);
        fprintf(biblioteca, "%d\n", mis_cds->cd[i].anio);
    }
    fclose(biblioteca);
    printf("Coleccion guardada exitosamente en Biblioteca.txt\n");
}