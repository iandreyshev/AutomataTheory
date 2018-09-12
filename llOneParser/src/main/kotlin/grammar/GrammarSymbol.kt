package grammar

class GrammarSymbol private constructor(
        val terminal: Terminal?,
        val nonTerminal: NonTerminal?
) {

    companion object {
        fun terminal(value: Terminal) =
                GrammarSymbol(value, null)

        fun nonTerminal(value: NonTerminal) =
                GrammarSymbol(null, value)
    }

}
