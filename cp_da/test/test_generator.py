#!/usr/bin/env python3

# -*- coding: utf8 -*-

import datetime

import sys
import random
import string

# MAX_VALUE_LEN = 2**64 - 1
MAX_VALUE = 18446744073709552000

def generate_random_str(length):
    random_list = [ random.choice(string.ascii_lowercase) for _ in range(length) ]
    return "".join(random_list)

def generate_random_value():
    return random.randint(0, MAX_VALUE)

def main():
    if len(sys.argv) < 3:
        print("Usage: {} <output dir> <test count> <values count>".format(sys.argv[0]))
        sys.exit(1)

    output_dir = sys.argv[1]
    test_cnt = int(sys.argv[2])
    strlen = int(sys.argv[3])

    for num in range(1, test_cnt + 1):
        values = []
        output_filename_pattern = "{}/{:02d}".format(output_dir, num)
        output_filename = "{}.t".format(output_filename_pattern)

        with open( output_filename, 'w' ) as foutput :
            value = generate_random_str(strlen)
            foutput.write("{}".format(value))

if __name__ == "__main__":
    main()
