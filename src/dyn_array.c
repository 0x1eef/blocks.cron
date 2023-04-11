#include <stdlib.h>
#include <stdio.h>
#include <blocklist.pf/malloc.h>
#include <blocklist.pf/dyn_array.h>

static char* read_line(FILE *f, int blocks);

dyn_array*
array_init(void) {
  dyn_array *ary = safe_malloc(sizeof(dyn_array));
  ary->size = 0;
  ary->items = safe_malloc(0);
  return ary;
}

dyn_array*
array_from_file(FILE *f) {
  dyn_array *ary;
  ary = array_init();
  while(!feof(f)) {
    array_push(ary, read_line(f, 16));
  }
  return ary;
}

int
array_push(dyn_array *arr, void *item) {
  arr->items = realloc(
    arr->items,
    (sizeof(void*) * arr->size) + sizeof(void*)
  );
  arr->items[arr->size++] = item;
  return arr->size;
}

dyn_array*
array_free_item(dyn_array *arr, int index) {
  free(arr->items[index]);
  for (int i = index; i < arr->size; i++) {
    arr->items[i] = arr->items[i+1];
  }
  arr->items = realloc(
    arr->items,
    (sizeof(void*) * arr->size) - sizeof(void*)
  );
  arr->size--;
  return arr;
}

char*
read_line(FILE *f, int blocks) {
  int i, buf;
  char c, *str;
  str = safe_malloc(sizeof(char[blocks]));
  buf = blocks;
  i = 0;
  while((c = (char)fgetc(f)) != '\n') {
    str[i++] = c;
    if (feof(f)) {
      break;
    } else if (i+1 == blocks) {
      buf += blocks;
      str = safe_realloc(str, sizeof(char[buf]));
    }
  }
  str[i++] = '\n';
  str[i] = '\0';
  return str;
}
