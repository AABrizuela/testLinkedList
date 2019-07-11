#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"

Employee* employee_new()
{
    Employee* this = malloc(sizeof(Employee)); //Creo un nuevo empleado con memodia dinamica "malloc"
    if(this == NULL) //Verifico que no sea NULL
    {
        printf("No hay lugar para crear nuevo empleado.\n");
        exit(EXIT_FAILURE); //De ser NULL salgo
    }
    else //De lo contrario parseo a 0 y cadena vacia las variables
    {
        this->id = 0;
        strcpy(this->nombre, "");
        this->horasTrabajadas = 0;
        this->sueldo = 0;
    }
    return this; //Retorno el puntero a la estructura creada
}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr)
{
    int auxHorasTrabajadas;
    int auxId;
    float auxSueldo;
    int flag = 1;
    Employee* this = employee_new();
    auxId = atoi(idStr);
    if(employee_setId(this,auxId)!= 1)
    {
        flag=0;
    }
    auxHorasTrabajadas = atoi(horasTrabajadasStr);
    if(employee_setHorasTrabajadas(this,auxHorasTrabajadas)!= 1)
    {
        flag=0;
    }
    if(employee_setNombre(this,nombreStr)!= 1)
    {
        flag=0;
    }
    auxSueldo = atof(sueldoStr);
    if(employee_setSueldo(this, auxSueldo)!=1)
    {
        flag=0;
    }
    if(flag == 0)
    {
        printf("\nError al cargar datos, revise la lista.\n");
    }
    return this;
}

int employee_setId(Employee* this,int id)
{
    int retorno = 0;
    if(this != NULL && id > 0)
    {
        this->id = id;
        retorno=1;
    }
    return retorno;
}

int employee_getId(Employee* this,int* id)
{
    int retorno = 0;
    if(this != NULL && id > 0)
    {
        *id = this->id;
        retorno=1;
    }
    return retorno;
}

int employee_setNombre(Employee* this,char* nombre)
{
    int retorno=0;
    if(this != NULL && strlen(nombre) > 0)
    {
        strcpy(this->nombre, nombre);
        retorno=1;
    }
    return retorno;
}

int employee_getNombre(Employee* this,char* nombre)
{
    int retorno = 0;
    if(this != NULL && nombre != NULL)
    {
        strcpy(nombre, this->nombre);
        retorno = 1;
    }
    return retorno;
}

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
    int retorno=0;
    if(this != NULL && horasTrabajadas > 0)
    {
        this->horasTrabajadas = horasTrabajadas;
        retorno=1;
    }
    return retorno;
}

int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
    int retorno = 0;
    if(this != NULL && horasTrabajadas > 0)
    {
        *horasTrabajadas = this->horasTrabajadas;
        retorno=1;
    }
    return retorno;
}

int employee_setSueldo(Employee* this,float sueldo)
{
    int retorno=0;
    if(this != NULL && sueldo > 0)
    {
        this->sueldo = sueldo;
        retorno=1;
    }
    return retorno;
}

int employee_getSueldo(Employee* this,float* sueldo)
{
    int retorno=0;
    if(this != NULL && sueldo > 0)
    {
        *sueldo = this->sueldo;
        retorno=1;
    }
    return retorno;
}

void employee_printData(Employee* this)
{
    int id; //Variable donde se almacena el id utilizando getId();
    char nombre[51]; //Variable donde se almacena el nombre utilizando getNobre();
    int horasTrabajadas; //Variable donde se almacenan las horas trabajadas utilizando getHorasTrabajadas();
    float sueldo; //Variable donde se almacena el sueldo utilizando getId();
    employee_getId(this, &id); //Obtengo el Id del empleado
    employee_getNombre(this, nombre); //Obtengo el nombre del empleado
    employee_getHorasTrabajadas(this, &horasTrabajadas); //Obtengo las horas trabajadas del empelado
    employee_getSueldo(this, &sueldo); //Obtengo el sueldo del empleado
    printf("   %5d | %12s |          %4d  |    $ %.2f\n", id, nombre, horasTrabajadas, sueldo); //Muestro los datos del empleado
}

int employee_ControlId(LinkedList* pArrayListEmployee, char* idStr)
{
    int retorno = 0; //Variable retorno funcion
    int id; //Variable ID
    id = atoi(idStr); //Casteo de string a entero
    Employee* this; //Puntero a estructura
    if(pArrayListEmployee != NULL) //Condicional, verifica que sea distinto de NULL
    {
        for(int i=0; i<ll_len(pArrayListEmployee); i++) //Recorro el for en busca del ID ingresado
        {
            this = (Employee*)ll_get(pArrayListEmployee, i); //Le asigno a this la estructura que retorna ll_get()
            if(this->id == id) //Si se encuentra el id ingresado se cambia la bandera y se rompe l iteraccion
            {
                retorno = 1;
                break;
            }
        }
    }
    return retorno; //Se retorna a la funcion el valor de retorno
}

int employee_SortById(void* employeeA, void* employeeB)
{
    int retorno = 0; //Variable retorno de la funcion
    Employee* empA; //Puntero a la estructura empA
    Employee* empB; //Puntero a la estructura empB
    if(employeeA !=NULL && employeeB !=NULL){ //Condicional, controla que employeeA y employeeB no sean NULL
        empA = (Employee*) employeeA; //Casteo la estructura employeeA puntero
        empB = (Employee*) employeeB; //Casteo la estructura employeeA puntero
        if((empA->id) < (empB->id)) //Condicional, si ID de A en menor que ID de B cambio al bandera retorno a 1
        {
            retorno = 1 ;
        }
        else if((empA->id) == (empB->id)) //Condicional, si ID de A en igual que ID de B cambio al bandera retorno a 0
        {
            retorno = 0;
        }
        else if((empA->id) > (empB->id)) //Condicional, si ID de A en mayor que ID de B cambio al bandera retorno a -1
        {
            retorno = -1 ;
        }

    }
    return retorno;
}

int employee_SortByName(void* employeeA, void* employeeB)
{
    int retorno = 0; //Variable retorno de la funcion
    Employee* empA; //Puntero a la estructura empA
    Employee* empB; //Puntero a la estructura empB
    if(employeeA !=NULL && employeeB !=NULL){ //Condicional, controla que employeeA y employeeB no sean NULL    {
        empA = (Employee*) employeeA; //Casteo la estructura employeeA puntero
        empB = (Employee*) employeeB; //Casteo la estructura employeeA puntero
        retorno = strcmp(empA->nombre, empB->nombre); //Copia el contenido de nombre A a nombre B
    }
    return retorno;
}

int employee_SortByHoursWorked(void* employeeA, void* employeeB)
{
    int retorno = 0; //Variable retorno de la funcion
    Employee* empA; //Puntero a la estructura empA
    Employee* empB; //Puntero a la estructura empB
    if(employeeA !=NULL && employeeB !=NULL){ //Condicional, controla que employeeA y employeeB no sean NULL    {
        empA = (Employee*) employeeA; //Casteo la estructura employeeA puntero
        empB = (Employee*) employeeB; //Casteo la estructura employeeA puntero
        if((empA->horasTrabajadas) < (empB->horasTrabajadas)) //Condicional, si horas trabajadas de A en menor que horas trabajadas de B cambio al bandera retorno a 1
        {
            retorno = 1 ;
        }
        else if((empA->horasTrabajadas)==(empB->horasTrabajadas)) //Condicional, si horas trabajadas de A en igual que horas trabajadas de B cambio al bandera retorno a 0
        {
            retorno = 0;
        }
        else if((empA->horasTrabajadas)>(empB->horasTrabajadas)) //Condicional, si horas trabajadas de A en mayor que horas trabajadas de B cambio al bandera retorno a -1
        {
            retorno = -1 ;
        }
    }
    return retorno;
}

int employee_SortBySalary(void* employeeA, void* employeeB)
{
    int retorno = 0; //Variable retorno de la funcion
    Employee* empA; //Puntero a la estructura empA
    Employee* empB; //Puntero a la estructura empB
    if(employeeA !=NULL && employeeB !=NULL) //Condicional, controla que employeeA y employeeB no sean NULL
    {
        empA = (Employee*) employeeA; //Casteo la estructura employeeA puntero
        empB = (Employee*) employeeB; //Casteo la estructura employeeA puntero
        if((empA->sueldo) < (empB->sueldo)) //Condicional, si sueldo de A en menor que sueldo de B cambio al bandera retorno a 1
        {
            retorno = 1 ;
        }
        else if((empA->sueldo) == (empB->sueldo)) //Condicional, si sueldo de A igual que sueldo de B dejo la bandera igual
        {
            retorno = 0;
        }
        else if((empA->sueldo)>(empB->sueldo)) //Condicional, si sueldo de A en mayor que sueldo de B cambio al bandera retorno a -1
        {
            retorno = -1 ;
        }
    }
    return retorno;
}
