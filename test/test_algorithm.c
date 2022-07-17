#include "test_algorithm.h"
#include "terrario/collections/linked-list.h"
#include "terrario/collections/array-list.h"
#include "terrario/error.h"
#include "test.h"

#pragma region Linked List Tests

START_TEST(test_linked_list_alloc)
{
    TR_LinkedList list = TR_linked_list_alloc();
    ck_assert_ptr_ne(NULL, list);

    ck_assert_int_eq(0, TR_linked_list_len(list));

    TR_linked_list_free(&list);
}
END_TEST

START_TEST(test_linked_list_free)
{
    TR_LinkedList list = TR_linked_list_alloc();
    TR_linked_list_free(&list);
    ck_assert_ptr_eq(NULL, list);
}
END_TEST


START_TEST(test_linked_list_append)
{
    TR_LinkedList list = TR_linked_list_alloc();
    char *item_1 = "Item 1";
    char *item_2 = "Item 2";
    char *item_3 = "Item 3";
    char *item_4 = "Item 4";
    char *item_5 = "Item 5";

    TR_linked_list_append(list, item_1);
    TR_linked_list_append(list, item_2);
    TR_linked_list_append(list, item_3);
    TR_linked_list_append(list, item_4);
    TR_linked_list_append(list, item_5);

    ck_assert_int_eq(5, TR_linked_list_len(list));
    ck_assert_ptr_eq(TR_linked_list_get(list, 0), item_1);
    ck_assert_ptr_eq(TR_linked_list_get(list, 4), item_5);
    ck_assert_ptr_eq(TR_linked_list_get(list, 1), item_2);
    ck_assert_ptr_eq(TR_linked_list_get(list, 3), item_4);
    ck_assert_ptr_eq(TR_linked_list_get(list, 2), item_3);

    TR_linked_list_free(&list);
}
END_TEST

START_TEST(test_linked_list_insert)
{
    TR_LinkedList list = TR_linked_list_alloc();
    char *item_1 = "Item 1";
    char *item_2 = "Item 2";
    char *item_3 = "Item 3";
    char *item_4 = "Item 4";
    char *item_5 = "Item 5";

    // Fill the list.
    TR_linked_list_append(list, item_1);
    TR_linked_list_append(list, item_2);
    TR_linked_list_append(list, item_3);
    TR_linked_list_append(list, item_4);
    ck_assert_int_eq(4, TR_linked_list_len(list));

    // Insert to start.
    int index = TR_linked_list_insert(list, 0, item_5);
    ck_assert_int_eq(0, index);
    ck_assert_int_eq(5, TR_linked_list_len(list));
    ck_assert_ptr_eq(TR_linked_list_get(list, 0), item_5);

    // Insert to middle.
    index = TR_linked_list_insert(list, 4, item_5);
    ck_assert_int_eq(4, index);
    ck_assert_int_eq(6, TR_linked_list_len(list));
    ck_assert_ptr_eq(TR_linked_list_get(list, 4), item_5);

    // Insert when index range over flows.
    index = TR_linked_list_insert(list, 10, item_5);
    ck_assert_int_eq(6, index);
    ck_assert_int_eq(7, TR_linked_list_len(list));
    ck_assert_ptr_eq(TR_linked_list_get(list, 6), item_5);

    // Insert with invalid index.
    index = TR_linked_list_insert(list, -1, item_5);
    ck_assert_int_eq(TR_INVALID_INDEX, index);
    // length stays the same.
    ck_assert_int_eq(7, TR_linked_list_len(list));

    TR_linked_list_free(&list);
}
END_TEST

START_TEST(test_linked_list_get)
{
    TR_LinkedList list = TR_linked_list_alloc();
    char *item_1 = "Item 1";
    char *item_2 = "Item 2";
    char *item_3 = "Item 3";
    char *item_4 = "Item 4";

    // Fill the list.
    TR_linked_list_append(list, item_1);
    TR_linked_list_append(list, item_2);
    TR_linked_list_append(list, item_3);
    TR_linked_list_append(list, item_4);
    ck_assert_int_eq(4, TR_linked_list_len(list));

    // With normal indexes.
    ck_assert_ptr_eq(TR_linked_list_get(list, 0), item_1);
    ck_assert_ptr_eq(TR_linked_list_get(list, 1), item_2);
    ck_assert_ptr_eq(TR_linked_list_get(list, 3), item_4);
    ck_assert_ptr_eq(TR_linked_list_get(list, 2), item_3);

    // With invalid index, should return null.
    ck_assert_ptr_eq(TR_linked_list_get(list, -1), NULL);
    ck_assert_ptr_eq(TR_linked_list_get(list, 10), NULL);

    TR_linked_list_free(&list);
}
END_TEST

START_TEST(test_linked_list_contains)
{
    TR_LinkedList list = TR_linked_list_alloc();
    char *item_1 = "Item 1";
    char *item_2 = "Item 2";
    char *item_3 = "Item 3";
    char *item_4 = "Item 4";
    char *item_5 = "Item 5";

    // Fill the list.
    TR_linked_list_append(list, item_1);
    TR_linked_list_append(list, item_2);
    TR_linked_list_append(list, item_3);
    TR_linked_list_append(list, item_4);

    ck_assert_int_eq(TR_linked_list_contains(list, item_1, 7), 0);
    ck_assert_int_eq(TR_linked_list_contains(list, item_2, 7), 1);
    ck_assert_int_eq(TR_linked_list_contains(list, item_3, 7), 2);
    ck_assert_int_eq(TR_linked_list_contains(list, item_4, 7), 3);

    // With item not in the list.
    ck_assert_int_eq(TR_linked_list_contains(list, item_5, 7), TR_INVALID_INDEX);
    // With null item.
    ck_assert_int_eq(TR_linked_list_contains(list, NULL, 7), TR_INVALID_INDEX);

    TR_linked_list_free(&list);
}
END_TEST


struct struct_for_test {
    int id;
    int age;
};

int find_for_test(void *value) {
    struct struct_for_test *v = value;
    if (v->id == 10) return 0;
    else return -1;
}


START_TEST(test_linked_list_find)
{
    TR_LinkedList list = TR_linked_list_alloc();

    // Empty list returns NULL.
    ck_assert_ptr_eq(TR_linked_list_find(list, find_for_test), NULL);

    struct struct_for_test obj_1  = {.age= 5, .id= 1};
    struct struct_for_test obj_2  = {.age= 5, .id= 2};
    struct struct_for_test obj_3  = {.age= 5, .id= 10};
    struct struct_for_test obj_4  = {.age= 5, .id= 4};

    // Fill the list.
    TR_linked_list_append(list, &obj_1);
    TR_linked_list_append(list, &obj_2);
    TR_linked_list_append(list, &obj_3);
    TR_linked_list_append(list, &obj_4);

    ck_assert_ptr_eq(TR_linked_list_find(list, find_for_test), &obj_3);

    TR_linked_list_remove(list, 2);
    ck_assert_ptr_eq(TR_linked_list_find(list, find_for_test), NULL);

    TR_linked_list_free(&list);
}
END_TEST

START_TEST(test_linked_list_len)
{
    TR_LinkedList list = TR_linked_list_alloc();

    int a, b, c, d;

    // Fill the list.
    TR_linked_list_append(list, &a);
    TR_linked_list_append(list, &b);
    TR_linked_list_append(list, &c);
    TR_linked_list_append(list, &d);
    
    ck_assert_int_eq(4, TR_linked_list_len(list));

    TR_linked_list_remove(list, 0);
    ck_assert_int_eq(3, TR_linked_list_len(list));

    TR_linked_list_remove(list, 0);
    ck_assert_int_eq(2, TR_linked_list_len(list));

    TR_linked_list_remove(list, 0);
    ck_assert_int_eq(1, TR_linked_list_len(list));

    TR_linked_list_remove(list, 0);
    ck_assert_int_eq(0, TR_linked_list_len(list));

    // remove one extra. Should be 0
    TR_linked_list_remove(list, 0);
    ck_assert_int_eq(0, TR_linked_list_len(list));

    TR_linked_list_free(&list);
}
END_TEST

START_TEST(test_linked_list_clear)
{
    TR_LinkedList list = TR_linked_list_alloc();

    int a, b, c, d;

    // Fill the list.
    TR_linked_list_append(list, &a);
    TR_linked_list_append(list, &b);
    TR_linked_list_append(list, &c);
    TR_linked_list_append(list, &d);
    ck_assert_int_eq(4, TR_linked_list_len(list));
    
    TR_linked_list_clear(list);
    ck_assert_int_eq(0, TR_linked_list_len(list));

    // Check when list is empty.
    TR_linked_list_clear(list);
    ck_assert_int_eq(0, TR_linked_list_len(list));

    TR_linked_list_free(&list);
}
END_TEST

int filter_for_test(void *value) {
    struct struct_for_test *v = value;
    if (v->id > 5) return 0;
    else return -1;
}

START_TEST(test_linked_list_filter)
{
    TR_LinkedList original_list = TR_linked_list_alloc();
    TR_LinkedList result_list;

    struct struct_for_test obj_1 = {.age= 5, .id= 1};
    struct struct_for_test obj_2 = {.age= 5, .id= 4};
    struct struct_for_test obj_3 = {.age= 5, .id= 10};
    struct struct_for_test obj_4 = {.age= 5, .id= 8};

    // Fill the list.
    TR_linked_list_append(original_list, &obj_1);
    TR_linked_list_append(original_list, &obj_2);
    TR_linked_list_append(original_list, &obj_3);
    TR_linked_list_append(original_list, &obj_4);

    result_list = TR_linked_list_filter(original_list, filter_for_test);

    // Only two objects fit the criteria.
    ck_assert_int_eq(2, TR_linked_list_len(result_list));

    // Order is the same.
    ck_assert_ptr_eq(&obj_3, TR_linked_list_get(result_list, 0));
    ck_assert_ptr_eq(&obj_4, TR_linked_list_get(result_list, 1));

    TR_linked_list_free(&result_list);
    TR_linked_list_clear(original_list);
    result_list = TR_linked_list_filter(original_list, filter_for_test);
    ck_assert_int_eq(0, TR_linked_list_len(result_list));

    TR_linked_list_free(&original_list);
    TR_linked_list_free(&result_list);
}
END_TEST

START_TEST(test_linked_list_reverse)
{
    TR_LinkedList list = TR_linked_list_alloc();

    int a = 0, b = 1, c = 2, d = 3;

    // Fill the list.
    TR_linked_list_append(list, &a);
    TR_linked_list_append(list, &b);
    TR_linked_list_append(list, &c);
    TR_linked_list_append(list, &d);

    ck_assert_ptr_eq(&a, TR_linked_list_get(list, 0));
    ck_assert_ptr_eq(&b, TR_linked_list_get(list, 1));
    ck_assert_ptr_eq(&c, TR_linked_list_get(list, 2));
    ck_assert_ptr_eq(&d, TR_linked_list_get(list, 3));

    TR_linked_list_reverse(list);

    ck_assert_ptr_eq(&d, TR_linked_list_get(list, 0));
    ck_assert_ptr_eq(&c, TR_linked_list_get(list, 1));
    ck_assert_ptr_eq(&b, TR_linked_list_get(list, 2));
    ck_assert_ptr_eq(&a, TR_linked_list_get(list, 3));

    TR_linked_list_free(&list);
}
END_TEST

START_TEST(test_linked_list_array_copy)
{
    TR_LinkedList list = TR_linked_list_alloc();
    const int ARR_LEN = 4;

    int a = 0, b = 1, c = 2, d = 3;
    int array[ARR_LEN];

    // Fill the list.
    TR_linked_list_append(list, &a);
    TR_linked_list_append(list, &b);
    TR_linked_list_append(list, &c);
    TR_linked_list_append(list, &d);

    int count = TR_linked_list_array_copy(list, 0, ARR_LEN, sizeof(int), array);
    ck_assert_int_eq(ARR_LEN, count);
    for (int i = 0; i < 4; i++)
    {
        ck_assert_int_eq(array[i], i);
    }

    memset(array, 0, ARR_LEN * sizeof(int));
    // Only two value in range 2-4. Expect only last two be copied.
    count = TR_linked_list_array_copy(list, 2, ARR_LEN, sizeof(int), array);
    ck_assert_int_eq(array[0], 2);
    ck_assert_int_eq(array[1], 3);
    ck_assert_int_eq(2, count);

    TR_linked_list_free(&list);
}
END_TEST

START_TEST(test_linked_list_remove)
{
    TR_LinkedList list = TR_linked_list_alloc();

    int a = 0, b = 1, c = 2, d = 3;

    // Fill the list.
    TR_linked_list_append(list, &a);
    TR_linked_list_append(list, &b);
    TR_linked_list_append(list, &c);
    TR_linked_list_append(list, &d);

    ck_assert_ptr_eq(&b, TR_linked_list_get(list, 1));
    ck_assert_int_eq(4, TR_linked_list_len(list));

    void *item = TR_linked_list_remove(list, 1);
    ck_assert_ptr_eq(&b, item);
    ck_assert_ptr_eq(&c, TR_linked_list_get(list, 1));
    ck_assert_int_eq(3, TR_linked_list_len(list));

    item = TR_linked_list_remove(list, 4);
    ck_assert_ptr_eq(NULL, item);

    item = TR_linked_list_remove(list, 0);
    ck_assert_ptr_eq(&a, item);

    TR_linked_list_free(&list);
}
END_TEST

START_TEST(test_linked_list_shift)
{
    TR_LinkedList list = TR_linked_list_alloc();

    int a = 0, b = 1, c = 2, d = 3;

    // Fill the list.
    TR_linked_list_append(list, &a);
    TR_linked_list_append(list, &b);
    TR_linked_list_append(list, &c);
    TR_linked_list_append(list, &d);
    ck_assert_int_eq(4, TR_linked_list_len(list));

    void *result = TR_linked_list_shift(list);
    ck_assert_ptr_eq(&a, result);
    ck_assert_ptr_eq(&d, TR_linked_list_get(list, 2));
    ck_assert_int_eq(3, TR_linked_list_len(list));

    result = TR_linked_list_shift(list);
    ck_assert_ptr_eq(&b, result);
    ck_assert_ptr_eq(&d, TR_linked_list_get(list, 1));
    ck_assert_int_eq(2, TR_linked_list_len(list));

    result = TR_linked_list_shift(list);
    ck_assert_ptr_eq(&c, result);
    ck_assert_ptr_eq(&d, TR_linked_list_get(list, 0));
    ck_assert_int_eq(1, TR_linked_list_len(list));

    result = TR_linked_list_shift(list);
    ck_assert_ptr_eq(&d, result);
    ck_assert_ptr_eq(NULL, TR_linked_list_get(list, 0));
    ck_assert_int_eq(0, TR_linked_list_len(list));

    // Empty list.
    result = TR_linked_list_shift(list);
    ck_assert_ptr_eq(NULL, result);
    ck_assert_ptr_eq(NULL, TR_linked_list_get(list, 0));
    ck_assert_int_eq(0, TR_linked_list_len(list));

    TR_linked_list_free(&list);
}
END_TEST

START_TEST(test_linked_list_pop)
{
    TR_LinkedList list = TR_linked_list_alloc();

    int a = 0, b = 1, c = 2, d = 3;

    // Fill the list.
    TR_linked_list_append(list, &a);
    TR_linked_list_append(list, &b);
    TR_linked_list_append(list, &c);
    TR_linked_list_append(list, &d);
    ck_assert_int_eq(4, TR_linked_list_len(list));

    void *result = TR_linked_list_pop(list);
    ck_assert_ptr_eq(&d, result);
    ck_assert_int_eq(3, TR_linked_list_len(list));

    result = TR_linked_list_pop(list);
    ck_assert_ptr_eq(&c, result);
    ck_assert_int_eq(2, TR_linked_list_len(list));

    result = TR_linked_list_pop(list);
    ck_assert_ptr_eq(&b, result);
    ck_assert_int_eq(1, TR_linked_list_len(list));

    result = TR_linked_list_pop(list);
    ck_assert_ptr_eq(&a, result);
    ck_assert_int_eq(0, TR_linked_list_len(list));

    // Empty list.
    result = TR_linked_list_pop(list);
    ck_assert_ptr_eq(NULL, result);
    ck_assert_int_eq(0, TR_linked_list_len(list));

    TR_linked_list_free(&list);
}
END_TEST

START_TEST(test_linked_list_iterate)
{

TR_LinkedList list = TR_linked_list_alloc();

    int item_1 = 0;
    int item_2 = 1;
    int item_3 = 2;
    int item_4 = 3;

    TR_linked_list_append(list, &item_1);
    TR_linked_list_append(list, &item_2);
    TR_linked_list_append(list, &item_3);
    TR_linked_list_append(list, &item_4);

    TR_Iterator iter = TR_linked_list_iterate(list);

    ck_assert(TR_linked_list_iter_has_next(iter));

    int i = 0;
    while (TR_linked_list_iter_has_next(iter))
    {
        ck_assert_int_eq(i++, *(int*)TR_Linked_list_iter_value(iter));
        iter = TR_linked_list_iter_next(iter);
    }

    ck_assert(!TR_linked_list_iter_has_next(iter));

    TR_linked_list_free(&list);
}
END_TEST

#pragma endregion Linked List Tests

START_TEST(test_array_list_alloc)
{
    TR_ArrayList list = TR_array_list_alloc();
    ck_assert_ptr_ne(NULL, list);

    ck_assert_int_eq(0, TR_array_list_len(list));

    TR_array_list_free(&list);
}
END_TEST

START_TEST(test_array_list_free)
{
    TR_ArrayList list = TR_array_list_alloc();
    TR_array_list_free(&list);
    ck_assert_ptr_eq(NULL, list);
}
END_TEST

START_TEST(test_array_list_append)
{
    TR_ArrayList list = TR_array_list_alloc();

    int a, b, c;
    TR_array_list_append(list, &a);
    TR_array_list_append(list, &b);
    TR_array_list_append(list, &c);

    int *a_addr = TR_array_list_get(list, 0);
    int *b_addr = TR_array_list_get(list, 1);
    int *c_addr = TR_array_list_get(list, 2);

    ck_assert_ptr_eq(a_addr, &a);
    ck_assert_ptr_eq(b_addr, &b);
    ck_assert_ptr_eq(c_addr, &c);

    TR_array_list_free(&list);
}
END_TEST

START_TEST(test_array_list_get)
{
    TR_ArrayList list = TR_array_list_alloc();

    int a, b, c;
    TR_array_list_append(list, &a);
    TR_array_list_append(list, &b);
    TR_array_list_append(list, &c);

    int *a_addr = TR_array_list_get(list, 0);
    int *b_addr = TR_array_list_get(list, 1);
    int *c_addr = TR_array_list_get(list, 2);
    void *invalid_addr = TR_array_list_get(list, 4);

    ck_assert_ptr_eq(a_addr, &a);
    ck_assert_ptr_eq(b_addr, &b);
    ck_assert_ptr_eq(c_addr, &c);
    ck_assert_ptr_eq(invalid_addr, NULL);

    TR_array_list_free(&list);
}
END_TEST

START_TEST(test_array_list_put)
{
    TR_ArrayList list = TR_array_list_alloc();

    int a, b;
    TR_array_list_append(list, &a);
    TR_array_list_put(list, 0, &b);
    int i = TR_array_list_put(list, 18, &b);

    int *b_addr = TR_array_list_get(list, 0);

    ck_assert_ptr_eq(b_addr, &b);
    ck_assert_int_eq(TR_INVALID_INDEX, i);

    TR_array_list_free(&list);
}
END_TEST

START_TEST(test_array_list_insert)
{
    TR_ArrayList list = TR_array_list_alloc();

    int a, b, c;
    TR_array_list_append(list, &a);
    TR_array_list_append(list, &b);

    TR_array_list_insert(list, 1, &c);

    int *a_addr = TR_array_list_get(list, 0);
    int *c_addr = TR_array_list_get(list, 1);
    int *b_addr = TR_array_list_get(list, 2);

    ck_assert_ptr_eq(a_addr, &a);
    ck_assert_ptr_eq(b_addr, &b);
    ck_assert_ptr_eq(c_addr, &c);
    ck_assert_int_eq(3, TR_array_list_len(list));

    TR_array_list_insert(list, 0, &c);
    ck_assert_ptr_eq(&c, TR_array_list_get(list, 0));
    ck_assert_ptr_eq(&a, TR_array_list_get(list, 1));

    ck_assert_int_eq(4, TR_array_list_len(list));

    TR_array_list_free(&list);
}
END_TEST

START_TEST(test_array_list_remove)
{

    TR_ArrayList list = TR_array_list_alloc();

    int a, b;
    TR_array_list_append(list, &a);
    TR_array_list_append(list, &b);

    int *a_addr = TR_array_list_get(list, 0);
    int *b_addr = TR_array_list_get(list, 1);

    ck_assert_ptr_eq(a_addr, &a);
    ck_assert_ptr_eq(b_addr, &b);
    ck_assert_int_eq(2, TR_array_list_len(list));

    a_addr = TR_array_list_remove(list, 0);
    b_addr = TR_array_list_remove(list, 0);

    ck_assert_ptr_eq(a_addr, &a);
    ck_assert_ptr_eq(b_addr, &b);
    ck_assert_int_eq(0, TR_array_list_len(list));

    TR_array_list_remove(list, 0);
    ck_assert_int_eq(0, TR_array_list_len(list));

    void *invalid_addr = TR_array_list_remove(list, 666);
    ck_assert_ptr_eq(invalid_addr, NULL);
    ck_assert_int_eq(0, TR_array_list_len(list));

    TR_array_list_free(&list);
}
END_TEST

START_TEST(test_array_list_pop)
{
    TR_ArrayList list = TR_array_list_alloc();

    int a, b;
    TR_array_list_append(list, &a);
    TR_array_list_append(list, &b);

    ck_assert_int_eq(2, TR_array_list_len(list));

    int *result;
    result = TR_array_list_pop(list);
    ck_assert_int_eq(1, TR_array_list_len(list));
    ck_assert_ptr_eq(&b, result);

    result = TR_array_list_pop(list);
    ck_assert_int_eq(0, TR_array_list_len(list));
    ck_assert_ptr_eq(&a, result);

    result = TR_array_list_pop(list);
    ck_assert_int_eq(0, TR_array_list_len(list));
    ck_assert_ptr_eq(NULL, result);

    TR_array_list_free(&list);
}
END_TEST

START_TEST(test_array_list_shift)
{
    TR_ArrayList list = TR_array_list_alloc();

    int a, b;
    TR_array_list_append(list, &a);
    TR_array_list_append(list, &b);

    ck_assert_int_eq(2, TR_array_list_len(list));

    int *result;
    result = TR_array_list_shift(list);
    ck_assert_int_eq(1, TR_array_list_len(list));
    ck_assert_ptr_eq(&a, result);

    result = TR_array_list_shift(list);
    ck_assert_int_eq(0, TR_array_list_len(list));
    ck_assert_ptr_eq(&b, result);

    result = TR_array_list_shift(list);
    ck_assert_int_eq(0, TR_array_list_len(list));
    ck_assert_ptr_eq(NULL, result);

    TR_array_list_free(&list);
}
END_TEST

START_TEST(test_array_list_iterate)
{
    TR_ArrayList list = TR_array_list_alloc();

    int a = 0, b = 1;
    TR_array_list_append(list, &a);
    TR_array_list_append(list, &b);

    int n = 0;
    TR_Iterator iter = TR_array_list_iter(list);
    while (TR_array_list_iter_has_next(iter))
    {
        int *val = TR_array_list_iter_value(iter);
        ck_assert_int_eq(n++, *val);
        iter = TR_array_list_iter_next(iter);
    }

    free(iter);

    TR_array_list_free(&list);
}
END_TEST

START_TEST(test_array_list_len)
{
    TR_ArrayList list = TR_array_list_alloc();

    int a, b, c;
    int len = TR_array_list_len(list);
    ck_assert_int_eq(0, len);

    TR_array_list_append(list, &a);
    len = TR_array_list_len(list);
    ck_assert_int_eq(1, len);

    TR_array_list_append(list, &b);
    len = TR_array_list_len(list);
    ck_assert_int_eq(2, len);

    TR_array_list_append(list, &c);
    len = TR_array_list_len(list);
    ck_assert_int_eq(3, len);

    TR_array_list_free(&list);
}
END_TEST

void test_linked_list_load_cases(Suite *suite)
{
    test_add_case(suite, test_linked_list_alloc);
    test_add_case(suite, test_linked_list_free);
    test_add_case(suite, test_linked_list_append);
    test_add_case(suite, test_linked_list_insert);
    test_add_case(suite, test_linked_list_get);
    test_add_case(suite, test_linked_list_contains);
    test_add_case(suite, test_linked_list_find);
    test_add_case(suite, test_linked_list_remove);
    test_add_case(suite, test_linked_list_len);
    test_add_case(suite, test_linked_list_clear);
    test_add_case(suite, test_linked_list_filter);
    test_add_case(suite, test_linked_list_reverse);
    test_add_case(suite, test_linked_list_array_copy);
    test_add_case(suite, test_linked_list_shift);
    test_add_case(suite, test_linked_list_pop);
    test_add_case(suite, test_linked_list_iterate);

    test_add_case(suite, test_array_list_alloc);
    test_add_case(suite, test_array_list_free);
    test_add_case(suite, test_array_list_append);
    test_add_case(suite, test_array_list_len);
    test_add_case(suite, test_array_list_get);
    test_add_case(suite, test_array_list_put);
    test_add_case(suite, test_array_list_insert);
    test_add_case(suite, test_array_list_remove);
    test_add_case(suite, test_array_list_pop);
    test_add_case(suite, test_array_list_shift);
    test_add_case(suite, test_array_list_iterate);
}
