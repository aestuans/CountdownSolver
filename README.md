# CountdownSolver

This is tiny program for solving the numbers game from the British TV program [Cowntown](https://en.wikipedia.org/wiki/Countdown_(game_show)), 
in which contestants are presented with 6 numbers and a randomly generated target number, and 
try to construct the target using the 6 numbers and the operations addition, subtraction, multiplication, and division. 

This simply brute-forces all possible expressions to find the solution. To avoid problems with operation orders, it creates all possible 
postfix expressions of input numbers, and evaluates them.

### Usage
```
countdown <number_of_numbers(n)> <n_1> <n_2> ... <n_n> <target>
```

Example:

![](http://wiki.apterous.org/images/0/0f/Rsz_george_solution.jpg)

```
countdown 6 50 75 100 25 2 1 940
```

output:
```
25 * 50 = 1250
2 + 1250 = 1252
75 * 1252 = 93900
93900 / 100 = 939
939 + 1 = 940
```
