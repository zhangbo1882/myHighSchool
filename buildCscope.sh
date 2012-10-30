#!/bin/bash
find `pwd` -name "*.h" -o -name "*.c" > cscope.files
cscope -bkqR

