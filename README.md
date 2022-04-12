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

 After deletion, the remaining files that are excluded from deletion are moved to a separate directory, and the user can see the original purpose of the file by viewing the log file (pathLog.txt) that can determine the original path of the remaining files.  

 This option is added to the existing 'rm' command code and is always available through an intuitive option name.  

<br>

## 3. 옵션 작명

| 옵션 타입      | 사용법                           |
| :----------: | ------------------------------ |
| Short option | rm -rb [디렉토리명]               |
| Long option  | rm -r [디렉토리명] --except-files |

- Short option

Short option은 반복(재귀) 삭제 옵션인 -r과 삭제 여부 확인 옵션인 -i를 함께 사용하는 「-ri」 처럼, 기존의 반복 삭제 -r 옵션과 새로운 삭제에서 제외하는 -b 옵션을 합친 것이다. 즉, 본 프로젝트에서 실제로 구현할 옵션은 -b로, 영어 but을 의미한다. ”일부 파일을 제외하곤 모두 삭제하라 (recursively remove but ‘some files’)”는 문장에서 영감을 받은 이름이다.

- Long option

Long option인 --except-files 또한 반복적으로 삭제하는 기존 -r 옵션과 함께 사용된다. Short option보다 더욱 직관적인 이름의 옵션으로, 입력한 디렉터리를 삭제하되 제외할 파일이 있다는 의미이다.

<br>

## 4. 사용자 가이드

1️⃣  새 옵션이 추가된 rm 명령어 옵션을 사용하기 위해 GNU 운영체제 버전을 업데이트한다.

2️⃣  터미널 창에 rm -rb [디렉터리명] 혹은 rm [디렉터리명] --execpt-files 옵션을 입력한다.

3️⃣  ‘What files do you want to exclude from deletion?’ 프롬프트가 출력되되면 삭제에서 제외되길 원하는 파일을 입력한다. **파일 입력 방법은 5. 파일 입력 방법을 참고한다.**

4️⃣  더 이상 제외할 파일이 없을 경우 ‘!no’를 입력해 삭제 제외 파일 입력 반복문에서 탈출한다.

5️⃣  삭제가 진행된 이후, 새로 생성된 ‘remain’ 디렉터리로 이동해 잔여 파일을 확인하고, 로그 파일(pathLog.txt)을 통해 원래 경로를 확인할 수 있다. **이는 6. 삭제 이후 잔여 파일 처리를 참고한다.**

<br>

## 5. 파일 입력 방법

![터미널 창에서의 입력 관련 프로토타입](/imgs/3prototype.png "터미널 창에서의 입력 관련 프로토타입")

첨부된 캡처 화면은 세부 기능을 설명하기 위한 입력 예시로, 삭제에서 제외할 파일 입력 관련 프로토타입이다. 위 프로토타입에서 Current Working Directory (CWD)는 ‘home/ kmi0817/opensource’이며, Sub Directory의 경로는 ‘home/kmi0817/opensource/parent’ 이다.

사용자가 특정 문구를 입력하기 전까지 프롬프트는 삭제에서 제외할 파일이 있냐는 질문을 반복한다. 즉, 사용자는 더 이상 입력할 파일이 없으면 ***“!no”*** 를 입력하여 질문 루프에서 빠져나오며, 이와 동시에 디렉터리 삭제가 진행된다. 프롬프트에서 파일 입력 시 기본적으로 상대경로로 입력한다. 이때 여느 터미널 기능처럼 **tab을 누르면 디렉토리명과 파일명이 자동으로 완성된다.**

### I. Current Working Directory 상의 파일을 입력하는 경우

경로명을 입력할 필요가 없다. 파일명과 확장자만 입력하면, 현재 디렉터리와 같은 위치에 존재한다고 간주한다. 위 프로토타입 캡처 화면에서는 첫 번째와 두 번째 입력 줄이 이에 해당한다.

### II.	Sub Directory 상의 파일을 입력하는 경우

경로명을 입력하되 서브 디렉터리 이름부터 입력하면 된다. 위 캡처 화면에서는 3번째 입력부터 이 상황에 대한 입력이다. CWD의 sub directory인 parent 상의 child1.c 파일을 삭제에서 제외하기 위해 /parent/child.c를 입력한 것이다.

### III. Sub Directory 이름을 잘못 입력하는 경우

Shell이 입력받은 이름의 디렉터리를 찾는 데 실패한다면, 해당 디렉터리를 찾을 수 없다는 문구(Cannot find [입력 디렉터리 이름] directory)와 함께 다시 한번 입력(Please, check it again)을 받는다. 다시 입력할 때 사용자는 처음에 입력했듯이 디렉터리 이름뿐만 아니라, 파일 이름도 적어야 한다.

### IV.	파일 이름을 잘못 입력하는 경우

Shell이 입력받은 이름의 파일을 찾는 데 실패한다면, 해당 파일을 찾을 수 없다는 문구(Cannot find [입력 파일 이름] file)와 함께 다시 한번 입력(Please, check it again)을 받는다. 입력 방식은 기존 입력 방법과 똑같다. 현재 디렉터리와 동일선상의 파일은 ‘파일명.확장자’, 서브 디렉터리 내 파일은 ‘/서브디렉터리/파일명.확장자’로 입력해야 한다.

<br>

## 6. 삭제 이후 잔여 파일 처리

![remain 디렉터리 내 pathLog.txt 예시](/imgs/4pathLog.png "remain 디렉터리 내 pathLog.txt 예시")

-b 혹은 --except-files 옵션으로 디렉터리리가 삭제되고 남은 파일은  「remain」라는 별도의 디렉터리에 저장된다. 이 디렉터리는 삭제한 디렉터리와 동일한 경로에서 자동 생성된다. 삭제에서 제외된 파일들은 기존 상하위 경로를 구분하지 않은 채 remain 디렉터리에 임시 저장되기 때문에 파일의 구조가 뒤섞여 구분하기 어려운 단점이 있다.

![삭제 이후 처리 그림 요약 ](/imgs/5remain.png "삭제 이후 처리 그림 요약 ")

이 문제를 해결하기 위해 remain 디렉터리 내부에 「pathLog.txt」라는 로그 파일도 함께 생성한다. 해당 로그 파일에는 복사된 파일들의 기존 경로를 텍스트로 가시화되어 있어, 어떤 하위 디렉터리 안에 있던 파일인지 확인할 수 있도록 한다.
