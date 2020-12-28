## SPL - HashSet&lt;T&gt;

This class is useful for managing set lists in contiguous memory by using a hash table with open-addressing technique, the initial container capacity is the size of 4 entries and the resizing policy is power of two. If you want to delve into the details please check the [source code](../library/header/hash_tables/hash_set.hpp).

```cpp
#include <spl/hash_tables.hpp>
using namespace SPL;

HashSet<const char*> mySet;                         // Empty container.
HashSet<const char*> mySet(8);                      // Pre-allocated container for 8 entries.
HashSet<const char*> mySet({ "first", "second" });  // Copy entries from a const array.
HashSet<const char*> mySet(fromSet);                // Copy entries from another hash set class.
HashSet<const char*> mySet(SPL::Move(fromSet));     // Move entries from other hash set.
```

### Method: getCapacity()

Get the hash set capacity.

```cpp
Size result = mySet.getCapacity();
```

### Method: getLoadFactor()

Get the load factor (between 0.0f and 1.0f).

```cpp
float result = mySet.getLoadFactor();
```

### Method: getSize()

Get the number of values in the hash set.

```cpp
Size result = mySet.getSize();
```

### Method: isEmpty()

Determines whether or not the hash set is empty.

```cpp
bool result = mySet.isEmpty();
```

> Returns true when it's empty, false otherwise.

### Method: getIterator()

Get a new entry iterator.

```cpp
auto result = mySet.getIterator();
```

### Method: add(value)

Add the specified value in the hash set by using copy or move semantics.
When the load factor is greater than or equals to 0.7f the current capacity will double.

| Parameter | Description |
| --------- | ----------- |
| value     | Entry value |

```cpp
mySet.add("value");
```

### Method: has(value)

Determines whether or not the hash set contains the specified value.

| Parameter | Description |
| --------- | ----------- |
| value     | Entry value |

```cpp
bool result = mySet.has("value");
```

> Returns true when the value was found, false otherwise.

### Method: remove(value)

Remove the specified value from the hash set.
When the load factor is less than or equals to 0.3f the hash set capacity will reduce by half.

| Parameter | Description |
| --------- | ----------- |
| value     | Entry value |

```cpp
auto result = mySet.remove("value");
```

> Returns true when the value was removed, false otherwise.

### Method: clear()

Clear the hash set.
The current capacity will remains the same.

```cpp
mySet.clear();
```

### Operator: = (other)

Assign all properties from the given hash set.

| Parameter | Description    |
| --------- | -------------- |
| other     | Other instance |

```cpp
HashSet<const char*> mySet;
mySet = fromSet;
```

### Operator: const HashEntry&lt;T&gt;\* ()

Get the array of entries.

```cpp
const auto result = static_cast<const HashEntry<const char*>*>(mySet);
```

## License

[MIT &copy; Silas B. Domingos](https://balmante.eti.br)
