calculator: calculator.c tokeniser.c tokeniser.h i2p.c i2p.h code_gen.c code_gen.h stack.c stack.h vm.c vm.h calculator_main.c calculator.h
	gcc -o calculator_program calculator.c calculator_main.c tokeniser.c i2p.c code_gen.c stack.c vm.c -lm
	@echo "2+2" > jcpd.io
	@echo "\n\n\n-------------------------------\nCS3500 - Calculator - Team JCPD\n- Jack Curtin       (117359191)\n- Cristian Guadino  (117434292)\n- Pual Gunnarsson   (117430404)\n- David Ryan-Lynch  (115310721)\n-------------------------------\n\nAn example expression, 2 + 2, has been added to the input file (jcpd.io).\nWrite your infix expression in this file and run\n\n\t./calculator_program\n\nto calculate the answer.\nThe answer is printed to stdout (below), and written to the file.\n"

test: test_tokeniser test_i2p test_code_gen test_vm test_calculator

test_tokeniser: tokeniser.c tokeniser.h tokeniser_test.c
	gcc -o test_tokeniser.t tokeniser_test.c tokeniser.c
	prove ./test_tokeniser.t

test_i2p: i2p.c i2p.h i2p_test.c
	gcc -o test_i2p.t i2p.c i2p_test.c
	prove ./test_i2p.t

test_code_gen: code_gen.c code_gen.h code_gen_test.c
	gcc -o test_code_gen.t code_gen.c code_gen_test.c
	prove ./test_code_gen.t

test_vm: stack.c stack.h vm.c vm.h vm_test.c
	gcc -o test_vm.t vm.c stack.c vm_test.c -lm
	prove ./test_vm.t

test_calculator: calculator_test.c calculator.c calculator.h
	gcc -o test_calculator.t calculator_test.c calculator.c tokeniser.c i2p.c code_gen.c vm.c stack.c -lm
	prove ./test_calculator.t
