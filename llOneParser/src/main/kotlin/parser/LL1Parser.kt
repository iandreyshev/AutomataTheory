package parser

import grammar.GrammarSymbol
import java.util.*

class LL1Parser(
        private val table: PredictParsingTable
) {

    private val mStack = Stack<GrammarSymbol>()

    fun execute(input: String): Boolean {
        val iterator = input.iterator()

        while (!mStack.empty()) {
            var currentCh = iterator.nextChar()
        }

        return true
    }

}
