use crate::tokens::{Token, TokenType};

pub fn tokenize(source: &str) -> Vec<Token> {
    let mut tokens = Vec::new();
    let mut chars = source.chars().peekable();

    while let Some(&ch) = chars.peek() {
        match ch {
            c if c.is_whitespace() => { chars.next(); } // Skip whitespace

            ';' => {
                tokens.push(Token { token_type: TokenType::TokenEnd, lexeme: ";".into() });
                chars.next();
            }

            c if c.is_ascii_digit() => {
                // Handle number
                let mut number = String::new();
                while let Some(&digit) = chars.peek() {
                    if digit.is_ascii_digit() {
                        number.push(digit);
                        chars.next();
                    } else {
                        break;
                    }
                }
                tokens.push(Token { token_type: TokenType::TokenInteger, lexeme: number });
            }

            c if c.is_ascii_alphabetic() => {
                let mut word = String::new();
                while let Some(&letter) = chars.peek() {
                    if letter.is_ascii_alphanumeric() || letter == '_' {
                        word.push(letter);
                        chars.next();
                    } else {
                        break;
                    }
                }

                let token_type = match word.as_str() {
                    "let" => TokenType::TokenLet,
                    "be" => TokenType::TokenBe,
                    "say" => TokenType::TokenSay,
                    "if" => TokenType::TokenIf,
                    "else" => TokenType::TokenElse,
                    "is" => TokenType::TokenIs,
                    _ => TokenType::TokenIdentifier,
                };

                tokens.push(Token { token_type, lexeme: word });
            }

            _ => {
                // Skip or collect unknowns
                tokens.push(Token { token_type: TokenType::TokenUnknown, lexeme: ch.to_string() });
                chars.next();
            }
        }
    }

    tokens.push(Token { token_type: TokenType::TokenEof, lexeme: "".into() });
    tokens
}