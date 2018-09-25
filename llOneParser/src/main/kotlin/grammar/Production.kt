package grammar

data class Production(
        val symbols: List<GrammarSymbol>
) {

    val isEpsilon by lazy {
        symbols.first().terminal == Terminal.newEpsilon()
    }

    override fun toString() = symbols.joinToString(separator = " ")

}
