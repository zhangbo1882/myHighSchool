#/bin/bash 
find . -name "*.h" -o -name "*.c" > cscope.files
cscope -bkq -i cscope.files
ctags -R
