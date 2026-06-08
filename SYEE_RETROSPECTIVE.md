# Minishell retrospective by _syee_:

## Intro :
Minishell is a project that requires us to remake the shell from scratch.

To quote the README of our project : 

	"The goal of this project is to understand how a shell works internally.It reads user input, separates the input into tokens, parses the command structure, handles quotes, expands environment variables, processes redirections and pipes, then executes the command.

	This project also teaches important system programming concepts such as process creation, file descriptors, signals, environment variables, and exit status handling.

	Minishell does not aim to fully recreate Bash.
	It only implements the required features from the 42 Minishell subject. "
Before starting the project i had to familiarize myself with what is a shell, what is bash and kernel as i kept using them interchangably.

The resource that helped me understand it was this youtube video :

- https://www.youtube.com/watch?v=hMSByvFHOro&
It breaks down the difference of terminals, bash, and command line

## Planning 

From the subject pdf it gave a small guideline on what to implement :
1. handle signals like ctrl-c, ctrl-\ and ctrl-d
2. handle 7 built ins : cd, echo , env, exit, export , pwd and unset
3. handle redirections : < , << , > , >>

But that wasn't sufficient to us where to actually start. Therefore thorugh evaluations done within campus as well as asking around that we find out there are two parts to. minishell : the **parser** and the **executionr**. 

The parser's job was to accept user inputs, split them into tokens (tokenizing), apply meanings to them (lexing), store them into a struct then pass it on to the executioner. Whereas the execution takes whaetver that's been parsed and run it, upon completion, return parser to continuously accpet user input until an exit signal is transmitted. 
	
Even with that much information it still was blurry on where to start, the command structures to use and the details. It was only after we started coding the thing that we knew what to add.

In the middle of development, we were able to break it down to :

	Parser :
	- tokenizing
	- lexing
	- heredoc
		+ expansion for heredoc
	- expansion 
	- history 
	- readline
	- signals
		- ctrl-\ (core dump) , ctrl-d (EOF), ctrl-c (sigint)

--- 

	Execution :
	- built-ins
		- (cd, echo , env, exit, export , pwd and unset)
	- binary
	- pipes
	- redirections 
		- (<, << , > , >>)

My teammates was the one that took up signals despite it being mainly the execution's job so he pulled lots of weight on this.

To breakdown on the overall flow it goes like this :
1. read user input with `readline` (parser)
2. Tokenise the input (parser)
3. Parse tokens into command structures (parser)
4. Process heredoc if needed (parser)
5. Expand variables (parser)
6. Handle redirections and pipes (execution)
7. Execute built-ins or external commands (execution)
8. Update the exit status (execution)
9. Free allocated memory before reading the next input (execution & parser)

Upon finishing the project for each parts, the tough parts of each roles are pipes for execution, expansion for parser.
	
## Project timeline
My teammate and i had planned to start this project way back in december 2025 and we completed it in june 2026. He actively developed throughout whereas i did it all at once around the month before submission. For me the time breakdown was : 

Week 1 : evaluate chiang and tristan's minishell to grasp the general concept behind it.

Week 2 (during cny) : planning and trying to understand what needs to be done by prompting chatgpt, looking up resources and just starting with pseudocode for built-ins. Plan the data struct / ast struct as we didn't really know how to build the chain of commands. 

Week 3 (after a long break, sem ended) : start on restarting with finishing and testing built-in funcitons. At this point, i finally figured out that the parser will be giving me an char** to run, whatever i do with it is up to me. 

Week 4 : Do binary, alot of struggle in figuring out where should i start to fork and where do i return the exit code. During which my teammate suggested to use linked list for the data structs. It took roughly 4 days to complete this though quite half assed and the rest of the time i moved on to figuring things out in week 5. 

Week 5 : Figure out the logic behind redirections and how to combine everything together, the built-ins, the binary, the piping. This was the messiest as i did not know which to come first. What i end up doing was create multiple high level overview of how data should flow, then create pseudocode and feeding it to chatgpt, by figuring out what determines how the program executes. I was able to breakdown how does redirections work and had a somewhat working prototype. 

Week 6: Through a discussion or more like a lecture from chiang and dylan, i was able to tackle the multiple pipes issue. This wasn't something i think i could have thought of myself, especially since i was in a rushing and panic mode which made me just throw whatever doubts i had to AI and hoped it solved it for me. But figuring out pipes was the finishing piece to the puzzle, it made it possible to connect all the funcitons together because it was the last hurdle to jump.

Week 7: thanks to my teammate's implementation of signals and his explanation, i was able to just plug it into my code. Finishing touches to complete the exit() buitl-in, heredoc handling, signal handling and norminate checking was done during this week. 

Week 8 : Submssion. It wasn't smooth sailing, i encountered major errors for 3 main things : 
	- redirections only caused the shell to exit instatly ; the fix was to restore the fd, as closing the fd sends an EOF signal(same with ctrl-D) that closes the shell
	- pwd if more than 1 arguments exist it should return error, my code even shows it, but it wasn't working as expeceted; there were 3 iterations : if (!(*(str++)) to (*(str++)) to (*(++str)). 
	- export did not replace existing values ; just coded the check and replacing which fixed the issue. 
	
And with that, minishell is finally done. a total working period of 7 weeks and a few days (week 8 wasn't exactly a full week)  

## Functions learnt
There were many allowed functions by the subject pdf, i have this habit of doing a through research on the funcitons before starting but it wasn't as effective as it would be more viable to research as you go. 

## Git commands used
This was the first project development where there were two people involved. So new concepts like branching, merging rebase was thrown to us when we wanted to commit, there were conficts to be reoslved. But here were some scenarios and commands that helped with it.

	1. 
	2. 
	3. 
	
## Misremembering simple concepts
There were questions like : 
	when should i be passing pointers? 
	when should i be passing addresses? 
	if i pass in this value will it modify its actual value or just its pointer?
	Is freeing this even a valid code ?
That i asked myself throughout the development, it really made me reflect on how reliant i am on AI to fix my issue when i was unsure of something. So this small section will be just to  clarify my common mistakes and engrane them to my memory. 


## Reflection 
I'm good at listening to people's explanaiton on code and get amazed when they can answer very detailed things. But realized that i can't replicate that as well. 
	- 



