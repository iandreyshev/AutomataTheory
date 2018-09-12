package grammar

class Terminal private constructor(
        val symbol: String,
        val isDollar: Boolean,
        val isEpsilon: Boolean
) {

    companion object {
        fun createTerm(symbol: String): Terminal =
                Terminal(symbol, false, false)

        fun createDollar(): Terminal =
                Terminal("", true, false)

        fun createEpsilon(): Terminal =
                Terminal("", false, true)
    }

}
