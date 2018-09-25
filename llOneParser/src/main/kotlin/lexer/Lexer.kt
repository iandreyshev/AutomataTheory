package lexer

import grammar.Terminal

object HandmadeLexer : Iterator<Terminal> by listOf(
        Terminal.newTerminal("id"),
        Terminal.newTerminal("+"),
        Terminal.newTerminal("id"),
        Terminal.newTerminal("*"),
        Terminal.newTerminal("id"),
        Terminal.newDollar()
).iterator()