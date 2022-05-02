from os import (
    system,
    path,
    listdir
)
from contextlib import suppress

def compile(code):
    cc = "g++"
    cf = "-std=c++20 -Wall"
    with suppress(Exception):
        if system(f"{cc} {cf} {f}/{code} -o ./bin/{code.replace('cpp','bin')}") == 256:
            print(f"[ ERROR ]")
            exit(1)
    print(f"[ SUCESS ]")

print("Starting test process")
for filename in listdir("."):
    f = path.join(".", filename)
    if f in "./code" and path.isdir(f):
        for codeCpp in listdir(f):
            print(f"Compiling {f}/{codeCpp}     || STATUS = ", end="")
            compile(codeCpp)

