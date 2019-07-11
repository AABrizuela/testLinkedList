#ifndef parser_H_INCLUDED
#define parser_H_INCLUDED
#include "LinkedList.h"

/** \brief Recorre el array y asigna los valores a estrcturas creadas
 *
 * \param pFile FILE* puntero al archivo
 * \param pArrayListEmployee LinkedList* puntero a la lista de empleados
 * \return int 0 si salio bien - 1 si hubo error
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee);

/** \brief Recorre el array y asigna los valores a estrcturas creadas
 *
 * \param pFile FILE* puntero al archivo
 * \param pArrayListEmployee LinkedList* puntero a la lista de empleados
 * \return int 0 si salio bien - 1 si hubo error
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee);

#endif // parser_H_INCLUDED
