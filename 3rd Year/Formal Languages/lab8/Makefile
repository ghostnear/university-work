b:
	@mkdir -p bin
	@mkdir -p out
	@lex -o out/lua_with_brackets.yy.c src/lua_with_brackets.l 
	@yacc -o out/lua_with_brackets.tab.c -d src/lua_with_brackets.y -Wcounterexamples
	@gcc out/lua_with_brackets.yy.c -ly -lfl -o bin/lwbp-lexer
	@gcc out/lua_with_brackets.tab.c -ly -lfl -o bin/lwbp-parser -Wno-incompatible-pointer-types
	
c:
	@rm -rf bin
	@rm -rf out

r:
	-@./bin/lwbp-lexer p1.plua bin/p1.lexer.out
	-@./bin/lwbp-lexer p2.plua bin/p2.lexer.out
	-@./bin/lwbp-lexer p3.plua bin/p3.lexer.out
	-@./bin/lwbp-lexer p1err.plua bin/p1err.lexer.out
	-@./bin/lwbp-parser bin/p1.lexer.out
	-@./bin/lwbp-parser bin/p2.lexer.out
	-@./bin/lwbp-parser bin/p3.lexer.out