#include "table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

Table* create_table(const char* table_name) {
    Table* table = (Table*)malloc(sizeof(Table));
    table->table_name = strdup(table_name);
    table->fields = NULL;
    table->num_fields = 0;
    return table;
}

void add_field(Table* table, const char* field_name, const char* field_type) {
    table->num_fields++;
    table->fields = realloc(table->fields, table->num_fields * sizeof(Field));
    table->fields[table->num_fields - 1].field_name = strdup(field_name);
    table->fields[table->num_fields - 1].field_type = strdup(field_type);
}


void print_table(Table* table) {
    printf("+--------------------------------+\n");
    printf("|           Table: %s         |\n", table->table_name);
    printf("+--------------------------------+\n");

    printf("| %-15s | %-12s |\n", "Field Name", "Field Type");
    printf("+-------------------+------------+\n");
    
    for (int i = 0; i < table->num_fields; i++) {
        printf("| %-15s | %-12s |\n", table->fields[i].field_name, table->fields[i].field_type);
    }

    printf("+-------------------+------------+\n");
}
