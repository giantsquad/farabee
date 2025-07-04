#pragma once
#include "tokens.h"

typedef enum {
	AST_INT_DECLARE,
	AST_PRINT
} ASTNodeType;

typedef struct {
	ASTNodeType type;
	char* varName;
	int value;
} ASTIntDeclare;

typedef struct {
	ASTNodeType type;
	char* printStatement;
} ASTPrint;

void parse(Token* tokens, int tokenCount);