#!/bin/sh


RUN=0
COMPILE=0
DRAW=0
OPCODES=0
while getopts 'rcdo' OPTION; do
	case "$OPTION"; do
		r)
			RUN=1
			;;
		c)
			COMPILE=1
			;;
		d)
			DRAW=1
			;;
		o)
			OPCODES=1
			;;
		?)
			echo "Usage: $(basename $0) [-r] [-c]"
			exit 1
			;;
	esac
done


[ ! -d ".bin/" ] && mkdir .bin
echo "CTX_REDRAW"
gcc -lcurses ../chip8.c test_ctx_redraw.c -o ./.bin/test_ctx_redraw
#./.bin/test_ctx_redraw
if [[ "$OPCODES" = 1 ]]; then
	echo "OPCODES"
	gcc -lcurses ../chip8.c test_opcodes.c -o ./.bin/test_opcodes
	if [[ $./.bin/test_opcodes
fi
