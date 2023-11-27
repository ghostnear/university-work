.PHONY: clean build run

clean:
	@rm -rf build/
	@rm -rf .cache/

build:
	@cmake -S . -B build/ -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	@cmake --build build/

run:
	@./build/client