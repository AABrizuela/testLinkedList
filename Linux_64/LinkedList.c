#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);
static Node* quicksort(LinkedList* this, Node* headNode, Node* endNode, int (*pFunc)(void*, void*), int order);
static Node* partition(LinkedList* this, Node* headNode, Node* endNode, Node** newLow, Node** newHigh, int (*pFunc)(void*, void*), int order);
static struct Node *getTail(struct Node *cur);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= NULL;
    this = (LinkedList*)malloc(sizeof(LinkedList));

    if(this != NULL)
    {
        this->size = 0;
        this->pFirstNode = NULL;
    }

    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        returnAux = this->size;
    }

    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* retNode;
    int found = 0;
    int counter = 0;

    if(this == NULL)
    {
        return NULL;
    }

    if (nodeIndex > this->size || nodeIndex < 0)
    {
        return NULL;
    }

    retNode = this->pFirstNode;

    while(!found)
    {
        if(counter == nodeIndex)
        {
            found = 1;
        }
        else
        {
            counter++;
            retNode = retNode->pNextNode;
        }
    }

    return retNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;
    Node* auxNode;
    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->pElement = pElement;
    newNode->pNextNode = NULL;

    if(nodeIndex != 0)
    {
        auxNode = getNode(this, nodeIndex-1);

        if(auxNode == NULL)
        {
            free(newNode);
            return returnAux;
        }

        newNode->pNextNode = auxNode->pNextNode;
        auxNode->pNextNode = newNode;
    }
    else
    {
        if (this->pFirstNode){
            auxNode = getNode(this, nodeIndex);

            if(auxNode == NULL)
            {
                return returnAux;
            }

            auxNode = this->pFirstNode;
            newNode->pNextNode = auxNode;
        }
        this->pFirstNode = newNode;
    }

    this->size++;
    returnAux = 0;
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int index = this->size-1;
    if (index < 0){
        index = 0;
    };

    if(addNode(this, index, pElement) == -1)
    {
        return returnAux;
    }

    returnAux = 0;

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* auxNode;

    auxNode = getNode(this, index);

    if(auxNode != NULL)
    {
        returnAux = auxNode->pElement;
    }

    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* auxNode;

    auxNode = getNode(this, index);

    if(auxNode != NULL)
    {
        //En caso de que tenga que borrar el elemento desde la lista
        //free(auxNode->pElement);
        auxNode->pElement = pElement;
        returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* auxNode;
    Node* delNode;

    if(index != 0)
    {
        auxNode = getNode(this, index-1);

        if(auxNode != NULL)
        {
            delNode = auxNode->pNextNode;
            auxNode->pNextNode = auxNode->pNextNode->pNextNode;
            free(delNode);
        }
        else
        {
            return returnAux;
        }
    }
    else
    {
        auxNode = getNode(this, index);

        if(auxNode != NULL)
        {
            delNode = this->pFirstNode;
            this->pFirstNode = auxNode->pNextNode;
            free(delNode);
        }
        else
        {
            return returnAux;
        }
    }

    this->size--;
    returnAux = 0;
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;

    if(this == NULL)
    {
        return returnAux;
    }

    while(this->pFirstNode != NULL)
    {
        ll_remove(this, 0);
    }

    returnAux = 0;
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this == NULL)
    {
        return returnAux;
    }

    if(!ll_clear(this))
    {
        free(this);
        returnAux = 0;
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i = 0;
    Node* auxNode;

    if(this == NULL && pElement == NULL)
    {
        return returnAux;
    }

    do
    {
        auxNode = getNode(this, i);

        if(auxNode == NULL)
        {
            return returnAux;
        }

        i++;

    }
    while(pElement != auxNode->pElement);

    returnAux = i;
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this == NULL)
    {
        return returnAux;
    }

    if(this->pFirstNode == NULL)
    {
        returnAux = 1;
    }
    else
    {
        returnAux = 0;
    }

    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;

    if(this == NULL)
    {
        return returnAux;
    }

    //El retorno de addNode (-1 o 0) se le pasa a la variable de retorno
    returnAux = addNode(this, index, pElement);

    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    Node* auxNode;

    if(this == NULL)
    {
        return returnAux;
    }

    auxNode = getNode(this, index);//Pido el nodo con getNode y lo guardo en el auxiliar

    if(auxNode == NULL)
    {
        return returnAux;
    }

    returnAux = auxNode->pElement;//Guardo el elemento del nodo en la variable de retorno
    ll_remove(this, index);

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int aux;

    if(this == NULL)
    {
        return returnAux;
    }

    aux = ll_indexOf(this, pElement);

    if(aux != -1)
    {
        returnAux = 1;
    }
    else
    {
        returnAux = 0;
    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int i = 0;
    int aux = 0;
    Node* auxNode2;

    if(this == NULL || this2 == NULL)
    {
        return returnAux;
    }

    do
    {
        auxNode2 = getNode(this2, i);

        if(auxNode2 == NULL)
        {
            return returnAux;
        }

        aux = ll_indexOf(this, auxNode2->pElement);
        i++;

        if(aux == -1)
        {
            returnAux = 0;
            return returnAux;
        }

    }
    while(i <= this2->size);  //o while(this2->pNextNode == NULL);

    returnAux = 1;
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int i;
    Node* auxNode;

    if(this == NULL)
    {
        return cloneArray;
    }
    //'from' no lo verifico porque se hace dentro de getNode
    //verifico 'to' para no ejecutar la funcion hasta que se pase
    if(to<from || to>=this->size)
    {
        return cloneArray;
    }

    cloneArray = ll_newLinkedList();

    for(i=from; i<=to; i++)
    {
        auxNode = getNode(this, i);//Obtengo el nodo de la lista original para usar el elemento mas adelante

        if(auxNode == NULL)
        {
            ll_deleteLinkedList(cloneArray);
            cloneArray = NULL;
            return cloneArray;
        }

        ll_add(cloneArray, auxNode->pElement);//Agrego a la lista clonada el elemento de la lista original
        //No hace falta checkear si devuelve NULL porque cloneArray no es NULL a esta altura del codigo
    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    Node* auxNode;
    int i = 0;

    if(this == NULL)
    {
        return cloneArray;
    }

    cloneArray = ll_newLinkedList();

    do
    {
        auxNode = getNode(this, i);//Obtengo el nodo de la lista original para usar el elemento mas adelante

        if(auxNode == NULL)
        {
            ll_deleteLinkedList(cloneArray);
            cloneArray = NULL;
            return cloneArray;
        }

        ll_add(cloneArray, auxNode->pElement);//Agrego a la lista clonada el elemento de la lista original
        //No hace falta checkear si devuelve NULL porque cloneArray no es NULL a esta altura del codigo
        i++;

    }
    while(cloneArray->size <= this->size);

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux =-1;
/*    int i;
    void* pElement1;
    void* pElement2;
    int flagSwap;
    int length;

    if(this!=NULL && order>=0 && pFunc != NULL)
    {
        length = ll_len(this);
        do
        {
            flagSwap=0;
            for (i = 0; i < length-1; i++)
            {
                pElement1 = ll_get(this, i);
                pElement2 = ll_get(this, i + 1);
                if( ((pFunc(pElement1, pElement2) < 0) && !order) ||
                    ((pFunc(pElement1, pElement2) > 0) && order) )
                {
                    flagSwap=1;
                    ll_set(this, i, pElement2);
                    ll_set(this, i + 1, pElement1);
                }
            }
        }while(flagSwap);
        returnAux=0;
    }
*/

    if(this == NULL)
    {
        return returnAux;
    }

    Node* headNode = getNode(this, 0);
    Node* endNode = getNode(this, this->size-1);
    //Llamo a quicksort pasandole pFunc para que ordene de manera ascendente
    quicksort(this, headNode, endNode, pFunc, order);

    return returnAux;
}

LinkedList* ll_filter(LinkedList* this, int (*pFunc)(void*))
{
    LinkedList* filteredList;
    int i;
    void* pElement;

    if(this != NULL)
    {
        filteredList = ll_newLinkedList();

        if(filteredList != NULL)
        {
            for(i = 0; i < this->size; i++)
            {
                pElement = ll_get(this, i);

                if(pFunc(pElement))
                {
                    ll_add(this, pElement);
                }
            }
        }
    }

    return filteredList;
}

/** \brief Funcion que reduce la lista en base al retorno de pFunc
 *
 * \param LinkedList* this La lista completa
 * \param int (*pFunc)(void*) La funcion que se usa como criterio
 * \return int ll_reduce(LinkedList* this, int
 *
 */
int ll_reduce(LinkedList* this, int (*pFunc)(void*))
{
    int returnAux = -1;
    int i;
    void* pElement;

    if(this == NULL)
    {
        return returnAux;
    }

    for(i = 0; i < this->size; i++)
    {
        pElement = ll_get(this, i);

        if(pFunc(pElement))
        {
            ll_remove(this, i);
        }
    }

    returnAux = 0;
    return returnAux;
}

/** \brief Funcion de mapeo, usa pFunc para todos los elementos de la lsita
 *
 * \param LinkedList* this La lista completa
 * \param int (*pFunc)(void*) La funcion que se usa como criterio
 * \return void
 *
 */
void ll_map(LinkedList* this, int (*pFunc)(void*))
{
    int i;
    void* pElement;

    if(this != NULL)
    {
        for(i = 0; i < this->size; i++)
        {
            pElement = ll_get(this, i);

            pFunc(pElement);
        }
    }
}

/** \brief Funcion que sirve de contador, usando el retorno de pFunc para aumentar
 *         dicho contador
 *
 * \param LinkedList* this La lista completa
 * \param int (*pFunc)(void*) La funcion que se usa como criterio
 * \param int* pCounter Puntero a una variable donde se va a guardar el contador
 * \return void
 *
 */
void ll_count(LinkedList* this, int (*pFunc)(void*), int* pCounter)
{
    int i;
    void* pElement;
    int counter = 0;
    int ret;

    if(this != NULL && pCounter != NULL && pFunc != NULL)
    {
        for(i = 0; i < ll_len(this); i++)
        {
            pElement = ll_get(this, i);

            if(pElement != NULL)
            {
                ret = pFunc(pElement);
                if(ret == 0)
                {
                    counter++;
                    *pCounter = counter;
                }
            }
        }
    }
}

/** \brief Funcion de ordenamiento QuickSort
 *
 * \param LinkedList* this La lista completa
 * \param Node* headNode Limite inferior
 * \param Node* endNode Limite superior
 * \param int (*pFunc)(void*, void*) La funcion que se usa como criterio para el orden de los elementos
 * \return void
 *
 */
static Node* quicksort(LinkedList* this, Node* headNode, Node* endNode, int (*pFunc)(void*, void*), int order)
{
    if(!headNode || headNode == endNode)
    {
        return endNode;
    }

    Node* newLow = NULL;
    Node* newHigh = NULL;

    Node* pivot = partition(this, headNode, endNode, &newLow, &newHigh, pFunc, order);

    if(newLow != pivot)
    {
        Node* tmpNode = newLow;
        while(tmpNode->pNextNode != pivot)
        {
            tmpNode = tmpNode->pNextNode;
        }
        tmpNode->pNextNode = NULL;

        newLow = quicksort(this, headNode, endNode, pFunc, order);

        tmpNode = getTail(newLow);
        tmpNode->pNextNode = pivot;
    }

    return newHigh;
    /*if(low<high)
    {
        //Llamo a la funcion partition para dividir la lista en dos y ordenarla
        retPartition = partition(this, low, high, pFunc, order);
        //LLamo a quicksort usando como limite superior el retorno de la funcion 'partition', para ordenar una mitad de la lista
        quicksort(this, low, retPartition-1, pFunc, order);
        //Llamo a quicksort usando como limite inferior el retorno de la funcion 'partition', para ordenar la otra mitad de la lista
        quicksort(this, retPartition+1, high, pFunc, order);
    }*/
}

static struct Node *getTail(struct Node *cur)
{
    while (cur != NULL && cur->pNextNode != NULL)
        cur = cur->pNextNode;
    return cur;
}

/** \brief Funcion que divide la lista a la mitad, usada por QuickSort
 *
 * \param LinkedList* this La lista completa
 * \param Node* headNode Limite inferior
 * \param Node* endNode Limite Superior
 * \param int o
 * \return int
 *
 */
static Node* partition(LinkedList* this, Node* headNode, Node* endNode, Node** newLow, Node** newHigh, int (*pFunc)(void*, void*), int order)
{
    Node* pivot;
    Node* auxNodePrev;
    Node* auxNodeCurr;
    //void* auxEle;
    //int i = low;
    //int j;
    //int swap;

    pivot = endNode;
    Node* auxNodeTail = pivot;

    while(auxNodeCurr != pivot)
    {
        if(pFunc)
        {
            if((*newLow) == NULL)
            {
                (*newLow) = auxNodeCurr;
            }

            auxNodePrev = auxNodeCurr;
            auxNodeCurr = auxNodeCurr->pNextNode;
        }
        else
        {
            if(auxNodePrev)
            {
                auxNodePrev->pNextNode = auxNodeCurr->pNextNode;
            }
            Node* tmpNode = auxNodeCurr->pNextNode;
            auxNodeCurr->pNextNode = NULL;
            auxNodeTail->pNextNode = auxNodeCurr;
            auxNodeTail = auxNodeCurr;
            auxNodeCurr = tmpNode;
        }
    }

    if((*newLow) == NULL)
    {
        (*newLow) = pivot;
    }

    (*newHigh) = auxNodeTail;
    /*for(j=low; j<high-1; j++)
    {
        //Pido el nodo que esta en 'j'
        auxNodeJ = getNode(this, j);
        swap = pFunc(auxNodeJ->pElement, pivot->pElement);
        if (swap <= 0)
        {
            swap = 0;
        }
        if (!order)
        {
            swap = !swap;
        }
        //Si la funcion me pide intercambiar los elementos entro a hacer el swap
        if(swap)
        {
            //Pido el nodo que esta en 'i'
            auxNodeI = getNode(this, i);

            //Hago el swap entre 'i' y 'j'
            //Guardo la referencia en el auxiliar para reemplazarlo sin que se pierda
            auxEle = auxNodeI->pElement;
            //Reemplazo el elemento que guarde en el auxiliar
            auxNodeI->pElement = auxNodeJ->pElement;
            //Reemplazo el elemento del auxiliar en el nodo J
            auxNodeJ->pElement = auxEle;
            i++;
        }
    }
    //Reacomodo el pivote
    if (i == low)
    {
        return i;
    }
    //Guardo la referencia al pivote en el auxiliar para poder reemplazarlo sin que se pierda
    auxEle = pivot->pElement;
    //Reemplazo el pivote
    pivot->pElement = auxNodeI->pElement;
    //Reemplazo el elemento del auxiliar en el nodo I
    auxNodeI->pElement = auxEle;
    */
    return pivot;
}
