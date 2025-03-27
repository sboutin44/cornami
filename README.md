# Cornami 

## Compiler Intern Exercise
This repository contains my answer to the following exercise:

A Tree represents an object with left and right nodes, as well as an integer value and a kind enumeration saying if it is an operator or operand. The tree represents an expression of the form (a+b) - c, and can be represented like this:
```
     -
    / \
   +  c
  / \
 a   b
```
where a,b and c are integers, - and + are the operators.

The exercise consists in implementing the function that evaluates the tree and returns the computation (a+b) - c: 
```
int eval(Tree* obj);
```

## Solution
The solution to the exercise is in eval.cpp:
```
├── README.md
└── eval.cpp
```

In the code, we create the following trees:

Example 1:
```
         -
        / \
       +  c=2
      / \
   a=5   b=3
```
representing the expression (5+3) - 2.

Example 2:
```
         +               n0 (names given these nodes in the code)
        / \
       3   *             n1 n2
          / \
         +   2           n3 n4
        / \ 
       5   9             n5 n6
```
representing 3 + ( (5+9) * 2 ).

Please build and run the code to see the evaluation.

## Build
```g++ eval.cpp -o eval```

## Run it
```./eval```

