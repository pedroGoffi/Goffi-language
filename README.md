# Goffi-SLang
Goffi-SLang is a [stack oriented language](https://en.wikipedia.org/wiki/Stack-oriented_programming) inspired in [Porth](https://gitlab.com/tsoding/porth) writed in C++
that can be compiled or simulated.

## Summary
* [Simple math](#Aritmetric-Operators)
* [Built-in Procedures](#Build-in-Procedures)
* [Flow Control](#Flow-Control)
* [Macros](#Macro-definition)

## <div id="Aritmetric-Operators">Aritmetric-Operators</div>	
    result of any operation will be pushed automatically ot the top of the stack
	In comparasions `<` or `>` will push 1 if true and 0 if false.

`=`	EQUALS operand, Usage: `1 1 =` is equivalent to (1 == 1)

`+`	PLUS operand. Usage:  `2 1 +` is equivalent to (2+1) 

`-`	MINUS operand, Usage: `2 1 -` is equivalent to (2-1) 

`<`	LESS THAN operand, Usage:  `2 1 <` is equivalent to (2<1) 

`>`	GREATER THAN operand, Usage:  `2 1 >` is equivalent to (2>1) 

`*`	MULTIPLY operand, example: `2 1 *` is equivalent to (2*1)




# <div id="Build-in-Procedures">Build-in Procedures </div>
	NOTE 	This will be launched to std.goffi 
    		when i implement procedures
`dump` print the last digit in the stack

`dup` duplicate the last element in the stack

# <div id="Flow-Control">Flow Control</div>



`if` if->expression->do-block will goto next do-block or jump the whole do-block.
    if 1 do 
	69 dump 
    end

`do` Always close end blocks this will perfome instructions jumps in some scenarios.
    do 1 dump end

`while` while->expr->do-block if expr is false will jump the do-block, otherwise will evaluate the do-block.
    0 while dup 10 < do
	dup dump
	1 +
    end


# <div id="Macro-definition">Macros</div>

`define`  is used to created a macro, that will be expanded when used 

Usage:
First define the macro:
    `define` (macro-name) `as` (macro-body) `end`
Then call the macro:
    (macro-name)

Example in examples, kinda obvious.





















