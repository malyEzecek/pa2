CC=g++
FLAGS= -std=c++11 -Wall -pedantic -Wextra -g

start: runMe doc

runMe:  directory/Cell.o directory/Bool.o directory/Expression.o  directory/Number.o directory/Operator.o directory/Reference.o directory/Text.o directory/Model.o directory/Command.o directory/View.o directory/Main.o
	$(CC) $(FLAGS) $^ -o $@

directory/Cell.o: Model/Cell.cpp Model/Cell.h | directory
	$(CC) $(FLAGS) -c $< -o $@

directory/Bool.o : Model/Bool.cpp Model/Cell.h Model/Bool.h | directory
	$(CC) $(FLAGS) -c $< -o $@

directory/Reference.o: Model/Reference.cpp Model/Cell.h Model/Reference.cpp | directory
	$(CC) $(FLAGS) -c $< -o $@

directory/Number.o: Model/Number.cpp Model/Model.h Model/Number.h | directory
	$(CC) $(FLAGS) -c $< -o $@

directory/Text.o: Model/Text.cpp Model/Cell.h Model/Text.h | directory
	$(CC) $(FLAGS) -c $< -o $@

directory/Expression.o: Model/Expression.cpp Model/Cell.h Model/Expression.h | directory
	$(CC) $(FLAGS) -c $< -o $@

directory/Operator.o: Model/Operator.cpp Model/Cell.h Model/Operator.h | directory
	$(CC) $(FLAGS) -c $< -o $@

directory/Model.o: Model/Model.cpp Model/Cell.h Model/Bool.h Model/Reference.h Model/Number.h Model/Text.h Model/Expression.h Model/Operator.h Model/Model.h | directory
	$(CC) $(FLAGS) -c $< -o $@

directory/Command.o: Controller/Command.cpp Model/Model.h Controller/Command.h | directory
	$(CC) $(FLAGS) -c $< -o $@

directory/View.o: View/View.cpp Controller/Command.h View/View.h | directory
	$(CC) $(FLAGS) -c $< -o $@

directory/Main.o: main.cpp View/View.h | directory
	$(CC) $(FLAGS) -c $< -o $@

doc: main.cpp Model/Cell.h Model/Bool.h Model/Expression.h Model/Number.h Model/Operator.h Model/Reference.h Model/Text.h Model/Model.h Controller/Command.h View/View.h
	doxygen -g DoxyFile

directory:

	mkdir directory;

clear:
	rm -r directory;
