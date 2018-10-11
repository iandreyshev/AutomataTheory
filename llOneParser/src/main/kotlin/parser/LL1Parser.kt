package parser

import grammar.*
import java.util.*

class LL1Parser {
    fun execute(root: GrammarSymbol, table: PredictParsingTable, lexer: Iterator<Terminal>) {
        val stack = Stack<GrammarSymbol>()
        stack.add(GrammarSymbol.newTerminal(Terminal.newDollar()))
        stack.add(root)
        var token = lexer.next()
        var tokenPosition = 0

        while (stack.peek().terminal?.isDollar != true) {
            val topNonTerminal: NonTerminal? by lazy {
                stack.peek().nonTerminal
            }
            val productionFromTable: Production? by lazy {
                table[topNonTerminal ?: return@lazy null, token]
            }

            println()
            println(stack.joinToString(separator = " "))
            println(lexer.toString())
            println(topNonTerminal)
            println(productionFromTable)
            println("$tokenPosition $token")

            when {
                stack.peek().terminal == token -> {
                    stack.pop()
                    token = lexer.next()
                    ++tokenPosition
                }
                topNonTerminal == null ->
                    throw IllegalArgumentException("  Terminal on stack top ${stack.peek()}")
                productionFromTable == null -> {
                    val expectedSymbols = table.getProductionsFor(topNonTerminal).keys
                    throw ParserException(tokenPosition, token.symbol, expectedSymbols)
                }
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
