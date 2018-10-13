package extension

fun<T> List<T>.addToList(element: T): List<T> {
    val newList = toMutableList()
    newList.add(element)
    return newList
}
