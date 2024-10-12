#!/usr/bin/env sh
cd ../cmake-build-coverage-ubuntu-clang
rm -rf ../coverage/html
rm -rf ../coverage/xml
rm -rf ../coverage/txt
rm -rf ../coverage/json
mkdir -p ../coverage/html
mkdir -p ../coverage/xml
mkdir -p ../coverage/json
mkdir -p ../coverage/txt
pipx run gcovr -r .. --gcov-executable "llvm-cov-18 gcov" --filter '\.\./engine/src' --html --html-details --html-self-contained --html-theme github.dark-green -o ../coverage/html/coverage.html --cobertura ../coverage/xml/coverage.xml --txt ../coverage/txt/coverage.txt --json ../coverage/json/coverage.json