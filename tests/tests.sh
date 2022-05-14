#!/bin/bash

function check()
{
  opt="$*"
  if [[ -n "$str" ]]; then
    printf "please give an argument to the function.";
    exit;
  else
    diff=$(diff <( find ${opt} 2>/dev/null) <( ./myfind ${opt} 2>/dev/null))
    if [ "$diff" != "" ]; then
      printf "\e[31m[ FAIL ]\e[39m ";
      printf "%b\n" "$opt"
      printf "%s\n" $diff;
    else
      printf "\e[32m[ PASS ]\e[39m\t "
      printf "%b\n" "$opt"
    fi
  fi
}

check src
check makefile src
check .
check error.l
check makefile -print
check src/include -print
check src -name 'myfind.*'
check src -name 'myfind.?'
check src/*.o
check tests -type d
check tests -type dir
check tests -type y
check src -type d
check src/*.o -o src/include/myfind.h
check find
check src/*.c -a src/*.o
check src/* -newer src/main.c
check src/myfind.o -newer src/myfind.c
check src/myfind.c -newer src/myfind.o
check src/* -newer src/main.c
check src/main.o -newer src/main.c 
