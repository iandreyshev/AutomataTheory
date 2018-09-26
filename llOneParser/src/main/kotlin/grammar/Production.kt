package grammar

data class Production(
        val symbols: List<GrammarSymbol>
) {

    val firstOrNull by lazy {
        symbols.firstOrNull()
    }

    val isEpsilon by lazy {
        symbols.first().terminal == Terminal.newEpsilon()
    }

    override fun toString() = symbols.joinToString(separator = " ")

}
