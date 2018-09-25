package grammar

data class GrammarSymbol private constructor(
        val terminal: Terminal?,
        val nonTerminal: NonTerminal?
) {

    override fun toString() = terminal?.symbol
            ?: (nonTerminal?.symbol ?: "")

    companion object {
        fun newTerminal(value: Terminal) =
                GrammarSymbol(value, null)

        fun newNonTerminal(value: NonTerminal) =
                GrammarSymbol(null, value)
    }

}
