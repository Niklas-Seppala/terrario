#include "terrario/collections/linked-list.h"
#include "terrario/collections/array-list.h"
#include "terrario/error.h"

#include <stdlib.h>
#include <string.h>

static const int EQUAL = 0;

struct array_iter 
{
    int index;
    struct array_list *list;
};

struct array_list
{
    int current_length;
    int length;
    // struct array_iter iterator;
    void **array;
};

struct node
{
    struct node *next;
    void *val;
};

union iterator 
{
    struct node node;
    struct array_iter array;
};

#pragma region Linked Lists

struct linked_list
{
    int length;
    struct node *root;
    struct node *tail;
};

TR_LinkedList TR_linked_list_alloc(void)
{
    struct linked_list *list = calloc(1, sizeof(struct linked_list));
    return list;
}

void TR_linked_list_append(TR_LinkedList list, void *value)
{
    NOT_NULL(list);

    struct node *node = calloc(1, sizeof(struct node));
    node->val = value;

    if (list->root == NULL) list->root = node;
    else                    list->tail->next = node;

    list->tail = node;
    list->length++;
}

void TR_linked_list_free(TR_LinkedList *list)
{
    NOT_NULL(list);
    NOT_NULL(*list);

    struct node *head = (*list)->root;
    while (head != NULL)
    {
        struct node *next = head->next;
        free(head);
        (*list)->length--;
        head = next;
    }
    free(*list);
    // Set to null to avoid dangling.
    *list = NULL;
}

int TR_linked_list_insert(TR_LinkedList list, int pos, void *value)
{
    NOT_NULL(list);
    if (pos < 0)
        return TR_INVALID_INDEX;

    int curr_pos = 0;
    struct node *prev = NULL;
    for (struct node *head = list->root; head != NULL; head = head->next)
    {
        if (curr_pos == pos)
        {
            // Create node for value storage.
            struct node *node = calloc(1, sizeof(struct node));
            node->val = value;
            node->next = head;

            // If inserting to the head of the list, attach to list root.
            // Otherwise to previous node.
            if (prev == NULL) list->root = node;
            else              prev->next = node;

            list->length++;
            return curr_pos;
        }
        curr_pos++;
        prev = head;
    }
    // Append the value and return index.
    TR_linked_list_append(list, value);
    return curr_pos;
}

void *TR_linked_list_get(TR_LinkedList list, int pos)
{
    NOT_NULL(list);
    if (pos < 0 || pos > list->length - 1)
        return NULL;

    int curr_pos = 0;
    for (struct node *head = list->root; head != NULL; head = head->next)
    {
        if (curr_pos++ == pos)
            return head->val;
    }
    return NULL;
}

int TR_linked_list_contains(TR_LinkedList list, const void *value, int val_bytes)
{
    NOT_NULL(list);
    if (value == NULL)
        return TR_INVALID_INDEX;

    int index = 0;
    for (struct node *head = list->root; head != NULL; head = head->next)
    {
        if (memcmp(head->val, value, val_bytes) == EQUAL)
            return index;
        else
            index++;
    }

    return TR_INVALID_INDEX;
}

void *TR_linked_list_find(TR_LinkedList list, TR_predicate cmp)
{
    NOT_NULL(list);
    NOT_NULL(cmp);

    if (list->length == 0)
        return NULL;

    for (struct node *head = list->root; head != NULL; head = head->next)
    {
        if (cmp(head->val) == EQUAL)
            return head->val;
    }
    return NULL;
}

TR_LinkedList TR_linked_list_filter(TR_LinkedList list, TR_predicate filter)
{
    NOT_NULL(list);
    TR_LinkedList result_list = TR_linked_list_alloc();

    for (struct node *head = list->root; head != NULL; head = head->next)
    {
        if (filter(head->val) == EQUAL)
            TR_linked_list_append(result_list, head->val);
    }

    return result_list;
}

void *TR_linked_list_pop(TR_LinkedList list)
{
    NOT_NULL(list);

    if (list->length == 0)
        return NULL;

    struct node *head = list->root;
    while (head->next != NULL)
    {
        list->tail = head;
        head = head->next;
    }
    void *result = head->val;
    list->tail->next = NULL;
    free(head);

    list->length--;
    if (list->length == 0)
        list->root = NULL;

    return result;
}

void *TR_linked_list_shift(TR_LinkedList list)
{
    NOT_NULL(list);

    if (list->length == 0)
        return NULL;

    struct node *head = list->root;
    list->root = head->next;

    void *result = head->val;
    free(head);
    list->length--;
    return result;
}

void *TR_linked_list_remove(TR_LinkedList list, int pos)
{
    NOT_NULL(list);
    if (pos < 0)
        return NULL;

    int curr_pos = 0;
    struct node *prev = NULL;
    struct node *head = list->root;
    while (head != NULL)
    {
        if (curr_pos++ == pos)
        {
            void *result = head->val;

            if (prev == NULL) list->root = head->next;
            else              prev->next = head->next;

            free(head);
            list->length--;
            return result;
        }
        prev = head;
        head = head->next;
    }
    return NULL;
}

int TR_linked_list_len(TR_LinkedList list)
{
    NOT_NULL(list);

    return list->length;
}

void TR_linked_list_clear(TR_LinkedList list)
{
    NOT_NULL(list);

    struct node *head = list->root;
    while (head != NULL)
    {
        struct node *next = head->next;
        free(head);
        list->length--;
        head = next;
    }
    list->root = NULL;
}

void TR_linked_list_reverse(TR_LinkedList list)
{
    NOT_NULL(list);

    struct node *prev = NULL;
    struct node *head = list->root;
    struct node *next = NULL;
    while (head != NULL)
    {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    list->root = prev;
}

int TR_linked_list_array_copy(TR_LinkedList list, int i,
                              int n, int size, void *array)
{
    int count = 0;
    int pos = 0;
    struct node *head = list->root;

    // Find starting position.
    while (head != NULL && pos < i)
    {
        head = head->next;
        pos++;
    }

    if (pos != i)
        return count;

    // Copy the values to array.
    char *arr_ptr = array;
    while (head != NULL && count < n)
    {
        memcpy(arr_ptr, head->val, size);
        arr_ptr += size;
        count++;
        head = head->next;
    }

    return count;
}

inline TR_Iterator TR_linked_list_iterate(TR_LinkedList list)
{
    NOT_NULL(list);
    return (TR_Iterator)list->root;
}

inline TR_Iterator TR_linked_list_iter_next(TR_Iterator iter)
{
    NOT_NULL(iter);
    return (TR_Iterator)iter->node.next;
}


inline bool TR_linked_list_iter_has_next(TR_Iterator iter)
{
    NOT_NULL(iter);
    return iter->node.next != NULL;
}

inline void *TR_Linked_list_iter_value(TR_Iterator iter)
{
    NOT_NULL(iter);
    return iter->node.val;
}


#pragma endregion Linked Lists

#pragma region Array Lists

static inline bool _index_out_of_range(TR_ArrayList list, int index)
{
    return index < 0 || index > list->current_length-1;
}

static void _resize_array_list(TR_ArrayList list)
{
    int new_length = list->length * ARRAY_LIST_DEFAULT_RESIZE_FACTOR;
    list->array = realloc(list->array, sizeof(void *) * new_length);

    NOT_NULL(list->array);
}


TR_ArrayList TR_array_list_alloc(void)
{
    struct array_list *list = calloc(1, sizeof(struct array_list));
    list->length = ARRAY_LIST_DEFAULT_SIZE;
    list->array = calloc(list->length, sizeof(void *));

    return list;
}

TR_ArrayList TR_array_list_alloc_with_size(int n)
{
    struct array_list *list = calloc(1, sizeof(struct array_list));
    list->length = n;
    list->array = calloc(list->length, sizeof(void *));

    return list;
}


void TR_array_list_free(TR_ArrayList *list)
{
    NOT_NULL(list);
    free((*list)->array);
    free(*list);
    *list = NULL;
}

void TR_array_list_append(TR_ArrayList list, void *value)
{
    NOT_NULL(list);

    int index = list->current_length;
    if (index > list->length)
        _resize_array_list(list);

    list->array[index] = value;
    list->current_length++;
}


void *TR_array_list_get(TR_ArrayList list, int index)
{
    NOT_NULL(list);
    if (_index_out_of_range(list, index)) 
        return NULL;

    return list->array[index];
}

int TR_array_list_put(TR_ArrayList list, int index, void *value)
{
    NOT_NULL(list);
    if (_index_out_of_range(list, index)) 
        return TR_INVALID_INDEX;
    
    list->array[index] = value;
    return index;
}

#include <stdio.h>
void TR_array_list_insert(TR_ArrayList list, int index, void *value)
{
    NOT_NULL(list);
    if (_index_out_of_range(list, index)) 
        return;

    const int number_of_tailing_entries = list->current_length - (index+1) +1;
    const int ptr_size = sizeof(void *);
    void **index_addr = list->array + index;
    void **index_next_addr = index_addr + 1;
    
    if (list->current_length + 1 >= list->length)
        _resize_array_list(list);

    if (number_of_tailing_entries > 0)
        memmove(index_next_addr, index_addr, number_of_tailing_entries * ptr_size);

    list->array[index] = value;
    list->current_length++;
}

void *TR_array_list_remove(TR_ArrayList list, int index)
{
    NOT_NULL(list);
    if (_index_out_of_range(list, index)) 
        return NULL;
    
    void *value = list->array[index];
    const int number_of_tailing_entries = list->current_length - (index + 1);
    const int ptr_size = sizeof(void *);
    void **index_addr = list->array + index;
    void **index_next_addr = index_addr + 1;

    if (number_of_tailing_entries > 0)
        memmove(index_addr, index_next_addr, number_of_tailing_entries * ptr_size);

    list->current_length--;
    return value;
}

void *TR_array_list_pop(TR_ArrayList list)
{
    NOT_NULL(list);
    return TR_array_list_remove(list, list->current_length-1);
}

void *TR_array_list_shift(TR_ArrayList list)
{
    NOT_NULL(list);
    return TR_array_list_remove(list, 0);
}

inline TR_Iterator TR_array_list_iter(TR_ArrayList list)
{
    NOT_NULL(list);

    TR_Iterator iter = calloc(1, sizeof(struct array_iter));
    iter->array.index = 0;
    iter->array.list = list;

    return iter;
}

inline TR_Iterator TR_array_list_iter_next(TR_Iterator iter)
{
    NOT_NULL(iter);

    iter->array.index++;
    return iter;
}

inline void *TR_array_list_iter_value(TR_Iterator iter)
{
    NOT_NULL(iter);

    TR_ArrayList list = iter->array.list;
    int index = iter->array.index;
    return list->array[index];
}

inline bool TR_array_list_iter_has_next(TR_Iterator iter)
{
    NOT_NULL(iter);

    TR_ArrayList list = iter->array.list;
    int index = iter->array.index;
    return index < list->current_length;
}

inline int TR_array_list_len(TR_ArrayList list)
{
    return list->current_length;
}

#pragma endregion Array Lists
