package parser

import java.util.*

class LLOneParser(
        private val table: PredictParseTable
) {

    private val mStack = Stack<StackNode>()

    fun execute(input: String): Boolean {
        val iterator = input.iterator()

        while (!mStack.empty()) {
            var currentCh = iterator.nextChar()
        }

        return true
    }

}
