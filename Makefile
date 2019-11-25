calculator: calculator.c tokeniser.c tokeniser.h i2p.c i2p.h code_gen.c code_gen.h stack.c stack.h vm.c vm.h
	gcc -o calculator_program calculator.c tokeniser.c i2p.c code_gen.c stack.c vm.c -lm

tokeniser: tokeniser.c tokeniser_main.c tokeniser.h
	gcc -o tokeniser_component tokeniser.c tokeniser_main.c 
	
tokeniser_test: tokeniser.c tokeniser_tester.c tokeniser.h
	gcc -o tokeniser_test.t tokeniser.c tokeniser_tester.c
	prove ./tokeniser_test.t
	
infix2postfix: i2p.c i2p_main.c i2p.h
	gcc -o i2p_component i2p.c i2p_main.c
	
test: tokeniser.c tokeniser.h calculator_test.c
	gcc -o calculator_test.t tokeniser.c calculator.c
