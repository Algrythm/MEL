# MEL Documentation



## \--Console Module--

The console module is the main module in MEL, granting access to many features of the terminal.



##### console::push(type: string\[String] OR type: variable);

Print a message into the terminal, flush the buffer, and create a newline.

##### console::write(type: string\[String] OR type: variable);

Print a message into the terminal.

##### console::command(type: string\[Command]);

Execute a terminal command.





## \--Variables Module--

The variables module gives the programmer the power to remove variables from the interpreter's varmap.



##### variables::remS(type: string\[Variable Name]);

Remove a string variable from the varmap.

##### variables::remI(type: string\[Variable Name]);

Remove an input variable from the varmap.

##### variables::remF(type: string\[Variable Name]);

Remove a float variable from the varmap.





## \--Filesys Module--

The filesys module gives the programmer the power to create, remove, read, and write to files.



##### filesys::create(type: string\[File Name]);

Create a file.

##### filesys::write(type: string\[File Name], type: string\[File Content] OR type: variable);

Write to a pre-existing file.

##### filesys::read(type: string\[File Name], type: variable);

Read file content into a variable.

##### filesys::remove(type: string\[File Name]);

Remove a file from the file system.







## Core features

##### Comments

Comments are done by starting a line with '#-'. Everything following the comment sign on the current line will be ignored by the interpreter.

##### \#import(type: string\[Imports Directory]);

Import your functions directory.

##### call(type: string\[Function Name]);

Call a function in your imported functions directory.

##### rcall(type: string\[Function Name], type: int\[Repeat Count]);

Repeat call a function in your imported functions directory a set amount of times, or ||inf||.

##### if(operand1 == operand2)

If the two operands are equal, execute the code between BEGINIF{ and }ENDIF.

##### ifn(operand1 == operand2)

If the two operands are NOT equal, execute the code between BEGINIF{ and }ENDIF.

##### terminate();

Terminate the interpretation.



## Variables



##### .i<variableName>;

Take user input from the terminal, and save it to the input varmap.

##### .s<variableName> = ("variableContent");

Save a string to the string varmap.

##### .f<variableName> = (123);

Save a float to the float varmap.

