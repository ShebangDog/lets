//
// Created by ayumu on 2020/07/14.
//

#ifndef CALCULATOR_NODE_H
#define CALCULATOR_NODE_H

typedef enum kind_n {
    NUMBER,
    OPERATOR
} KindNode;

typedef struct node {
    char value;
    KindNode kind;

    struct node* left;
    struct node* right;
} Node;

Node *new_node(KindNode kind, char value, Node* left, Node* right);

#endif //CALCULATOR_NODE_H
