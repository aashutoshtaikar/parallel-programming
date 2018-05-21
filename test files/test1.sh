#!usr/bin/bash

PID=2232
if  ps -p $PID >&- ; then
  echo running
else
  echo not running
fi
