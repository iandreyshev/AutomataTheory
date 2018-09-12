package grammar

class GrammarSymbol private constructor(
        val term: Term?,
        val determ: Determ?
) {

    companion object {
        fun term(value: Term) =
                GrammarSymbol(value, null)

        fun determ(value: Determ) =
                GrammarSymbol(null, value)
    }

}
