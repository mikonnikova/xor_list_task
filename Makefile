.PHONY : test
test: test2 test1
	./test1
	@echo "Test 1 run"
	./test2
	@echo "Test 2 run"
	@echo "All tests run"

.PHONY : clean
clean:
	rm -f $(wildcard *.o)

.PHONY : clean_all
clean_all:
	rm -f test1 test2
