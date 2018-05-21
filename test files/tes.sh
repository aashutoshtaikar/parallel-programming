#!usr/bin/bash

nohup while &
pid=$2232
...more stuff...
ps -p $pid > /dev/null
[ $2232 == 1 ] && echo "it's gone, buddy!"
