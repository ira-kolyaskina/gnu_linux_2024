#!/bin/sh

tput clear

text=$(od -v -An -tx1)

cur_x=0
cur_y=0

for byte in $text; do
    if [ $byte != "20" ]  && [ "$byte" != "0a" ]; then
        echo "$byte/$cur_x/$cur_y"
    fi

    if [ $byte != "0a" ]; then
        cur_y=$(($cur_y + 1))
    else
        cur_x=$(($cur_x + 1))
        cur_y=0
    fi
done | shuf | while IFS='/' read -r byte line col; do
    char=$(/bin/echo -e "\x$byte")

    tput cup $line $col
    echo -n $char

    tput cup $(($(tput lines) - 1)) 0

    if ! [ -z $1 ]; then
        sleep $1
    fi
done