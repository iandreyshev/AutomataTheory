package grammar

data class Production(
        val symbols: List<GrammarSymbol>
) {

    override fun toString() = symbols.joinToString(separator = " ")

}
