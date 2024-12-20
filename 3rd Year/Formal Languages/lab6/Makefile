.PHONEY: all

TARGET = lab5

MAKEFLAGS += --no-print-directory

c:
	@cmake -E remove_directory .cache/
	@cmake -E remove_directory build/
	@cmake -E remove_directory out/

bud:
	@cmake -B build -S . --preset unix-debug
	@cmake --build build/
	@cmake --install build/

bur:
	@cmake -B build -S . --preset unix-release
	@cmake --build build/
	@cmake --install build/

ru:
	@./out/bin/${TARGET} ./inputs/token.in ./inputs/p1.plua

b: bur
r: ru
f:
	@./out/bin/${TARGET} fa-showcase yes

g:
	@./out/bin/${TARGET} gr-showcase yes