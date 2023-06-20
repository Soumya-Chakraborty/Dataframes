#include <stdio.h>
#include <string.h>

#define MAX_COLS 100
#define MAX_ROWS 100

typedef struct {
    char name[50];
    char dtype[50];
} Column;

typedef struct {
    int shape[2];
    Column columns[MAX_COLS];
    char _values[MAX_ROWS][MAX_COLS][50];
} DataFrame2;

typedef struct {
    int shape[2];
    char col_name[50];
    char data[MAX_ROWS][MAX_COLS][50];
} DataFrame;

typedef struct {
    int ignore_index;
    DataFrame2* frame;
    char id_vars[MAX_COLS][50];
    int num_id_vars;
    char value_vars[MAX_COLS][50];
    int num_value_vars;
    char var_name[MAX_COLS][50];
    int num_var_name;
    char value_name[50];
    char col_level[50];
} MeltParams;

void melt(MeltParams* params, DataFrame* result) {
    DataFrame2* frame = params->frame;
    int num_cols = frame->shape[1];
    int num_rows = frame->shape[0];
    int num_new_cols = num_cols - params->num_id_vars - params->num_value_vars;

    char mdata[2][MAX_ROWS][MAX_COLS][50] = {0};

    // Check if id_vars and value_vars are specified
    if (params->num_id_vars == 0 || params->num_value_vars == 0) {
        printf("Please specify 'id_vars' and 'value_vars' parameters.\n");
        return;
    }

    // Check if value_name is specified
    if (strlen(params->value_name) == 0) {
        printf("Please specify 'value_name' parameter.\n");
        return;
    }

    // Check if id_vars are present in frame
    int id_vars_present = 1;
    for (int i = 0; i < params->num_id_vars; i++) {
        int id_var_present = 0;
        for (int j = 0; j < num_cols; j++) {
            if (strcmp(params->id_vars[i], frame->columns[j].name) == 0) {
                id_var_present = 1;
                break;
            }
        }
        if (!id_var_present) {
            id_vars_present = 0;
            break;
        }
    }
    if (!id_vars_present) {
        printf("The following 'id_vars' are not present in the DataFrame:\n");
        for (int i = 0; i < params->num_id_vars; i++) {
            int id_var_present = 0;
            for (int j = 0; j < num_cols; j++) {
                if (strcmp(params->id_vars[i], frame->columns[j].name) == 0) {
                    id_var_present = 1;
                    break;
                }
            }
            if (!id_var_present) {
                printf("%s\n", params->id_vars[i]);
            }
        }
        return;
    }

    // Check if value_vars are present in frame
    int value_vars_present = 1;
    for (int i = 0; i < params->num_value_vars; i++) {
        int value_var_present = 0;
        for (int j = 0; j < num_cols; j++) {
            if (strcmp(params->value_vars[i], frame->columns[j].name) == 0) {
                value_var_present = 1;
                break;
            }
        }
        if (!value_var_present) {
            value_vars_present = 0;
            break;
        }
    }
    if (!value_vars_present) {
        printf("The following 'value_vars' are not present in the DataFrame:\n");
        for (int i = 0; i < params->num_value_vars; i++) {
            int value_var_present = 0;
            for (int j = 0; j < num_cols; j++) {
                if (strcmp(params->value_vars[i], frame->columns[j].name) == 0) {
                    value_var_present = 1;
                    break;
                }
            }
            if (!value_var_present) {
                printf("%s\n", params->value_vars[i]);
            }
        }
        return;
    }

    // Find the indices of id_vars and value_vars
    int idx[MAX_COLS];
    int idx_count = 0;
    for (int i = 0; i < num_cols; i++) {
        int id_var_found = 0;
        for (int j = 0; j < params->num_id_vars; j++) {
            if (strcmp(params->id_vars[j], frame->columns[i].name) == 0) {
                id_var_found = 1;
                break;
            }
        }
        if (!id_var_found) {
            int value_var_found = 0;
            for (int j = 0; j < params->num_value_vars; j++) {
                if (strcmp(params->value_vars[j], frame->columns[i].name) == 0) {
                    value_var_found = 1;
                    break;
                }
            }
            if (value_var_found) {
                idx[idx_count] = i;
                idx_count++;
            }
        }
    }

    // Set data for mdata
    int mdata_col_idx = 0;
    for (int i = 0; i < params->num_id_vars; i++) {
        for (int j = 0; j < num_rows; j++) {
            strcpy(mdata[0][j][mdata_col_idx], frame->_values[j][i]);
        }
        mdata_col_idx++;
    }
    for (int i = 0; i < idx_count; i++) {
        for (int j = 0; j < num_rows; j++) {
            strcpy(mdata[0][j][mdata_col_idx], frame->columns[idx[i]].name);
            strcpy(mdata[1][j][mdata_col_idx], frame->_values[j][idx[i]]);
        }
        mdata_col_idx++;
    }
    for (int i = 0; i < params->num_var_name; i++) {
        for (int j = 0; j < num_rows; j++) {
            strcpy(mdata[0][j][mdata_col_idx], params->var_name[i]);
        }
        mdata_col_idx++;
    }
    for (int i = 0; i < params->num_value_vars; i++) {
        for (int j = 0; j < num_rows; j++) {
            strcpy(mdata[0][j][mdata_col_idx], params->value_vars[i]);
            strcpy(mdata[1][j][mdata_col_idx], frame->_values[j][idx[i + params->num_id_vars]]);
        }
        mdata_col_idx++;
    }

    // Set columns for the result DataFrame
    strcpy(result->col_name, frame->columns[0].name);
    for (int i = 0; i < params->num_id_vars; i++) {
        strcpy(result->col_name, params->id_vars[i]);
    }
    for (int i = 0; i < params->num_var_name; i++) {
        strcpy(result->col_name, params->var_name[i]);
    }
    strcpy(result->col_name, params->value_name);

    // Set data for the result DataFrame
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < mdata_col_idx; j++) {
            strcpy(result->data[i][j], mdata[0][i][j]);
        }
        strcpy(result->data[i][mdata_col_idx], mdata[1][i][0]);
    }

    // Set shape for the result DataFrame
    result->shape[0] = num_rows;
    result->shape[1] = mdata_col_idx + 1;
}

int main() {
    DataFrame2 frame = {
        .shape = {3, 4},
        .columns = {
            {"A", "int"},
            {"B", "int"},
            {"C", "int"},
            {"D", "int"}
        },
        ._values = {
            {"1", "2", "3", "4"},
            {"5", "6", "7", "8"},
            {"9", "10", "11", "12"}
        }
    };

    MeltParams params = {
        .ignore_index = 0,
        .frame = &frame,
        .id_vars = {"A"},
        .num_id_vars = 1,
        .value_vars = {"B", "C", "D"},
        .num_value_vars = 3,
        .var_name = {"variable"},
        .num_var_name = 1,
        .value_name = "value",
        .col_level = ""
    };

    DataFrame result;

    melt(&params, &result);

    // Print the result DataFrame
    printf("Shape: %d x %d\n", result.shape[0], result.shape[1]);
    printf("Columns: \n");
    for (int i = 0; i < result.shape[1]; i++) {
        printf("%s ", result.col_name);
    }
    printf("\n");

    for (int i = 0; i < result.shape[0]; i++) {
        for (int j = 0; j < result.shape[1]; j++) {
            printf("%s ", result.data[i][j]);
        }
        printf("\n");
    }

    return 0;
}
