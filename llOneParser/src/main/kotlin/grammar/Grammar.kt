package grammar

typealias TermSet = Set<Terminal>

class Grammar internal constructor(
        grammarStr: String
) {

    val root: GrammarSymbol

    val nonTerminals: Set<NonTerminal>
        get() = mNonTerminals

    val terminals: TermSet
        get() = mTerminals

    private val mRules = GrammarParser(grammarStr).parse()

    private val mNonTerminals = mRules
            .map { it.nonTerminal }
            .toHashSet()

    private val mTerminals = mRules
            .flatMap { it.productions }
            .flatMap { it.symbols }
            .mapNotNull { it.terminal }
            .filter { !it.isEpsilon }
            .toHashSet()

    private val mFirstSetMap = mNonTerminals.associate { mappedNonTerminal ->
        mappedNonTerminal to (mRules.firstOrNull { it.nonTerminal.symbol == mappedNonTerminal.symbol }
                ?.firstSet
                ?: setOf())
    }

    private val mFollowSetMap = mNonTerminals.associate { mappedNonTerminal ->
        mappedNonTerminal to (mRules.firstOrNull { it.nonTerminal.symbol == mappedNonTerminal.symbol }
                ?.followSet
                ?: setOf())
    }

    init {
        root = GrammarSymbol.newNonTerminal(mRules.first().nonTerminal)
    }

    fun firstSetFor(nonTerminal: NonTerminal) =
            mFirstSetMap.getOrDefault(nonTerminal, setOf())

    fun followSetFor(nonTerminal: NonTerminal) =
            mFollowSetMap.getOrDefault(nonTerminal, setOf())

    fun productionsFor(nonTerminal: NonTerminal) =
            mRules.associate { it.nonTerminal.symbol to it.productions }
                    .getOrDefault(nonTerminal.symbol, listOf())

    companion object {
        internal const val NODE_DELIMITER = "\n"
        internal const val NODE_PARTS_DELIMITER = "->"
        internal const val PRODUCTION_DELIMITER = "|"
        internal const val SYMBOLS_DELIMITER = " "
        internal const val EPSILON_SYMBOL = "#epsilon"
        internal const val DOLLAR_SYMBOL = "#dollar"
    }

}
