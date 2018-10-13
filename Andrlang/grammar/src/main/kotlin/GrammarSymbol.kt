package grammar

data class GrammarSymbol constructor(
        val terminal: Terminal?,
        val nonTerminal: NonTerminal?
) {

    init {
        val isTerminal = terminal != null && nonTerminal == null
        val isNonTerminal = terminal == null && nonTerminal != null
        assert(isTerminal or isNonTerminal)
    }

    override fun toString() = terminal?.symbol
            ?: (nonTerminal?.symbol ?: "")

    companion object {
        fun from(value: Terminal) = GrammarSymbol(value, null)
        fun from(value: NonTerminal) = GrammarSymbol(null, value)
    }

}
