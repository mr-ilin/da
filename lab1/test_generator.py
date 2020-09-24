#!/usr/bin/env python3

# -*- coding: utf8 -*-

import datetime

import sys
import random
import string

MAX_VALUE_LEN = 18446744073709551614

def generate_random_value():
    return random.randint(0, MAX_VALUE_LEN)

def generate_random_key_0():
    return "".join([str(random.randint(1, 31))])

def generate_random_key_1():
    return "".join([str(random.randint(1, 12))])

def generate_random_key_2():
    return "".join([str(random.randint(1700, 3100))])

def main():
    if len(sys.argv) < 3:
        print("Usage: {} <output dir> <test count>".format(sys.argv[0]))
        sys.exit(1)

    output_dir = sys.argv[1]
    test_cnt = int(sys.argv[2])
    values_cnt = int(sys.argv[3])

    for num in range(1, test_cnt+1):
        values = []
        output_filename_pattern = "{}/{:02d}".format(output_dir, num)
        output_filename = "{}.t".format(output_filename_pattern)
        with open( output_filename, 'w') as foutput:
            for _ in range( 0, values_cnt ):
                key_0 = generate_random_key_0()
                key_1 = generate_random_key_1()
                key_2 = generate_random_key_2()
                value = generate_random_value()
                values.append((key_0, key_1, key_2, value))
                foutput.write("{}.{}.{}\t{}\n".format(key_0, key_1, 
                key_2, value))
        # Записываем файл с ответом.
        # values[0][0] -- key
        # values[0][1] -- value
        answer_filename = "{}.a".format(output_filename_pattern)
        with open(answer_filename, 'w') as fans:
            #values = sorted(values, key = lambda x: int(x[0]))
            values = sorted(sorted(sorted(values, key=lambda x: int(x[0])), key=lambda x: int(x[1])),  key=lambda x: int(x[2]))
            for value in values:
                fans.write("{}.{}.{}\t{}\n".format(value[0], value[1], value[2], value[3]))

if __name__ == "__main__":
    main()
