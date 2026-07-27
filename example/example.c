// A simple example demonstrating the basic usage of MLib List


#include "../list/list.h"
#include <stdio.h>


struct test {
        int val;
        mlib_list_head_t list;
};


int main(void)
{
        mlib_list_head_t head;
        struct test t1 = {.val = 1};
        struct test t2 = {.val = 2};
        struct test *iter;

        mlib_list_head_init(&head);


        mlib_list_add(&t1.list, &head);
        mlib_list_add(&t2.list, &head);


        mlib_list_for_each_entry(iter, &head, list) {
                printf("%d\n", iter->val);
        }


        mlib_list_del(&t2.list);
        mlib_list_del(&t1.list);
}