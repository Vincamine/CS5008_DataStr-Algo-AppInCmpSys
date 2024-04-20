/*
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
#include "gtest/gtest.h"
extern "C" {
    #include "Hashtable_easy.h"
    #include "LinkedList_easy.h"
}
const char* first = "first";
const char* second="second";
const char* third = "third";
const char* fourth = "fourth";

#define MAX_VALUE_LEN 75



TEST(Hashtable, Create) {
  Hashtable ht = CreateHashtable(5);
  EXPECT_FALSE(ht == NULL);
  EXPECT_FALSE(ht->buckets == NULL);
  EXPECT_EQ(NumElemsInHashtable(ht), 0);
  DestroyHashtable(ht);
}

TEST(Hashtable, AddOneRemoveOne) {

    Hashtable ht = CreateHashtable(5);
    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    // printf("----\n");
    // for (LinkedListNode* ptr = ht->buckets->head; ptr != NULL; ptr = ptr->next) {
    //     printf("%u %s\n", ptr->payload->key, ptr->payload->value);
    // }

    // Make KeyValue Pair
    HTKeyValue kv, old_kv;

    kv.key = 0;
    kv.value = "valueForAddOneRemoveOne";
    PutInHashtable(ht, kv, &old_kv);

    // printf("----\n");
    // printf("%p, %p\n", ht->buckets->head, ht->buckets->tail);
    for (LinkedListNode* ptr = ht->buckets->head; ptr != NULL; ptr = ptr->next) {
        printf("--%p %u %s\n", ptr, ptr->payload->key, ptr->payload->value);
    }

    EXPECT_EQ(NumElemsInHashtable(ht), 1);

    HTKeyValue junk;
    RemoveFromHashtable(ht, kv.key, &junk);

    // printf("----\n");
    // printf("%p, %p\n", ht->buckets->head, ht->buckets->tail);
    for (LinkedListNode* ptr = ht->buckets->head; ptr != NULL; ptr = ptr->next) {
        printf("--%p %u %s\n", ptr, ptr->payload->key, ptr->payload->value);
    }

    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    DestroyHashtable(ht);

}

TEST(Hashtable, AddOneElemDestroy) {
    Hashtable ht = CreateHashtable(5);

    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    // Make KeyValue Pair
    HTKeyValue kv, old_kv;

    kv.key = 0;
    kv.value = "valueForAddOneElemDestroy";
    PutInHashtable(ht, kv, &old_kv);

    EXPECT_EQ(NumElemsInHashtable(ht), 1);

    DestroyHashtable(ht);
}

TEST(Hashtable, AddOneElemTwoTimes) {
    Hashtable ht = CreateHashtable(5);
    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    // Make KeyValue Pair
    HTKeyValue kv;
    HTKeyValue old_kv;
    old_kv.value = NULL;

    // TODO(student): Fill this with something meaningful
    kv.key = 1;
    kv.value = "valueForAddOneElemTwoTimes1";

    int result = PutInHashtable(ht, kv, &old_kv);

    EXPECT_EQ(result, 0);
    EXPECT_EQ(NumElemsInHashtable(ht), 1);

    // Trying to put it in again should result in an error
    result = PutInHashtable(ht, kv, &old_kv);
    EXPECT_EQ(result, 2);
    EXPECT_EQ(NumElemsInHashtable(ht), 1);

    // Also want to try a different element with the same key (diff val)
    // TODO(student): Put something meaningful here. 
    HTKeyValue kv2;
    kv2.key = 1;
    kv2.value = "valueForAddOneElemTwoTimes2";

    result = PutInHashtable(ht, kv2, &old_kv);
    EXPECT_EQ(result, 2);
    EXPECT_EQ(NumElemsInHashtable(ht), 1);
    // Because this was replaced, gotta free the value
    // TODO(student): This should be something related to "meaningful" earlier
    // printf("pass\n");
    // printf("-----check old_kv: %p\n", &old_kv);
    // printf("-----check old_kv->key: %d\n", old_kv.key);
    // printf("-----check old_kv->value: %s\n", old_kv.value);

    EXPECT_EQ(old_kv.value, kv2.value);

    DestroyHashtable(ht);
}

TEST(Hashtable, AddOneRemoveTwice) {
    
    Hashtable ht = CreateHashtable(5);

    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    // Make KeyValue Pair
    HTKeyValue kv, old_kv;
    // TODO(student): Put something meaningful here
    kv.key = 1;
    kv.value = "valueForAddOneRemoveTwice";

    // int result = PutInHashtable(ht, kv, &old_kv);
    int result = PutInHashtable(ht, kv, &old_kv);

    
    // for (LinkedListNode* ptr = ht->buckets->head; ptr != NULL; ptr = ptr->next) {
    //     printf("%p | %d: %p | %s\n", ptr, ptr->payload->key, ptr->payload->value, ptr->payload->value);
    // }


    EXPECT_EQ(result, 0);
    EXPECT_EQ(NumElemsInHashtable(ht), 1);

    // for (LinkedListNode* ptr = ht->buckets->head; ptr != NULL; ptr = ptr->next) {
    //     printf("%p | %d: %p | %s\n", ptr, ptr->payload->key, ptr->payload->value, ptr->payload->value);
    // }

    HTKeyValue junk;
    // printf("kv: %p | kv.value: %p\n", &kv, kv.value);
    result = RemoveFromHashtable(ht, kv.key, &junk);

    EXPECT_EQ(result, 0); 
    EXPECT_EQ(NumElemsInHashtable(ht), 0);
    // TODO(student): Put something meaningful here

    // printf("%s\n",junk.value);
    EXPECT_EQ(junk.value, kv.value);

    result = RemoveFromHashtable(ht, kv.key, &junk);
    EXPECT_EQ(result, -1);
    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    DestroyHashtable(ht);
}

TEST(Hashtable, AddMultipleItems) {
    Hashtable ht = CreateHashtable(100);

    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    // Make KeyValue Pair
    HTKeyValue kv;
    HTKeyValue old_kv;

    // TODO(student): Put something meaningful here
    kv.key = 1;
    kv.value = "valueForAddMultipleItems1";
    PutInHashtable(ht, kv, &old_kv);

    ASSERT_EQ(NumElemsInHashtable(ht), 1);

    // TODO(student): Put something meaningful here
    kv.key = 2;
    kv.value = "valueForAddMultipleItems2";
    PutInHashtable(ht, kv, &old_kv);

    ASSERT_EQ(NumElemsInHashtable(ht), 2);

    // TODO(student): Put something meaningful here
    kv.key = 3;
    kv.value = "valueForAddMultipleItems3";
    PutInHashtable(ht, kv, &old_kv);

    ASSERT_EQ(NumElemsInHashtable(ht), 3);

    DestroyHashtable(ht);
}

TEST(Hashtable, LookupInHashtable) {
    Hashtable ht = CreateHashtable(100);

    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    // Make KeyValue Pair
    HTKeyValue kv1;
    HTKeyValue old_kv;

    // TODO(student): Put something meaningful here
    kv1.key = 1;
    kv1.value = "valueForLookupInHashtable1";
    PutInHashtable(ht, kv1, &old_kv);

    ASSERT_EQ(NumElemsInHashtable(ht), 1);

    // TODO(student): Put something meaningful here
    HTKeyValue kv2;
    kv2.key = 2;
    kv2.value = "valueForLookupInHashtable2";
    PutInHashtable(ht, kv2, &old_kv);

    ASSERT_EQ(NumElemsInHashtable(ht), 2);

    // TODO(student): Put something meaningful here
    HTKeyValue kv3;
    kv3.key = 3;
    kv3.value = "valueForLookupInHashtable3";
    PutInHashtable(ht, kv3, &old_kv);

    ASSERT_EQ(NumElemsInHashtable(ht), 3);

    HTKeyValue lookup_result;
    // Now, lookup:
    // TODO(student): Put something meaningful here
    int result = LookupInHashtable(ht,
        1,
        &lookup_result);
    // TODO(student): Put something meaningful here
    EXPECT_EQ(result, 0);
    // EXPECT_EQ("", "");
    // EXPECT_EQ("", "");

    EXPECT_EQ(NumElemsInHashtable(ht), 3);

    // TODO: Test looking up something not in the table

    DestroyHashtable(ht);
}

TEST(Hashtable, TwoElemsOneBucket) {
    Hashtable ht = CreateHashtable(15);

    EXPECT_EQ(NumElemsInHashtable(ht), 0);

    // Make KeyValue Pair
    HTKeyValue kv, kv2;
    HTKeyValue old_kv;

    // TODO(student): Put something meaningful here
    kv.key = 1;
    kv.value = "valueForTwoElemsOneBucket1";
    PutInHashtable(ht, kv, &old_kv);

    ASSERT_EQ(NumElemsInHashtable(ht), 1);

    kv2.key = 2;
    kv2.value = "valueForTwoElemsOneBucket2";
    PutInHashtable(ht, kv2, &old_kv);

    ASSERT_EQ(NumElemsInHashtable(ht), 2);

    HTKeyValue lookup_result;
    int result = LookupInHashtable(ht,
        1,
        &lookup_result);
    ASSERT_EQ(result, 0);
    // TODO(student): Put something meaningful here
    ASSERT_EQ(lookup_result.key, FNVHashInt64(1));
    ASSERT_EQ(lookup_result.value, "valueForTwoElemsOneBucket1");

    result = LookupInHashtable(ht,
                               4,
                               &lookup_result);
    ASSERT_EQ(result, -1);
    // TODO(student): Put something meaningful here
    ASSERT_EQ(lookup_result.key, FNVHashInt64(1));
    ASSERT_EQ(lookup_result.value, "valueForTwoElemsOneBucket1");

    DestroyHashtable(ht);
}

// TEST(Hashtable, Resize) {
//   Hashtable ht = CreateHashtable(15);

//   for (unsigned int i = 0; i < 60; i++) {
//     // do the insert
//     // SomeNumPtr np = static_cast<SomeNumPtr>(malloc(sizeof(someNum)));
//     HTKeyValuePtr np = static_cast<HTKeyValuePtr>(malloc(sizeof(HTKeyValue)));
    
//     HTKeyValue old, newkv, old_kv;
//     assert(np != NULL);
//     np->num = static_cast<int>(i);
//     newkv.key = i;
//     newkv.value = static_cast<void *>(np);
//     ASSERT_EQ(0, PutInHashtable(ht, newkv, &old_kv));

//     //printf("i = %d\n", i);

//     // test double insert
//     ASSERT_EQ(2, PutInHashtable(ht, newkv, &old_kv));

//     // test lookup
//     old.key = 1;
//     old.value = NULL;
//     ASSERT_EQ(0, LookupInHashtable(ht, i, &old));
//     ASSERT_EQ(i, old.key);
//     ASSERT_EQ(static_cast<void *>(np), old.value);

//     // test bad lookup
//     ASSERT_EQ(-1, LookupInHashtable(ht, i+1, &old));

//     // test bad remove
//     ASSERT_EQ(-1, RemoveFromHashtable(ht, i+1, &old));

//     // test good remove and reinsert
//     old.key = -100;
//     old.value = NULL;
//     ASSERT_EQ(0, RemoveFromHashtable(ht, i, &old));
//     ASSERT_EQ(i, old.key);
//     ASSERT_EQ(static_cast<void *>(np), old.value);
//     ASSERT_EQ(i, (unsigned)NumElemsInHashtable(ht));
//     ASSERT_EQ(0, PutInHashtable(ht, newkv, &old_kv));
//     ASSERT_EQ(2, PutInHashtable(ht, newkv, &old_kv));
//     ASSERT_EQ(i+1, (unsigned)NumElemsInHashtable(ht));
//   }
//     DestroyHashtable(ht);
// }

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
