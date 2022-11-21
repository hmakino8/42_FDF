# push_swap
https://user-images.githubusercontent.com/95123726/203006838-c238f67b-88b9-48f6-ad06-878de0f879a8.mp4
### ・Program name
`push_swap`, `checker`
### ・Turn in files
`*.c`, `*.h`, `Makefile`
### ・Usage
・Compile with make command, set arguments, and execute push_swap.
```sh
make; ./push_swap 3 1 2 4 0 -1
```
・To start the visualizer, clean the file once and make with the "v" option.
```sh
make fclean; make v; ./push_swap 3 1 2 4 0 -1
```
・To make sure it's sorted correctly, use a checker.
```sh
make fclean; make; make bonus; ./push_swap 3 1 2 4 0 -1 | ./checker 3 1 2 4 0 -1
```
### ・Description
Sort data on a stack, with a limited set of instructions, using
the lowest possible number of actions.
In this task, use the following commands to sort numbers while exchanging numbers using two stack areas.
### ・Commands
|||
-|-
[`sa (swap a)`]()|Swap the first 2 elements at the top of stack a.<br>Do nothing if there is only one or no elements.
[`sb (swap b)`]()|Swap the first 2 elements at the top of stack b.<br>Do nothing if there is only one or no elements.
[`ss`]()|sa and sb at the same time.
[`pa (push a)`]()|Take the first element at the top of b and put it at the top of a.<br>Do nothing if b is empty.
[`pb (push b)`]()|Take the first element at the top of a and put it at the top of b.<br>Do nothing if a is empty.
[`ra (rotate a)`]()|Shift up all elements of stack a by 1.<br>The first element becomes the last one.
[`rb (rotate b)`]()|Shift up all elements of stack b by 1.<br>The first element becomes the last one.
[`rr`]()|ra and rb at the same time.
[`rra (reverse rotate a)`]()|Shift down all elements of stack a by 1.<br>The last element becomes the first one.
[`rrb (reverse rotate b)`]()|Shift down all elements of stack b by 1.<br>The last element becomes the first one.
[`rrr`]()|rra and rrb at the same time.
### ・Result
Number of commands in 10000 test cases with
#### 100 arguments
  　`max: 684`  `avg: 629`  `min: 550`
#### 500 arguments
  　`max: 4881` `avg: 4722` `min: 4552`
