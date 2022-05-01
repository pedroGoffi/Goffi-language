cf= -std=c++20
cc=g++
main=main.cpp
output=debug

main:
	${cc} ${cf} ${main} -o ${output}
