## ToyLang - the new big thing ##

ToyLang is a simple compiled programming language developed for the lulz

## Syntax ##

1. Function definition
   ```
   TYPE name(ARGS) { CODE }
   ```
   Example:
   ```
   int test()
   {
    ...
   }
   ```

2. Return statements
    ```
    return EXPRESSION
    ```
    Example:
    ```
    return 2 + 5
    ```
3. Types
    - int : 64 bit integer
    - double : double (obviously)


## Roadmap ##
- more types like chars, arrays and pointers
- loops
- make compiler to output native executable instead of IR bitcode
