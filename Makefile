cf= -std=c++20
cc=g++
main=main.cpp
output=goffi

main:
	${cc} ${cf} ${main} -o ${output}
