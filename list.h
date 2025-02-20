#ifndef LIST_H
#define LIST_H
#include "list.c"
typedef struct DYNAMIC_LIST_STRUCT list_t;
/* array should be freed */
void list_new(list_t *new_list);
void list_grow(list_t *l);
/* Puts `element` at the end of array */
void list_append(list_t *l, void *element);
/* Puts `element` at the specified `index`. Returns -1 if theres any problem */
int list_insert(list_t *l, void *element, int index);
/* Removes element at the `index` value. Returns -1 if theres any problem */
int list_remove(list_t *l, int index);
/* Removes last element. Returns -1 if theres any problem */
int list_pop(list_t *l);
/* frees all element of the array and the array itself (also it set them NULL)
 */
void list_free(list_t *l);

int list_remove_stack(list_t *l, int index);
int list_pop_stack(list_t *l);

void list_free_stack(list_t *l);
#endif // LIST_H
