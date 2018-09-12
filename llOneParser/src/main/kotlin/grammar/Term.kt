package grammar

class Term private constructor(
        val symbol: String,
        val isDollar: Boolean,
        val isEpsilon: Boolean
) {

    companion object {
        fun createTerm(symbol: String): Term =
                Term(symbol, false, false)

        fun createDollar(): Term =
                Term("", true, false)

        fun createEpsilon(): Term =
                Term("", false, false)
    }

}
