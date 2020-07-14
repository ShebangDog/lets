#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "token.h"
#include "node.h"

//ch -> token
unsigned is_num(char ch);
unsigned is_space(char ch);
unsigned is_operator(char ch);

//token -> node
unsigned is_num_token(Token *token);
unsigned is_operator_token(Token *token);
unsigned is_root_token(Token *token);
unsigned is_end_token(Token *token);

Token *tokenize(char *string);
Node *parse(Token *token, Node *head);

void print_token(Token* token);
void print_node(Node* node);

int main(void) {
    char buffer[256] = {0};

    scanf("%[^\n]255s", buffer);
    char *string = buffer;

    Token *token = tokenize(string);
    print_token(token);

    Node *node = parse(token, NULL);
    print_node(node);

    return 0;
}

//ch -> token
unsigned is_num(char ch) {
    return '0' <= ch && ch <= '9';
}

unsigned is_space(char ch) {
    return isspace(ch);
}

unsigned is_operator(char ch) {
    return ch == '+' || ch == '-';
}

//token -> node
unsigned is_num_token(Token *token) {
    return token->kind == T_NUM;
}

unsigned is_operator_token(Token *token) {
    return token->kind == T_OPE;
}

unsigned is_root_token(Token *token) {
    return token->kind == T_ROOT;
}

unsigned is_end_token(Token *token) {
    return token->kind == T_END;
}

Token *tokenize(char *string) {
    Token *root = calloc(sizeof(Token), 1);
    root->kind = T_ROOT;

    Token *head = root;

    for(;; string++) {
        char value = string[0];

        if (is_space(value)) continue;
        if (is_num(value)) {
            Token token = {.value = value, .kind = T_NUM, .next_token = NULL};
            head = new_token(token, head);
        }

        if (is_operator(value)) {
            Token token = {.value = value, .kind = T_OPE, .next_token = NULL};
            head = new_token(token, head);
        }

        if (value == '\0') {
            Token token = {.kind = T_END};
            head = new_token(token, head);

            break;
        }

    }

    return root;
}

Node* number(Token *token);
Node* expression(Token *token);

Node* expression(Token *token) {
    Node *node = number(token);
    token = token->next_token;

    while (1) {
        if (is_num_token(token)) exit(1);

        if (is_end_token(token)) return node;

        if (is_operator_token(token)) {
            char symbol = token->value;
            token = token->next_token;

            Node *right_number = number(token);
            node = new_node(OPERATOR, symbol, node, right_number);

            token = token->next_token;
            continue;
        }

        exit(2);
    }
}

Node* number(Token *token) {
    Node *node =  new_node(NUMBER, token->value, NULL, NULL);

    return node;
}

Node *parse(Token *token ,Node* node) {
    if (!is_root_token(token)) exit(3);

    Node *result = expression(token->next_token);

    return result;
}

void print_token(Token* token) {
    Token *head = token;
    while (head->kind != T_END) {
        if (head->kind != T_ROOT) printf("%c ", head->value);

        head = head->next_token;
    }
    puts("");
}

void _print_node(Node* node) {
    if (node->left != NULL) _print_node(node->left);
    if (node->right != NULL) _print_node(node->right);

    printf("%c ", node->value);
}

void print_node(Node* node) {
    _print_node(node);
}
