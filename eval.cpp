#include <cstdlib>
#include <iostream>

using namespace std;

int add(int a, int b) {return a + b;}
int sub(int a, int b) {return a - b;}
int mul(int a, int b) {return a * b;}
int divide(int a, int b) {
    if (b == 0) {
        printf("Division by zero\n");
        exit(1);
    }
    return a / b;
}

enum KIND
{
    OPERAND,
    OPERATOR
};

enum OPERATOR
{
    ADD,
    SUB,
    MUL,
    DIV
};

// Mapping enumeration operators to their corresponding function:
typedef int (*fn)(int, int);
static fn funcs[] = {add, sub, mul, divide};

class Node
{
    enum KIND kind;
    Node *left;
    Node *right;
    int value;
    enum OPERATOR op;
    
public:
    // Constructor for operands
    Node(enum KIND k, int v) : kind(k), value(v), left(nullptr), right(nullptr) {}
    // Constructor for operators
    Node(enum KIND k, enum OPERATOR o, Node* l, Node* r) : kind(k), op(o), left(l), right(r) {}
    int eval();
};

int Node::eval()
{
    Node *current = this;
    if (current->kind == OPERAND)
    {
        return current->value;
    }
    else if (current->kind == OPERATOR)
    {
        // We recursively go deeper in the tree by calling eval on the left and right 
        // nodes, and then we apply the operator by calling our array of function pointers
        // by calling `funcs[current->op] ( a , b )` .
        return funcs[current->op](current->left->eval(), current->right->eval());
    }
    else
    {
        printf("Unexpected kind value: %d\n", current->kind);
        exit(1);
    }
}

int main()
{
    /** Example 1: 
        Expression: (5+3) - 2
        Tree:
         -
        / \
        +  c=2
        / \
    a=5   b=3
    */
    Node a(OPERAND, 5);
    Node b(OPERAND, 3);
    Node c(OPERAND, 2);
    Node plus(OPERATOR, ADD, &a,&b);
    Node minus(OPERATOR, SUB,&plus,&c);

    // Evaluate the tree
    int e0 = minus.eval();
    printf("Evaluation of example 1: (5+3) - 2 = %d\n", e0);

    /** Example 2: 
        Expression: 3 + ( (5+9) * 2 )
        Tree:
         +               n0
        / \
        3  *             n1 n2
          / \
         +   2           n3 n4
        / \ 
        5 9              n5 n6
    */
    Node n6(OPERAND, 5);
    Node n5(OPERAND, 9);
    Node n4(OPERAND, 2);
    Node n3(OPERATOR, ADD,&n5,&n6);
    Node n2(OPERATOR, MUL,&n3,&n4);
    Node n1(OPERAND, 3);
    Node n0(OPERATOR, ADD,&n1,&n2);

    // Evaluate the tree
    int e1 = n0.eval();
    printf("Evaluation of example 2: 3 + ( (5+9) * 2 ) = %d\n", e1);

    return 0;
}