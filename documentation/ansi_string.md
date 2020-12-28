## SPL - AnsiString

This class is useful for managing raw ANSI strings, each character is represented by 1 byte and you can have a binary safe string with any character from the ASC table. If you want to delve into the details please check the [source code](../library/header/strings/ansi_string.hpp).

```cpp
#include <spl/strings.hpp>
using namespace SPL;

AnsiString myString;                        // Empty container.
AnsiString myString(128);                   // Pre-allocated container for 128 characters.
AnsiString myString(fromPointer, 128);      // Copy characters from a pointer with specific length.
AnsiString myString("Hello word");          // Copy characters from a const string.
AnsiString myString(fromString);            // Copy characters from another ANSI string class.
AnsiString myString(SPL::Move(fromString)); // Move characters from another ANSI string.
```

### Method: getLength()

Get the number of characters in the string.

```cpp
Size result = myString.getLength();
```

### Method: isEmpty()

Determines whether or not the string is empty.

```cpp
bool result = myString.isEmpty();
```

> Returns true when it's empty, false otherwise.

### Method: getIterator()

Get a new string iterator.

```cpp
auto result = myString.getIterator();
```

### Method: concat(pack)

Merge all the given strings into a new one.

| Parameter | Description     |
| --------- | --------------- |
| pack      | Pack of strings |

```cpp
auto result = myString.concat({
        fromString1,
        fromString2,
        AnsiString("example...")
    });
```

### Method: indexOf(search, from)

Get the first index occurrence of the specified character in the string.

| Parameter | Description               |
| --------- | ------------------------- |
| search    | Search character          |
| from      | From the zero-based index |

```cpp
Index result = myString.indexOf("find me");
Index result = myString.indexOf("find me", 10); // Starting from the 10th index.
```

> Returns the corresponding index or -1 when the character wasn't found.

### Method: lastIndexOf(search, from)

Get the last index occurrence of the specified character in the string.

| Parameter | Description               |
| --------- | ------------------------- |
| search    | Search character          |
| from      | From the zero-based index |

```cpp
Index result = myString.lastIndexOf("find me");
Index result = myString.lastIndexOf("find me", 10); // Starting from the 10th index.
```

> Returns the corresponding index or -1 when the character wasn't found.

### Method: contains(search)

Determines whether or not the string contains the specified character.

| Parameter | Description      |
| --------- | ---------------- |
| search    | Search character |

```cpp
bool status = myString.contains("find me");
```

> Returns true when the character was found, false otherwise.

### Method: startsWith(search)

Determines whether or not the string starts with the specified character.

| Parameter | Description      |
| --------- | ---------------- |
| search    | Search character |

```cpp
bool status = myString.startsWith("find me");
```

> Returns true when the string starts with the specified character, false otherwise.

### Method: endsWith(search)

Determines whether or not the string ends with the specified character.

| Parameter | Description      |
| --------- | ---------------- |
| search    | Search character |

```cpp
bool status = myString.endsWith("find me");
```

> Returns true when the string ends with the specified character, false otherwise.

### Method: compare(other, from, to)

Compare both strings.

| Parameter | Description               |
| --------- | ------------------------- |
| other     | Other string              |
| from      | From the zero-based index |
| to        | To the zero-based index   |

```cpp
Index result = myString.compare("compare me");
Index result = myString.compare("compare me", 10);      // Starting from the 10th character.
Index result = myString.compare("compare me", 10, 20);  // From the 10th to the 20th character.
```

> Returns -1 when this string is less than the other one, 0 when this string is equals to the other one or 1 when this string is greater than the other one.

### Method: slice(from, to)

Slice a portion of the string based on the given range and generate a new one.

| Parameter | Description               |
| --------- | ------------------------- |
| from      | From the zero-based index |
| to        | To the zero-based index   |

```cpp
auto result = myString.slice(10);       // Starting from the 10th character.
auto result = myString.slice(10, 20);   // From the 10th to the 20th character.
```

### Method: reverse()

Reverse the string (in-place).

```cpp
myString.reverse();
```

### Operator: [] (index)

Get the character that corresponds to the specified index.

| Parameter | Description      |
| --------- | ---------------- |
| index     | Zero based index |

```cpp
auto result = myString[0];
```

> Returns the corresponding character.

### Operator: = (other)

Assign all properties from the given string.

| Parameter | Description    |
| --------- | -------------- |
| other     | Other instance |

```cpp
AnsiString myString;
myString = fromString;
```

## License

[MIT &copy; Silas B. Domingos](https://balmante.eti.br)
