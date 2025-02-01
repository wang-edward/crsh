# crsh

crsh is unix shell that disinventicizes making mistakes.
- when a program returns a non-zero error code, the computer will shut down.

## Usage
```bash
make
sudo ./crsh

# examples
root@crsh $ ls
root@crsh $ ./bin/fizzbuzz
root@crsh $ ./bin/factorial
root@crsh $ vi THIS_IS_COOL.txt
root@crsh $ cat notafile # what happens?????
```
