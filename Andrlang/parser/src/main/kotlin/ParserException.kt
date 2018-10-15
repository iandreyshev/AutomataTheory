package parser

class ParserException(
        position: Int,
        given: String,
        expected: Collection<String> = listOf()
) : Exception(
        """
            Invalid symbol at position $position
            Given: '$given'
            ${if (expected.isNotEmpty()) "Expected: " + expected.toExpectedText() else ""}
            """.replaceIndent("    ")
) {

    companion object {
        private fun Collection<String>.toExpectedText(): String =
                joinToString(separator = " or ", transform = { "'$it'" })
    }

}
