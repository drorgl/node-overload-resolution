console.log("starting");
var tape = require("tape");
var chalk = require("chalk");


let errorColor = chalk.red.bold;
let okColor = chalk.green.bold;
var level = 0;

function logger(module, level, message) {
    //if (level < 99) {
    //console.log(module, level, message);
    //}
}
function tablevel() {
    let retval = "";
    for (let i = 0; i < level; i++) {
        retval += "\t";
    }
    return retval;
}

var results = {
    passed: 0,
    failed : 0
};

tape.createStream({ objectMode: true }).on('data', (row) => {
    //console.log(JSON.stringify(row));
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
            results.passed++;
            console.log(tablevel() + okColor("%d. \t %s \t %s"), row.id, row.ok, row.name);
            if (row.operator == "throws" && row.actual != undefined) {
                console.log(tablevel() + okColor(" threw: %s"), row.actual);
            }
        }
        else {
            results.failed++;
            console.log(tablevel() + errorColor("%d. \t %s \t %s"), row.id, row.ok, row.name);
            console.log(tablevel() + errorColor("\t expected: %s actual: %s"),row.expected, row.actual);
        }
    }
    //console.log(JSON.stringify(row))
});

tape.createStream({ objectMode: true }).on('end', (r) => {
    console.log("passed:", results.passed);
    console.log("failed:", results.failed);
});


function showObject(tobj) {
    let objstr = JSON.stringify(tobj, null, '\t');
    let showObjectContents = false;
    if (showObjectContents) {
        console.log(objstr);
    }
    else {
        console.log("object size: " + objstr.length);
    }
}



var addon = null;
var aoRelease = null;
var aoDebug = null;

if (addon == null) {
    try {
        addon = require('../build/Release/tester');
    } catch (e) {
        aoRelease = e;
    }
}

if (addon == null) {
    try {
        addon = require('../build/Debug/tester');
    } catch (e) {
        aoDebug = e;
    }
}

if (addon == null) {
    console.log(aoRelease, aoDebug);
}


tape('test function without overload resolution', function (t) {
    t.equal(addon.testfunction_no_overload_resolution(),"testfunction_no_overload_resolution", "function without overload returned true");
    t.end();
});



tape('base_function on base_class', function (t) {
    var bc = new addon.base_class();
    t.ok(bc, "base class created successfully");
    t.ok(bc.base_function(), "function called on base_class");
    t.end();
});

tape('function on derived class', function (t) {
    var dc = new addon.derived_class();
    t.ok(dc, "derived class created successfully");
    t.ok(dc.derived_function(), "function called on derived_class");
    t.end();
});

tape('base_class.base_function  test function on derived class', function (t) {
    var dc = new addon.derived_class();
    t.ok(dc, "derived class created successfully");
    t.ok(dc.base_function(), "base_class.base_function function called on derived_class");
    t.end();
});


var dataTypes = [
    {
        value: 1,
        name: "number"
    }
    , {
        value: 2 ^ 33,
        name: "number"
    }
    , {
        value: true,
        name: "bool"
    }
    , {
        value: false,
        name: "bool"
    }
    , {
        value: "1",
        name: "string"
    }
    , {
        value: "str",
        name: "string"
    }
    , {
        value: new Date(),
        name: "date"
    }
    , {
        value: function () { },
        name: "function"
    }
    , {
        value: new Map(),
        name: "map"
    }
    , {
        value: new Set(),
        name: "set"
    }
    , {
        value: new Buffer(0),
        name: "buffer"
    }
    , {
        value: Promise.resolve(0),
        name: "promise"
    }
    , {
        value: new Proxy({}, {}),
        name: "proxy"
    }
    , {
        value: new RegExp("[a-z]"),
        name: "regexp"
    }
    , {
        value: new addon.base_class(),
        name: "base_class"
    }
    , {
        value: new addon.derived_class(),
        name: "derived_class"
    }
    , {
        value: { "prop1": "val1", "prop2": "val2" },
        name: "struct_A"
    }
    , {
        value: { "prop1": "val1", "prop2": 2 },
        name: "struct_B"
    }
    , {
        value: [],
        name: "array"
    }
     //, {
     //    value: {},
     //    name: "object"
     //}
     //, {
     //    value: null,
     //    name: "null"
     //}
     //, {
     //    value: undefined,
     //    name: "undefined"
     //}
];


tape('function overload 1 parameter, no defaults', function (t) {
    t.doesNotThrow(function () {
        t.equal(addon.number_testers(), ".no_parameters", "number_testers no_params");

        for (var dt of dataTypes) {
            t.equal(addon.number_testers(dt.value), "." + dt.name, "number_testers " + dt.name);
        }

    });
    t.end();
});



//TODO: test member/static functions

tape('member function overload 1 parameter, no defaults', function (t) {
    t.doesNotThrow(function () {
        let bc = new addon.base_class();

        t.equal(bc.base_function(), "base_class.base_function.no_parameters_testers", "no_params");

        for (var dt of dataTypes) {
            t.equal(bc.base_function(dt.value), "base_class.base_function." + dt.name, "number_testers " + dt.name);
        }

    });
    t.end();
});

//TODO: test class inheritance chain calls
//e.g. derived class overload implements function x and base class overload implement function x, which will be called when and on which parameters? 
//overload should be across class graph, otherwise no true inheritance will be implemented.
//also, what happens when calling function inherited from base but not overloaded in derived?

tape('derived member function overload 1 parameter, no defaults', function (t) {
    t.doesNotThrow(function () {
        let bc = new addon.derived_class();

        t.equal(bc.base_function(), "derived_class.base_function.no_parameters_testers", "no_params");

        for (var dt of dataTypes) {
            t.equal(bc.base_function(dt.value), "derived_class.base_function." + dt.name, "derived_class.base_function " + dt.name);
        }
        
    });
    t.end();
});

//TODO: test structs, succes, fail, multiple
tape('function overload - structs', function (t) {
    t.doesNotThrow(function () {
        t.equal(addon.structs_testers(), "structs_testers.no_parameters", "no parameters")
        t.equal(addon.structs_testers({ "prop1": "1", "prop2": "2" }), "structs_testers.struct_A", "structs_testers struct_A");
        t.equal(addon.structs_testers({ "prop1": "1", "prop2": 2 }), "structs_testers.struct_B", "structs_testers struct_B");

        t.equal(addon.structs_testers({ "prop1": "1", "prop2": "2" }, { "prop1": "1", "prop2": "2" }), "structs_testers.struct_A_struct_A", "structs_testers struct_A struct_A");
        t.equal(addon.structs_testers({ "prop1": "1", "prop2": 2 }, { "prop1": "1", "prop2": 2 }), "structs_testers.struct_B_struct_B", "structs_testers struct_B struct_B");

        t.equal(addon.structs_testers({ "prop1": "1", "prop2": "2" }, { "prop1": "1", "prop2": 2 }), "structs_testers.struct_A_struct_B", "structs_testers struct_A struct_B");
        t.equal(addon.structs_testers({ "prop1": "1", "prop2": 2 }, { "prop1": "1", "prop2": "2" }), "structs_testers.struct_B_struct_A", "structs_testers struct_B struct_A");

    });
    t.end();
});





//test multiple parameters
tape('function overload 2 parameter, no defaults', function (t) {
    t.doesNotThrow(function () {

        for (var dt1 of dataTypes) {
            for (var dt2 of dataTypes) {
                t.equal(addon.two_testers(dt1.value, dt2.value), "." + dt1.name + "." + dt2.name, "two_testers " + dt1.name + " " + dt2.name);
            }
        }

    });
    t.end();
});

//test array types, array types overloads, array types defaults, array<struct>, array<array<struct>>
tape('function overload for arrays, no defaults', function (t) {
    t.doesNotThrow(function () {
        t.equal(addon.array_testers(), ".no_parameters_testers", "array_testers()");

        for (var dt of dataTypes) {
            t.equal(addon.array_testers([dt.value]), ".array<" + dt.name + ">", "array_testers array<" + dt.name + ">");
        }

        for (var dt of dataTypes) {
            t.equal(addon.array_testers([[dt.value]]), ".array<array<" + dt.name + ">>", "array_testers array<array<" + dt.name + ">>");
        }

        //test array with multiple types

        for (var dt1 of dataTypes) {
            for (var dt2 of dataTypes) {
                if (dt1.name != dt2.name) {
                    t.equal(addon.array_testers([dt1.value, dt2.value]), ".array", "array_testers array (multiple types - " + dt1.name +"," + dt2.name + ")");
                }
            }
        }

        for (var dt1 of dataTypes) {
            for (var dt2 of dataTypes) {
                if (dt1.name != dt2.name) {
                    t.equal(addon.array_testers([[dt1.value, dt2.value]]), ".array<array>", "array_testers array<array> (multiple types - " + dt1.name + "," + dt2.name + ")");
                }
            }
        }

        for (var dt1 of dataTypes) {
            for (var dt2 of dataTypes) {
                if (dt1 != dt2) {
                    t.equal(addon.array_testers([[dt1.value], dt2.value]), ".array", "array_testers array<array> (multiple types - " + dt1.name + "," + dt2.name + ")");
                }
            }
        }

        //test array with multiple values of the same type

        for (var dt of dataTypes) {
            t.equal(addon.array_testers([dt.value, dt.value]), ".array<" + dt.name + ">", "array_testers array<" + dt.name + ">");
        }

        for (var dt of dataTypes) {
            t.equal(addon.array_testers([[dt.value,dt.value]]), ".array<array<" + dt.name + ">>", "array_testers array<array<" + dt.name + ">>");
        }

    });
    t.end();
});

////TODO: test parameter defaults
//// what to do if multiple overloads have the same parameter, different types with defaults? this is invalid..

