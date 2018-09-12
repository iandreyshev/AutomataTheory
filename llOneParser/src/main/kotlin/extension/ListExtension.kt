package extension

fun<T> List<T>.addToList(element: T): List<T> {
    toMutableList().add(element)
    return this
}
