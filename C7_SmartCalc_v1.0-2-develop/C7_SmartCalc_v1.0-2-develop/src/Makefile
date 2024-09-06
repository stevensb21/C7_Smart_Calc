CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11 -lm
GCOVFLAGS := -fprofile-arcs -ftest-coverage
LDFLAGS := -lcheck -lgcov -fprofile-arcs --coverage -lsubunit -lm

ifeq ($(shell uname), Linux)
    LDFLAGS += -lpthread -lrt -lm -lsubunit
    OPEN_CMD := xdg-open
else ifeq ($(shell uname), Darwin)
    OPEN_CMD := open
endif

SRC := $(wildcard Back/*.c)
OBJ = $(patsubst Back/%.c, Back/%.o, $(SRC))
OBJ_GCOV = $(patsubst Back/%.c, gcov_obj/%.o, $(SRC))


TARGET := calculator

all: install

Back/%.o: $(SRC)
	@$(CC) $(CFLAGS) -c $< -o $@


gcov_obj/%.o: $(SRC)
	@$(CC) $(CFLAGS) $(GCOVFLAGS) -c $< -o $@

libcalc.a: $(OBJ_GCOV)
	@ar -src libcalc.a $(OBJ_GCOV)

lib_calc_gcov.a: $(OBJ_GCOV)
	@ar -src $@ $(OBJ_GCOV)

test: test/test_calc

test/test_calc: test/tests.o libcalc.a
	@$(CC) -g $< libcalc.a -o $@ $(SRC) $(LDFLAGS) $(GCOVFLAGS)
	@./test/test_calc

gcov_report: test/test_calc
	@./test/test_calc
	lcov -c -d test/. -o gcov_obj/coverage.info
	genhtml gcov_obj/coverage.info --output-directory out
	@$(OPEN_CMD) out/index.html

install:
	@mkdir -p ../build
	@cd ../build && qmake ../src/View/calculator.pro && make
	@./../build/calculator

dvi:
	@$(OPEN_CMD)  ../README_RUS.md

dist:
	@mkdir -p ../dist
	@cp -R ../build/$(TARGET) ../dist
	@cp ../README_RUS.md ../dist && cp ../README.md ../dist
	@cd ../dist && tar cvzf $(TARGET).tgz *
	@cd ../dist && rm -rf $(TARGET) README.md README_RUS.md

clean_gcov:
	@rm -rf ./test/*.gcno
	@rm -rf ./test/*.gcda
	@rm -rf out


clean:
	@rm -rf ./gcov_obj/*.o
	@rm -rf ./gcov_obj/*.gcno
	@rm -rf ./gcov_obj/*.info
	@rm -rf ./test/*.o
	@rm -rf ./test/test_calc
	@rm -rf out
	@rm -rf libcalc.a

clean_all: clean clean_gcov

uninstall:
	@rm -rf ../build/$(TARGET)

uninstall_build:
	@rm -rf ../build

uninstall_all: clean_all uninstall_build
	@rm -rf ../dist
	@rm -rf ./Back/*.gch

clang:
	@clang-format -i Back/*.c Back/*.h test/*.c View/*.cpp View/*.h View/*.ui

style:
	@clang-format -n Back/*.c Back/*.h test/*.c View/*.cpp View/*.h View/*.ui

cppcheck: clean clean_gcov test/test_calc
	@cppcheck --enable=all --suppress=missingIncludeSystem Back/ View/

valgrind: clean clean_gcov test/test_calc
	@CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test/test_calc

leaks: clean clean_gcov test/test_calc
	@leaks -atExit -- ./test/test_calc