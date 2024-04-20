
#include <stdint.h>
// Hashtables store key/value pairs.  We'll define a key to be an
// unsigned 64-bit integer; it's up to the customer to figure out how
// to produce an appropriate hash key, but below we provide an
// implementation of FNV hashing to help them out.  We'll define
// a value to be a (void *), so that customers can pass in pointers to
// arbitrary structs as values, but of course we have to worry about
// memory management as a side-effect.

#ifndef HASHABLE_BASE_H
#define HASHABLE_BASE_H

typedef struct ht_key_value {
  uint64_t   key;    // the key in the key/value pair
  char      *value;  // the value in the key/value pair
//   struct HTKeyValue *next;
} HTKeyValue, *HTKeyValuePtr;

#endif