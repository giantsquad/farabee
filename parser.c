#include "parser.h"
#include "tokens.h"
#include <stdlib.h>

void parse(Token* tokens, int tokenCount) {
	int i = 0;

	while (i < tokenCount) {
		if (tokens[i].type == TOKEN_LET) { // Declarative pieces
			if (tokens[i + 1].type == TOKEN_IDENTIFIER) {
				if (tokens[i + 2].type == TOKEN_BE) {
					if (tokens[i + 3].type == TOKEN_INTEGER) {
						if (tokens[i + 4].type == TOKEN_EOF) {
							char* varName = tokens[i + 1].lexeme;
							int value = atoi(tokens[i + 3].lexeme);
							ASTIntDeclare newInt;
							newInt.type = AST_INT_DECLARE;
							newInt.value = value;
							newInt.varName = varName;

							i += 5;
							continue;
						}
					}
				}
			}
		}
	}
}