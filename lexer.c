#include "lexer.h"
#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define INITIAL_CAPACITY 1

void appendToken(Token** tokens, int* count, int* capacity, Token token) {
	printf("[appendToken] Adding token of type %d with lexeme \"%s\"\n", token.type, token.lexeme);

	if (*count >= *capacity) {
		printf("[appendToken] Reallocating from capacity %d\n", *capacity);
		*capacity = (*capacity < 2) ? 2 : (*capacity + (*capacity >> 1));

		// Use a temp pointer to avoid losing the original if realloc fails
		Token* newTokens = realloc(*tokens, sizeof(Token) * (*capacity));
		if (newTokens == NULL) {
			fprintf(stderr, "[appendToken] ERROR: Failed to realloc, out of memory!\n");
			free(*tokens); // Optionally free old block if you’re aborting
			exit(1);       // Or return an error code if you prefer
		}

		*tokens = newTokens;
		printf("[appendToken] New capacity: %d\n", *capacity);
	}

	(*tokens)[(*count)++] = token;
}



Token* tokenize(const char* source, int* outTokenCount) {
	Token* tokens = malloc(sizeof(Token) * INITIAL_CAPACITY);
	if (!tokens) {
		fprintf(stderr, "ERROR: Initial malloc failed\n");
		exit(1);
	}
	int count = 0;
	int capacity = INITIAL_CAPACITY;

	int i = 0;
	while (source[i] != '\0') {
		if (isdigit((unsigned char)source[i])) { // Integers
			int start = i;
			while (isdigit(source[i])) {
				i++;
			}

			Token token = makeToken(TOKEN_INTEGER, &source[start], i - start);

			appendToken(&tokens, &count, &capacity, token);
			continue;
		}
		else if (isalpha((unsigned char)source[i])) { // Start of all things alphabet (variables, be, let, if, etc.)
			int start = i;
			while (isalnum((unsigned char)source[i]) || source[i] == '_') {
				i++;
			}

			if (matchKeyword(source, start, "let")) {
				Token token = makeToken(TOKEN_LET, &source[start], i - start);

				appendToken(&tokens, &count, &capacity, token);
				continue;
			}
			else if (matchKeyword(source, start, "be")) {
				if (tokens[count - 1].type == TOKEN_IDENTIFIER) {
					if (tokens[count - 2].type == TOKEN_LET) {
						Token token = makeToken(TOKEN_BE, &source[start], i - start);

						appendToken(&tokens, &count, &capacity, token);
						continue;
					}
					else {
						fprintf(stderr, "ERROR: Assignment \"be\" at location %d expects to start with \"let\".\n", start);
						return NULL;
					}
				}
				else {
					fprintf(stderr, "ERROR: Assignment \"be\" at location %d expects to be before variable name.\n", start);
					return NULL;
				}
			}
			else if (matchKeyword(source, start, "say")) {
				Token token = makeToken(TOKEN_SAY, &source[start], i - start);

				appendToken(&tokens, &count, &capacity, token);
				continue;
			}
			else {
				Token token = makeToken(TOKEN_IDENTIFIER, &source[start], i - start);

				appendToken(&tokens, &count, &capacity, token);
				continue;
			}
		}
		else if (source[i] == ';') {
			Token token = makeToken(TOKEN_END, &source[i], 1);

			appendToken(&tokens, &count, &capacity, token);
			i++;
			continue;
		}
		else if (isspace((unsigned char)source[i])) { // Skips over whitespace
			i++;
			continue;
		}
		else {
			i++;
		}
	}

	Token token = makeToken(TOKEN_EOF, "", 0);
	appendToken(&tokens, &count, &capacity, token);

	*outTokenCount = count;
	return tokens;
};
