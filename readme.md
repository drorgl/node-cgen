# PEG.js C++ Parser
This is a C++ parser based on [Pau Fernández](http://pauek.info/) [ccjs](https://github.com/pauek/ccjs), it was an attempt to write a PEG.js C++ parser which failed and is published so others can take a look, learn from it or finish it if they want to.

Its not clean and should not be used as is.

If you would like to build the parser, you should install pegjs:
npm install -g pegjs

You can build the parser with:
```
pegjs "c++.pegjs" "cppparser.js"
```

Or with tracing enabled:
```
pegjs --trace "c++.pegjs" "cppparser.js"
```

A better way to use the C++ grammer is through the builder.js which compiles the grammar on the fly, it is slower, but it does help with debugging.
```
usage: builder.js [--parsetest] [--trace] [--backtrace] <input-file>
```
where:

> --parsetest is just returning FAIL or OK for the input file.

> --trace is returning json [trace](https://gist.github.com/tonypujals/808f91bfdfb88c7d5ed7) from PEG.js

> --backtrace is returning visual backtrace fail tree from [Mitsutaka Okazaki](https://github.com/okaxaki)'s [pegjs-backtrace](https://github.com/okaxaki/pegjs-backtrace)

There are tests I've used to improve the grammar and make sure the changes don't regress, at the moment some of them are failing as I've discovered a few more edge cases.

I've used the OpenCV headers to do the actual grammar development so you'll find fragments of OpenCV headers in the test files inside testdata. there are also test files from the [ccjs](https://github.com/pauek/ccjs) project.

Hopefully the test and builder will be useful for anyone wishes to develop grammars. I've found them useful.

