#include "linked_list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

node_t* make_test_node(char* str);
node_t* make_test_node_int(int num);
node_t* alloc_test_node(void* data);
char* alloc_test_string(const char* str);
int* alloc_test_int(int x);

void test_existing();



/**
 * test_existing:  Test linked list functions that are already implemented
 * in the stencil version of the lab.
 *
 * YOU SHOULD NOT MODIFY THIS FUNCTION.  You should assume that all of
 * the test code here uses the linked list library properly -- all
 * bugs are contained in linked_list.c.
 */
void test_existing() {
    // Test setup:  create a list with 3 elements
    // "test" -> "test1" -> "test2"
    char* s1 = alloc_test_string("test");
    char* s2 = alloc_test_string("test1");
    char* s3 = alloc_test_string("test2");
    node_t* n1 = alloc_test_node(s1);
    node_t* n2 = alloc_test_node(s2);
    node_t* n3 = alloc_test_node(s3);
    n1->prev = NULL;
    n1->next = n2;
    n2->prev = n1;
    n2->next = n3;
    n3->prev = n2;
    n3->next = NULL;

    // Start of a list is just a pointer to its first node
    node_t* list_a = n1;

    // *** TEST LENGTH ***
    int three_element_len = ll_length(list_a);
    assert(three_element_len == 3);

    assert(ll_length(n3) == 1); // Starting from last node, list has length 1

    node_t* list_b = NULL; // Make a new empty list
    assert(ll_length(list_b) == 0);


    // *** TEST GET_FIRST ***
    char* first_empty = ll_get_first(list_b);
    assert(!first_empty); // same as assert(first_empty == NULL)

    char* first = ll_get_first(list_a);
    assert(!strcmp(first, "test"));

    // *** TEST REMOVE_FIRST ***
    char* removed = ll_remove_first(&list_a);

    assert(removed == s1);            // Compare pointers
    assert(!strcmp(removed, "test")); // Compare contents
    free(removed);

    // now the list looks like: test1 -> test2
    assert(ll_length(list_a) == 2);

    // *** TEST INSERT_LAST AND GET_LAST ***
    // add another element to list_a (this time, a long!)
    long a_long = 401;
    long* long_mem = (long*)malloc(sizeof(long));
    *long_mem = a_long;
    ll_insert_last(&list_a, long_mem);
    long* last_data = ll_get_last(list_a);
    assert(long_mem == last_data); // Compare the pointers
    assert(*last_data == 401);  // Compare the **data**

    // list should look like: test1 -> test2 -> 401

    // *** TEST REVERSE ***
    // reverse an empty list
    ll_reverse(&list_b);
    assert(ll_length(list_b) == 0);

    // reverse a three element list
    // new list should look like: 401 -> test2 -> test1
    ll_reverse(&list_a);

    // Size should be unchanged
    assert(ll_length(list_a) == 3);

    // Check the elements
    long* new_first_element = ll_get_first(list_a);
    assert(*new_first_element == 401);
    char* new_last_element = ll_get_last(list_a);
    assert(!strcmp(new_last_element, "test1"));

    // Remove the elements
    char* data1 = ll_remove_element(&list_a, "test1", 6);
    char* data2 = ll_remove_element(&list_a, "test2", 6);
    long* data3 = ll_remove_element(&list_a, &a_long, sizeof(long));
    assert(list_a == NULL);

    free(data1);
    free(data2);
    free(data3);

    // list should now be empty
    assert(ll_length(list_a) == 0);
}

void test_student_get() {
    // Make a list with one element
    char* str1 = "systems";
    node_t* node1 = make_test_node(str1);
    node_t* list1 = node1;

    // *** TESTS FOR LL_GET ***
    node_t* empty_list = NULL;
    assert(!ll_get(empty_list, 0));
    assert(!ll_get(empty_list, 2));

    char* get1 = ll_get(list1, 0);
    assert(!strcmp(get1, str1));
    assert(!ll_get(list1, 1));

    int one = 1;
    node_t* list2 = make_test_node_int(one);
    int* get2 = ll_get(list2, 0);
    assert(*get2 == one);

    free(list1->data);
    free(list1);
    free(list2->data);
    free(list2);

    // Make a four-element list
    char* check[] = {"hello", "world", "how", "cool"};
    node_t* four_list = malloc(sizeof(node_t));
    four_list->data = "hello";
    node_t* fl2 = malloc(sizeof(node_t));
    fl2->data = "world";
    node_t* fl3 = malloc(sizeof(node_t));
    fl3->data = "how";
    node_t* fl4 = malloc(sizeof(node_t));
    fl4->data = "cool";
    four_list->prev = NULL;
    four_list->next = fl2;
    fl2->prev = four_list;
    fl2->next = fl3;
    fl3->prev = fl2;
    fl3->next = fl4;
    fl4->prev = fl3;
    fl4->next = NULL;

    // *** MORE TESTS FOR LL_GET ***
    for (int i = 0; i < 4; i++) {
        assert(!strcmp(ll_get(four_list, i), check[i]));
    }

    free(four_list);
    free(fl2);
    free(fl3);
    free(fl4);
}



/**
 * test_student_insert_first:  Tests for your insert_first function
 *
 * YOU SHOULD NOT MODIFY THIS FUNCTION.  You should assume that all of
 * the test code here uses the linked list library properly -- all
 * bugs are contained in linked_list.c.
 */
void test_student_insert_first() {
    // *** TEST INSERT_FIRST ***

    node_t* list3 = NULL;

    char* s1 = alloc_test_string("programming");
    ll_insert_first(&list3, s1);
    assert(ll_length(list3) == 1);

    assert(!strcmp(ll_get_first(list3), ll_get_last(list3)));
    assert(list3->data == s1);
    assert(!list3->prev);
    assert(!list3->next);

    // Make another one-element list
    char* s2 = alloc_test_string("systems");
    node_t* list_b = NULL;
    ll_insert_first(&list_b, s2);

    // Add another element
    char* s3 = alloc_test_string("computer");
    ll_insert_first(&list_b, s3);

    // list_b should now be "computer" -> "systems"
    assert(!strcmp(ll_get_first(list_b), "computer"));
    assert(!list_b->prev);

    node_t* next_element = list_b->next;
    assert(next_element->prev == list_b);
    assert(!strcmp(next_element->data, "systems"));
    assert(!strcmp(ll_get(list_b, 1), "systems"));

    // Cleanup
    // (need to manually clean up list nodes since we haven't tested remove yet)
    assert(list3->data == s1);
    free(list3->data);
    free(list3);

    assert(next_element->data == s2);
    free(next_element->data);
    free(next_element);
    assert(list_b->data == s3);
    free(list_b->data);
    free(list_b);
}


/**
 * test_student_remove:  Tests for your remove functions
 *
 * YOU SHOULD NOT MODIFY THIS FUNCTION.  You should assume that all of
 * the test code here uses the linked list library properly -- all
 * bugs are contained in linked_list.c.
 */

void test_student_remove() {

    char* s1 = alloc_test_string("programming");
    node_t* list_a = NULL;
    ll_insert_first(&list_a, s1);

    // **** Remove from one-element list ****
    char* removed_empty = ll_remove_last(&list_a);
    assert(!ll_get_last(list_a));
    assert(!ll_get(list_a, 0));
    assert(ll_length(list_a) == 0);
    assert(!list_a);
    free(removed_empty);

    // **** Try to remove from empty list ****
    assert(!ll_remove_last(&list_a));


    // **** Make and remove from a two-element list ****
    char* s2 = alloc_test_string("systems");
    char* s3 = alloc_test_string("computer");

    node_t* list_b = NULL;
    ll_insert_first(&list_b, s2);
    ll_insert_first(&list_b, s3);
    // list1 is now "computer" -> "systems"

    node_t* head_before_remove = list_b;
    char* removed_one = ll_remove_last(&list_b);
    assert(!strcmp(removed_one, "systems")); // Compare data
    assert(removed_one == s2); // Compare pointers
    free(removed_one);

    assert(!list_b->next);
    assert(!list_b->prev);
    assert(ll_length(list_b) == 1);
    assert(!strcmp(ll_get(list_b, 0), "computer"));
    assert(list_b == head_before_remove);

    char* data3 = ll_remove_element(&list_b, "computer", 9);
    assert(data3 == s3);
    free(data3);
    assert(list_b == NULL); // list should now be empty

    // ****************************
    // make a new list:  3 -> 2 -> 1
    int* num1 = alloc_test_int(1);
    int* num2 = alloc_test_int(2);
    int* num3 = alloc_test_int(3);
    node_t* nums = NULL;

    ll_insert_first(&nums, num1);
    ll_insert_first(&nums, num2);
    ll_insert_first(&nums, num3);

    // nums is now 3 -> 2 -> 1
    head_before_remove = nums;
    void* removed_num = ll_remove_last(&nums);
    assert(*(int*)removed_num == 1);
    assert(nums->data == num3);
    assert(nums == head_before_remove);
    free(removed_num);

    removed_num = ll_remove_last(&nums);
    assert(*(int*)removed_num == 2);
    assert(nums == head_before_remove);
    free(removed_num);

    removed_num = ll_remove_first(&nums);
    assert(*(int*)removed_num == 3);
    free(removed_num);
}


void test_student_implementation() {
    test_student_get();
    test_student_insert_first();
    test_student_remove();
}

int main(int argc, char** argv) {
    if (argc == 2) {
	if (!strcmp(argv[1], "all")) {
	    printf("===Running all linked list tests===\n");
	    test_existing();
	    test_student_implementation();
	    printf("\033[32mALL TESTS PASSED!\033[0m\n");
	} else if (!strcmp(argv[1], "existing")) {
	    printf("===Running only existing implementation tests===\n");
	    test_existing();
	    printf("\033[32mALL EXISTING TESTS PASSED!\033[0m\n");
	} else if (!strcmp(argv[1], "student")) {
	    printf("===Running only student implementation tests===\n");
	    test_student_implementation();
	    printf("\033[32mALL STUDENT TESTS PASSED!\033[0m\n");
	} else {
	    printf("usage: <all | existing | student>\n");
	}
    } else {
	printf("usage: <all | existing | student>\n");
    }
}


// Helper:  allocate a list node with a string as data
node_t* make_test_node(char* str) {
    size_t len = strlen(str) + 1;
    node_t* new_node = malloc(sizeof(node_t));
    new_node->data = malloc(len);
    new_node->prev = NULL;
    new_node->next = NULL;
    memcpy(new_node->data, str, len);

    return new_node;
}

// Helper: allocate a list node with an int as data
node_t* make_test_node_int(int num) {
    node_t* new_node = malloc(sizeof(node_t));
    new_node->data = malloc(sizeof(int));
    new_node->prev = NULL;
    new_node->next = NULL;
    memcpy(new_node->data, &num, sizeof(int));

    return new_node;
}


// Helper:  allocate a list node, given a pointer to the data
node_t* alloc_test_node(void* data) {
    node_t* new_node = malloc(sizeof(node_t));
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next = NULL;

    return new_node;
}


// Helper:  allocate space for a string on the heap,
// then copy the string data there
char* alloc_test_string(const char* str) {
    size_t len = strlen(str) + 1;
    char* data = (char*)malloc(len);
    memcpy(data, str, len);

    return data;
}

// Helper:  allocate space for an int on the heap
int* alloc_test_int(int x) {
    int* data = (int*)malloc(sizeof(int));
    *data = x;

    return data;
}
