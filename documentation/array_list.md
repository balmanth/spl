# SPL - ArrayList&lt;T&gt;

This class is useful for managing contiguous memory lists, the container size will be determined by the size of the template's T parameter, its initial capacity is the size of 4 elements and the resizing policy is power of two. If you want to delve into the details, check the [source code](../library/header/arrays/array_list.hpp).

```cpp
#include <spl/arrays.hpp>
using namespace SPL;

ArrayList<int> myList;                      // Empty container.
ArrayList<int> myList(16);                  // Pre-allocated container for 16 elements.
ArrayList<int> myList({ 1, 2, 3 });         // Copy elements from a const array.
ArrayList<int> myList(fromList);            // Copy elements from another array list class.
ArrayList<int> myList(SPL::Move(fromList)); // Move elements from other array list.
```

### Method: getCapacity()

Get the capacity of the array.

```cpp
Size result = myList.getCapacity();
```

### Method: getLength()

Get the number of elements in the array.

```cpp
Size result = myList.getLength();
```

### Method: isEmpty()

Determines whether or not the array is empty.

```cpp
bool result = myList.isEmpty();
```

> Returns true when it's empty, false otherwise.

### Method: getIterator()

Get a new array iterator.

```cpp
auto result = myList.getIterator();
```

### Method: add(element)

Add the specified element at the end of the array by using copy or move semantics.
When the array is at its capacity, the current capacity will double.

| Parameter | Description |
| --------- | ----------- |
| element   | New element |

```cpp
Size result = myList.add(999);
```

> Returns the current length of the array.

### Method: add(index, element)

Add the specified element at the specified index by using copy or move semantics.
When the array is at its capacity, the current capacity will double.

| Parameter | Description      |
| --------- | ---------------- |
| index     | Zero-based index |
| element   | New element      |

```cpp
Size result = myList.add(3, 999);   // Adding in the 3rd index.
```

> Returns the current length of the array.

### Method: set(index, element)

Replace the element at the specified index with the given one by using copy or move semantics.

| Parameter | Description      |
| --------- | ---------------- |
| index     | Zero-based index |
| element   | New element      |

```cpp
auto result = myList.set(3, 999);   // Replacing in the 3rd index.
```

> Returns the replaced element.

### Method: concat(pack)

Merge all the given list into a new array.

| Parameter | Description   |
| --------- | ------------- |
| pack      | Pack of lists |

```cpp
auto result = myList.concat({
        fromList1,
        fromList2,
        ArrayList({ 4, 5, 6 })
    });
```

### Method: get(index)

Get the element that corresponds to the specified index.

| Parameter | Description      |
| --------- | ---------------- |
| index     | Zero-based index |

```cpp
auto result = myList.get(3);    // Getting the 3rd index.
```

> Returns the corresponding element.

### Method: get(index, element)

Get a copy of the element that corresponds to the specified index.

| Parameter | Description      |
| --------- | ---------------- |
| index     | Zero-based index |
| element   | Output element   |

```cpp
int result;
bool status = myList.get(3, result);    // Getting the 3rd index.
```

> Returns true when the element was found, false otherwise.

### Method: indexOf(search, from)

Get the first index occurrence of the specified element in the array.

| Parameter | Description               |
| --------- | ------------------------- |
| search    | Search element            |
| from      | From the zero-based index |

```cpp
Index result = myList.indexOf(999);
Index result = myList.indexOf(999, 3); // Starting from the 3th index.
```

> Returns the corresponding index or -1 when the element wasn't found.

### Method: lastIndexOf(search, from)

Get the last index occurrence of the specified element in the array.

| Parameter | Description               |
| --------- | ------------------------- |
| search    | Search element            |
| from      | From the zero-based index |

```cpp
Index result = myList.lastIndexOf(999);
Index result = myList.lastIndexOf(999, 3); // Starting from the 3th index.
```

> Returns the corresponding index or -1 when the element wasn't found.

### Method: contains(search)

Determines whether or not the array contains the specified element.

| Parameter | Description    |
| --------- | -------------- |
| search    | Search element |

```cpp
bool status = myList.contains(999);
```

> Returns true when the element was found, false otherwise.

### Method: remove(index)

Remove the element that corresponds to the specified index from the array.
When the array length is 1/4 of the current capacity, the current capacity will be reduced by half.

| Parameter | Description      |
| --------- | ---------------- |
| index     | Zero-based index |

```cpp
auto result = myList.remove(3); // Removing the 3rd index.
```

> Returns the removed element.

### Method: remove(index, element)

Remove the element that corresponds to the specified index from the array.
When the array length is 1/4 of the current capacity, the current capacity will be reduced by half.

| Parameter | Description      |
| --------- | ---------------- |
| index     | Zero-based index |
| element   | Output element   |

```cpp
int result;
bool status = myList.remove(3, result); // Removing the 3rd index.
```

> Returns true when the element was removed, false otherwise.

### Method: remove(element)

Remove the first occurrence of the specified element from the array.
When the array length is 1/4 of the current capacity, the current capacity will be reduced by half.

| Parameter | Description       |
| --------- | ----------------- |
| element   | Element reference |

```cpp
bool status = myList.remove(element);
```

> Returns true when the element was removed, false otherwise.

### Method: slice(from, to)

Slice a portion of the array based on the given range and generate a new one.

| Parameter | Description               |
| --------- | ------------------------- |
| from      | From the zero-based index |
| to        | To the zero-based index   |

```cpp
auto result = myList.slice(3);      // Starting from the 3rd character.
auto result = myList.slice(3, 6);   // From the 3rd to the 6th character.
```

### Method: sort()

Sort the array.

```cpp
myList.sort();
```

### Method: reverse()

Reverse the array (in-place).

```cpp
myList.reverse();
```

### Method: clear()

Clear the array.

```cpp
myList.clear();
```

### Operator: [] (index)

Get the element that corresponds to the specified index.

| Parameter | Description      |
| --------- | ---------------- |
| index     | Zero based index |

```cpp
auto result = myList[0];
```

> Returns the corresponding character (char or wchar_t).

### Operator: = (other)

Assign all properties from the given array.

| Parameter | Description    |
| --------- | -------------- |
| other     | Other instance |

```cpp
ArrayList<int> myList;
myList = fromList;
```

## License

[MIT &copy; Silas B. Domingos](https://balmante.eti.br)
