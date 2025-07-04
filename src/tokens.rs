#[derive(Debug, Clone, PartialEq, Eq)]
pub enum TokenType {
    TokenLet,
    TokenBe, // Equivalent to "="
    TokenSay, // Basic print
    TokenIdentifier,
    TokenInteger,
    TokenIf,
    TokenElse,
    TokenIs, // Equivalent to "=="
    TokenEnd, // Equivalent to ";"
    TokenEof,
}

#[derive(Debug, Clone)]
pub struct Token {
    pub token_type: TokenType,
    pub lexeme: String,
}
