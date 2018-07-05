#!/bin/bash
#!/bin/bin/gcov
#!/usr/bin/lcov
#!/usr/bin/genhtml

rm results -r
rm unittest.info

find ./src -name "*.cc" -o -name "*.cpp" | xargs gcov

lcov -d ./src -c -o unittest.info
genhtml -o results unittest.info
