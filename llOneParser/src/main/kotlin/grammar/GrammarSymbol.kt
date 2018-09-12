package grammar

class GrammarSymbol private constructor(
        val terminal: Term?,
        val nonTerminal: NonTerminal?
) {

    companion object {
        fun terminal(value: Term) =
                GrammarSymbol(value, null)

        fun nonTerminal(value: NonTerminal) =
                GrammarSymbol(null, value)
    }

}
