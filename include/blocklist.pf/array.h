typedef struct {
  int size;
  void **items;
} array;

array* array_init(void);
int array_push(array *ary, void *ptr);
