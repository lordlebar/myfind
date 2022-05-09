#!/bin/bash

function check
{
  opt="$*"
  DIFF=$(diff <( ./myfind ${opt} 2>/dev/null) <( find ${opt} 2>/dev/null))
  if [ "$DIFF" != "" ]; then
    printf "\e[31m[ FAIL ]\e[39m  ";
    printf "%b\n" "$opt"
    printf "%s\n" $DIFF;
  else
    printf "\e[32m[ OK ]\e[39m\t  "
    printf "%b\n" "$opt"
  fi
}

check src
check makefile src
