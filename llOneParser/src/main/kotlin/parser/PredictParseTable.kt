package parser

import grammar.Grammar
import grammar.Determ
import grammar.Production
import grammar.Term

class PredictParseTable(
        private val grammar: Grammar
) {

    operator fun get(nonTerm: Determ, term: Term): Production {
        TODO()
    }

}
