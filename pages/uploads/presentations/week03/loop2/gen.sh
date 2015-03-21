#!/usr/bin/env bash

pandoc slides.md -o slides.html -t revealjs -s \
-V theme=night --no-highlight --variable hlss=zenburn \
--template=template-revealjs.html \
--mathjax=https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML

