package grammar

class NonTerm(
        val firstSet: List<Term>,
        val followSet: List<Term>
)
