#ifndef STRINGS_H
#define STRINGS_H

#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct STRING_STRUCT {
  char *str;
  uint32_t len;
} string_t;

#define NO_CUSTOM NULL, NULL
#define STRING_PROPS(this) this.len, this.str
#define STRING_PTR_PROPS(this) this->len, this->str

// IMPORTANT: every function that uses custom_alloc must have some sort of
// rezising remember to free your pointer :D

void str_constructor(string_t *_this, char *str, uint32_t len,
                     void *(custom_alloc)(void *, size_t, uint32_t),
                     void *first_arg);

void concat(string_t *_this, string_t source,
            void *(custom_alloc)(void *, size_t, uint32_t), void *first_arg);

uint8_t in(string_t hay, string_t needle);

string_t *get_sub_string(string_t *_this, int32_t from, int32_t to,
                         int32_t step,
                         void *(custom_alloc)(void *, size_t, uint32_t),
                         void *first_arg);

void reverse(string_t *_this);

string_t **split(string_t *hay, const char *needle, uint32_t needle_len,
                 uint32_t *ptr_len_split,
                 void *(custom_alloc)(void *, size_t, uint32_t),
                 void *first_arg);

void trim(string_t *bush, string_t *trimmed,
          void *(custom_alloc)(void *, size_t, uint32_t), void *first_arg);

#endif // STRINGS_H
