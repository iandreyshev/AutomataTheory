package grammar

data class Terminal private constructor(
        val symbol: String,
        val isDollar: Boolean,
        val isEpsilon: Boolean
) {

    override fun toString() = symbol

    companion object {
        fun newTerminal(symbol: String): Terminal = when (symbol) {
            Grammar.EPSILON_SYMBOL -> Terminal.newEpsilon()
            Grammar.DOLLAR_SYMBOL -> Terminal.newDollar()
            else -> Terminal(symbol, false, false)
        }

        fun newDollar(): Terminal =
                Terminal(Grammar.DOLLAR_SYMBOL, true, false)

        fun newEpsilon(): Terminal =
                Terminal(Grammar.EPSILON_SYMBOL, false, true)
    }

}
