/*
 *  Contains implmentation of FNV Hash function. 
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  See <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Hashtable_easy.h"
#include "LinkedList_easy.h"

uint64_t FNVHash64(unsigned char *buffer, unsigned int len) {
  // This code is adapted from code by Landon Curt Noll
  // and Bonelli Nicola:
  //
  // http://code.google.com/p/nicola-bonelli-repo/
  static const uint64_t FNV1_64_INIT = 0xcbf29ce484222325ULL;
  static const uint64_t FNV_64_PRIME = 0x100000001b3ULL;
  unsigned char *bp = (unsigned char *) buffer;
  unsigned char *be = bp + len;
  uint64_t hval = FNV1_64_INIT;
  /*
   * FNV-1a hash each octet of the buffer
   */
  while (bp < be) {
    /* xor the bottom with the current octet */
    hval ^= (uint64_t) * bp++;
    /* multiply by the 64 bit FNV magic prime mod 2^64 */
    hval *= FNV_64_PRIME;
  }
  /* return our new hash value */
  return hval;
}


uint64_t FNVHashInt64(uint64_t makehash) {
  unsigned char buf[8];
  int i;
  for (i = 0; i < 8; i++) {
    buf[i] = (unsigned char) (makehash & 0x00000000000000FFULL);
    makehash >>= 8;
  }
  return FNVHash64(buf, 8);
}

// where I implement 

// Create a new hashtable
Hashtable CreateHashtable(int num_buckets) {
    Hashtable ht = (Hashtable)malloc(sizeof(HashTableInfo));
    if (ht == NULL) {
        return NULL;
    }
    ht->num_buckets = num_buckets;

    ht->buckets = CreateLinkedList();
    while(num_buckets--) {
      InsertLinkedList(ht->buckets, NULL);
    }

    ht->num_elements = 0;
    return ht;
}

// Destroy the hashtable
void DestroyHashtable(Hashtable ht) {
    if (ht != NULL) {
      DestroyLinkedList(ht->buckets);
      free(ht);
    }
}

// Add a key-value pair to the hashtable
int PutInHashtable(Hashtable ht, HTKeyValue kvp, HTKeyValue* old_kvp) {
  uint64_t hashedKey = FNVHashInt64(kvp.key);
  kvp.key = hashedKey;
  for (LinkedListNode* ptr = ht->buckets->head; ptr != NULL; ptr = ptr->next) {
    if (ptr->payload->key == kvp.key) {
      // old_kvp = ptr->payload;
      old_kvp->key = ptr->payload->key;
      old_kvp->value = ptr->payload->value;
      // ptr->payload->value = kvp.value;
      ptr->payload = &kvp;

      return 2;
    }
  }

  if (InsertLinkedList(ht->buckets, &kvp) == 0) {
    ht->num_elements++;
    return 0;
  }

  return 1;
}

int LookupInHashtable(Hashtable ht, uint64_t key, HTKeyValue *result){
  if(ht == NULL || ht->buckets == NULL){
    return -1;
  }
  uint64_t hashedKey = FNVHashInt64(key);
  key = hashedKey;
  for(LinkedListNode* ptr = ht->buckets->head; ptr != NULL; ptr = ptr->next){
    if(ptr->payload->key == key){
      result->key = ptr->payload->key;
      result->value = ptr->payload->value;
      return 0;
    }
  }

  return -1;
}

int NumElemsInHashtable(Hashtable ht){
  return ht->num_elements;
}


int RemoveFromHashtable(Hashtable ht, uint64_t key, HTKeyValue *junk_kvp){
  if(ht == NULL || ht->buckets == NULL){
    return -1;
  }

  uint64_t hashedKey = FNVHashInt64(key);
  key = hashedKey;
  for(LinkedListNode* ptr = ht->buckets->head; ptr != NULL; ptr = ptr->next){
    // printf("check1 ptr->payload->value: %s\n", ptr->payload->value);
    if(ptr->payload->key == key){
      // printf("check: %p | %d: %p | %s\n", ptr, ptr->payload->key, ptr->payload->value, ptr->payload->value);
      // printf("check2 ptr->payload->value: %s\n", ptr->payload->value);
      junk_kvp->key = key;
      junk_kvp->value = ptr->payload->value;
      if(RemoveLLElem(ht->buckets, ptr) == 0){
        ht->num_elements--;
        return 0;
      }
    }
  }
  return -1;
}
