import lexer.TestLexer

const val MATH_GRAMMAR = "math_grammar.txt"
const val YOLANG_GRAMMAR = "yolang_grammar.txt"

val MATH_LEXERS: List<TestLexer> = listOf(
        "",
        "id",
        "id + id",
        "+ id",
        "id +",
        "id / id",
        "id * id",
        "id * id / id",
        "id * ( id / id )",
        "( id * ( id ) / id )",
        "( id ) * ( id ) / ( id )",
        "( id + id ) / id * ( id + id )",
        "id * * id",
        "( ) + id",
        "id id",
        "( id )",
        "- id",
        "- ( id )",
        "( - id ) - id"
).map { TestLexer(it) }

val YOLANG_LEXERS: List<TestLexer> = listOf(
        """
            fun id ( id : Int , id : Int ) => Int : return id ;
        """.trimIndent()
).map { TestLexer(it) }
