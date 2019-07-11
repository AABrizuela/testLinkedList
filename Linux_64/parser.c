#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "parser.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
    Employee* this; //Creo un nuevo empleado
    int datosLeidos; //Contador de lectura
    char auxId[50], auxNombre[50], auxHorasTrabajadas[50], auxSueldo[50]; //Variables buffer
    fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", auxId, auxNombre, auxHorasTrabajadas, auxSueldo); //Hago una primera lectura "fantasma" para leer el titulo el cual no voy a almacenar y le asigno a "datosLeidos" el retorno de la lectura "fscanf"
    while(!feof(pFile)) //Mientras no se llege al final del archivo
    {
        datosLeidos = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", auxId, auxNombre, auxHorasTrabajadas, auxSueldo); //Le asigno a "datosLeidos" el retorno de la lectura "fscanf"
        if(datosLeidos == 4) //Si datosLeidos es igual a los 4 datos pedidos a leer
        {
            this = employee_newParametros(auxId, auxNombre, auxHorasTrabajadas, auxSueldo); //Le asigno a "this" las variables leidas casteadas en la funcion
            printf("%s", this->nombre);
            ll_add(pArrayListEmployee, this); //Agrego "this" al final del array de empleados
        }
        else if(datosLeidos != 4 && this != NULL) //Si datosLeidos es distinto a los 4 datos pedidos a leer
        {
            if(!feof(pFile)) //Si aun no se llego al final del archivo lo informo
            {
                printf("\nError al leer el ultimo dato.");
                break;
            }
            else //Si se leyo todo el archivo sin problemas lo informo
            {
                printf("\nSe leyo todo el archivo.");
            }
        }
    }
    printf("\n --> Empleados cargados correctamente.\n\n");
    fclose(pFile); //Cierro el archivo
    return 1;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{
    Employee* this; //Creo un nuevo empleado
    int datosLeidos; //Contador de lectura
    while(!feof(pFile))
    {
        this = employee_new();
        datosLeidos = fread(this, sizeof(Employee), 1, pFile);
        if(datosLeidos == 1 && this != NULL)
        {
            ll_add(pArrayListEmployee, this);
        }
        else if(datosLeidos != 1) //Si datosLeidos es distinto a los 4 datos pedidos a leer
        {
            if(!feof(pFile)) //Si aun no se llego al final del archivo lo informo
            {
                printf("\nError al leer el ultimo dato.");
                break;
            }
            else //Si se leyo todo el archivo sin problemas lo informo
            {
                printf("\n --> Empleados cargados correctamente.\n\n");//printf("\nSe leyo todo el archivo.");
            }
        }
    }
    //printf("\n --> Empleados cargados correctamente.\n\n");
    fclose(pFile); //Cierro el archivo
    return 1;
}
