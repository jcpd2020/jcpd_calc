calculator: calculator.c tokeniser.c tokeniser.h i2p.c i2p.h code_gen.c code_gen.h stack.c stack.h vm.c vm.h calculator_main.c calculator.h
	gcc -o calculator_program calculator.c calculator_main.c tokeniser.c i2p.c code_gen.c stack.c vm.c -lm
	echo "2+2" > jcpd.io
	./calculator_program
	

test: test_tokeniser test_i2p test_code_gen test_vm test_calculator

# full test of all individual components, and integration
#test: calculator_test.c calculator.c calculator.h tokeniser.c tokeniser.h #tokeniser_test.c i2p.c i2p.h i2p_test.c code_gen.c code_gen.h code_gen_test.c stack.c #stack.h vm.c vm.h vm_test.c
#	gcc -o test_tokeniser.t tokeniser_test.c tokeniser.c
#	gcc -o test_i2p.t i2p.c i2p_test.c
#	gcc -o test_code_gen.t code_gen.c code_gen_test.c
#	gcc -o test_vm.t vm.c stack.c vm_test.c -lm
#	gcc -o test_calculator.t calculator_test.c calculator.c tokeniser.c i2p.c code_gen.c stack.c vm.c -lm
#	prove -v ./test_tokeniser.t
#	prove -v ./test_i2p.t
#	prove -v ./test_code_gen.t
#	prove -v ./test_vm.t
#	prove -v ./test_calculator.t


test_tokeniser: tokeniser.c tokeniser.h tokeniser_test.c
	gcc -o test_tokeniser.t tokeniser_test.c tokeniser.c
	prove -v ./test_tokeniser.t

test_i2p: i2p.c i2p.h i2p_test.c
	gcc -o test_i2p.t i2p.c i2p_test.c
	prove -v ./test_i2p.t

test_code_gen: code_gen.c code_gen.h code_gen_test.c
	gcc -o test_code_gen.t code_gen.c code_gen_test.c
	prove -v ./test_code_gen.t

test_vm: stack.c stack.h vm.c vm.h vm_test.c
	gcc -o test_vm.t vm.c stack.c vm_test.c -lm
	prove -v ./test_vm.t

test_calculator: calculator_test.c calculator.c calculator.h
	gcc -o test_calculator.t calculator_test.c calculator.c tokeniser.c i2p.c code_gen.c vm.c stack.c -lm
	prove -v ./test_calculator.t
