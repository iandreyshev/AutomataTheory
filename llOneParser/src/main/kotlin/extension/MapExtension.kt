package extension

fun<K, V> MutableMap<K, V>.putIfContains(key: K, value: V) {
    if (containsKey(key)) {
        put(key, value)
    }
}
