#ifndef TABLE_H
#define TABLE_H

typedef struct {
    char* field_name;
    char* field_type;
} Field;

typedef struct {
    char* table_name;
    Field* fields;
    int num_fields;
} Table;

Table* create_table(const char* table_name);
void add_field(Table* table, const char* field_name, const char* field_type);
void print_table(Table* table);

#endif
