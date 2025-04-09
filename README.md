# Dictionary-Program
This program searches for the word entered by the user in its pre-set "dictionary" and offers suggestions as needed.

How to execute the Dictionary program

Files needed:
1. dictionary.cpp
2. Dictionary.txt

Execution:
1. All of the aforementioned files should be in the same folder
2. The folder where the files are should be your present working directory
3. On the Terminal, type and enter the command "g++ dictionary.cpp " to compile and create the executable a.out
4. Type and enter the command "a.out" to run the program

Using the running program:
1. The program prompts for a word to be entered to check against the list of words in the Dictionary.txt file
2. If the word you enter exists in Dictionary.txt, it returns True
3. If the word you enter is a slight misspelling of an existing word in Dictionary.txt, then it suggests the correct word and asks is that is what you meant. If yes, it returns true. If no, it returns false.
4. If the word you enter has no resemblance to any word in Dictionary.txt, it returns false.
5. If the word you enter is not in Dictionary.txt, but there are single-letter words in Dictionary.txt that are the first letter of the word you enter, then it asks if you want single-letter matches and returns them if yes.
6. Enter "exit" to quit the program.
