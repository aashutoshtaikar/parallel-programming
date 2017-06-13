#!/bin/bash

echo performance>>out.txt
awk -F: '/performance/ {print $2}' text.txt>>out.txt
