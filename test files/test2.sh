#!usr/bin/bash
process=$(ps -ef | grep mount.ntfs | grep -v grep)
if [ "$process" ]; then
 echo running
else
 echo not running
fi
