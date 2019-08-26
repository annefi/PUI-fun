#!/bin/bash
# Re-attaches .mak files to Makefiles for default make behavior
find `pwd` -name '*.mak' -exec perl tools/lnmak.pl '{}' ';'
