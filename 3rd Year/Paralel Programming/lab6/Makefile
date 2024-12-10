.PHONEY: all

TARGET = lab6

MAKEFLAGS += --no-print-directory

g:
	@python generator.py

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

ru: bur
	@./out/bin/${TARGET}

bwd:
	@cmake -B build -S . --preset windows-debug
	@cmake --build build/
	@cmake --install build/

bwr:
	@cmake -B build -S . --preset windows-release
	@cmake --build build/
	@cmake --install build/

rw: bwr
	@./out/bin/${TARGET}

r: ru