use crate::tokens::{Token, TokenType};

pub fn tokenize(source: &str) -> Vec<Token> {
    let mut tokens = Vec::new();
    let mut chars = source.chars().peekable();
    // TODO: Add code that properly tokenizes each set of characters
    tokens.push(Token { token_type: TokenType::TokenEof, lexeme: "".into() });
    tokens
}