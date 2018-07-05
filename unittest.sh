#!/bin/bash
#!/bin/bin/gcov
#!/usr/bin/lcov
#!/usr/bin/genhtml

find ./ -name "*.cc" -o -name "*.cpp" | xargs gcov

lcov -d ./ -c -o unittest.info
genhtml -o results unittest.info
