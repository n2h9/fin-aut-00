CFLAGS = -std=c23 -Wall -Wextra -g -O0

build/number: cmd/number/main.c
	gcc $(CFLAGS) -o ./build/number ./cmd/number/main.c

build/id-alpha-char-5-alpha-num: cmd/id-alpha-char-5-alpha-num/main.c
	gcc $(CFLAGS) -o ./build/id-alpha-char-5-alpha-num ./cmd/id-alpha-char-5-alpha-num/main.c

build/fa-id-alpha-char-5-alpha-num: cmd/fa-id-alpha-char-5-alpha-num/main.c fa.c
	gcc $(CFLAGS) -o ./build/fa-id-alpha-char-5-alpha-num ./cmd/fa-id-alpha-char-5-alpha-num/main.c fa.c

build/re-from-str: cmd/re-from-str/main.c re.c
	gcc $(CFLAGS) -o ./build/re-from-str ./cmd/re-from-str/main.c re.c

