#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "table.h"
#include "btree.h"
#include "input.h" 

InputBuffer* input_buffer;
BTree* btree;

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT } PrepareResult;

typedef enum { STATEMENT_INSERT, STATEMENT_SELECT, STATEMENT_CREATE_TABLE } StatementType;

typedef struct {
    StatementType type;
} Statement;

void print_prompt() { printf("db > "); }

MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        close_input_buffer(input_buffer);
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
    if (strncmp(input_buffer->buffer, "INSERT", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if (strcmp(input_buffer->buffer, "SELECT") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
        if (strncmp(input_buffer->buffer, "CREATE TABLE", 12) == 0) {
        statement->type = STATEMENT_CREATE_TABLE;
        return PREPARE_SUCCESS;
    }
    return PREPARE_UNRECOGNIZED_STATEMENT;
}

void execute_statement(Statement* statement) {
    switch (statement->type) {
        case (STATEMENT_CREATE_TABLE): {
            char table_name[100];

             int matched = sscanf(input_buffer->buffer, "CREATE TABLE %99s", table_name);

            if (matched != 1) {
                printf("Erreur : nom de la table non valide.\n");
                return;
            }

            Table* table = create_table(table_name);
            add_field(table, "id", "int(AUTO-INCREMENT)");
            printf("Table '%s' creee. Merci d'indiquer les champs.\n", table->table_name);

            char field_name[100];
            char field_type[100];

            while (true) {
                printf("Nom du champ (ou 'q' pour terminer) : ");
                scanf("%s", field_name);

                if (strcmp(field_name, "q") == 0) {
                    break;
                }

                printf("Type du champ : ");
                scanf("%s", field_type);

                add_field(table, field_name, field_type);
            }

            insert_btree(btree, table);
            printf("Table %s créée avec succès.\n", table->table_name);
            print_table(table);
            break;
        }

        case (STATEMENT_SELECT):
            printf("Commande SELECT reçue.\n");
            break;

        default:
            printf("Commande non reconnue.\n");
            break;
    }
}

void repl(void) {
    input_buffer = new_input_buffer();
    btree = create_btree(3);  // Initialise le B-tree avec un ordre de 3

    while (true) {
        print_prompt();
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.') {
            switch (do_meta_command(input_buffer)) {
                case META_COMMAND_SUCCESS:
                    continue;
                case META_COMMAND_UNRECOGNIZED_COMMAND:
                    printf("Unrecognized command '%s'\n", input_buffer->buffer);
                    continue;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement)) {
            case PREPARE_SUCCESS:
                printf("recognized statement\n");
                break;
            case PREPARE_UNRECOGNIZED_STATEMENT:
                printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
                continue;
        }

        execute_statement(&statement);
        printf("Executed.\n");
    }
}
