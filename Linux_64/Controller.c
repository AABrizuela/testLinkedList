#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include "parser.h"
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "utn.h"

/** \brief Menu de opciones
 *
 * \return int La opcion elegida por el usuario
 *
 */
int menu()
{
    system("clear");
    int opcion;
    printf("   -- ABM DINAMICO-- \n\n");
    printf("-------------------------------------------------------------------------------\n\n");
    printf("1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n");
    printf("2. Cargar los datos de los empleados desde el archivo data.bin (modo binario).\n");
    printf("3. Alta de empleado\n");
    printf("4. Modificar datos de empleado\n");
    printf("5. Baja de empleado\n");
    printf("6. Listar empleados\n");
    printf("7. Ordenar empleados\n");
    printf("8. Guardar los datos de los empleados en el archivo data.csv (modo texto).\n");
    printf("9. Guardar los datos de los empleados en el archivo data.bin (modo binario).\n");
    printf("10. Limpiar la lista de empleados.\n");
    printf("11. Salir\n\n");
    printf("------------------------------------------------------------------------------\n");
    opcion = getValidInt("Ingrese opcion: ", "Error de ingreso, reintente.\n");
    return opcion;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
    int retorno = -1; //Variable que retorna la funcion (1 - TodoOK // 0 - Error)
    FILE* pArchivo; //Variable puntero al archivo
    if((pArchivo = fopen(path, "r")) != NULL) //Condicional, verifico si la lectura del archivo, si no retorna NULL accedo al parse_Employee
    {
        parser_EmployeeFromText(pArchivo, pArrayListEmployee); //Funcion parser empleados modo texto
    }
    else{ //Si retorna NULL no encontro el archivo, por lo tanto lo creo e informo que no se encontro y se creo uno nuevo
        if((pArchivo = fopen(path, "w")) != NULL){
            printf("\n --> No se encontro el archivo. Se creo uno nuevo con el nombre \"%s\"\n\n", path);
            retorno = 0; //Cambio el el valor del retorno
        }
    }
    return retorno; //Retorno a la varaible
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path, LinkedList* pArrayListEmployee)
{
    int retorno = -1; //Variable que retorna la funcion (1 - TodoOK // 0 - Error)
    FILE* pArchivo; //Variable puntero al archivo
    if((pArchivo = fopen(path, "rb")) != NULL) //Condicional, verifico si la lectura del archivo, si no retorna NULL accedo al parse_Employee
    {
        parser_EmployeeFromBinary(pArchivo, pArrayListEmployee); //Funcion parser empleados modo texto
    }
    else{ //Si retorna NULL no encontro el archivo, por lo tanto lo creo e informo que no se encontro y se creo uno nuevo
        if((pArchivo = fopen(path, "wb")) != NULL){
            printf("\n --> No se encontro el archivo. Se creo uno nuevo con el nombre \"%s\"\n\n", path);
            retorno = 0; //Cambio el el valor del retorno
        }
    }
    return retorno; //Retorno a la varaible
    return 1;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee)
{
    char auxId[128], auxNombre[128], auxHorasTrabajadas[128], auxSueldo[128]; //Variables buffer
    Employee* this = employee_new(); //Creo un nuevo empleado

    system("clear");
    __fpurge(stdin);
    printf(" *** ALTA DE EMPLEADO ***\n\n");
    getStringNumeros("Ingrese ID: ", auxId); //Solicito y valido el id (string)
    __fpurge(stdin);
    while(employee_ControlId(pArrayListEmployee, auxId)==1){ //Valido que el id ingresado no se encuentre dado de alta en sistema, de estar dado de alta pide uno nuevo
        printf("El ID ingresado ya se encuentra dado de alta en sistema. Reintente.\n\n");
        getStringNumeros("Ingrese ID: ", auxId); //Solicito y valido el id (string)
    }
    getValidStringRango("Ingrese nombre: ", "Error de ingreso, reintente.", auxNombre, 128); //Solicito y valido el nombre (string)
    __fpurge(stdin);
    getStringNumeros("Ingrese horas trabajadas: ", auxHorasTrabajadas); //Solicito y valido las horas trabajadas (string)
    __fpurge(stdin);
    getStringNumerosFlotantes("Ingrese sueldo: ", auxSueldo); //Solicito y valido el sueldo (string)
    __fpurge(stdin);
    this = employee_newParametros(auxId, auxNombre, auxHorasTrabajadas, auxSueldo);  //Le asigno a "this" las variables casteadas en la funcion
    ll_add(pArrayListEmployee, this); //Agrego "this" al final del array de empleados
    printf("\n      ID |      Nombre  | Hs. Trabajadas |     Sueldo\n\n");
    employee_printData(this);
    printf("\nEmpleado dado de alta con exito.\n\n");
    return 1;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = 0; //Variable que retorna la funcion (0 - TodoOK // 1 - Error)
    int flag = 0; //Bandera encontro usuario
    char confirmacion; //Variable confirmacion modificacion del empleado
    int idEmpleado; //Variable almacena id del empleado ingresado por teclado
    int opcion; //Almacena la opcion a modificar

    char auxNombre[51]; //Almacena el nombre ingresado por teclado
    int auxHorasTrabajadas; //Almacena las horas ingresadas por teclado
    float auxSueldo; //Almacena el sueldo ingresado por teclado

    int id; //Variable donde se almacena el id utilizando getId();
    char nombre[51]; //Variable donde se almacena el nombre utilizando getNobre();
    int horasTrabajadas; //Variable donde se almacenan las horas trabajadas utilizando getHorasTrabajadas();
    float sueldo; //Variable donde se almacena el sueldo utilizando getId();

    Employee* this; //Creo puntero a empleado

    system("clear");
    printf(" *** MODIFICAR EMPLEADO ***\n\n");
    idEmpleado = getValidInt("Ingrese ID: ", "Error de ingreso. Reintente."); //Pido y valido el id por teclado
    __fpurge(stdin);
    for(int i=0; i<ll_len(pArrayListEmployee); i++)  //Recorro el array de empleados
    {
        this = (Employee*)ll_get(pArrayListEmployee, i); //Le asigno a "this" lo que retorna "ll_get()"
        if(this->id == idEmpleado)  //Condicional, si this->id es igual al id ingresado por teclado muestro al empleado
        {
            flag = 1; //Cambio la bandera si encontre al empleado
            break; //Rompo la iteraccion para no volver a buscar
        }
    }
    if(flag == 1)  //Si encontre al empleado muestro un menu de opciones para modificar los datos
    {
        employee_getId(this, &id); //Obtengo el Id del empleado
        employee_getNombre(this, nombre); //Obtengo el nombre del empleado
        employee_getHorasTrabajadas(this, &horasTrabajadas); //Obtengo las horas trabajadas del empelado
        employee_getSueldo(this, &sueldo); //Obtengo el sueldo del empleado
        printf("\n     ID |      Nombre  | Hs. Trabajadas |     Sueldo\n\n");
        printf("   %4d | %12s |          %4d  | $ %.2f\n", id, nombre, horasTrabajadas, sueldo); //Muestro los datos del empleado
        printf("\n Menu de opciones ->\n\n1- Modificar nombre.\n2- Modificar horas trabajadas.\n3- Modificar sueldo.\n4- Salir.\n\n");
        opcion = getValidIntRango("Ingrese opcion: ", "Error de ingreso. Reintente.", 1, 4); //Solicito al usuario que ingrese una opcion
        __fpurge(stdin);
        switch(opcion)
        {
        case 1:
            printf("\nModificar nombre -->\n\n");
            getValidStringRango("Ingrese nuevo nombre: ", "Error, solo se admiten letras.\n", auxNombre, 51); //Solicito y valido el nuevo nombre
            printf("\n -> Se modificara \"%s\" por \"%s\"\n\n", auxNombre, nombre); //Muestro los cambios a realizar
            __fpurge(stdin);
            confirmacion = getValidChar("Confirma la modificacion (s/n)?: ", "\nError de ingreso. Reintente.\n", 's', 'n'); //Solicito confirmacion del cambio
            if(confirmacion == 's')  //Si la confirmacion es positiva hago un setNombre() e imprimo los datos nuevamente mostrando los cambios realizados
            {
                employee_setNombre(this, auxNombre);
                printf("Se modifico el nombre con exito.\n");
                printf("\n     ID |      Nombre  | Hs. Trabajadas |     Sueldo\n\n");
                employee_printData(this);
                retorno = 1; //Cambio el retorno a 1 para informar que el cambio fue positivo
            }
            else  //Si no se confirma el cambio se informa
            {
                printf("Se cancelo la modificacion del nombre.\n\n");
            }
            break;
        case 2:
            printf("\nModificar horas trabajadas -->\n\n");
            auxHorasTrabajadas = getValidIntRango("Ingrese las horas trabajadas: ", "Error, solo se admiten numeros.\n", 0, 500); //Solicito y valido las nuevas horas trabajadas
            printf("\n -> Se modificara \"%d\" por \"%d\"\n\n", auxHorasTrabajadas, horasTrabajadas); //Muestro los cambios a realizar
            __fpurge(stdin);
            confirmacion = getValidChar("Confirma la modificacion (s/n)?: ", "\nError de ingreso. Reintente.\n", 's', 'n'); //Solicito confirmacion del cambio
            if(confirmacion == 's')  //Si la confirmacion es positiva hago un setHorasTrabajadas() e imprimo los datos nuevamente mostrando los cambios realizados
            {
                employee_setHorasTrabajadas(this, auxHorasTrabajadas);
                printf("Se modificaron las horas trabajadas con exito.\n");
                printf("\n     ID |      Nombre  | Hs. Trabajadas |     Sueldo\n\n");
                employee_printData(this);
                retorno = 1; //Cambio el retorno a 1 para informar que el cambio fue positivo
            }
            else  //Si no se confirma el cambio se informa
            {
                printf("Se cancelo la modificacion de las horas.\n");
            }
            break;
        case 3:
            printf("\nModificar sueldo -->\n\n");
            auxSueldo = getValidFloat("Ingrese nuevo sueldo: ", "Error, solo se admiten numeros.\n"); //Solicito y valido nuevo sueldo
            printf("\n -> Se modificara \"%.2f\" por \"%.2f\"\n\n", auxSueldo, sueldo); //Muestro los cambios a realizar
            __fpurge(stdin);
            confirmacion = getValidChar("Confirma la modificacion (s/n)?: ", "\nError de ingreso. Reintente.\n", 's', 'n'); //Solicito confirmacion del cambio
            if(confirmacion == 's')  //Si la confirmacion es positiva hago un setSueldo() e imprimo los datos nuevamente mostrando los cambios realizados
            {
                employee_setSueldo(this, auxSueldo);
                printf("Se modifico el sueldo con exito.\n\n");
                printf("\n     ID |      Nombre  | Hs. Trabajadas |     Sueldo\n\n");
                employee_printData(this);
                retorno = 1; //Si no se confirma el cambio se informa
            }
            else  //Si no se confirma el cambio se informa
            {
                printf("Se cancelo la modificacion del sueldo.\n\n");
            }
            break;
        case 4: //Opcion de salida.
            break;
        default: //Si se ingresa una opcion incorracta se avisa al usuario.
            printf("\nUsted ingreso una opcion incorrecta.\n\n");
        }
    }
    else  //Si no existe el empleado con el id ingresado se informa.
    {
        printf("\nNo existe empleado con el ID ingresado.\n\n");
    }
    return retorno; //Retorno la variable a la funcion
}

/** \brief Baja de empleado
 *
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = 0; //Variable que retorna la funcion (1 - TodoOK // 0 - Error)
    int flag = 0; //Bandera existe empleado
    int index; //Indice del empelado
    char confirmacion; //Variable confirmacion baja empleado
    Employee* this; //Creo puntero a empleado
    int idEmpleado; //Variable almacena id del empleado ingresado por teclado
    system("clear");
    printf(" *** BAJA DE EMPLEADO ***\n\n");
    idEmpleado = getValidInt("Ingrese ID: ", "Error de ingreso. Reintente."); //Pido y valido el id por teclado
    for(int i=0; i<ll_len(pArrayListEmployee); i++)  //Recorro el array de empleados
    {
        this = (Employee*) ll_get(pArrayListEmployee, i); //Le asigno a "this" lo que retorna "ll_get()"
        if(this->id == idEmpleado)  //Condicional, si this->id es igual al id ingresado por teclado muestro al empleado
        {
            flag = 1; //Cambio la bandera para informar que lo encontre
            index = i; //asigno a index el valor del indice del empleado en el array
            break;
        }
    }
    if(flag == 1)
    {
        printf("\n      ID |      Nombre  | Hs. Trabajadas |     Sueldo\n\n");
        employee_printData(this);
        confirmacion = getValidChar("\nDesea eliminar al empleado (s/n)?: ", "\nError, ingreso un caracter no valido, reintente.", 's', 'n'); //Pido y valido confirmacion de baja
        if(confirmacion == 's') //Condicional, si confirma la baja
        {
            ll_remove(pArrayListEmployee, index); //Elimino al empleado del array
            printf("\nEmpleado dado de baja con exito.\n\n");
            retorno = 1; //Cambio la variable de retorno
        }
        else //De lo contrario informo que se cancelo la baja
        {
            printf("\nSe cancelo la baja del empleado\n\n");
        }
    }
    else
    {
        printf("\nNo existe empleado con el ID ingresado.\n");
    }
    return retorno; //Retorno a la funcion el valor de retorno
}

/** \brief Listar empleados
 *
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int retorno = 0; //Variable que retorna la funcion (1 - TodoOK // 0 - Error)
    Employee* this; //Creo puntero a empleado
    system("clear");
    printf(" *** LISTA DE EMPLEADOS ***\n\n");
    printf("      ID |      Nombre  | Hs. Trabajadas |     Sueldo\n\n");
    for(int i=0; i<ll_len(pArrayListEmployee); i++) //Recorro el array de empleados
    {
        this = (Employee*)ll_get(pArrayListEmployee, i); //Le asigno a "this" lo que retorna "ll_get()"
        employee_printData(this); //Imprimo los datos del empleado
        retorno = 1; //Cambio la variable
    }
    printf("\n");
    return retorno; //Retorno la variable a la funcion
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 *
 */
void controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    system("clear");
    int opcion; //Almacela la opcion de que tipo de ordenamiento se eligio
    int ordenLista; //Almacela la opcion del orden del array
    printf("  *** ORDENAR EMPLEADOS ***\n\n");
    printf(" Menu de opciones:\n\n");
    printf(" 1. Ordenar por ID.\n");
    printf(" 2. Ordenar por nombre.\n");
    printf(" 3. Ordenar por horas trabajadas.\n");
    printf(" 4. Ordenar por salario.\n");
    printf(" 5. Salir.\n\n");
    opcion = getValidInt(" Ingrese opcion: ", "Error de ingreso, reintente.\n");

    switch(opcion){
    case 1:
        system("clear");
        printf("\n Ordenamiento por ID -->\n");
        ordenLista = getValidIntOpcion("\n Ingrese 0 para ascendente y 1 para ordenar de forma descendente: ", "\nError de ingreso. Reintente.\n", 0, 1);
        ll_sort(pArrayListEmployee, employee_SortById, ordenLista);
        printf("\n  --> Se ordeno la lista por ID correctamente.\n\n");
        break;
    case 2:
        system("clear");
        printf("\n Ordenamiento por nombre -->\n");
        ordenLista = getValidIntOpcion("\n Ingrese 0 para ascendente y 1 para ordenar de forma descendente: ", "\nError de ingreso. Reintente.\n", 0, 1);
        ll_sort(pArrayListEmployee, employee_SortByName, ordenLista);
        printf("\n  --> Se ordeno la lista por nombre correctamente.\n\n");
        break;
    case 3:
        system("clear");
        printf("\n Ordenamiento por horas trabajdas -->\n");
        ordenLista = getValidIntOpcion("\n Ingrese 0 para ascendente y 1 para ordenar de forma descendente: ", "\nError de ingreso. Reintente.\n", 0, 1);
        ll_sort(pArrayListEmployee, employee_SortByHoursWorked, ordenLista);
        printf("\n  --> Se ordeno la lista por horas trabajadas correctamente.\n\n");
        break;
    case 4:
        system("clear");
        printf("\n Ordenamiento por salario -->\n");
        ordenLista = getValidIntOpcion("\n Ingrese 0 para ascendente y 1 para ordenar de forma descendente: ", "\nError de ingreso. Reintente.\n", 0, 1);
        ll_sort(pArrayListEmployee, employee_SortBySalary, ordenLista);
        printf("\n  --> Se ordeno la lista por salario correctamente.\n\n");
        break;
    case 5:
        break;
    default:
        printf("\nIngreso una opcion incorrecta.\n\n");
    }
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path, LinkedList* pArrayListEmployee)
{
    FILE* pArchivo; //Puntero al archivo
    Employee* this; //Creo puntero a estructura empleado
    int retorno = -1; //Variable retorno
    //Variables buffer -->
    char nombre[51];
    int id;
    int horasTrabajadas;
    float sueldo;
    //<---
    pArchivo = fopen(path, "w"); //Abro el archivo en modo escritura
    if(pArchivo != NULL && pArrayListEmployee != NULL) //Condicional, verifico que la apertura del archivo y el array de empelados no sea NULL, si no lo es ingreso
    {
        rewind(pArchivo); //Voy al inicio del archivo
        fprintf(pArchivo, "id,nombre,horasTrabajadas,sueldo\n"); //Escribo la primera linea en el archivo, el encabezado
        for(int i=0; i<ll_len(pArrayListEmployee); i++) //Recorro el array de empleados
        {
            this = (Employee*)ll_get(pArrayListEmployee, i); //Le asigno a "this" lo que retorna "ll_get()"
            employee_getId(this,&id); //Almaceno por referencia en id el valor que contiene la estructura en el campo id
            employee_getNombre(this, nombre); //Almaceno por referencia en nombre el valor que contiene la estructura en el campo nombre
            employee_getHorasTrabajadas(this, &horasTrabajadas); //Almaceno por referencia en horasTrabajadas el valor que contiene la estructura en el campo horasTrabajadas
            employee_getSueldo(this, &sueldo); //Almaceno por referencia en sueldo el valor que contiene la estructura en el campo sueldo
            fprintf(pArchivo, "%d,%s,%d,%f\n", id, nombre, horasTrabajadas, sueldo); //Almaceno en el archivo los datos del empelado
        }
        printf("\n --> Datos guardados con exito.\n\n");
        retorno = 0; //Cambio el valor de la variable que retorna la funcion
    }
    fclose(pArchivo); //Cierro el archivo
    return retorno; //Retorno el valor de la variable
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path, LinkedList* pArrayListEmployee)
{
    FILE* pArchivo; //Puntero al archivo
    Employee* this; //Creo puntero a estructura empleado
    int retorno = -1; //Variable retorno
    int datosLeidos;
    pArchivo = fopen(path, "wb"); //Abro el archivo en modo escritura binaria
    if(pArchivo != NULL && pArrayListEmployee != NULL) //Condicional, verifico que la apertura del archivo y el array de empelados no sea NULL, si no lo es ingreso
    {
        rewind(pArchivo); //Voy al inicio del archivo
        for(int i=0; i<ll_len(pArrayListEmployee); i++){ //Recorro el array de empleados
            this = (Employee*)ll_get(pArrayListEmployee,i); //Le asigno a "this" lo que retorna "ll_get()"
            datosLeidos = fwrite(this, sizeof(Employee), 1, pArchivo); //Le asigno a datosLeidos el valor que retorna la funcion
            retorno = 0; //Cambio el estado de la varible que retorna la funcion
            if(datosLeidos != 1){//Condicional, si no leyo el archivo lo informo
                printf("\nError al escribir los datos en el archivo.\n");
            }
        }
        printf("\n --> Datos guardados con exito!!!.\n\n");
    }
    else{ //Si no pudo acceder al archivo lo informo
        printf("\nNo se pudo acceder al archivo.\n");
    }
    fclose(pArchivo); //Cierro el archivo
    return retorno; //Retorno el valor de la variable
}

int controller_freeLinkedList(LinkedList* pArrayListEmployee){
    int retorno = -1;
    if(pArrayListEmployee != NULL){
        for(int i=0; i<ll_len(pArrayListEmployee); i++){
            ll_remove(pArrayListEmployee, i);
        }
        ll_deleteLinkedList(pArrayListEmployee);
        retorno = 0;
    }
    printf("\n  --> Se elimino la lista de empleados.\n");
    return retorno;
}
