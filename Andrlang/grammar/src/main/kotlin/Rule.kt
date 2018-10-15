package grammar

data class Rule(
        val nonTerminal: NonTerminal,
        val productions: List<Production>
) {

    fun productionsWith(symbol: GrammarSymbol) = productions
            .filter { it.symbols.contains(symbol) }

    override fun toString() = "${nonTerminal.literal} -> ${productions.joinToString(separator = " | ")}"

}
