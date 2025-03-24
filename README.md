# Cornami 

## Compiler Intern Exercice
This repository contains my answer to the following exercice:
```
A Tree represents an object with left and right node as well as a integer value and a kind enumeration saying if its an operator or operand. A tree representing the expression (a+b) - c would be represented like this:
         -
        / \
       +  c
      / \
     a   b

The exerice is to implement the function: 
int eval(Tree* obj);
returning the evaluated 
(a + b) - c
```

## Solution
The solution to the exercise is in eval.cpp:
```
├── README.md
└── eval.cpp
```

## Build
```g++ eval.cpp -o eval```

## Run it
```./eval```

