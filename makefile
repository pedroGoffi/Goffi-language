cflags = -Wall -Wextra \
		 -Wswitch-enum \
		 -Wconversion -Wno-missing-braces \
		 -pedantic -fno-strict-aliasing \
		 -ggdb -std=c++20 -g
cc = g++
output = debug-app
input = main.cpp 
third = Lexer.cpp
third_h = Lexer.h
compile:
	${cc} ${input} ${cflags} -o ${output} 

