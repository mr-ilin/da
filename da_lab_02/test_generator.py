#!/usr/bin/env python3

# -*- coding: utf8 -*-

import datetime

import sys
import random
import string

# MAX_VALUE_LEN = 2**64 - 1
MAX_VALUE = 18446744073709552000

def generate_random_key():
    length = random.randint(1, 256)
    # length = 256
    random_list = [ random.choice(string.ascii_letters) for _ in range(length) ]
    return "".join(random_list)

def generate_random_value():
    return random.randint(0, MAX_VALUE)

def main():
    if len(sys.argv) < 3:
        print("Usage: {} <output dir> <test count> <values count>".format(sys.argv[0]))
        sys.exit(1)

    output_dir = sys.argv[1]
    test_cnt = int(sys.argv[2])
    values_cnt = int(sys.argv[3])

    for num in range(1, test_cnt + 1):
        values = []
        output_filename_pattern = "{}/{:02d}".format(output_dir, num)
        output_filename = "{}.t".format(output_filename_pattern)

        output_filename_pattern = "{}/{:02d}".format(output_dir, num)
        output_filename = "{}.t".format(output_filename_pattern)
        with open( output_filename, 'w') as foutput :
            for _ in range( 0, values_cnt ) :
                key = generate_random_key()
                value = generate_random_value()
                values.append((key, value))
                # Вставка
                foutput.write("+ {} {}\n".format(key, value))

            # Поиск
            # random.shuffle(values)
            for value in values:
                foutput.write("{}\n".format(value[0]))
            
            # Удаление
            # random.shuffle(values)
            for value in values:
                foutput.write("- {}\n".format(value[0]))

if __name__ == "__main__":
    main()
