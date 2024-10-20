.PHONEY: all

TARGET = bonus1

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
	@./out/bin/${TARGET} ./random_phrases_combined_1_million_words.txt

b: bur
r: ru
