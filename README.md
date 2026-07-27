# MLib List

MLib List is a small header-only implementation of an intrusive doubly linked
list for C, inspired by the Linux kernel `list.h`.

The library is lightweight, allocation-free, and suitable for embedded systems,
operating systems, kernels, and general-purpose C projects.

## Features

- Header-only
- Intrusive doubly linked list
- No dynamic memory allocation
- O(1) insertion and removal
- Linux kernel-like API
- Safe iteration macros
- List splicing, moving, and replacement helpers

## Building the Example

Run:

```sh
./test.sh
```

or compile manually:

```sh
cc example/example.c -o example
./example
```

Expected output:

```
2
1
```

## Basic Usage

```c
#include "list/list.h"
#include <stdio.h>

struct node {
    int value;
    mlib_list_head_t list;
};

int main(void)
{
    mlib_list_head_t head;
    struct node a = { .value = 1 };
    struct node b = { .value = 2 };
    struct node *iter;

    mlib_list_head_init(&head);

    mlib_list_add(&a.list, &head);
    mlib_list_add(&b.list, &head);

    mlib_list_for_each_entry(iter, &head, list)
        printf("%d\n", iter->value);

    return 0;
}
```

## API Overview

### Initialization

```c
mlib_list_head_init()
```

Initialize an empty list.

### Adding

```c
mlib_list_add()
mlib_list_add_tail()
```

Insert elements at the beginning or end of the list.

### Removing

```c
mlib_list_del()
mlib_list_del_init()
```

Remove elements from a list.

### Moving

```c
mlib_list_move()
mlib_list_move_tail()
```

Move existing elements within a list.

### Replacing

```c
mlib_list_replace()
mlib_list_replace_init()
```

Replace one list node with another.

### Splicing

```c
mlib_list_splice()
mlib_list_splice_tail()
mlib_list_splice_init()
```

Merge entire lists in constant time.

### Iteration

Node iteration:

```c
mlib_list_for_each()
mlib_list_for_each_prev()
mlib_list_for_each_safe()
mlib_list_for_each_prev_safe()
```

Entry iteration:

```c
mlib_list_for_each_entry()
mlib_list_for_each_entry_prev()
mlib_list_for_each_entry_safe()
mlib_list_for_each_entry_prev_safe()
```

### Helpers

- `mlib_list_entry()`
- `mlib_list_first_entry()`
- `mlib_list_last_entry()`
- `mlib_list_next_entry()`
- `mlib_list_prev_entry()`

### State Checks

- `mlib_list_empty()`
- `mlib_list_is_singular()`
- `mlib_list_is_first()`
- `mlib_list_is_last()`
- `mlib_list_is_head()`

## Notes

MLib List is an intrusive list implementation.

The list node (`mlib_list_head_t`) must be embedded inside the structure you
want to store. The library never allocates or frees memory; lifetime management
is entirely the caller's responsibility.