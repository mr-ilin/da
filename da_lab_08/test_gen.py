#! /usr/bin/env python

import sys
import random

# Максимально возможное значение числа.
MIN_VALUE = 1

def get_random_int():
    return random.randint(MIN_VALUE, 2 ** random.randint(1, 32))

def get_random_short():
    return random.randint(MIN_VALUE, 2 ** random.randint(1, 4))

def get_random_nums():
    return get_random_int(), get_random_short(), get_random_int()


def main():
    # Ожидаем, что будет три аргумента: название программы,
    # путь до директории с тестами
    # и количество тестов в каждом файле.
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <tests directory> <tests count> <tests type>")
        sys.exit(1)

    # Считываем путь до папки с тестами.
    test_dir = sys.argv[1]
    # Считываем количество тестов
    tests_count = int(sys.argv[2])

    for test in range(0, tests_count):
        filename_pattern = f'{test_dir}/0{test + 1}'
        with open(f'{filename_pattern}.t', 'w') as test_file:
                num1, num2, num3 = get_random_nums()
                # Записываем в файл получившийся тест.
                test_file.write(f"{num1} {num2}\n{num3}\n")

if __name__ == "__main__":
    main()
