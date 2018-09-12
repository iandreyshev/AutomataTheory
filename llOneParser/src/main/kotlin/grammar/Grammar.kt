package grammar

typealias TermSet = Set<Terminal>

class Grammar internal constructor(
        grammarStr: String
) {

    val nonTerminals: Set<NonTerminal>
        get() = mNonTerminals

    val terms: TermSet
        get() = mTerms

    private val mRules: List<Rule> = GrammarParser(grammarStr).parse()

    private val mNonTerminals: Set<NonTerminal> = mRules.mapNotNull { it.nonTerminal.nonTerminal }
            .toHashSet()

    private val mTerms: TermSet = mRules.flatMap { it.productions }
            .flatMap { it.symbols }
            .mapNotNull { it.terminal }
            .filter { !it.isEpsilon }
            .toHashSet()

    private val mFirstSetMap: Map<NonTerminal, TermSet> = mNonTerminals.associate { mappedNonTerminal ->
        mappedNonTerminal to (mRules.firstOrNull { it.nonTerminal.nonTerminal?.symbol == mappedNonTerminal.symbol }
                ?.firstSet
                ?: setOf())
    }

    private val mFollowSetMap: Map<NonTerminal, TermSet> = mNonTerminals.associate { mappedNonTerminal ->
        mappedNonTerminal to (mRules.firstOrNull { it.nonTerminal.nonTerminal?.symbol == mappedNonTerminal.symbol }
                ?.followSet
                ?: setOf())
    }

    fun firstSetFor(nonTerminal: NonTerminal): TermSet =
            mFirstSetMap.getOrDefault(nonTerminal, setOf())

    fun followSetFor(nonTerminal: NonTerminal): TermSet =
            mFollowSetMap.getOrDefault(nonTerminal, setOf())

    fun productionsFor(nonTerminal: NonTerminal): List<Production> = TODO()

    companion object {
        internal const val NODE_DELIMITER = "\n"
        internal const val NODE_PARTS_DELIMITER = "->"
        internal const val PRODUCTION_DELIMITER = "|"
        internal const val SYMBOLS_DELIMITER = " "
        internal const val EPSILON_SYMBOL = "#epsilon"
        internal const val DOLLAR_SYMBOL = "#dollar"
    }

}
