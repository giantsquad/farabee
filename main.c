#include "lexer.h"
#include "parser.h"
#include "generator.h"
#include "tokens.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* f = fopen("program.frb", "r");
	if (!f) {
		fprintf(stderr, "ERROR: Failed to open Farabee file.\n");
		return 1;
	}

	// Used to determine file length
	fseek(f, 0, SEEK_END);
	long long length = ftell(f);
	fseek(f, 0, SEEK_SET);

    // Allocate buffer and read file
    char* source = malloc(length + 1);
    fread(source, 1, length, f);
    source[length] = '\0';
    fclose(f);

    // Tokenize
    int tokenCount = 0;
    Token* tokens = tokenize(source, &tokenCount);
    if (!tokens) {
        fprintf(stderr, "Tokenization failed.\n");
        free(source);
        return 1;
    }

    // Print tokens
    printf("Tokens:\n");
    for (int i = 0; i < tokenCount; i++) {
        printf("Type: %d\tLexeme: %s\n", tokens[i].type, tokens[i].lexeme);
    }

    // Cleanup
    for (int i = 0; i < tokenCount; i++) {
        free(tokens[i].lexeme);
    }

    free(tokens);
    free(source);

    return 0;
}