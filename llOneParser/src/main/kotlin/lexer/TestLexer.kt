package lexer

import extension.addToList
import grammar.Terminal

class TestLexer(val input: String) : Iterator<Terminal> by (
        input.split(" ")
                .map { Terminal.newTerminal(it) }
                .addToList(Terminal.newDollar())
                .iterator()
        )