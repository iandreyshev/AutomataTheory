package grammar

class Rule(
        val nonTerminal: GrammarSymbol,
        val productions: List<Production>,
        val firstSet: Set<Terminal>,
        val followSet: Set<Terminal>
)
