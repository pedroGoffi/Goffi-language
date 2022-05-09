cf= -std=c++20 -Wall -Wextra -pedantic
cc=g++
main=main.cpp
output=goffi

main:
	${cc} ${cf} ${main} -o ${output}
