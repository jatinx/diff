#!/usr/bin/env python

import sys


def print_usage():
    print('Diff tool!')
    print('Usage: ./diff # uses default names')
    print('\tor')
    print('Usage: ./diff nvidia_log.txt amd_log.txt')


def read_file(file_name):
    lines = []
    with open(file_name) as f:
        lines = f.readlines()
    return lines


if __name__ == '__main__':
    argv_count = len(sys.argv)
    nvidia_log_file = 'nvidia_log.txt'
    amd_log_file = 'amd_log.txt'
    if argv_count != 1 and argv_count != 3:
        print_usage()
        exit(-1)

    if argv_count == 3:
        nvidia_log_file = sys.argv[1]
        amd_log_file = sys.argv[2]

    print('Using Nvidia Log file: ', nvidia_log_file,
          ' AMD Log file: ', amd_log_file)

    nvidia_lines = read_file(nvidia_log_file)
    amd_lines = read_file(amd_log_file)

    if len(nvidia_lines) != len(amd_lines):
        print('Nvidia and AMD log files have different lengths!')
        print('Nvidia len: ', len(nvidia_lines))
        print('AMD len: ', len(amd_lines))

    min_lines = len(amd_lines) if len(nvidia_lines) > len(
        amd_lines) else len(nvidia_lines)

    if amd_lines != nvidia_lines:
        print('There is a mismatch, iterating over line by line!')
    else:
        print('Files match!')
        exit(0)

    for i in range(min_lines):
        if nvidia_lines[i] != amd_lines[i]:
            print('Mismatch in line:', i)
            print(' NV :', nvidia_lines[i],'AMD:', amd_lines[i])
            exit(-1)
