build:
	gcc baby-keyboard.c -o baby-keyboard

run: build
	baby-keyboard.exe

run_space: build
	baby-keyboard.exe 0x20

run_simple_game: build
	# space up down left right esc enter
	baby-keyboard.exe 0x20 0x25 0x26 0x27 0x28 0x1B 0x0D