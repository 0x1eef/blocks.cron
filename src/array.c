#include <blocklist.pf/array.h>
#include <stdlib.h>
#include <blocklist.pf/blocklist.h>

array*
array_init(void) {
  array *ary = malloc(sizeof(array));
  ary->size = 0;
  ary->items = malloc(sizeof(void*));
  return ary;
}

int
array_push(array *arr, void *el) {
  arr->items = realloc(arr->items, sizeof(arr->items) + sizeof(void*));
  arr->items[arr->size++] = el;
  return arr->size;
}
