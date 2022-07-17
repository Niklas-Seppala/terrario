#if !defined(GUARD_LINKED_LIST_H)
#define GUARD_LINKED_LIST_H
#include <stdbool.h>
#include "terrario/collections.h"

typedef struct linked_list *TR_LinkedList;

typedef int (*TR_predicate)(void *);

/**
 * @brief 
 * 
 * @return TR_LinkedList 
 */
TR_LinkedList TR_linked_list_alloc(void);


/**
 * @brief 
 * 
 * @param list 
 * @return void* 
 */
void *TR_linked_list_pop(TR_LinkedList list);

/**
 * @brief 
 * 
 * @param list 
 * @return void* 
 */
void *TR_linked_list_shift(TR_LinkedList list);

/**
 * @brief 
 * 
 * @param list 
 * @param pos 
 * @return void* 
 */
void *TR_linked_list_remove(TR_LinkedList list, int pos);

/**
 * @brief 
 * 
 * @param list 
 * @param value 
 */
void TR_linked_list_append(TR_LinkedList list, void *value);

/**
 * @brief 
 * 
 * @param list 
 */
void TR_linked_list_free(TR_LinkedList *list);

/**
 * @brief 
 * 
 * @param list 
 * @param pos 
 * @param value 
 * @return int 
 */
int TR_linked_list_insert(TR_LinkedList list, int pos, void* value);


/**
 * @brief 
 * 
 * @param list 
 * @param pos 
 * @return void* 
 */
void *TR_linked_list_get(TR_LinkedList list, int pos);

/**
 * @brief 
 * 
 * @param list 
 * @param value 
 * @param val_bytes 
 * @return int 
 */
int TR_linked_list_contains(TR_LinkedList list, const void *value, int val_bytes);

/**
 * @brief 
 * 
 * @param list 
 * @param cmp 
 */
void *TR_linked_list_find(TR_LinkedList list, TR_predicate cmp);

/**
 * @brief 
 * 
 * @param list 
 * @param filter 
 * @return TR_LinkedList 
 */
TR_LinkedList TR_linked_list_filter(TR_LinkedList list, TR_predicate filter);

/**
 * @brief 
 * 
 * @param list 
 * @return int 
 */
int TR_linked_list_len(TR_LinkedList list);

/**
 * @brief 
 * 
 * @param list 
 */
void TR_linked_list_clear(TR_LinkedList list);

/**
 * @brief 
 * 
 * @param list 
 */
void TR_linked_list_reverse(TR_LinkedList list);

/**
 * @brief 
 * 
 * @param list 
 * @param i 
 * @param n 
 * @param size 
 * @param array 
 * @return int 
 */
int TR_linked_list_array_copy(TR_LinkedList list, int i,
                               int n, int size, void *array);

/**
 * @brief 
 * 
 * @param list 
 * @return TR_ListIterator 
 */
TR_Iterator TR_linked_list_iterate(TR_LinkedList list);

/**
 * @brief 
 * 
 * @param iter 
 * @return TR_ListIterator 
 */
TR_Iterator TR_linked_list_iter_next(TR_Iterator iter);

/**
 * @brief 
 * 
 * @param iter 
 * @return true 
 * @return false 
 */
bool TR_linked_list_iter_has_next(TR_Iterator iter);

/**
 * @brief 
 * 
 * @param iter 
 * @return void* 
 */
void * TR_Linked_list_iter_value(TR_Iterator iter);


#endif  // GUARD_LINKED_LIST_H
