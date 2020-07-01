//
// Created by flo on 23.06.20.
//

#include "rv64minilibc.h"
#include <stdbool.h>

void init(int number);

void check_condition(bool cond);

/**
 * Compile with:
 * riscv64-unknown-linux-gnu-gcc -o arithm compiled_test_arithm.c rv64minilibc.c rv64minilibc.h -fPIE -static -march=rv64im -mabi=lp64 -nostdlib -lgcc
 * Reference run: qemu-riscv64 arithm
 * or ./translator -v -f arithm.
 *
 * Makefile for compile:
 * arithmetic: compiled_test_arithm.c rv64minilibc.c rv64minilibc.h
	riscv64-unknown-linux-gnu-gcc -o arithm compiled_test_arithm.c rv64minilibc.c rv64minilibc.h -fPIE -static -march=rv64im -mabi=lp64 -nostdlib -lgcc
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
    int num = 0;

    {
        init(++num);
        size_t i = 4;
        i /= 2;
        check_condition(i == 2);
    }

    {
        init(++num);
        size_t j = 4;
        j <<= 2;
        check_condition(j == 16);
    }

    {
        init(++num);
        size_t m = 5;
        m /= 2;
        check_condition(m == 2);
    }

    {
        init(++num);
        size_t n = 256;
        size_t o = 128;
        n += o;
        n *= 10;
        n /= 19;
        check_condition(n == 202);
    }

    {
        init(++num);
        size_t n = 3000;
        size_t m = 7;
        check_condition((n * m) == 21000);
    }

    {
        init(++num);
        size_t n = 3000;
        size_t m = 7;
        check_condition((n / m) == 428);
    }

    {
        //div-zero quotient should have all bits set
        init(++num);
        size_t n = 256;
        size_t m = 0;
        check_condition((n / m) == 0xFFFFFFFFFFFFFFFF);
    }

    {
        //div-zero remainder should equal the dividend todo fix failing test
        init(++num);
        size_t n = 256;
        size_t m = 0;
        check_condition((n % m) == 256);
    }

    {
        init(++num);
        size_t res = 1 << 10;
        check_condition(res == 0b10000000000);
    }

    {
        //control flow experiment todo unknown opcode?
        init(++num);
        const int bound = 2048;

        size_t sum = 0;
        for (int i = 1; i <= bound; ++i) {
            sum += i;
        }

        size_t gauss = (bound * (bound + 1)) / 2;
        check_condition(sum == gauss);
    }

    {
        //factorial experiments
        const size_t len = 19;
        static uint64_t expecteds[] = {
                1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800, 479001600, 6227020800, 87178291200,
                1307674368000, 20922789888000, 355687428096000, 6402373705728000, 121645100408832000
        };

        for (int n = 1; n < len; ++n) {
            init(++num);

            //calculate the factorial
            size_t fact = 1;

            for (size_t i = 1; i <= n; i++) {
                fact *= i;
            }

            check_condition(fact == expecteds[n - 1]);
        }
    }

    m_exit();
}

void init(int number) {
    m_write(1, "Test ", 5);
    printi(number);
    m_write(1, "...\t", 4);
}

void check_condition(bool cond) {
    if (cond) {
        m_write(1, "PASSED\n", 7);
    } else {
        m_write(1, "FAILED\n", 7);
    }
}