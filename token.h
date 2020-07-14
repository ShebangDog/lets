//
// Created by ayumu on 2020/07/14.
//

#ifndef CALCULATOR_TOKEN_H
#define CALCULATOR_TOKEN_H

typedef enum kind_t {
    T_NUM,
    T_OPE,
    T_ROOT,
    T_END,
} KindToken;

typedef struct token {
    char value;
    KindToken kind;

    struct token* next_token;
} Token;

Token* new_token(Token token, Token *parent);

#endif //CALCULATOR_TOKEN_H
