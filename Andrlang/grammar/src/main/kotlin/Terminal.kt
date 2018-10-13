package grammar

data class Terminal constructor(
        val literal: String
) {

    companion object {
        fun newDollar(): Terminal =
                Terminal(Grammar.DOLLAR_SYMBOL)

        fun newEpsilon(): Terminal =
                Terminal(Grammar.EPSILON_SYMBOL)
    }

    val isEpsilon: Boolean = literal == Grammar.EPSILON_SYMBOL
    val isDollar: Boolean = literal == Grammar.DOLLAR_SYMBOL

    fun toSymbol(): GrammarSymbol = GrammarSymbol.from(this)

    override fun toString(): String = literal

}
