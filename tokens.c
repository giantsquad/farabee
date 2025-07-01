#include "tokens.h"
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

Token makeToken(TokenType type, const char* start, int length) {
	Token token;
	token.type = type;
	token.lexeme = (char*)malloc(length + 1);
	strncpy(token.lexeme, start, length);
	token.lexeme[length] = '\0';
	return token;
}

int matchKeyword(const char* src, int start, const char* keyword) {
	int keywordLen = strlen(keyword);
	return (strncmp(&src[start], keyword, keywordLen) == 0);
}