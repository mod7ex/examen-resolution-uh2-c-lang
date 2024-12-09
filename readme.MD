| Specifier | Description                                    | Example Output           |
|-----------|------------------------------------------------|--------------------------|
| `%d`      | Integer (decimal)                             | `42`                     |
| `%i`      | Integer (same as `%d`)                        | `42`                     |
| `%u`      | Unsigned integer                              | `42`                     |
| `%f`      | Floating-point number                         | `3.141590`               |
| `%.nf`    | Floating-point with `n` decimal places        | `3.14` (for `%.2f`)      |
| `%e`      | Scientific notation (lowercase `e`)           | `3.14e+00`               |
| `%E`      | Scientific notation (uppercase `E`)           | `3.14E+00`               |
| `%g`      | Shorter of `%f` or `%e`                       | `3.14`                   |
| `%G`      | Shorter of `%F` or `%E`                       | `3.14`                   |
| `%c`      | Single character                              | `A`                      |
| `%s`      | Null-terminated string                        | `Hello`                  |
| `%p`      | Pointer address                               | `0x7ffde1234567`         |
| `%x`      | Hexadecimal (lowercase)                       | `1a3f`                   |
| `%X`      | Hexadecimal (uppercase)                       | `1A3F`                   |
| `%o`      | Octal                                         | `377`                    |
| `%n`      | Writes the number of characters printed so far| (rarely used)            |
| `%%`      | Prints a literal `%`                          | `%`                      |

### Flags for Format Specifiers

| Flag     | Description                                    | Example                  |
|----------|------------------------------------------------|--------------------------|
| `-`      | Left-align the output                         | `%-10d` → `42        `   |
| `+`      | Forces a sign (+ or -) for numeric values      | `%+d` → `+42`           |
| ` ` (space)| Prints a space before positive numbers        | `% d` → ` 42`           |
| `0`      | Pads numbers with leading zeros               | `%05d` → `00042`        |
| `#`      | Adds prefix for octal (`0`), hex (`0x`/`0X`)   | `%#x` → `0x1a3f`        |

### Width and Precision Modifiers

| Modifier | Description                                    | Example                  |
|----------|------------------------------------------------|--------------------------|
| `width`  | Minimum field width                           | `%10d` → `        42`   |
| `.prec`  | Number of digits after decimal for floats      | `%.2f` → `3.14`         |
| `*`      | Width or precision taken from arguments       | `%*d` (width = 5) → `   42` |
