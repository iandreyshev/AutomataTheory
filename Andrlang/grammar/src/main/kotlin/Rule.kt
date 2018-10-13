package grammar

data class Rule(
        val nonTerminal: NonTerminal,
        val productions: List<Production>
) {

    override fun toString() = "${nonTerminal.symbol} -> ${productions.joinToString(separator = " | ")}"

}
