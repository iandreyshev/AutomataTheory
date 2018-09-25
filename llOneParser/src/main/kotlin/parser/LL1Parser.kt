package parser

import grammar.GrammarSymbol
import grammar.Terminal
import java.util.*

class LL1Parser(
        private val table: PredictParsingTable,
        private val lexer: Iterator<Terminal>
) {

    private lateinit var mStack: Stack<GrammarSymbol>

    fun execute(input: String, rootSymbol: GrammarSymbol) {
        initStack(rootSymbol)

        while (mStack.peek().terminal?.isDollar == false) {
            val token = lexer.next()

            when {
                mStack.peek().terminal == token -> mStack.pop()
                mStack.peek().nonTerminal == null -> throw IllegalArgumentException("Terminal on stack top. Grammar is not LL1")
                table[mStack.peek().nonTerminal!!, token] != null -> {
                }
                table[mStack.peek().nonTerminal!!, token] == -> {
                }
            }
        }
    }

    private fun initStack(rootSymbol: GrammarSymbol) {
        mStack = Stack()
        mStack.add(GrammarSymbol.newTerminal(Terminal.newDollar()))
        mStack.add(rootSymbol)
    }

}
