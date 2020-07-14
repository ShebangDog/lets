//
// Created by ayumu on 2020/07/14.
//

#include "token.h"
#include <stdlib.h>

Token* new_token(Token token, Token *parent) {
    Token *t = calloc(sizeof(Token), 1);
    parent->next_token = t;

    t->kind = token.kind;
    t->value = token.value;

    return t;
}