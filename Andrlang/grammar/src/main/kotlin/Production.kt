package grammar

data class Production(
        val symbols: List<GrammarSymbol>
) {

    val firstOrNull by lazy {
        symbols.firstOrNull()
    }

    val isEpsilon by lazy {
        symbols.first().terminal == Terminal.emptySymbol()
    }

    fun symbolsAfter(symbol: GrammarSymbol): List<GrammarSymbol> =
            symbols.dropWhile { it != symbol }
                    .drop(1)

    override fun toString() = symbols.joinToString(separator = " ")

}
