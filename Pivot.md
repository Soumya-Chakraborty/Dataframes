# DataFrame Pivot Operation in C

This C program demonstrates a DataFrame structure and performs a pivot operation on it. The program transposes the index and columns of a DataFrame and displays the original and pivoted DataFrames.

## Code Explanation

The code consists of the following components:

1. Includes the necessary libraries for input/output, standard library, and string handling.
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
```

2. Defines the `DataFrame` structure to store index, columns, and values.
```c
typedef struct {
    int index_size;
    char** index;
    int columns_size;
    char** columns;
    double** values;
} DataFrame;
```

3. Implements the `pivot` function that takes a DataFrame pointer and returns a new DataFrame pointer with transposed index and columns.
```c
DataFrame* pivot(DataFrame* df) {
    // Implementation details
    return result;
}
```

4. Implements the `printDataFrame` function that prints the index, columns, and values of a DataFrame.
```c
void printDataFrame(DataFrame* df) {
    // Implementation details
}
```

5. The `main` function creates a sample DataFrame, performs the pivot operation, and displays the original and pivoted DataFrames.
```c
int main() {
    // Create sample data for the DataFrame
    
    // Create DataFrame structure
    
    // Perform pivot operation
    
    // Display the result
    
    // Clean up memory
    
    return 0;
}
```

## Usage

1. Compile the program using a C compiler.
```
gcc dataframe_pivot.c -o dataframe_pivot
```

2. Run the executable.
```
./dataframe_pivot
```

## Output

The program generates the following output:

```
Original DataFrame:
| Index         | Index A    | Index B    | Index C    |
| Columns       | Column X   | Column Y   |
| Values        |
| Column X      | 1.10       | 3.30       | 5.50       |
| Column Y      | 2.20       | 4.40       | 6.60       |

Pivoted DataFrame:
| Index         | Column X   | Column Y   |
| Columns       | Index A    | Index B    | Index C    |
| Values        |
| Index A       | 1.10       | 2.20       |
| Index B       | 3.30       | 4.40       |
| Index C       | 5.50       | 6.60       |
```

## Cleanup

The program frees the memory allocated for the DataFrames to avoid memory leaks.

## License

This project is licensed under the [MIT License](LICENSE).

Feel free to modify and use the code according to your needs.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any changes or improvements you would like to make.

## Acknowledgements

This program was developed by Soumya Chakraborty as a demonstration of DataFrame pivot operation in C.
