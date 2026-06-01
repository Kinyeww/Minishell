
## Kinyew : 
1. tokenise
2. store in AST	(so executing part understand what to run first)
3. execute

ky - organised dir, did makefile, created simple struct for parsing

todo - complete parsing, then tokenise and store in AST
cd
ls -l

typical minishell flow:

1. store readline
2. tokenise (finished on 12/2) (error, prints garbage while reading spaces)
3. parse ->doing this now (scan for text and assign value)
4. expand
5. execute
6. free everything


## syee : 
1. store env
    - [ ] as linked list
    - [ ] as array
    - [ ] 
2. Signals 
    - die 

2. traverse cmd
    - [ ] store ast nodes as ..
    - 
1. built ins
    - [ ] echo
        - [ ] n 
    - [ ] cd
        - [ ] relative path : location relative to current folder
        - [ ] absolute path : full location starting from the root directory /homw/root/john
    - [ ] pwd
    - [ ] export
    - [ ] unset 
    - [ ] env
    - [ ] exit
        - [ ] update exit codes
        - [ ] free the stuff

2. binary
    - [ ] locate where binary is , run
    - [ ] create child processes
    - [ ] manage fd

3. redirections
    - [ ] << (Heredoc) handles by kinyew
    - [ ] < (redir in / input) : wc -l < file.txt // takes input for command instead of keyboard
    - [ ] >> (append) : echo "hello" >> file.txt
    - [ ] > (redir out / replace ) : echo "hello" > file.txt
4. pipes
    - [ ] | 
	
5. exit codes ($?)
https://www.redhat.com/en/blog/exit-codes-demystified

### code planning
1. 
2. 

### imporatnt resources / references
(https://docs.google.com/document/d/1mBKItC0TWcLdb45fbZGwoYGZ4lUKIsWU6lQXuWHUTfU/edit?tab=t.0#heading=h.9rnyqtjoft6r)  
This link breaksdown :
- a senior notes on handling minishell

(https://stackoverflow.com/questions/52666511/create-an-ast-from-bash-in-c)  
This link breaksdown :
- AST 

(https://portfolio.beddinao.me/projects/mini-shell)  
This link breaksdown :
- external funciton sused within minishell
- explainations on redirections, binaries, built-ins
- overall guide for minishell 

execve :
(https://www.youtube.com/watch?v=Wtd-8OiZOjk)

exit codes :


pipe() and fork():
https://www.geeksforgeeks.org/c/c-program-demonstrate-fork-and-pipe/

## misc
- manipulate envp ?
- 

1. under main :
/*
- envp has to be copied because the original envp is pointing to the address but if we want to add stuff to it its impossible 
1. count envp
2. the envp list inside the data should be initialized with amt * sizeof(t_env *), so that can go to each t_env and set the key and value 
3. find the delimited "=" then strdup the KEY then strdup the value 
4. 
*/

case :
- whehn x|x|x , then usleep then quit, rmb to free child 