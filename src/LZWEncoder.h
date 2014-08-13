#ifndef LZWEncoder_H
#define LZWEncoder_H
#include "Instream.h"
#include "OutStream.h"
#include "Dictionary.h"

typedef enum{
  END
} ErrorCode;

void lzwEncoder(InStream *in, Dictionary *dictionary, OutStream *out);
int getIntFromChar(Dictionary *dict, char *code);
#endif // LZWEncoder_H
