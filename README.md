# Leaks Locater

## Description

in short this program logs every `malloc` you called and backtrace it calls and print the 
output of `leaks` tool and compare the both outputs and search for the address `leaks` returns
and the prints all the information in the log file about this allocation

## Features

- You can identify where your program leaks more easily

## Screenshots
![png](https://raw.githubusercontent.com/jrayoub/leaks-finder/main/Screens/screen_01.png)


## How to use
- copy source file to your project directory 

- include the header file :
    ```c
    # include "./leaks_locater/includes/Allocater.h"

- add system call to end of your main :
    ```c
    int main()
    {
        //your code here

        system("leaks NAME_OF_YOUR_PROGRAM");
        return (0);
    }

- add my_malloc.c file to your compilation 
  ```bash
    gcc *.c leaks_locater/my_malloc.c

-- run your program through the script
   ```bash
    ./leaks_locater/script.sh "./NAME_OF_YOUR_PROGRAM ARGUMENTS"