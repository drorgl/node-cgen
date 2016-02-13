var fs = require('fs');
var test = require('tape');
var colors = require('colors');
var async = require('async');

var PEG = require("pegjs");

var cppdialect = fs.readFileSync('c++.pegjs', { encoding: 'utf8' });

var parserSource = PEG.buildParser(cppdialect,{output: "source"});
var parser = eval(parserSource);

var level = 0;


function tablevel() {
    var retval = "";
    for (var i = 0; i < level; i++) {
        retval += "\t";
    }
    return retval;
}
test.createStream({ objectMode: true }).on('data', function (row) {
    if (row.type == "end") {
        console.log();
        level--;
    }
    else if (row.type == "test") {
        level++;
        console.log();
        console.log(tablevel() + "%d. Testing %s", row.id, row.name);
    }
    else {
        if (row.ok) {
            console.log(tablevel() + "%d. \t %s \t %s".green.bold, row.id, row.ok, row.name);
            if (row.operator == "throws" && row.actual != undefined) {
                console.log(tablevel() + " threw: %s".green.bold, row.actual);
            }
        }
        else {
            console.log(tablevel() + "%d. \t %s \t %s".red.bold, row.id, row.ok, row.name);
            console.log(tablevel() + "\t %s".red.bold, row.actual);
        }
    }
});

test("Pre test", function (t) {
	t.ok(parser, "parser is valid");
	fs.readdir("testdata", function(err,files){
		t.ok(files.length > 0, "found " + files.length + " test files");
		
		
		
		async.forEachOf(files,function(file,key,cb){
			fs.readFile("testdata\\" + file, 'utf-8', function (err, data) {
				if (err){
					t.fail("unable to read " + file);
				}

				try {
					parser.parse(data);
					t.ok(true, "testing " + file + " successfully");
					cb(null);
				} catch (e) {
					t.fail("testing " + file + " failed: " + e.location.start.line + ":" + e.location.start.column + "-" + e.location.end.line + ":" + e.location.end.column + " " + e.message);
					cb(null);
				}

				
			});
		},function(err){
			t.end();
		});
		
		//t.end();
	});
    
    
});
