#include <iostream>
#include <cstring>

#define CANTIDAD_MINIMA_LIBROS 1

struct Libro {
    int codigo;
    char nombre[50];
    char autor[50];
    char editorial[50];
    char tipo;
};

struct Genero {
    int codigo;
    char nombre[50];

};

void listarGenero(struct Genero[], int);

void insertar(struct Genero[], int &, Genero, int);

void insertar_ordenado(struct Genero[], int &, Genero);

void inicializarArray(struct Genero [], int, int, const char *);


int main() {
    FILE *biblioteca;
    FILE *drama;
    FILE *accion;
    FILE *terror;
    int cantidad_peliculas; //cantidad de registros a indicar por el usuario
    int cont = 0;
    struct Libro libro;


    biblioteca = fopen("biblioteca.dat", "wb");
    drama = fopen("drama.dat", "wb");
    accion = fopen("accion.dat", "wb");
    terror = fopen("terror.dat", "wb");


    do {
        std::cout << "Por favor ingresa la cantidad de libros (>=10): ";
        std::cin >> cantidad_peliculas;
    } while (cantidad_peliculas < CANTIDAD_MINIMA_LIBROS);

    while (cont < cantidad_peliculas) {
        std::cout << "Por favor ingresa los datos para la pelicula " << cont + 1 << "/" << cantidad_peliculas
                  << std::endl;

        std::cout << "codigo: ";
        std::cin >> libro.codigo;

        std::cout << "nombre: ";
        std::cin >> libro.nombre;

        std::cout << "autor: ";
        std::cin >> libro.autor;

        std::cout << "editorial: ";
        std::cin >> libro.editorial;

        //Validacion de tipo de pelicula.
        do {
            std::cout << "tipo (A = Accion, D = Drama , T = Terror): ";
            std::cin >> libro.tipo;
            libro.tipo = toupper(libro.tipo);

            if (libro.tipo != 'D' && libro.tipo != 'T' && libro.tipo != 'A') {

                std::cout << "Opcion incorrecta, por favor elija otra opcion tipo (A = Accion, D = Drama , T = Terror)"
                          << std::endl;
            }

        } while (libro.tipo != 'D' && libro.tipo != 'T' && libro.tipo != 'A');

        fwrite(&libro, sizeof(struct Libro), 1, biblioteca);

        cont++;
    }

    std::cout << std::endl << "--- FIN DE GENERACION DE ARCHIVO BIBLIOTECA.DAT ---" << std::endl;

    fclose(biblioteca);

    std::cout << "--- INICIO PROCESAMIENTO ARCHIVO BIBLIOTECA.DAT ---" << std::endl;


    struct Genero genero;

    struct Genero v_terror[cantidad_peliculas];
    struct Genero v_accion[cantidad_peliculas];
    struct Genero v_drama[cantidad_peliculas];

    inicializarArray(v_terror, cantidad_peliculas, 0, NULL);
    inicializarArray(v_accion, cantidad_peliculas, 0, NULL);
    inicializarArray(v_drama, cantidad_peliculas, 0, NULL);

    cont = 0;
    int cont_terror = 0;
    int cont_accion = 0;
    int cont_drama = 0;

    biblioteca = fopen("biblioteca.dat", "rb");
    fread(&libro, sizeof(struct Libro), 1, biblioteca);

    while (!feof(biblioteca)) {

        std::cout << "Procesando pelicula (" << ++cont << "/" << cantidad_peliculas << ")..." << std::endl;
        std::cout << "(tipo = " << libro.tipo
                  << ",autor = " << libro.autor
                  << ",nombre = " << libro.nombre
                  << ",codigo = " << libro.codigo
                  << ",editorial = " << libro.editorial
                  << ")"
                  << std::endl;


        genero.codigo = libro.codigo;
        strcpy(genero.nombre, libro.nombre);

        if (libro.tipo == 'D') {

            fwrite(&genero, sizeof(struct Genero), 1, drama);
            insertar(v_drama, cont_drama, genero, cont_drama);

        } else if (libro.tipo == 'A') {

            fwrite(&genero, sizeof(struct Genero), 1, accion);
            insertar(v_accion, cont_accion, genero, cont_accion);

        } else {

            insertar_ordenado(v_terror, cont_terror, genero);
        }

        fread(&libro, sizeof(struct Libro), 1, biblioteca);

    }

    fclose(biblioteca);
    fclose(drama);
    fclose(accion);
    fclose(terror);

    std::cout << "--- FINALIZO EL PROCESAMIENTO DEL 'ARCHIVO BIBLIOTECA.DAT' ---" << std::endl;
    std::cout << "Usted desea ver el contenido de algun archivo (S/N)?." << std::endl;

    char respuesta_usario;
    std::cin >> respuesta_usario;

    if (toupper(respuesta_usario) == 'S') {

        do {
            std::cout << "Que listado desea ver?tipo (A = Accion, D = Drama , T = Terror, X para salir)" << std::endl;
            std::cin >> respuesta_usario;
            respuesta_usario = toupper(respuesta_usario);

            switch (respuesta_usario) {
                case 'A':
                    if (cont_accion == 0) {
                        std::cout << "No hay libros de accion para mostrar" << std::endl;
                    } else {
                        std::cout << "Listando los libros de Accion: " << std::endl;
                        listarGenero(v_accion, cont_accion);
                    }
                    break;
                case 'D':
                    if (cont_drama == 0) {
                        std::cout << "No hay libros de drama para mostrar" << std::endl;
                    } else {
                        std::cout << "Listando los libros de Drama: " << std::endl;
                        listarGenero(v_drama, cont_drama);
                    }

                    break;
                case 'T':
                    if (cont_terror == 0) {
                        std::cout << "No hay libros de terror para mostrar" << std::endl;
                    } else {
                        std::cout << "Listando los libros de Terror: " << std::endl;
                        listarGenero(v_terror, cont_terror);
                    }
                    break;
                case 'X':
                    std::cout << "Saliendo del programa... " << std::endl;
                    break;
                default:
                    std::cout << "Opcion incorrecta!" << std::endl;
                    break;
            }

        } while (respuesta_usario != 'X');


    }

    std::cout << "--- FIN DEL PROGRAMA --- " << std::endl;


    return 0;
}


/**
 * Muestra el listado de libros.
 * @param libros la lista de libros a mostrar.
 * @param longitud cantidad de elementos del vector.
 *
 */
void listarGenero(Genero libros[], int longitud) {

    for (int i = 0; i < longitud; ++i) {

        std::cout << i + 1 << "- " << "codigo = " << libros[i].codigo
                  << ",nombre = " << libros[i].nombre
                  << std::endl;

    }
}

/**
 * Inserta un elemento en un vector de manera ordenada.
 *
 * @param genero vecto de libros.
 * @param longitud longitud del vector.
 * @param nuevoGenero el genero a insertar.
 */
void insertar_ordenado(Genero genero[], int &longitud, Genero nuevoGenero) {

    int posicion = 0;

    while (genero[posicion].codigo < nuevoGenero.codigo && posicion < longitud) {
        posicion++;
    }

    if (posicion == longitud) {

        genero[longitud] = nuevoGenero;
        longitud++;
    } else {
        insertar(genero, longitud, nuevoGenero, posicion);
    }

}


/**
 * Inserta un elemento en un vector.
 *
 * @param genero vecto de libros.
 * @param longitud longitud del vector.
 * @param nuevoGenero el genero a insertar.
 * @param posicion posicion del elemento.
 *
 */
void insertar(Genero genero[], int &longitud, Genero nuevoGenero, int posicion) {


    for (int i = longitud; i > posicion; i--) {
        genero[i] = genero[i - 1];
    }

    genero[posicion] = nuevoGenero;
    longitud++;
}


/**
 * Inicializa un array con valores provistos.
 * @param genero el array de libros.
 * @param longitud longitud del array.
 * @param valor_default_codigo valor default para el codigo.
 * @param valor_default_nombre valor default para el nombre.
 */
void
inicializarArray(struct Genero genero[], int longitud, int valor_default_codigo, const char *valor_default_nombre) {

    for (int i = 0; i < longitud; ++i) {
        genero[i].codigo = valor_default_codigo;
    }

}
