# -b and --execpt-files

### Options to set files to exclude from deletion when deleting directories

<br>

## 1. Background

- Problem 1: Combination of 'find' and 'rm' commands  

 Sometimes you want to delete some files from a directory and only the rest. Users familiar with Unix/Linux systems can use a combination of the file/directory delete command rm and the find command. However, it is inconvenient to use a combination of two commands when removing multiple files. Examples include:  
    
 Suppose you have 1) a.txt 2) b.c 3) c.h 4) d.py files in the /find directory.
If you want to delete all files in the /find directory except for the a.txt and b.c files, you muse input "find . type f -and ! -name a.c and ! -name b.c | xargs rm -rvf".  

![find . -type f -and ! -name a.c -and ! -name b.c | xargs rm -rvf ](/imgs/1find_rm.png "find . -type f -and ! -name a.c -and ! -name b.c | xargs rm -rvf ")

 You have to input "-name [file] -and' repeatedly, and if you want to exclue many files, it is inconvenient to input and modify commands. In addition, there is a hassle that user has to check themselves because there is no procedure to check whether they have inputted correctly after inputting multiple deletion exclusion files.  
 If you don't use it for an additional few days, the command doesn't look neat enough to forget quickly, and the command is not intuitive enough to look like a command to find and delete 'a.c' and 'b.c.'  

- Problem 2: -i option

![rm -ri parent](/imgs/2rm_ri.png "rm -ri parent")

 The '-i' option continues to check whether the directory is entered and whether the file is deleted as shown in the picture above. In the above capture screen, n(no) was entered in the second question of removing '/parent/child1.c' to leave the 'child1.c' file.  
 It was not difficult to answer whether to delete or not because the number of directories and files is small for testing for now. However, if the number of directories and files to be deleted increases, the time and effort to leave a few files becomes laborious.  

- Conclusion

 In short, there is no easy command option to 'leave some files from a directory and delete only the rest'. As this feature is frequently used by anyone in a graphical user interface environment provided by the underlying computer OS, rather than in a command line, it is hoped that the feature can be easily used in the Unix/Linux terminal window.  

 Of course, there are ways to turn the 'find' and 'rm' commands into shell script file, but this causes some inconveniences.  
 First, the user must download the shell script file separately from our GitHub. That files can't be registered with the 'rm' command option in the default GNU library.  
 Second, the user must separately execute Shell Script to set the environment variable. If you do not register as an environment variable, you can use this feature only in the directory where the shell script file resides. Therefore, environmental variable registration is required to use the function of the shell script file at any location, such as the actual 'rm' command and option.

 So, this project will directly add an option that means there are files to be excluded from deletion when deleting directories" to GNU Untils 'rm.c' file. We want to provide an environment where many users can enjoy this function more simply and easily.

<br>

## 2. Expectation effectiveness

Commands that use a combination of existing 'rm' and 'find' had to enter the same option name several times to delete multiple files. it is very difficult to distinguish between incorrectly entered file names in the process of entering files, and inconvenience occurs when modifying commands. So in this project, users can save time by adding options that help them delete advanced by entering one option name and repeatedly entering only the file name and extension.  

If this command option is used, all files in the directory are deleted at once except for the files entered by the user, and the remaining files remain hierarchical, making it easy to understand the structure and purpose of the files.

Since this option is added to the existing rm command code, it is always available through an intuitive option name.

<br>

## 3. Option naming

| option type      | instruction                           |
| :----------: | ------------------------------ |
| Short option | rm -rb [directory name]               |
| Long option  | rm -r [directory name] --except-files |

- Short option

 Short option is a combination of the existing repeat deletion '-r' option and the new deletion '-b' option, such as '-ri', which uses the repeat deletion option '-r' and the confirmation of deletion option '-i'. In other words, the option we will actually implement is '-b', which means "but". The name was inspired by "recursively remove but 'some files'".

- Long option

 Long option '--exception-files' is similarly used with the existing '-r' option, which is repeatedly deleted. It is an option with a more intuitive name than a short option. Meaning that there are files to be excluded when deleting the entered directory.

<br>

## 4. Developer Guide
1. Install the essential tools in the README-prereq
https://github.com/coreutils/coreutils/blob/master/README-prereq

2. Proceed as directed in the README-hacking
https://github.com/coreutils/coreutils/blob/master/README-hacking

3. Replace the 3 modified files  
 [Reference](https://github.com/YejinHwang-D/rm-execpt-files/tree/main/coreutils_rm/src)  
remove.h  
remove.c  
rm.c  

4. Test after compilation

Recompile with changes
```
cd ~/coreutils
make
```
command option test
```
~/coreutils/rm -rb [Directory Name]
~/coreutils/rm -r --except-files [Directory Name]
```

## 5. User's Guide

1??????  Update the GNU operating system version to use the rm command option with the new option added.

2??????  Enter the "rm -rb [directory name]" or "rm [directory name] --execpt-files" option in your terminal.

3??????  When the 'What files do you want to exclude from deletion?' prompt is displayed, enter the file that you want to be excluded from deletion. **For file input methods, refer to 5. File input methods.**

4??????  If there are no more files to exclude, enter '!no' to escape from the delete exclusion file entry repetition.

5??????  After the deletion is in progress, move to the directory where you want to delete the file and check the remaining files. For this, **See 6. Processing of remaining files after deletion.**

<br>

## 6. How to input files

![????????? ???????????? ?????? ?????? ???????????????](/imgs/3prototype.png "????????? ???????????? ?????? ?????? ???????????????")

 The attached capture screen is an input example for describing a detailed function, and is a file input-related prototype to be excluded from deletion. In the above prototype, the Current Working Directory (CWD) is 'home/kmi0817/opensource', and the path to the subdirectory is 'home/kmi0817/opensource/parent'.

 The prompt repeats the question of whether there are files to be excluded from deletion until the user enters a particular phrase. In other words, if there are no more files to enter, the user enters ***"!no"*** or ***"exit"*** to exit the question loop, and at the same time, directory deletion proceeds. When entering a file at the prompt, enter it as a relative path by default. At this time, like any terminal function, pressing **tab automatically completes the directory name and file name.**

### I. If you enter a file on the Current Working Directory

 There is no need to enter a path name. If you enter only the file name and extension, it is considered to exist in the same location as the current directory. In the above prototype capture screen, the first and second input lines correspond to this.

### II.	If you enter a file on the Sub Directory

 Enter the path name, but enter the subdirectory name first. In the above capture screen, it is the input for this situation from the third input. '/parent/child.c' was entered to exclude the file 'child1.c' on parent, which is the subdirectory of CWD, from deletion.

### III. If you enter a subdirectory name incorrectly

 If Shell fails to find a directory with the entered name, it will print "Please, check it again" with the phrase "Cannot find [input directory] directory]" and the user will have to reenter the correct directory name and file name.

### IV.	If you enter the wrong file name

 If Shell fails to find a file with the entered name, print "Please, check it again" with the phrase "Cannot find [input file]") and re-enter it. The input method is the same as the existing input method, and the user re-enters the file.

<br>

## 7. Processing remaining files, after deletion.

After deletion, you can see that the remaining files in the top directory where the internal deletion has been performed remain in the original path. Among other objects (files, directories) inside, only the files to be excluded remain and are deleted. Therefore, the files can maintain the original hierarchical structure, and the user can conveniently check them even after deletion.
