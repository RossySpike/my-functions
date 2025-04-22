#include "strings.h"

void str_constructor(string_t *_this, char *str, uint32_t len,
                     void *(custom_alloc)(void *, size_t, uint32_t),
                     void *first_arg) {
  assert(_this);
  _this->str = custom_alloc && first_arg
                   ? (char *)custom_alloc(first_arg, sizeof(char), len)
                   : (char *)calloc(len, sizeof(char));
  assert(_this->str);
  for (int i = 0; i < len; i++) {
    _this->str[i] = str[i];
  }
  _this->len = len;
}

void concat(string_t *_this, string_t source,
            void *(custom_alloc)(void *, size_t, uint32_t), void *first_arg) {
  assert(_this);
  _this->len += source.len;
  _this->str = custom_alloc && first_arg
                   ? (char *)custom_alloc(first_arg, sizeof(char), _this->len)
                   : (char *)realloc(_this->str, _this->len * sizeof(char));
  assert(_this->str);
  for (uint32_t i = _this->len - source.len; i < _this->len; i++) {
    _this->str[i] = source.str[i - (_this->len - source.len)];
  }
}

uint8_t in(string_t hay, string_t needle) {
  assert(hay.str && needle.str);
  for (uint32_t i = 0; i < hay.len; i++) {
    uint32_t matching = 0;
    for (uint32_t j = 0; j < needle.len && hay.len > i + j; j++) {
      if (hay.str[i + j] == needle.str[j]) {
        matching++;
      }
    }
    if (matching == needle.len) {
      return 1;
    }
  }
  return 0;
}

string_t *get_sub_string(string_t *_this, int32_t from, int32_t to,
                         int32_t step,
                         void *(custom_alloc)(void *, size_t, uint32_t),
                         void *first_arg) {

  string_t *sub_string =
      custom_alloc && first_arg
          ? (string_t *)custom_alloc(first_arg, sizeof(string_t), 1)
          : (string_t *)malloc(sizeof(string_t));

  sub_string->len = abs((to - from) / step);

  sub_string->str =
      custom_alloc && first_arg
          ? (char *)custom_alloc(first_arg, sizeof(char), sub_string->len)
          : (char *)malloc(sub_string->len * sizeof(char));

  uint32_t index = 0;
  if (step > 0 && to > from) {

    for (uint32_t i = from; i < to; index++, i += step) {

      sub_string->str[index] = _this->str[i];
    }
  } else {

    for (int32_t i = from - 1; i >= to; index++, i += step) {

      sub_string->str[index] = _this->str[i];
    }
  }

  return sub_string;
}

void reverse(string_t *_this) {
  assert(_this && _this->str);
  for (uint32_t i = 0; i < _this->len / 2; i++) {
    if (_this->str[i] == _this->str[_this->len - 1 - i]) {
      continue;
    }
    _this->str[i] ^= _this->str[_this->len - 1 - i];
    _this->str[_this->len - 1 - i] ^= _this->str[i];
    _this->str[i] ^= _this->str[_this->len - 1 - i];
  }
}

string_t **split(string_t *hay, const char *needle, uint32_t needle_len,
                 uint32_t *ptr_len_split,
                 void *(custom_alloc)(void *, size_t, uint32_t),
                 void *first_arg) {
  uint8_t *mask = (uint8_t *)calloc(hay->len, sizeof(uint8_t));
  uint32_t count = 1;
  // Sliding window
  for (uint32_t i = 0; i < hay->len; i++) {
    uint32_t matching = 0;
    for (uint32_t j = 0; j < needle_len && hay->len > i + j; j++) {
      if (hay->str[i + j] == needle[j]) {
        matching++;
      }
    }
    if (matching == needle_len) {
      mask[i] = 1;
      count++;
    }
  }

  string_t **split = (string_t **)malloc(sizeof(string_t *) * count);
  uint32_t index = 0, i = 0;

  for (uint32_t j = 0; j < hay->len; j++) {
    if (mask[j] == 1) {
      printf("index: %d j: %d\n", index, j);
      split[i++] = get_sub_string(hay, index, j, 1, custom_alloc, first_arg);
      index = j + needle_len;
      j += needle_len - 1;
    }
  }

  split[i++] = get_sub_string(hay, index, hay->len, 1, custom_alloc, first_arg);

  *ptr_len_split = count;
  free(mask);
  return split;
}
void trim(string_t *bush, string_t *trimmed,
          void *(custom_alloc)(void *, size_t, uint32_t), void *first_arg) {
  assert(bush && bush->str && trimmed);
  uint32_t start = 0;
  while (start < bush->len &&
         (bush->str[start] == ' ' || bush->str[start] == '\n' ||
          bush->str[start] == '\t')) {
    start++;
  }
  if (start == bush->len) {
    trimmed->len = 0;
    trimmed->str = NULL;
    return;
  }
  uint32_t end = bush->len - 1;
  while (end > start && (bush->str[end] == ' ' || bush->str[end] == '\n' ||
                         bush->str[end] == '\t')) {
    end--;
  }
  trimmed->len = end - start + 1;
  trimmed->str =
      custom_alloc && first_arg
          ? (char *)custom_alloc(first_arg, sizeof(char), trimmed->len)
          : (char *)malloc(trimmed->len * sizeof(char));
  for (uint32_t i = 0; i < trimmed->len; i++) {
    trimmed->str[i] = bush->str[start + i];
  }
}
