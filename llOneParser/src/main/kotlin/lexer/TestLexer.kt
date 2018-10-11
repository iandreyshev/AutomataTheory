package lexer

import extension.addToList
import grammar.Terminal

class TestLexer(val input: String) : Iterator<Terminal> {

    private val mTokens: MutableList<Terminal> = input.split(" ", "\r", "\n", "\t")
            .filter { it.isNotBlank() && it.isNotEmpty() }
            .map { it.trim() }
            .map { Terminal.newTerminal(it) }
            .addToList(Terminal.newDollar())
            .toMutableList()

    override fun next(): Terminal {
        val next = mTokens.first()
        mTokens.removeAt(0)
        return next
    }

    override fun hasNext(): Boolean =
            mTokens.isNotEmpty()

    override fun toString(): String =
            mTokens.joinToString(separator = " ")

}