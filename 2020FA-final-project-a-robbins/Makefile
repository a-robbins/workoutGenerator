repl-build.out: 2020FA-final-project-a-robbins.c
	gcc -o $@ $^

.PHONY: run
run: repl-build.out
	./$^

.PHONY: clean

clean:
	rm -f repl-build.out


  