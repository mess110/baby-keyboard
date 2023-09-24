default: help

build:
	gcc src/baby-keyboard.c -o baby-keyboard

dev: build
	./baby-keyboard.exe ctrl c

help: build
	./baby-keyboard.exe help
