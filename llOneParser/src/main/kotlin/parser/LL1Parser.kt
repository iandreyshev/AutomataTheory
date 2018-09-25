package parser

import grammar.*
import java.util.*

class LL1Parser {
    fun execute(root: GrammarSymbol, table: PredictParsingTable, lexer: Iterator<Terminal>) {
        val stack = Stack<GrammarSymbol>()
        stack.add(GrammarSymbol.newTerminal(Terminal.newDollar()))
        stack.add(root)
        var token = lexer.next()

        while (stack.peek().terminal?.isDollar != true) {
            val topNonTerminal: NonTerminal? by lazy {
                stack.peek().nonTerminal
            }
            val productionFromTable: Production? by lazy {
                table[topNonTerminal ?: return@lazy null, token]
            }
            when {
                stack.peek().terminal == token -> {
                    stack.pop()
                    token = lexer.next()
                }
                topNonTerminal == null ->
                    throw IllegalArgumentException("Terminal on stack top")
                productionFromTable == null ->
                    throw IllegalArgumentException("Try to take error state from table")
                else -> {
                    stack.pop()
                    if (!productionFromTable.isEpsilon) {
                        productionFromTable.symbols.reversed().onEach(stack::addElement)
                    }
                }
            }
        }
    }
}
