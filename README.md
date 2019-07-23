# BK-Tree
[![Build Status](https://travis-ci.org/oliversno/BK-Tree.svg?branch=master)](https://travis-ci.org/oliversno/BK-Tree)
[![Coverage Status](https://coveralls.io/repos/github/oliversno/BK-Tree/badge.svg)](https://coveralls.io/github/oliversno/BK-Tree)

Impliments a BK Tree using the Levenshtein Distence as metric to impliment a spell checker

# Instructions
Run the program using ` ./main $DICT  ` where ` $DICT ` is a text file containing one word per line.

Once you see ` Please Input Text ` begin inputing words to the command line. If a word is not in ` $DICT ` the program will inform you and offer suggestions as to the correct spelling.

To end input input ` EXIT ` in all caps.

It is recomended to use input redirection ( ` << ` in bash `) to spell check an entire file at once.
