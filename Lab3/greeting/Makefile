all: clean run clean

greetings: goodbye.c greeting.c start.c user.h
	@echo -e  "\033[1;93mRunning compile...\033[0m"
	gcc -g goodbye.c greeting.c start.c -o greetings

run: greetings
	@echo -e "\033[1;93mRunning program....\033[0m"
	./greetings

.PHONY: compile clean

clean: 
	@echo -e  "\033[1;93mCleaning...\033[0m"
	rm -rf greetings
