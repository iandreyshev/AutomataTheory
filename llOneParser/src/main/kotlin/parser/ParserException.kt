package parser

class ParserException(
        position: Int,
        given: String,
        expected: Collection<String>
) : Exception(
        """
            Invalid symbol at position $position
            Given: '$given'
            Expected: ${expected.toExpectedText()}
            """.replaceIndent("    ")
) {

    companion object {
        private fun Collection<String>.toExpectedText(): String =
                joinToString(separator = " or ", transform = { "'$it'" })
    }

}
