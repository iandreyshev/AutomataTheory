package grammar

data class GrammarSymbol constructor(
        val terminal: Terminal?,
        val nonTerminal: NonTerminal?
) {

    companion object {
        fun from(value: Terminal) = GrammarSymbol(value, null)
        fun from(value: NonTerminal) = GrammarSymbol(null, value)
    }

    val isTerminal: Boolean = terminal != null && nonTerminal == null
    val isNonTerminal: Boolean = terminal == null && nonTerminal != null

    init {
        assert(isTerminal != isNonTerminal)
    }

    override fun toString() = terminal?.literal
            ?: (nonTerminal?.literal ?: "")

}
