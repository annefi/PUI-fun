#! /bin/bash
# gzip all results files
find . -type f -and \( -name '*.out' -or -name '*.dat' -or -name '*.ps' \) \
    -exec gzip '{}' ';' &
