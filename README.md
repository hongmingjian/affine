# Note
The [Affine Transformations](https://doc.qt.io/qt-5/qtwidgets-painting-affine-example.html) is used to demonstrate how to embed Common Lisp into a Qt application. 
The idea and some codes are borrowed from [1].

It's only tested on ECL-24.5.10 and Qt-5.15.2 built with MSVC2019 on Windows 7 (x86).

# Examples
   1. Start Swank server, then you can get a REPL via [SLIME](https://github.com/slime/slime)/[SLIMV](https://github.com/kovisoft/slimv).
   > affine.exe -e "(load \\"/path/to/start-swank.lisp\\")"
   2. Take a snapshot and exit:
   > affine.exe -e "(take-snapshot (merge-pathnames \\"1.png\\" (user-homedir-pathname)))" -e "(exit)"

# References
[1] https://fulcrumbright.com/embedding-lisp-in-c-a-recipe/