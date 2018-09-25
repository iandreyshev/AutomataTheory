package grammar

class Rule(
        val nonTerminal: NonTerminal,
        val productions: List<Production>,
        val firstSet: Set<Terminal>,
        val followSet: Set<Terminal>
) {

    override fun toString() = "${nonTerminal.symbol} -> ${productions.joinToString(separator = " | ")}"

}
