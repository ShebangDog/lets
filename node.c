//
// Created by ayumu on 2020/07/14.
//

#include "node.h"
#include <stdlib.h>

Node *new_node(KindNode kind, char value, Node* left, Node* right) {
    Node *node = calloc(sizeof(Node), 1);

    node->kind = kind;
    node->value = value;

    node->left = left;
    node->right = right;

    return node;
}
