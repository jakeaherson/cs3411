SimpleSH

by Jake Herson

SimpleSH is a simple implementation of a shell in C. 
In demonstarates tha basics of how a shell works. 
That is: read, parse, fork, exec, and wait.

It has many limitations, including:

	Commands must be on a single line.
	Arguments must be separated by whitespace.
	No quoting arguments or escaping whitespace.
	Only builtins are: cd, >, <, |, help, exit.