package grammar

data class NonTerminal(
        val literal: String
) {

    fun toSymbol(): GrammarSymbol = GrammarSymbol.from(this)

    override fun toString(): String = literal

}
