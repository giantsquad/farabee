#pragma once

#include "tokens.h"

Token* tokenize(const char* source, int* outTokenCount);

void appendToken(Token** tokens, int* count, int* capacity, Token token);