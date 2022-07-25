#if !defined(GUARD_ARRAY_LIST_H)
#define GUARD_ARRAY_LIST_H
#include <stdbool.h>
#include "terrario/collections.h"

#define ARRAY_LIST_DEFAULT_SIZE 32
#define ARRAY_LIST_DEFAULT_RESIZE_FACTOR 2

typedef struct array_list *TR_ArrayList;

/**
 * @brief 
 * 
 * @return TR_ArrayList 
 */
TR_ArrayList TR_array_list_alloc(void);

/**
 * @brief 
 * 
 * @param n 
 * @return TR_ArrayList 
 */
TR_ArrayList TR_array_list_alloc_with_size(int n);

/**
 * @brief 
 * 
 * @param list 
 */
void TR_array_list_free(TR_ArrayList *list);

/**
 * @brief 
 * 
 * @param list 
 * @return int 
 */
int TR_array_list_len(TR_ArrayList list);

/**
 * @brief 
 * 
 * @param value 
 * @return int 
 */
void TR_array_list_append(TR_ArrayList list, void *value);

/**
 * @brief 
 * 
 * @param list 
 * @param index 
 * @return void* 
 */
void *TR_array_list_get(TR_ArrayList list, int index);


/**
 * @brief 
 * 
 * @param list 
 * @param index 
 * @param value 
 */
int TR_array_list_put(TR_ArrayList list, int index, void *value);

/**
 * @brief 
 * 
 * @param list 
 * @param index 
 * @param value 
 */
void TR_array_list_insert(TR_ArrayList list, int index, void *value);

/**
 * @brief 
 * 
 * @param list 
 * @param index 
 * @return void* 
 */
void *TR_array_list_remove(TR_ArrayList list, int index);

/**
 * @brief 
 * 
 * @param list 
 * @return void* 
 */
void *TR_array_list_pop(TR_ArrayList list);


/**
 * @brief 
 * 
 * @param list 
 * @return void* 
 */
void *TR_array_list_shift(TR_ArrayList list);

/**
 * @brief 
 * 
 * @param list 
 * @return TR_Iterator 
 */
TR_Iterator TR_array_list_iter(TR_ArrayList list);

/**
 * @brief 
 * 
 * @param iter 
 * @return TR_Iterator 
 */
TR_Iterator TR_array_list_iter_next(TR_Iterator iter);

/**
 * @brief 
 * 
 * @param iter 
 * @return void* 
 */
void *TR_array_list_iter_value(TR_Iterator iter);

/**
 * @brief 
 * 
 * @param iter 
 * @return true 
 * @return false 
 */
bool TR_array_list_iter_has_next(TR_Iterator iter);


#endif // GUARD_ARRAY_LIST_H
