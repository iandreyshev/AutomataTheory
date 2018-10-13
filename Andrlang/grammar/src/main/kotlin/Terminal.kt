package grammar

data class Terminal constructor(
        val symbol: String
) {

    val isEpsilon: Boolean = symbol == Grammar.EPSILON_SYMBOL
    val isDollar: Boolean = symbol == Grammar.DOLLAR_SYMBOL

    override fun toString() = symbol

    companion object {
        fun newDollar(): Terminal =
                Terminal(Grammar.DOLLAR_SYMBOL)

        fun newEpsilon(): Terminal =
                Terminal(Grammar.EPSILON_SYMBOL)
    }

}
