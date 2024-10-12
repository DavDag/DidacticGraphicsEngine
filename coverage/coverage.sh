#!/usr/bin/env sh
cd ../cmake-build-coverage-ubuntu-clang
gcovr -r .. --gcov-executable "llvm-cov-18 gcov" --filter /mnt/e/Extra/DidacticGraphicsEngine/engine/src --html --html-details --html-self-contained --html-theme github.dark-green -o ../coverage/coverage_index.html --cobertura ../coverage/coverage_cobertura.xml