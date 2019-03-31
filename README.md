# demeter
## Nutrition Tracker - Portfolio project for CS 201
Welcome, nutrient-starved vagabonds! Your search for a nutrition tracker ends here. Demeter is a program that allows users to create, update, delete, and display their food consumption using the USDA food item database. This is my submission for the CS 201 portfolio project at The University of Alabama.  

## Prerequisites 
Please ensure you have the following tools installed on your system before attempting to run this project: 
- Ubuntu (on Windows machines this can be installed from the Microsoft store). 
- ANSI C11 - The program is written in C, so it'd be helpful to have it installed!
- wget (should already be installed on Ubuntu). 

## Installing
You can clone this repo by typing: 
```
git clone https://github.com/thebrandonlucas/demeter.git
```
Once downloaded, type the following command to build and run the project: 
```
make build
```
If that worked, great! Skip ahead to the next section. If not, continue reading below. 
If for some reason the above fails, you can download the database file here: https://ndb.nal.usda.gov/ndb/
Click on "Downloads", then BFPD ASCII Files. Move the data files to the demeter directory and type: 
```
bash build.sh
```
You can then just type
```
make
./demeter
```
And the project should run. 

## Tutorial
The Demeter tutorial video can be viewed here: https://www.youtube.com/watch?v=4QPjLcLdENs&list=UULdlyhzQAQaZgfIkKui8fJQ

## File System
Users create new files, and sign in later with their usernames. The username matches the filename, which has a .log extension. 

## Code Structure
There are five .c files and four .h files: 
- demeter.c: The main program
- diary.c: All functions that handle the user diary log
- product.c: All functions that handle operations on the database AVL tree
- auxiliary.c: Helper functions for menus and running the main program
- menu.c: Printing functions which display menus, prompts, and error messages

The .h files are heavily commented and can be helpful for understanding what each function's function (hehe) is. 

## Precautions
Do not mess with the .log file that the program creates. If you delete it, your food diary is gone (duh!), and if you tamper with the file contents, the program may behave unexpectedly. 

## Algorithm and Data Structures Justification
### AVL tree
I chose the AVL tree data structure to represent the nutrition database for a few of reasons: it is a self-balancing tree with O(log N) height and therefore all operations cost O(log N) to execute, it has simpler rules and is easier to implement than a red-black tree, and is more rigidly balanced than a red-black tree, keeping operations at a stricter O(log N) runtime. The tree can also be structured alphabetically for an easy item-name based search. 

### Longest Common Subsequence
I used the LCS algorithm to implement search for the user diary. This is generally much better than the bst structure at returning results similar to the search query, as the bst relies on an alphabetical match, where LCS relies on the number of shared characters. 
