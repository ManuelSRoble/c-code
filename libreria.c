#include <stdio.h>
#include <string.h>
// Los datos se deben de consultar, editar y modificar en un archivo(txt).? preguntar

//estructura para libros
struct libro{
    char nombre[100];
    char autor[100];
    int cantidad;
};

//estructura para reservas
struct reserva{
    char usuario[100];
    char nombreLibro[100];
    char fechaReserva[15];
    char fechaRegreso[15];
    float costo;
};

//icono de la biblioteca
void icono(){ //icono que representa un libro abierto

    printf("   #######################\n");
    printf("   ###### ##### ###### ###\n");
    printf("   ##### ##### ######  ###\n");
    printf("   #### ##### ######  ####\n");
    printf("   #### ##### ###### #####\n");
    printf("   #######################\n\n");
}

//funcion para agregar libro a stock
//no necesita retornar valores ya que modifica en el espacio de memoria los parametros que recibe
void agregarLibro(struct libro *libros, int *numLibros)
{

    printf("Nombre del libro: ");
    scanf("%s", libros[*numLibros].nombre); // en el array libros en la posicion numLibros, en el campo nombre
    printf("Autor: ");
    scanf("%s", libros[*numLibros].autor); // guarda el autor en el array libros en la posicion numLibros
    printf("Cantidad: ");
    scanf("%d", &libros[*numLibros].cantidad);
    (*numLibros)++; //incrementa el contador de libros en uno

    //char resultado[100];
    //libros[*numLibros].autor;
    //strcat(resultado, libros[*numLibros].autor);//concatena

    //abrir y leer
    FILE *archivo;
    archivo = fopen("libreria.txt", "a");

    if (archivo != NULL){ // si el archivo se abrio correctamente
      //Escribe en el archivo nombre, autor y cantidad del libro
      fprintf(archivo, "Nombre: %s\nAutor: %s\nCantidad: %d\n\n", libros[*numLibros - 1].nombre, libros[*numLibros -1].autor, libros[*numLibros -1].cantidad);
      fclose(archivo);
    } else {
      printf("Error al abrir el archivo"); //Imprime un mesaje si ocurrio un error al abrir el archivo
    }

    //char texto[1000]; // Variable para almacenar el contenido del archivo
    //printf(resultado);
    // Abre el archivo en modo lectura

    // "Nombre: %s\nAutor: %s\nCantidad: %f\n\n", libros[i].nombre, libros[i].autor, libros[i].cantidad);
    //fprintf(archivo, resultado);

}


void agregarReserva(struct reserva *reservas, int *numReservas, struct libro *libros, int *numLibros) {
    printf("Nombre de usuario: ");
    scanf("%s", reservas[*numReservas].usuario);

    printf("Nombre del libro: ");
    scanf("%s", reservas[*numReservas].nombreLibro);

    printf("Fecha reserva: ");
    scanf("%s", reservas[*numReservas].fechaReserva);

    printf("Fecha regreso: ");
    scanf("%s", reservas[*numReservas].fechaRegreso);

    printf("Costo: ");
    scanf("%f", &reservas[*numReservas].costo);

    (*numReservas)++;

    FILE *archivoReservas = fopen("reservas_de_la_libreria.txt", "a");
    if (archivoReservas != NULL) {
        for (int i = 0; i < *numLibros; i++) {
            if (strcmp(reservas[*numReservas - 1].nombreLibro, libros[i].nombre) == 1) { //0false 1true
                fprintf(archivoReservas, "Usuario: %s\nLibro: %s\nFecha de reserva: %s\nFecha de regreso: %s\nCosto: %.2f\n\n",
                        reservas[*numReservas - 1].usuario, reservas[*numReservas - 1].nombreLibro, reservas[*numReservas - 1].fechaReserva,
                        reservas[*numReservas - 1].fechaRegreso, reservas[*numReservas - 1].costo);

                fclose(archivoReservas);

                FILE *archivoLibreria = fopen("libreria.txt", "w");
                if (archivoLibreria != NULL) {
                    libros[i].cantidad--;
                    fprintf(archivoLibreria, "Nombre: %s\nAutor: %s\nCantidad: %d\n\n",
                            libros[*numLibros - 1].nombre, libros[*numLibros - 1].autor, libros[*numLibros - 1].cantidad);
                    fclose(archivoLibreria);
                } else {
                    printf("Error al abrir el archivo de librería");
                }

            } else {
                printf("No hay un libro con el nombre de: %s", reservas[*numReservas - 1].nombreLibro);
            }
        }
    } else {
        printf("Error al abrir el archivo /al agregar reserva/");
    }
}
/*
//funcion para agregar reserva de un libro
void agregarReserva(struct reserva *reservas, int *numReservas, struct libro *libros, int *numLibros){
    printf("Nombre de usuario: ");
    scanf("%s", reservas[*numReservas].usuario); // guardar el nombre del usuario en el array reservas en la posicion numReservas

    printf("Nombre del libro: ");
    scanf("%s",reservas[*numReservas].nombreLibro);

    printf("Fecha reserva: ");
    scanf("%s", reservas[*numReservas].fechaReserva);

    printf("Fecha regreso: ");
    scanf("%s", reservas[*numReservas].fechaRegreso);

    printf("Costo: ");
    scanf("%f", &reservas[*numReservas].costo);

    (*numReservas)++;

    //guardar reserva en el archivo de reservas
    FILE *archivo = fopen("reservas_de_la_libreria.txt", "a");

    if (archivo != NULL) {
      for(int i=0; i< *numLibros; i++){
         if (reservas[*numReservas-1].nombreLibro == libros[i].nombre){
            //escribe en el archivo el usuario, nombre del libro, fecha de reserva, fecha de regreso y el costo de usarlo
            fprintf(archivo, "Usuario: %s\nLibro: %s\nFecha de reserva: %s\nFecha de regreso: %s\nCosto: %.2f\n\n",reservas[*numReservas - 1].usuario, reservas[*numReservas-1].nombreLibro, reservas[*numReservas -1].fechaReserva, reservas[*numReservas -1].fechaRegreso, reservas[*numReservas -1].costo);
            fclose(archivo);// cerrar el archivo una vez que se ha escrito todas las reservas

            //descontar el libro reservado del stock
                FILE *archivo;
                archivo = fopen("libreria.txt", "w");

                if (archivo != NULL){ // si el archivo se abrio correctamente
                  //Escribe en el archivo nombre, autor y cantidad del libro
                  fprintf(archivo, "Nombre: %s\nAutor: %s\nCantidad: %d\n\n", libros[*numLibros - 1].nombre, libros[*numLibros -1].autor, libros[*numLibros -1].cantidad);
                  fclose(archivo);
                } else {
                  printf("Error al abrir el archivo"); //Imprime un mesaje si ocurrio un error al abrir el archivo
                }

         }else {
            printf("No hay un libro con el nombre de: %s",reservas[*numReservas-1].nombreLibro);
         }
      }
    } else {
      printf("Error al abrir el archivo /al agregar reserva/");
    }
}               */

// Funcion para ver libros disponibles en stock
void verLibros(struct libro *libros, int numLibros)
{
    printf("Libros disponibles en stock: \n");
    FILE *archivo;
    archivo = fopen("libreria.txt","r");
    char linea[100];

    while(fgets(linea, sizeof(linea), archivo) != NULL){
        printf("%s",linea);
    }
    /*
    for (int i = 0; i< numLibros; i++)
    {
        printf("Nombre: %s\nAutor: %s\nCantidad: %f\n\n", libros[i].nombre, libros[i].autor, libros[i].cantidad);
    }*/
}

//funcion para ver reservas de libros
void verReservas(struct reserva *reservas, int numReservas)
{
    FILE *archivo = fopen("reservas_de_la_libreria.txt","r");

    if (archivo != NULL) {
        printf("Reservas de libros: \n");

        // Leer y mostrar cada reserva del archivo
        while (fscanf(archivo, "Usuario: %s\nLibro: %s\nFecha de reserva: %s\nFecha de regreso: %s\nCosto: %f\n\n",
                  reservas[numReservas].usuario, reservas[numReservas].nombreLibro, reservas[numReservas].fechaReserva, reservas[numReservas].fechaRegreso, &reservas[numReservas].costo) != EOF) {
            printf("Usuario: %s\nLibro: %s\nFecha de reserva: %s\nFecha de regreso: %s\nCosto: %.2f\n\n",
                  reservas[numReservas].usuario, reservas[numReservas].nombreLibro, reservas[numReservas].fechaReserva, reservas[numReservas].fechaRegreso, reservas[numReservas].costo);
            numReservas++;
        }
        fclose(archivo);
    } else {
        printf("No se pudo abrir el archivo de reservas.\n");
    }
    /*ver linea por linea el archivo reservas de la libreria
    printf("Reservas de libros:\n");
    FILE *archivo;
    archivo = fopen("reservas_de_la_libreria.txt","r");
    char linea[100];

    while(fgets(linea, sizeof(linea), archivo) != NULL){
        printf("%s",linea);
    }
    fclose(archivo);*/

    /*
    for(int i=0; i<numReservas; i++)
    {
        pritnf();
        printf("Usuario: %s\nNombre del libro: %s\nFecha de reserva: %s\nFecha de regreso: %s\nCosto: %.2f\n\n",
               reservas[i].usuario, reservas[i].nombreLibro, reservas[i].fechaReserva, reservas[i].fechaRegreso, reservas[i].costo);
    }
*/
}
void borrar() {
    printf("\033[2J\033[H"); // Código de escape ANSI para limpiar la pantalla
    fflush(stdout); // Limpiar el buffer de salida
}

void esperar_enter() {
    printf("Presiona 's' y luego 'enter' para volver al menu...\n");

    char tecla = 'n';
    while (tecla != 's') { // 13 es el valor ASCII de "Enter"
        tecla = getchar();
    }
    borrar();
}

int main()
{
    struct libro libros[100]; //array con capacidad de 100 libros
    struct reserva reservas[100];
    int numLibros=0, numReservas=0, opcion;

    do
    {
        icono();
        printf("----- Biblioteca ----- \n");
        printf("1. Agregar libro al stock\n");
        printf("2. Agregar reserva de libro\n");
        printf("3. Ver libros disponibles en stock\n");
        printf("4. Ver reservas de libros\n");
        printf("5. Salir\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
        case 1:
            agregarLibro(libros, &numLibros); //envio el array con los libros y la direccion de memoria de numero de libros para que la pueda modificar
            break;
        case 2:
            agregarReserva(reservas, &numReservas, libros, &numLibros);
            break;
        case 3:
            verLibros(libros, numLibros);
            break;
        case 4:
            verReservas(reservas, numReservas);
            break;
        case 5:
            printf("vuelva pronto!!\n\n");
            break;
        default:
            printf("Opcion no valida");
        }//switch
        // si elige salir (5) no espera a que se ingrese 's'
        if (opcion != 5)
            esperar_enter(); //para que muestre el resultado de la opcion ingresada y espere a que el usuario quiera salir
    }
    while(opcion != 5);
/*    //abrir y leer
    FILE *archivo;
    char texto[1000]; // Variable para almacenar el contenido del archivo

    // Abre el archivo en modo lectura
    archivo = fopen("archivo.txt", "a");// r

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    // Lee el contenido del archivo y lo guarda en la variable 'texto'
    fgets(texto, 1000, archivo);

    // Muestra el contenido leido del archivo
    printf("Contenido del archivo:\n%s\n", texto);

    // Cierra el archivo despues de usarlo
    fclose(archivo);

    */
    return 0;
}
