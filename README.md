# GLang
Its like Porth but in C++ with my bad data Structure knowledge
and some diferences in the syntax


### Aritmetric operators

Usage == Mathematicall equivalent == result
- `=` - 1 2 = == (1 == 2)   == 3
- `+` - 1 2 + == 1 + 2      == 3
- `-` - 2 1 - == 2 - 1      == 1
- `*` - 2 2 * == 2 * 2      == 4
- `/` - 8 2 / == 8 / 2      == 3
- `<` - 8 2 < == 8 < 2      == FALSE: 0
- `>` - 8 2 > == 8 > 2      == TRUE: 1

### Memory usage

- `mem` - push the address of the begining of the memory where you can READ and
  WRITE onto the stack.
-`store` - Will store in the buffer the next value of bytes, ex: store8
-`load` -  Will load the last value of bytes, ex: load8

### Flow Control
Dump will print in the screen the last digit in the stack and consume it
-`dump`
Dup will duplicate the last digit in the stack
-`dup` -    
exit(exit code) will exit the program with exit code in the arg
-`exit` -   
 Sugar syntax to crossreference in the Lexing stage
-`if` -    
Will perm a loop wile expression is true
-`while` -  
Points to the next element to jump
-`do` -
use between if and else
-`elif` -
use after elif or if
-`else` -
use after blocks
-`end`- 
