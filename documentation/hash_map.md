## SPL - HashMap&lt;K, V&gt;

This class is useful for managing associative arrays in contiguous memory by using a hash table with open-addressing technique, the initial container capacity is the size of 4 entries and the resizing policy is power of two. If you want to delve into the details, check the [source code](../library/header/hash_tables/hash_map.hpp).

```cpp
#include <spl/hash_tables.hpp>
using namespace SPL;

HashMap<const char*, int> myMap;                        // Empty container.
HashMap<const char*, int> myMap(8);                     // Pre-allocated container for 8 entries.
HashMap<const char*, int> myMap({ { "key", 999 } });    // Copy entries from a const array.
HashMap<const char*, int> myMap(fromMap);               // Copy entries from another hash map class.
HashMap<const char*, int> myMap(SPL::Move(fromMap));    // Move entries from other hash map.
```

### Method: getCapacity()

Get the hash map capacity.

```cpp
Size result = myMap.getCapacity();
```

### Method: getLoadFactor()

Get the load factor (between 0.0f and 1.0f).

```cpp
float result = myMap.getLoadFactor();
```

### Method: getSize()

Get the number of entries in the hash map.

```cpp
Size result = myMap.getSize();
```

### Method: isEmpty()

Determines whether or not the hash map is empty.

```cpp
bool result = myMap.isEmpty();
```

> Returns true when it's empty, false otherwise.

### Method: getIterator()

Get a new entry iterator.

```cpp
auto result = myMap.getIterator();
```

### Method: set(key, value)

Set the specified key to map the given value by using copy or move semantics.
When the load factor is greater than or equals to 0.7f the current capacity will double.

| Parameter | Description |
| --------- | ----------- |
| key       | Entry key   |
| value     | Entry value |

```cpp
auto result = myMap.set("key", 999);
```

> Returns the previous value for the given key.

### Method: get(key)

Get the value that corresponds to the specified key.

| Parameter | Description |
| --------- | ----------- |
| key       | Entry key   |

```cpp
auto result = myMap.get("key");
```

> Returns the corresponding entry value.

### Method: get(key, value)

Get a copy of the value that corresponds to the specified key.

| Parameter | Description  |
| --------- | ------------ |
| key       | Entry key    |
| value     | Output value |

```cpp
int result;
bool status = myMap.get("key", result);
```

> Returns true when the value was found, false otherwise.

### Method: has(key)

Determines whether or not the hash map contains the specified key.

| Parameter | Description |
| --------- | ----------- |
| key       | Entry key   |

```cpp
bool result = myMap.has("key");
```

> Returns true when the key was found, false otherwise.

### Method: remove(key)

Remove the specified key from the hash map.
When the load factor is less than or equals to 0.3f the map capacity will reduce by half.

| Parameter | Description |
| --------- | ----------- |
| key       | Entry key   |

```cpp
auto result = myMap.remove("key");
```

> Returns the removed value.

### Method: remove(key, value)

Remove the specified key from the hash map.
When the load factor is less than or equals to 0.3f the map capacity will reduce by half.

| Parameter | Description  |
| --------- | ------------ |
| key       | Entry key    |
| value     | Output value |

```cpp
int result;
bool status = myMap.remove("key", result);
```

> Returns true when the value was removed, false otherwise.

### Method: clear()

Clear the hash map.
The current capacity will remains the same.

```cpp
myMap.clear();
```

### Operator: [] (key)

Get the value that corresponds to the specified key.
If the hash map isn't constant, it creates a new entry when the given key doesn't exists.
When the load factor is greater than or equals to 0.7f the map capacity will double.

| Parameter | Description |
| --------- | ----------- |
| key       | Entry key   |

```cpp
auto result = myMap["key"];
```

> Returns the corresponding entry value.

### Operator: = (other)

Assign all properties from the given hash map.

| Parameter | Description    |
| --------- | -------------- |
| other     | Other instance |

```cpp
HashMap<const char*, int> myMap;
myMap = fromMap;
```

### Operator: const HashEntry&lt;K, V&gt;\* ()

Get the array of entries.

```cpp
const auto result = static_cast<const HashEntry<const char*, int>*>(myMap);
```

## License

[MIT &copy; Silas B. Domingos](https://balmante.eti.br)
