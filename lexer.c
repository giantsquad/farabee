#include "lexer.h"
#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define INITIAL_CAPACITY 10

void appendToken(Token** tokens, int* count, int* capacity, Token token) {
	if (*count >= *capacity) {
		*capacity = *capacity + (*capacity >> 1);
		*tokens = realloc(*tokens, sizeof(Token) * (*capacity));
	}

	(*tokens)[(*count)++] = token;
}

Token* tokenize(const char* source, int* outTokenCount) {
	Token* tokens = malloc(sizeof(Token) * INITIAL_CAPACITY);
	int count = 0;
	int capacity = INITIAL_CAPACITY;

	int i = 0;
	while (source[i] != '\0') {
		if (isdigit(source[i])) { // Integers
			int start = i;
			while (isdigit(source[i])) {
				i++;
			}

			Token token = makeToken(TOKEN_INTEGER, &source[start], i - start);

			appendToken(&tokens, &count, &capacity, token);
			continue;
		} else if (isalpha(source[i])) { // Start of all things alphabet (variables, be, let, if, etc.)
			int start = i;
			while (isalnum(source[i]) || source[i] == '_') {
				i++;
			}

			if (matchKeyword(source, start, "let")) {
				Token token = makeToken(TOKEN_LET, &source[start], i - start);

				appendToken(&tokens, &count, &capacity, token);
				continue;
			} else if(matchKeyword(source, start, "be")) {
				if (tokens[count - 1].type == TOKEN_IDENTIFIER) {
					if (tokens[count - 2].type == TOKEN_LET) {
						Token token = makeToken(TOKEN_BE, &source[start], i - start);

						appendToken(&tokens, &count, &capacity, token);
						continue;
					} else {
						printf("ERROR: Assignment \"be\" at location %d expects to start with \"let\".\n", start);
						return NULL;
					}
				} else {
					printf("ERROR: Assignment \"be\" at location %d expects to be before variable name.\n", start);
					return NULL;
				}
			}
			else {
				Token token = makeToken(TOKEN_IDENTIFIER, &source[start], i - start);

				appendToken(&tokens, &count, &capacity, token);
				continue;
			}
		} else if (source[i] == ';') {
			Token token = makeToken(TOKEN_END, &source[i], 1);

			appendToken(&tokens, &count, &capacity, token);
			continue;
		} else if (isspace(source[i])) {
			i++;
			continue;
		} else {
			i++;
		}
	}

	Token token = makeToken(TOKEN_EOF, "", 0);
	appendToken(&tokens, &count, &capacity, token);

	*outTokenCount = count;
	return tokens;
};