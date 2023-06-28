#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int index_size;
    char** index;
    int columns_size;
    char** columns;
    double** values;
} DataFrame;

DataFrame* pivot(DataFrame* df) {
    int num_index = df->index_size;
    int num_columns = df->columns_size;

    DataFrame* result = malloc(sizeof(DataFrame));
    result->index_size = num_columns;
    result->index = malloc(num_columns * sizeof(char*));
    result->columns_size = num_index;
    result->columns = malloc(num_index * sizeof(char*));
    result->values = malloc(num_columns * sizeof(double*));

    // Transpose the index and columns
    for (int i = 0; i < num_index; i++) {
        result->index[i] = strdup(df->columns[i]);
    }
    for (int i = 0; i < num_columns; i++) {
        result->columns[i] = strdup(df->index[i]);
    }

    // Allocate memory for values and transpose the data
    for (int i = 0; i < num_columns; i++) {
        result->values[i] = malloc(num_index * sizeof(double));
        for (int j = 0; j < num_index; j++) {
            result->values[i][j] = df->values[j][i];
        }
    }

    return result;
}

void printDataFrame(DataFrame* df) {
    printf("| Index\t\t|");
    for (int i = 0; i < df->index_size; i++) {
        printf(" %s\t|", df->index[i]);
    }
    printf("\n");

    printf("| Columns\t|");
    for (int i = 0; i < df->columns_size; i++) {
        printf(" %s\t|", df->columns[i]);
    }
    printf("\n");

    printf("| Values\t|\n");
    for (int i = 0; i < df->columns_size; i++) {
        printf("| %s\t|", df->columns[i]);
        for (int j = 0; j < df->index_size; j++) {
            printf(" %.2f\t|", df->values[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Create sample data for the DataFrame
    char* index[] = { "Index A", "Index B", "Index C" };
    char* columns[] = { "Column X", "Column Y" };
    double values[][2] = {
        { 1.1, 2.2 },
        { 3.3, 4.4 },
        { 5.5, 6.6 }
    };
    int index_size = sizeof(index) / sizeof(index[0]);
    int columns_size = sizeof(columns) / sizeof(columns[0]);

    // Create DataFrame structure
    DataFrame df;
    df.index_size = index_size;
    df.index = index;
    df.columns_size = columns_size;
    df.columns = columns;
    df.values = malloc(index_size * sizeof(double*));
    for (int i = 0; i < index_size; i++) {
        df.values[i] = values[i];
    }

    // Perform pivot operation
    DataFrame* result = pivot(&df);

    // Display the result
    printf("Original DataFrame:\n");
    printDataFrame(&df);

    printf("\nPivoted DataFrame:\n");
    printDataFrame(result);

    // Clean up memory
    for (int i = 0; i < index_size; i++) {
        free(df.index[i]);
    }
    free(df.index);
    for (int i = 0; i < columns_size; i++) {
        free(df.columns[i]);
    }
    free(df.columns);
    for (int i = 0; i < index_size; i++) {
        free(df.values[i]);
    }
    free(df.values);
    free(result);

    return 0;
}
