package parser

import grammar.Grammar
import grammar.NonTerm
import grammar.Production
import grammar.Term

internal class PredictParseTable(
        private val grammar: Grammar
) {

    operator fun get(nonTerm: NonTerm, term: Term): Production {
        TODO()
    }

}
