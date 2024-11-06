.PHONEY: all

TARGET = lab2

MAKEFLAGS += --no-print-directory

c:
	@cmake -E remove_directory .cache
	@cmake -E remove_directory build
	@cmake -E remove_directory out

b:
	@cmake -B build -S . -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_INSTALL_PREFIX=./out
	@cmake --build build/
	@cmake --install build/

r: b
	@./out/bin/${TARGET}

rv: b
	@valgrind --leak-check=full --show-leak-kinds=all ./out/bin/${TARGET}
