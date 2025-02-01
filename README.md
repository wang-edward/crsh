# crsh

crsh is unix shell that disinventicizes making mistakes.
- when a program returns a non-zero error code, the computer will shut down.

## Usage
```bash
make
./crsh

# examples
root@crsh $ ls
root@crsh $ ./bin/print
root@crsh $ ./bin/fizzbuzz
root@crsh $ ./bin/factorial
root@crsh $ cat notafile # what happens?????
```
