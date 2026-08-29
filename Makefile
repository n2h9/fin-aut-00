build/number: cmd/number/main.c
	gcc -g -O0 -o ./build/number ./cmd/number/main.c

build/id-alpha-char-5-alpha-num: cmd/id-alpha-char-5-alpha-num/main.c
	gcc -g -O0 -o ./build/id-alpha-char-5-alpha-num ./cmd/id-alpha-char-5-alpha-num/main.c

build/fa-id-alpha-char-5-alpha-num: cmd/fa-id-alpha-char-5-alpha-num/main.c fa.c
	gcc -g -O0 -o ./build/fa-id-alpha-char-5-alpha-num ./cmd/fa-id-alpha-char-5-alpha-num/main.c fa.c

build/re-from-str: cmd/re-from-str/main.c re.c
	gcc -g -O0 -o ./build/re-from-str ./cmd/re-from-str/main.c re.c

