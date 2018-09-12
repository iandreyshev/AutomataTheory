package grammar

class Rule(
        val determ: GrammarSymbol,
        val productions: List<Production>,
        val firstSet: Set<Term>,
        val followSet: Set<Term>
)
