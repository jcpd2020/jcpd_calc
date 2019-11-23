calculator: tokeniser.c tokeniser.h calculator.c
	gcc -o calculator_program tokeniser.c calculator.c

tokeniser: tokeniser.c tokeniser_main.c tokeniser.h
	gcc -o tokeniser_component tokeniser.c tokeniser_main.c 
	
tokeniser_test: tokeniser.c tokeniser_tester.c tokeniser.h
	gcc -o tokeniser_test.t tokeniser.c tokeniser_tester.c
	prove ./tokeniser_test.t
	
test: tokeniser.c tokeniser.h calculator_test.c
	gcc -o calculator_test.t tokeniser.c calculator.c
