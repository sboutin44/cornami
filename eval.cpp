#include <cstdlib>
#include <iostream>

using namespace std;

// Define the operator functions, which is how we will apply 
// them when evaluating the tree.
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

class Node
{
    enum KIND kind;
    Node *left;
    Node *right;
    int value;

    // Function pointers are used here for ease of use in the eval function.
    int (*operatorFunctionPointer)(int, int);  

public:
    // Constructor for operands
    Node(enum KIND k, int v) : 
        kind(k), value(v), left(nullptr), right(nullptr) {}
    // Constructor for operators
    Node(enum KIND k, int (*functionName)(int, int), Node* l, Node* r) : 
        kind(k), operatorFunctionPointer(functionName), left(l), right(r) {}
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
        // We recursively traverse the tree by calling "eval" on the left and right 
        // nodes, and then apply the operator by calling the function it points to.
        return current->operatorFunctionPointer(
            current->left->eval(),
            current->right->eval() 
        );
    }
    else
    {
        printf("Unexpected kind value: %d\n", current->kind);
        exit(1);
    }
}

int main()
{
    /** -----------------------------------
        Example 1:
        -----------------------------------
        Expression: (5+3) - 2
        Tree:
         -
        / \
        +  c=2
        / \
    a=5   b=3
    */

    // 1. Build the tree, node by node. 
    // The order in which nodes are created matters as the addresses of children
    // nodes is used by the constructor for operator nodes.
    Node a(OPERAND, 5);
    Node b(OPERAND, 3);
    Node c(OPERAND, 2);
    Node plus(OPERATOR, add, &a,&b);
    Node minus(OPERATOR, sub,&plus,&c);

    // 2. Evaluate the tree
    int result0 = minus.eval();

    printf("\nEvaluation of example 1: (5+3) - 2:\n");
    printf("--- Result: %d\n",result0);
    printf("--- Expected: 6\n");


    /** -----------------------------------
        Example 2: 
        -----------------------------------
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

    // 1. Build the tree, node by node. 
    // The order in which nodes are created matters as the addresses of children
    // nodes is used by the constructor for operator nodes.
    Node n6(OPERAND, 5);
    Node n5(OPERAND, 9);
    Node n4(OPERAND, 2);
    Node n3(OPERATOR, add,&n5,&n6);
    Node n2(OPERATOR, mul,&n3,&n4);
    Node n1(OPERAND, 3);
    Node n0(OPERATOR, add,&n1,&n2);

    // 2. Evaluate the tree
    int result1 = n0.eval();

    printf("\nEvaluation of example 2: 3 + ( (5+9) * 2 ):\n");
    printf("--- Result: %d\n",result1);
    printf("--- Expected: 31\n");

    printf("\n");
    return 0;
}