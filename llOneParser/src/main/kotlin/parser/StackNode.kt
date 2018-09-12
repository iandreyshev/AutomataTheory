package parser

import grammar.NonTerm
import grammar.Term

internal class StackNode private constructor(
        val term: Term?,
        val nonTerm: NonTerm?
) {

    constructor(term: Term) : this(term, null)
    constructor(nonTerm: NonTerm) : this(null, nonTerm)

}
