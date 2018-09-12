package grammar

class Grammar private constructor(
        private val rules: List<Rule>
) {


    class Parser {

        private var mGrammarStr = ""
        private val mNonTermCollection: List<NonTerm> = listOf()
        private val mTermCollection: List<Term> = listOf()
        private val mGrammar: Grammar by lazy {
            val rulesStr = mGrammarStr.split("\n")
            val rules = rulesStr.map { parseRule(it) }
            return@lazy Grammar(rules)
        }

        fun parse(grammarStr: String): Grammar {
            mGrammarStr = grammarStr
            return mGrammar
        }

        private fun parseRule(ruleStr: String): Rule {
            TODO()
        }

    }

}
