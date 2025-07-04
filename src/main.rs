mod lexer;
mod parser;
mod tokens;
mod ast;
mod generator;

use lexer::tokenize;

fn main() {
    let farabee_code = "let x be 42; say x;"; // Test input, to be replaced by file reader
    let tokens = tokenize(farabee_code);

    for token in tokens {
        println!("{:?}", token);
    }
}
