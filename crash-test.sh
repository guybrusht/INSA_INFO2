#! /bin/bash

valgrind --leak-check=full ./a.out < crashTest.dat 
