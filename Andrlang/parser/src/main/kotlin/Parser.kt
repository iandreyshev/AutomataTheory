package parser

import grammar.*
import java.util.*

class Parser {
    fun execute(root: GrammarSymbol, table: ParsingTable, lexer: Iterator<Terminal>) {
        val stack = Stack<GrammarSymbol>()
        stack.add(Terminal.endOfInput().toSymbol())
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

//            println()
//            println(stack.joinToString(" "))
//            println(lexer.toString())
//            println(topNonTerminal)
//            println(productionFromTable)
//            println("$tokenPosition $token")

            when {
                stack.peek().terminal == token -> {
                    stack.pop()
                    token = lexer.next()
                    ++tokenPosition
                }
                topNonTerminal == null ->
                    throw ParserException(tokenPosition, stack.peek().toString())
                productionFromTable == null -> {
                    val expectedSymbols = table.productionsFor(topNonTerminal).keys
                    throw ParserException(tokenPosition, token.literal, expectedSymbols)
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
