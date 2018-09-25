package lexer

import grammar.Terminal

class Lexer : Iterator<Terminal> by listOf(
        Terminal.newTerminal("id"),
        Terminal.newTerminal("+"),
        Terminal.newTerminal("id"),
        Terminal.newTerminal("*"),
        Terminal.newTerminal("id"),
        Terminal.newDollar()
).iterator()