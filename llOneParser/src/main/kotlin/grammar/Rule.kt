package grammar

class Rule(
        val nonTerminal: GrammarSymbol,
        val productions: List<Production>,
        val firstSet: Set<Term>,
        val followSet: Set<Term>
)
