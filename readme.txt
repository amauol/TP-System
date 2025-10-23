Exercice 5.
It's important to initialize the buffer with '\0' termination characters to ensure there are no conflicts due to memory overwriting
or an inappropriate overlay for the compiler. This can be done using the bzero() function.

Exercice 6.
The free() function is used to “free” memory allocated during a previous dynamic allocation. 
Free “frees” (can be reused) just the memory space but does not totally delete the stored data, which is still accessible until a new 
new allocation. 

Exercice 12.
To test my mini_calloc function, we'll declare an integer array pointer and allocate memory for it using the mini_calloc function , then we'll fill this array with integers (with the square of each index here) and display the result to see if everything works.
To test whether free() works, we free(array) then repeat the display operation and we should have a segmentation fault since memory space has been freed.
To test the mini_free functiun, we use it on array to see if the statut of array have been changed correctly. 

Exercice 17.
When you use mini_printf on a string with the chracter '\n', mini_printf write the string without writing the line break. 
It's totally normal as we escribe mini_printf to work like that.
But, when you use mini_printf on a string without the character '\n' it doesn't print anything because in our functiun mini_printf we only write 
the message if we encounter the break line character or if our buffer is full.
With this supostions we can't check cases.

Exercice 18.
To solve the probleme hilitgh highilighted by the exercice 17, we create a functiun empty which writes the message ont the standard output 
if buffer is not nul and ind not null and not equal to BUF_SIZE. After that, we use mini_free (and not free because not use malloc to allocated space memory but mini_calloc)
then, we reinitialize the buffer to NULL and ind to 0, so we can use again mini_printf or empty.
In mini_exit, we call empyt and we exit to end the process.

Exercice 20.
If we declare a buffer with the size of 20 and if we write 20 caracthers, when we execute this, our shell let a command line empty and put a new one.
In the functiun mini_scanf, we the size in the read at size_buffers-1 to fix the problem and add properly the end carachter. 

Exercice 22.
For the security of our several programs, we have to be carrefully that our programs treat the case that the strins is NULL.
Moreover, in mini_strcopy  and mini_strcmp we need to take care of the length of each string.

Exercice 34.
If the program finish despite the buffer_write isn't full, then the datas wiil be in the buffer_write will be lost.
To avoid this problem, we need to run the loop to close each file which is NULL.


During the second class, I mainly crrect some errors inside of my mini_functiuns to make it more pleasent and useful.


I must prevent you that my mini_exit() provok a seg fault but I don't know why