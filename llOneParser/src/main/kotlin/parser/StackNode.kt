package parser

import grammar.Determ
import grammar.Term

internal class StackNode private constructor(
        val term: Term?,
        val nonTerm: Determ?
) {

    constructor(term: Term) : this(term, null)
    constructor(nonTerm: Determ) : this(null, nonTerm)

}
