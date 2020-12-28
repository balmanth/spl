# Standard Personal Library

Welcome to my Standard Personal Library (a.k.a SPL), fell free to use it in any project that you want.

The idea of this library is to provide as many generic purpose algorithms and data structures as possible... And to make it possible, I will try to use this library in any personal project developed in the near future, as I'm always learning something new I can evolve this library during the process.

## How to use

```cpp
#include "{PROJECT_INCLUDE}/spl/{SPL_HEADER}"
```

> Replace `{PROJECT_INCLUDE}` and `{SPL_HEADER}` to the corresponding path in your environment.

## Ready to use

See below what is already done and ready to use.

#### Containers

List of available containers, for more details please check the respective documentation.

| Name                                                        | Header              | Description/Documentation                           |
| ----------------------------------------------------------- | ------------------- | --------------------------------------------------- |
| [SPL::AnsiString](./library/header/strings/ansi_string.hpp) | spl/strings.hpp     | [See documentation](./documentation/ansi_string.md) |
| [SPL::WideString](./library/header/strings/wide_string.hpp) | spl/strings.hpp     | [See documentation](./documentation/wide_string.md) |
| [SPL::ArrayList](./library/header/arrays/array_list.hpp)    | spl/arrays.hpp      | [See documentation](./documentation/array_list.md)  |
| [SPL::HashSet](./library/header/hash_tables/hash_set.hpp)   | spl/hash_tables.hpp | [See documentation](./documentation/hash_set.md)    |
| [SPL::HashMap](./library/header/hash_tables/hash_map.hpp)   | spl/hash_tables.hpp | [See documentation](./documentation/hash_map.md)    |
| [SPL::PrefixSet](./library/header/prefixtrees/set.hpp)      | spl/prefixtrees.hpp | A prefix set container (with ternary search tree)   |
| [SPL::PrefixMap](./library/header/prefixtrees/map.hpp)      | spl/prefixtrees.hpp | A prefix map container (with ternary search tree)   |

> Use them by including the provided header file.

#### Interfaces

List of available interfaces.

| Name                                                          | Description                             |
| ------------------------------------------------------------- | --------------------------------------- |
| [SPL::Exception](./library/header/interfaces/exception.hpp)   | Common interface for exceptions         |
| [SPL::Iterator](./library/header/interfaces/iterator.hpp)     | Common interface for iterators          |
| [SPL::Iterable](./library/header/interfaces/iterable.hpp)     | Common interface for iterable objects   |
| [SPL::Comparable](./library/header/interfaces/comparable.hpp) | Common interface for comparable objects |
| [SPL::String](./library/header/interfaces/string.hpp)         | Common interface for strings            |
| [SPL::List](./library/header/interfaces/list.hpp)             | Common interface for list containers    |
| [SPL::Hash](./library/header/interfaces/hash.hpp)             | Common interface for hash generators    |
| [SPL::Set](./library/header/interfaces/set.hpp)               | Common interface for set containers     |
| [SPL::Map](./library/header/interfaces/map.hpp)               | Common interface for map containers     |

> Use all of them by including `spl/interfaces.hpp`

## Disclaimer

This library is strictly personal, if you want to use some feature in production but found a bug, you are welcome to contact me and contribute.

Ah, and English isn't my main language, I'm trying to get better on that as well 😊

## License

[MIT &copy; Silas B. Domingos](https://balmante.eti.br)
