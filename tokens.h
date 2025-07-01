#pragma once
#define _CRT_SECURE_NO_WARNINGS

typedef enum {
	TOKEN_LET, // Start of variable change or creation
	TOKEN_IDENTIFIER, // Name of variable
	TOKEN_INTEGER, // Integer-type variable
	// TOKEN_CHARACTER,
	// TOKEN_STRING,
	TOKEN_BE, // Equivalent to "=" sign. Assigns right side value to left side variable
	TOKEN_END, // Delimiter to end something. Still a ";"
	TOKEN_IS, // Equivalent to "==" pair. Used to see if left side is the same as right side
	TOKEN_IF,
	// TOKEN_COMMA,
	TOKEN_EOF, // End of file
	TOKEN_UNKNOWN // Used for anytime something doesn't seem to be recognized
} TokenType;

typedef struct {
	TokenType type; // Type of token it is (self-explanatory)
	char* lexeme; // Pointer to the matched text
} Token;

Token makeToken(TokenType type, const char* start, int length);

int matchKeyword(const char* src, int i, const char* keyword);