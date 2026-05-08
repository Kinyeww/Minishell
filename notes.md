
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
1. built ins
    - [ ] echo
        - [ ] n 
    - [ ] cd
        - [ ] relative path
        - [ ] absolute path
    - [ ] pwd
    - [ ] export
    - [ ] unset 
    - [ ] env
    - [ ] exit
2. binary
    - [ ] locate where binary is , run
    - [ ] create child processes
    - [ ] manage fd
3. redirections
    - [ ] << (Heredoc)
    - [ ] < (redir in / input) : wc -l < file.txt // takes input for command instead of keyboard
    - [ ] >> (append) : echo "hello" >> file.txt
    - [ ] > (redir out / replace ) : echo "hello" > file.txt
4. pipes
    - [ ] | 
5. exit codes ($?)

### code planning
1. write builtins
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

## misc
- heredoc is under parser ?