#pragma once



/*
----FULL-API----


Data types:
- mlib_list_head_t    List head/node structure {next, prev}

Utility macros:
- mlib_list_util_container_of(ptr, type, member)    Get container from member pointer

Entry access:
- mlib_list_entry(list, type, member)               Get entry from list head
- mlib_list_next(list)                              Get next node
- mlib_list_prev(list)                              Get previous node

List information:
- mlib_list_is_head(list, head)                     Check if node is head
- mlib_list_is_singular(head)                       Check if list has exactly one element
- mlib_list_empty(head)                             Check if list is empty
- mlib_list_is_first(list, head)                    Check if node is first element
- mlib_list_is_last(list, head)                     Check if node is last element

First/Last entry access:
- mlib_list_first_entry(head, type, member)         Get first entry in list
- mlib_list_last_entry(head, type, member)          Get last entry in list
- mlib_list_next_entry(p, member)                   Get next entry from current
- mlib_list_prev_entry(p, member)                   Get previous entry from current

Iteration macros:
- mlib_list_for_each(p, head)                       Forward iteration over nodes
- mlib_list_for_each_prev(p, head)                  Reverse iteration over nodes
- mlib_list_for_each_safe(p, tmp, head)             Safe forward iteration (delete-safe)
- mlib_list_for_each_prev_safe(p, tmp, head)        Safe reverse iteration (delete-safe)
- mlib_list_for_each_entry(p, head, member)         Forward iteration over entries
- mlib_list_for_each_entry_prev(p, head, member)    Reverse iteration over entries
- mlib_list_for_each_entry_safe(p, tmp, head, member)      Safe forward entry iteration
- mlib_list_for_each_entry_prev_safe(p, tmp, head, member) Safe reverse entry iteration

Initialization:
- mlib_list_head_init(head)                         Initialize empty list head

Adding elements:
- mlib_list_add(list, head)                         Add node after head (at beginning)
- mlib_list_add_tail(list, head)                    Add node before head (at end)

Removing elements:
- mlib_list_del(list)                               Remove node from list
- mlib_list_del_init(list)                          Remove node and reinitialize it
- mlib_list_move(list, head)                        Move node to beginning
- mlib_list_move_tail(list, head)                   Move node to end

Replacing:
- mlib_list_replace(old, new)                       Replace old node with new
- mlib_list_replace_init(old, new)                  Replace and reinitialize old node

Splicing:
- mlib_list_splice(list, head)                      Move entire list to beginning
- mlib_list_splice_tail(list, head)                 Move entire list to end
- mlib_list_splice_init(list, head)                 Move and reinitialize source list


----------------
*/




#include <stddef.h>




#define mlib_list_util_container_of(ptr, type, member) \
        (type*)((unsigned char*)(ptr) - offsetof(type, member))




typedef struct mlib_list_head {
        struct mlib_list_head *next;
        struct mlib_list_head *prev;
} mlib_list_head_t;



#define mlib_list_entry(list, type, member) ({                                  \
                mlib_list_head_t *__mliblist_list = (list);                     \
                mlib_list_util_container_of(__mliblist_list, type, member); \
        })


#define mlib_list_next(list)    (list)->next
#define mlib_list_prev(list)    (list)->prev


#define mlib_list_is_head(list, head)   ((list) == (head))


#define mlib_list_is_singular(head) ({                                          \
                mlib_list_head_t *__mliblist_head = (head);                     \
                (__mliblist_head->next != __mliblist_head &&                    \
                        __mliblist_head->next->next == __mliblist_head);        \
        })


#define mlib_list_empty(head) ({                                \
                mlib_list_head_t *__mliblist_head = (head);     \
                (__mliblist_head->next == __mliblist_head);     \
        })


#define mlib_list_is_first(list, head)  ((list)->prev == (head))
#define mlib_list_is_last(list, head)   ((list)->next == (head))


#define mlib_list_first_entry(head, type, member) \
        mlib_list_util_container_of((head)->next, type, member)


#define mlib_list_last_entry(head, type, member) \
        mlib_list_util_container_of((head)->prev, type, member)


#define mlib_list_next_entry(p, member) \
        mlib_list_util_container_of((p)->member.next, __typeof__(*(p)), member)


#define mlib_list_prev_entry(p, member) \
        mlib_list_util_container_of((p)->member.prev, __typeof__(*(p)), member)



#define mlib_list_for_each(p, head) \
        for ((p) = (head)->next; (p) != (head); (p) = (p)->next)


#define mlib_list_for_each_prev(p, head) \
        for ((p) = (head)->prev; (p) != (head); (p) = (p)->prev)


#define mlib_list_for_each_safe(p, tmp, head)           \
        for ((p) = (head)->next, (tmp) = (p)->next;     \
                (p) != (head);                          \
                (p) = (tmp), (tmp) = (tmp)->next)       \


#define mlib_list_for_each_prev_safe(p, tmp, head)      \
        for ((p) = (head)->prev, (tmp) = (p)->prev;     \
                (p) != (head);                          \
                (p) = (tmp), (tmp) = (tmp)->prev)       \


#define mlib_list_for_each_entry(p, head, member)                               \
        for ((p) = mlib_list_first_entry((head), __typeof__(*(p)), member);     \
                &(p)->member != (head);                                         \
                (p) = mlib_list_next_entry((p), member))


#define mlib_list_for_each_entry_prev(p, head, member)                          \
        for ((p) = mlib_list_last_entry((head), __typeof__(*(p)), member);      \
                &(p)->member != (head);                                         \
                (p) = mlib_list_prev_entry((p), member))


#define mlib_list_for_each_entry_safe(p, tmp, head, member)                     \
        for ((p) = mlib_list_first_entry((head), __typeof__(*(p)), member),     \
                        (tmp) = mlib_list_next_entry((p), member);              \
                &(p)->member != (head);                                         \
                (p) = (tmp), (tmp) = mlib_list_next_entry((tmp), member))


#define mlib_list_for_each_entry_prev_safe(p, tmp, head, member)                \
        for ((p) = mlib_list_last_entry((head), __typeof__(*(p)), member),      \
                        (tmp) = mlib_list_prev_entry((p), member);              \
                &(p)->member != (head);                                         \
                (p) = (tmp), (tmp) = mlib_list_prev_entry((tmp), member))




static inline void mlib_list_head_init(mlib_list_head_t *head)
{
        head->next = head;
        head->prev = head;
}


static inline void mlib_list_add(mlib_list_head_t *list,
        mlib_list_head_t *head)
{
        list->next = head->next;
        list->prev = head;

        head->next->prev = list;
        head->next = list;
}


static inline void mlib_list_add_tail(mlib_list_head_t *list,
        mlib_list_head_t *head)
{
        list->next = head;
        list->prev = head->prev;

        head->prev->next = list;
        head->prev = list;
}


static inline void mlib_list_replace(mlib_list_head_t *old,
        mlib_list_head_t *new)
{
        new->next = old->next;
        new->prev = old->prev;

        old->next->prev = new;
        old->prev->next = new;
}


static inline void mlib_list_replace_init(mlib_list_head_t *old,
        mlib_list_head_t *new)
{
        mlib_list_replace(old, new);
        mlib_list_head_init(old);
}


static inline void mlib_list_splice(mlib_list_head_t *list,
        mlib_list_head_t *head)
{
        if (mlib_list_empty(list))
                return;

        list->next->prev = head;
        list->prev->next = head->next;

        head->next->prev = list->prev;
        head->next = list->next;
}


static inline void mlib_list_splice_tail(mlib_list_head_t *list,
        mlib_list_head_t *head)
{
        if (mlib_list_empty(list))
                return;


        list->prev->next = head;
        list->next->prev = head->prev;

        head->prev->next = list->next;
        head->prev = list->prev;
}


static inline void mlib_list_splice_init(mlib_list_head_t *list,
        mlib_list_head_t *head)
{
        if (!mlib_list_empty(list))
                mlib_list_splice(list, head);


        mlib_list_head_init(list);
}


static inline void mlib_list_del(mlib_list_head_t *list)
{
        list->next->prev = list->prev;
        list->prev->next = list->next;
}


static inline void mlib_list_del_init(mlib_list_head_t *list)
{
        mlib_list_del(list);
        mlib_list_head_init(list);
}


static inline void mlib_list_move(mlib_list_head_t *list,
        mlib_list_head_t *head)
{
        mlib_list_del(list);
        mlib_list_add(head, list);
}


static inline void mlib_list_move_tail(mlib_list_head_t *list,
        mlib_list_head_t *head)
{
        mlib_list_del(list);
        mlib_list_add_tail(head, list);
}
