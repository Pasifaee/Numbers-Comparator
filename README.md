# Numbers-Comparator
This program allows you to compare lines of words and numbers in multiple formats.

**How it works:**  
This program reads lines of:
- words,
- integer numbers in decimal, hexadecimal and octal base,
- floating point numbers in decimal format,
and returns numbers of lines that contain the same sets of words and numbers.
Numbers with the same value but in different formats are interpreted as the same numbers.

A line that starts with '#' is interpreted as a comment and is ignored.
A line that includes a non-ASCII character is isgnored.

*Example input: (numbers at the beginning are only line numbers, not actual input)*  
 
`1` `9 abc`  
`2` `abc 0x09`  
`3` `011 ABC`  
`4` `.9e1 aBc`  
`5` `ABc 09`  
`6` `# To jest komentarz.`  
`7` `żółć`  
`8`  
`9` `9 9 abc`  
`10` `9 abc abc`  
`11` `9 abc ĘĄ`  
`12` `9223372036854775807`  
`13` `0x7fffffffffffffff`  
`14` `0777777777777777777777`  
`15` `-9223372036854775808`  
`16` `9223372036854775808`  
`17` `0x8000000000000000`  
`18` `01000000000000000000000`  
`19` `-1`  
`20` `18446744073709551615`  
`21` `0xffffffffffffffff`  
`22` `01777777777777777777777`  
`23` `-9000000000000000000`  
`24` `-9e18`  
`25` `18e18`  
`26` `18000000000000000000`  

*Output:*  
`1 2 3 4 5`  
`9`  
`10`  
`12 13 14`  
`15`  
`16 17 18`  
`19`  
`20 21 22`  
`23 24`  
`25 26`  

**How to compile the program:**  
You can compile the program by writing 'make' in the linux terminal and pressing enter. Make sure that the 'makefile' file is in the same folder as the rest of the files.

**About test.sh:**  
Program test.sh enables you to test the program for correct output and memory problems.
It takes two arguments: first - name of the executable file you want to test (in this case 'similar_lines'); second - name of the folder with test files.

Each test in the folder should consist of two files with the same name and two different extensions: '.in' and '.out'.
The '.in' file should include input and the '.out' file should include the expected output of the program that processed input from the '.in' file.  

Memory problems are detected using *valgrind*.
