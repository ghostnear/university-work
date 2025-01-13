%{
#include <stdio.h>
#include <stdlib.h>

FILE *yyout;
const char *yyout_filename;
const char *filename;
int line_num = 1;
int col_num = 1;

void print_error(const char *msg, char symbol, const char *filename, int line, int col) {
    fprintf(stderr, "Lexer error in file %s at line %d, column %d:\n\t%s '%c'.\n", filename, line, col, msg, symbol);
    remove(yyout_filename);
}
%}

/* Define tokens */
DIGIT [0-9]
LETTER [a-zA-Z]
ID {LETTER}({LETTER}|{DIGIT})*
COMMENT "--".*

%%

"if"            { fprintf(yyout, "IF\n"); col_num += yyleng; }
"else"          { fprintf(yyout, "ELSE\n"); col_num += yyleng; }
"function"      { fprintf(yyout, "FUNCTION\n"); col_num += yyleng; }
"local"         { fprintf(yyout, "LOCAL\n"); col_num += yyleng; }
"return"        { fprintf(yyout, "RETURN\n"); col_num += yyleng; }
"for"           { fprintf(yyout, "FOR\n"); col_num += yyleng; }
"("             { fprintf(yyout, "LEFT_PARENTHESIS\n"); col_num++; }
")"             { fprintf(yyout, "RIGHT_PARENTHESIS\n"); col_num++; }
"="             { fprintf(yyout, "ASSIGNMENT\n"); col_num++; }
"{"             { fprintf(yyout, "LEFT_BRACE\n"); col_num++; }
"}"             { fprintf(yyout, "RIGHT_BRACE\n"); col_num++; }
"["             { fprintf(yyout, "LEFT_BRACKET\n"); col_num++; }
"]"             { fprintf(yyout, "RIGHT_BRACKET\n"); col_num++; }
"=="            { fprintf(yyout, "EQUAL_TO\n"); col_num += yyleng; }
">"             { fprintf(yyout, "GREATER_THAN\n"); col_num++; }
"<"             { fprintf(yyout, "LESS_THAN\n"); col_num++; }
">="            { fprintf(yyout, "GREATER_THAN_OR_EQUAL_TO\n"); col_num += yyleng; }
"<="            { fprintf(yyout, "LESS_THAN_OR_EQUAL_TO\n"); col_num += yyleng; }
"!="            { fprintf(yyout, "NOT_EQUAL_TO\n"); col_num += yyleng; }
"+"             { fprintf(yyout, "PLUS\n"); col_num++; }
"-"             { fprintf(yyout, "MINUS\n"); col_num++; }
"*"             { fprintf(yyout, "MULTIPLY\n"); col_num++; }
"/"             { fprintf(yyout, "DIVIDE\n"); col_num++; }
"%"             { fprintf(yyout, "MODULUS\n"); col_num++; }

{ID}            { fprintf(yyout, "IDENTIFIER %s\n", yytext); col_num += yyleng; }
{DIGIT}+        { fprintf(yyout, "NUMBER %s\n", yytext); col_num += yyleng; }

{COMMENT}       { /* ignore comments */ col_num += yyleng; }

[ \t\n,]        { 
    if (yytext[0] == '\n') { 
        line_num++; 
        col_num = 1; 
    } else { 
        col_num += yyleng; 
    }
    /* skip whitespace and comma */ 
}

.               { 
    print_error("Unallowed symbol", yytext[0], filename, line_num, col_num); 
    exit(1); 
}

%%

int yywrap(void) {
    return 1;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <input-file> <output-file>\n", argv[0]);
        exit(1);
    }

    filename = argv[1];
    yyin = fopen(argv[1], "r");
    if (!yyin) {
        fprintf(stderr, "Error opening file %s.\n", argv[1]);
        exit(1);
    }

    yyout = fopen(argv[2], "w");
    if (!yyout) {
        fprintf(stderr, "Error opening file %s.\n", argv[2]);
        fclose(yyin);
        exit(1);
    }
    yyout_filename = argv[2];

    yylex();

    fclose(yyin);
    fclose(yyout);
    return 0;
}
