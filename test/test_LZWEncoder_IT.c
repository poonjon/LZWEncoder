#include "unity.h"
#include "LZWEncoder.h"
#include "CException.h"
#include "InStream.h"
#include "OutStream.h"
#include "Dictionary.h"
#include <stdio.h>

void setUp(){}
void tearDown(){}

// lzwEncoder test//
void test_lzwEncoder_encode_banana(){
  CEXCEPTION_T e;
  OutStream *out;
  InStream *in;
  Dictionary *dictionary = dictionaryNew(4000);

  in = openInStream("test/Data/lzw_banana.txt", "r");
  out = openOutStream("test/Data/lzw_banana_enc.txt", "w");
  
  Try{
    lzwEncoder(in, dictionary, out);
  }Catch(e){
    TEST_ASSERT_EQUAL(2, e);
    TEST_ASSERT_EQUAL_STRING("ba", dictionary->entries[256].code);
    TEST_ASSERT_EQUAL_STRING("an", dictionary->entries[257].code);
    TEST_ASSERT_EQUAL_STRING("na", dictionary->entries[258].code); 
    TEST_ASSERT_EQUAL_STRING("ana", dictionary->entries[259].code); 
  }
}

void test_lzwEncoder_encode_aaaaaa(){
  CEXCEPTION_T e;
  OutStream *out;
  InStream *in;
  Dictionary *dictionary = dictionaryNew(4000);
  
  in = openInStream("test/Data/lzw_aaaaaa.txt", "r");
  out = openOutStream("test/Data/lzw_aaaaaa_enc.txt", "w");
  
  Try{
    lzwEncoder(in, dictionary, out);
  }Catch(e){
    TEST_ASSERT_EQUAL_STRING("aa", dictionary->entries[256].code);
    TEST_ASSERT_EQUAL_STRING("aaa", dictionary->entries[257].code);
  }
}

void test_lzwEncoder_encode_banana_nanaba(){
  CEXCEPTION_T e;
  OutStream *out;
  InStream *in;
  Dictionary *dictionary = dictionaryNew(4000);

  in = openInStream("test/Data/lzw_banana_nanaba.txt", "r");
  out = openOutStream("test/Data/lzw_banana_nanaba_enc.txt", "w");
  
  Try{
    lzwEncoder(in, dictionary, out);
  }Catch(e){
    TEST_ASSERT_EQUAL_STRING("ba", dictionary->entries[256].code);
    TEST_ASSERT_EQUAL_STRING("an", dictionary->entries[257].code);
    TEST_ASSERT_EQUAL_STRING("na", dictionary->entries[258].code); 
    TEST_ASSERT_EQUAL_STRING("ana", dictionary->entries[259].code); 
    TEST_ASSERT_EQUAL_STRING("a_", dictionary->entries[260].code); 
    TEST_ASSERT_EQUAL_STRING("_n", dictionary->entries[261].code); 
    TEST_ASSERT_EQUAL_STRING("nan", dictionary->entries[262].code); 
    TEST_ASSERT_EQUAL_STRING("nab", dictionary->entries[263].code); 
  }
}

// getIntFromChar test//
void test_getIntFromChar_get_97(){
  Dictionary *dictionary = dictionaryNew(4000);
  char *code = "a";
  
  TEST_ASSERT_EQUAL(97, getIntFromChar(dictionary, code));

}

void test_getIntFromChar_get_32(){
  Dictionary *dictionary = dictionaryNew(4000);
  char *code = " ";

  TEST_ASSERT_EQUAL(32, getIntFromChar(dictionary, code));
}

void test_getIntFromChar_get_256(){
  Dictionary *dictionary = dictionaryNew(4000);
  char *code = "ba";
  
  dictionary->entries[256].code = "ba";
  
  TEST_ASSERT_EQUAL(256, getIntFromChar(dictionary, code));

}

void test_getIntFromChar_get_257(){
  Dictionary *dictionary = dictionaryNew(4000);
  char *code = "ba";
  
  dictionary->entries[256].code = "na";
  dictionary->entries[257].code = "ba";
  dictionary->entries[258].code = "ra";
  
  TEST_ASSERT_EQUAL(257, getIntFromChar(dictionary, code));

}

void test_getIntFromChar_get_258(){
  Dictionary *dictionary = dictionaryNew(4000);
  char *code = "*a";
  
  dictionary->entries[256].code = "na";
  dictionary->entries[257].code = "ba";
  dictionary->entries[258].code = "*a";
  
  TEST_ASSERT_EQUAL(258, getIntFromChar(dictionary, code));

}

