%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_IDENTIFIER_LEN 128
#define MAX_NUMBER_LEN 128

// Linked list to store tokens
typedef struct TokenNode {
    int token;
    union {
        char strval[MAX_IDENTIFIER_LEN];
        int numval;
    } value;
    struct TokenNode *next;
} TokenNode;

TokenNode *tokenQueueHead = NULL;
TokenNode *tokenQueueTail = NULL;

// Lexer prototype and other definitions
FILE *yyin;
const char *filename;
int line_num = 1;
char invalid_token[128];
int error_flag = 0;

void yyerror(const char *s);
int yylex(void);

%}

%union {
    char strval[MAX_IDENTIFIER_LEN];
    int numval;
}

%token IF ELSE FUNCTION LOCAL RETURN FOR LEFT_PARENTHESIS RIGHT_PARENTHESIS ASSIGNMENT LEFT_BRACE RIGHT_BRACE LEFT_BRACKET RIGHT_BRACKET EQUAL_TO GREATER_THAN LESS_THAN GREATER_THAN_OR_EQUAL_TO LESS_THAN_OR_EQUAL_TO NOT_EQUAL_TO PLUS MINUS MULTIPLY DIVIDE MODULUS COMMA PRINT
%token <strval> IDENTIFIER
%token <numval> NUMBER

%%
program:
    statements
;

statements:
    | statements statement
;

statement:
    IF expression LEFT_BRACE statements RIGHT_BRACE
    | IF expression LEFT_BRACE statements RIGHT_BRACE ELSE LEFT_BRACE statements RIGHT_BRACE
    | LOCAL IDENTIFIER ASSIGNMENT expression
    | FUNCTION IDENTIFIER LEFT_PARENTHESIS parameters RIGHT_PARENTHESIS LEFT_BRACE statements RIGHT_BRACE
    | IDENTIFIER LEFT_PARENTHESIS expression_list RIGHT_PARENTHESIS
    | RETURN expression
    | FOR IDENTIFIER ASSIGNMENT expression COMMA expression LEFT_BRACE statements RIGHT_BRACE
    | expression
    | PRINT LEFT_PARENTHESIS expression_list RIGHT_PARENTHESIS
;

parameters:
    | parameters_list
;

parameters_list:
    IDENTIFIER
    | parameters_list COMMA IDENTIFIER
;

expression_list:
    expression
    | expression_list COMMA expression
;

expression:
    term
    | expression PLUS term
    | expression MINUS term
    | expression MULTIPLY term
    | expression DIVIDE term
    | expression MODULUS term
    | expression EQUAL_TO term
    | expression GREATER_THAN term
    | expression LESS_THAN term
    | expression GREATER_THAN_OR_EQUAL_TO term
    | expression LESS_THAN_OR_EQUAL_TO term
    | expression NOT_EQUAL_TO term
;

term:
    IDENTIFIER
    | NUMBER
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Parser error in file %s:\n", filename);
    if (invalid_token[0] != '\0') {
        fprintf(stderr, "\tInvalid token: %s\n", invalid_token);
    } else {
        fprintf(stderr, "\t%s\n", s);
    }
    error_flag = 1;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input-file>\n", argv[0]);
        exit(1);
    }

    filename = argv[1];
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Error opening file %s.\n", argv[1]);
        exit(1);
    }

    // Enqueue all tokens first
    while (yylex() != 0);

    // Start parsing by dequeuing tokens
    // yyparse();  // Start parsing

    fclose(yyin);

    if (!error_flag) {
        printf("File %s parsed successfully.\n", filename);
    }

    return 0;
}

// Enqueue token to the linked list
void enqueueToken(int token, union YYSTYPE *value) {
    TokenNode *newNode = (TokenNode *)malloc(sizeof(TokenNode));
    newNode->token = token;
    if (token == IDENTIFIER) {
        strncpy(newNode->value.strval, value->strval, MAX_IDENTIFIER_LEN);
    } else if (token == NUMBER) {
        newNode->value.numval = value->numval;
    }
    newNode->next = NULL;
    
    if (tokenQueueTail == NULL) {
        tokenQueueHead = newNode;
        tokenQueueTail = newNode;
    } else {
        tokenQueueTail->next = newNode;
        tokenQueueTail = newNode;
    }
}

// Dequeue token from the linked list
int dequeueToken(union YYSTYPE *value) {
    if (tokenQueueHead == NULL) {
        return 0; // No tokens left
    }
    int token = tokenQueueHead->token;
    if (token == IDENTIFIER) {
        strncpy(value->strval, tokenQueueHead->value.strval, MAX_IDENTIFIER_LEN);
    } else if (token == NUMBER) {
        value->numval = tokenQueueHead->value.numval;
    }
    TokenNode *temp = tokenQueueHead;
    tokenQueueHead = tokenQueueHead->next;
    if (tokenQueueHead == NULL) {
        tokenQueueTail = NULL;
    }
    free(temp);
    return token;
}

int yylex(void) {
    if (tokenQueueHead != NULL) {
        return dequeueToken(&yylval);
    }

    char type[MAX_IDENTIFIER_LEN];
    char value[MAX_IDENTIFIER_LEN];
    int c;

    while ((c = fgetc(yyin)) != EOF) {
        // Skip whitespace characters
        while (c == ' ' || c == '\t') {
            c = fgetc(yyin);
        }

        // Skip empty lines
        if (c == '\n') {
            line_num++;
            continue; // Ignore empty lines and continue reading
        }

        ungetc(c, yyin);

        if (fscanf(yyin, "%s", type) == EOF) break;

        union YYSTYPE yylval_temp;

        if (strcmp(type, "IF") == 0) { enqueueToken(IF, &yylval_temp); continue; }
        if (strcmp(type, "ELSE") == 0) { enqueueToken(ELSE, &yylval_temp); continue; }
        if (strcmp(type, "FUNCTION") == 0) { enqueueToken(FUNCTION, &yylval_temp); continue; }
        if (strcmp(type, "LOCAL") == 0) { enqueueToken(LOCAL, &yylval_temp); continue; }
        if (strcmp(type, "RETURN") == 0) { enqueueToken(RETURN, &yylval_temp); continue; }
        if (strcmp(type, "FOR") == 0) { enqueueToken(FOR, &yylval_temp); continue; }
        if (strcmp(type, "LEFT_PARENTHESIS") == 0) { enqueueToken(LEFT_PARENTHESIS, &yylval_temp); continue; }
        if (strcmp(type, "RIGHT_PARENTHESIS") == 0) { enqueueToken(RIGHT_PARENTHESIS, &yylval_temp); continue; }
        if (strcmp(type, "ASSIGNMENT") == 0) { enqueueToken(ASSIGNMENT, &yylval_temp); continue; }
        if (strcmp(type, "LEFT_BRACE") == 0) { enqueueToken(LEFT_BRACE, &yylval_temp); continue; }
        if (strcmp(type, "RIGHT_BRACE") == 0) { enqueueToken(RIGHT_BRACE, &yylval_temp); continue; }
        if (strcmp(type, "LEFT_BRACKET") == 0) { enqueueToken(LEFT_BRACKET, &yylval_temp); continue; }
        if (strcmp(type, "RIGHT_BRACKET") == 0) { enqueueToken(RIGHT_BRACKET, &yylval_temp); continue; }
        if (strcmp(type, "EQUAL_TO") == 0) { enqueueToken(EQUAL_TO, &yylval_temp); continue; }
        if (strcmp(type, "GREATER_THAN") == 0) { enqueueToken(GREATER_THAN, &yylval_temp); continue; }
        if (strcmp(type, "LESS_THAN") == 0) { enqueueToken(LESS_THAN, &yylval_temp); continue; }
        if (strcmp(type, "GREATER_THAN_OR_EQUAL_TO") == 0) { enqueueToken(GREATER_THAN_OR_EQUAL_TO, &yylval_temp); continue; }
        if (strcmp(type, "LESS_THAN_OR_EQUAL_TO") == 0) { enqueueToken(LESS_THAN_OR_EQUAL_TO, &yylval_temp); continue; }
        if (strcmp(type, "NOT_EQUAL_TO") == 0) { enqueueToken(NOT_EQUAL_TO, &yylval_temp); continue; }
        if (strcmp(type, "PLUS") == 0) { enqueueToken(PLUS, &yylval_temp); continue; }
        if (strcmp(type, "MINUS") == 0) { enqueueToken(MINUS, &yylval_temp); continue; }
        if (strcmp(type, "MULTIPLY") == 0) { enqueueToken(MULTIPLY, &yylval_temp); continue; }
        if (strcmp(type, "DIVIDE") == 0) { enqueueToken(DIVIDE, &yylval_temp); continue; }
        if (strcmp(type, "MODULUS") == 0) { enqueueToken(MODULUS, &yylval_temp); continue; }
        if (strcmp(type, "COMMA") == 0) { enqueueToken(COMMA, &yylval_temp); continue; }
        if (strcmp(type, "PRINT") == 0) { enqueueToken(PRINT, &yylval_temp); continue; }

        if (strcmp(type, "IDENTIFIER") == 0) {
            if (fscanf(yyin, "%s", value) != 1) {
                yyerror("Error reading identifier value");
                return -1;
            }
            strncpy(yylval_temp.strval, value, MAX_IDENTIFIER_LEN);
            enqueueToken(IDENTIFIER, &yylval_temp);
            continue;
        }

        if (strcmp(type, "NUMBER") == 0) {
            if (fscanf(yyin, "%s", value) != 1) {
                yyerror("Error reading number value");
                return -1;
            }
            yylval_temp.numval = atoi(value);
            enqueueToken(NUMBER, &yylval_temp);
            continue;
        }

        // Handle unrecognized tokens
        strcpy(invalid_token, type);
        yyerror("Invalid Token found.");
        return -1;
    }
    return 0; // End of file
}


