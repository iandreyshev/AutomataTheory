package parser

import grammar.Grammar
import java.util.*

class LLOneParser private constructor(
        private val table: PredictParseTable,
        private val input: String
) {

    private val mStack = Stack<StackNode>()

    private fun execute(): Boolean {
        val iterator = input.iterator()

        while (!mStack.empty()) {
            var currentCh = iterator.nextChar()

            if (mSt)
        }

        return true
    }

    companion object {
        fun parse(grammar: Grammar, input: String): Boolean {
            val table = PredictParseTable(grammar)
            val parser = LLOneParser(table, input)
            return parser.execute()
        }
    }

}
