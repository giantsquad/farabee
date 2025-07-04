#[derive(Debug, Clone, PartialEq, Eq)]
pub enum TokenType {
    TokenLet,
    TokenBe, // Equivalent to "="
    TokenSay, // Basic print
    TokenIdentifier,
    TokenInteger,
    // TokenString,
    // TokenCharacter,
    // TokenComma,
    TokenIf,
    TokenElse,
    TokenIs, // Equivalent to "=="
    TokenEnd, // Equivalent to ";"
    TokenEof,
    TokenUnknown
}

#[derive(Debug, Clone)]
pub struct Token {
    pub token_type: TokenType,
    pub lexeme: String,
}
