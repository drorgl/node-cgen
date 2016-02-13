var fs = require('fs');

var PEG = require("pegjs");

var cppdialect = fs.readFileSync('c++.pegjs', { encoding: 'utf8' });

var tracer = require('pegjs-backtrace');

var util = require("util");

function usage() {
   console.log("usage: builder.js [--prettyprint] [--parsetest] [--trace] [--backtrace] <input-file>");
   process.exit(1);
}

if (process.argv.length < 3) {
   usage();
}

var opts = {};
var args = process.argv.slice(1);
for (var i in args) {
   var a = args[i];
   if (a == '--prettyprint') {
      opts.prettyprint = true;
   } else if (a == '--parsetest') {
      opts.parsetest = true;
   } else if (a == '--trace'){
	  opts.trace = true;
   } else if (a == '--backtrace'){
	  opts.backtrace = true;
   } else {
      opts.ccfile = a;
   }
}

if (!('ccfile' in opts)) {
   usage();
}

fs.readFile(opts.ccfile, 'utf-8', function (err, data) {
   if ('backtrace' in opts){
      var parserSource = PEG.buildParser(cppdialect,{"trace":true,output: "source"});
	  var parser = eval(parserSource);
	  var t = new tracer(data);
	  
	  try {
         var tree = parser.parse(data, {tracer:t});
		 console.log(JSON.stringify(tree,undefined,2));
      }  catch (e) {
		 console.log(t.getBacktraceString());
         var lines = data.split("\n");
         console.log("error: " + e.location.start.line + ":" + e.location.start.column + "-" + e.location.end.line + ":" + e.location.end.column + " " + e.message);
      }
	  
   } else if ('trace' in opts) {
	  var parserSource = PEG.buildParser(cppdialect,{"trace":true,output: "source"});
	  var parser = eval(parserSource);
	  try {
         var tree = parser.parse(data, {tracer : { trace : function (evt) {
			console.log(evt);
		 }}});
		 console.log(JSON.stringify(tree,undefined,2));
      }  catch (e) {
         var lines = data.split("\n");
         console.log("error: " + e.location.start.line + ":" + e.location.start.column + "-" + e.location.end.line + ":" + e.location.end.column + " " + e.message);
      }
   } else if ('parsetest' in opts) {
      var parserSource = PEG.buildParser(cppdialect,{output: "source"});
	  var parser = eval(parserSource);
      try {
         parser.parse(data);
         process.stdout.write("OK   ");
      } catch (e) {
         process.stdout.write("FAIL ");
      }
      process.stdout.write(opts.ccfile + "\n");
   } else {
      var parserSource = PEG.buildParser(cppdialect,{output: "source"});
	  var parser = eval(parserSource);
      try {
         var tree = parser.parse(data);
		 console.log(JSON.stringify(tree,undefined,2));
      }  catch (e) {
         var lines = data.split("\n");
         console.log("error: " + e.location.start.line + ":" + e.location.start.column + "-" + e.location.end.line + ":" + e.location.end.column + " " + e.message);
		 
		 
      }
   }
});

