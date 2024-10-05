.PHONY: clean build run

clean:
	@rm -rf build/

build:
	@cmake -S . -B build/ -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	@cmake --build build/

run:
	@./build/client 127.0.0.1 25565