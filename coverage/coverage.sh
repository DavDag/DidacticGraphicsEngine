#!/usr/bin/env sh
cd ../cmake-build-coverage-ubuntu-clang
rm -rf ../coverage/html
rm -rf ../coverage/xml
mkdir -p ../coverage/html
mkdir -p ../coverage/xml
pipx run gcovr -r .. --gcov-executable "llvm-cov-18 gcov" --filter /mnt/e/Extra/DidacticGraphicsEngine/engine/src --html --html-details --html-self-contained --html-theme github.dark-green -o ../coverage/html/coverage_index.html --cobertura ../coverage/xml/coverage_cobertura.xml