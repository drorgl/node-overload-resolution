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
        addon = require('../build/Release/overload-tester');
    } catch (e) {
        aoRelease = e;
    }
}

if (addon == null) {
    try {
        addon = require('../build/Debug/overload-tester');
    } catch (e) {
        aoDebug = e;
    }
}

if (addon == null) {
    console.log(aoRelease, aoDebug);
}


for (var i = 0; i < 1; i++) {

    tape('test function without overload resolution', function (t) {
        t.equal(addon.testfunction_no_overload_resolution(), "testfunction_no_overload_resolution", "function without overload returned true");
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
            defaultValue : 1,
            name: "number"
            
        }
        , {
            value: 2 ^ 33,
            defaultValue: 1,
            name: "number"
        }
        , {
            value: true,
            defaultValue: true,
            name: "bool"
        }
        , {
            value: false,
            defaultValue: true,
            name: "bool"
        }
        , {
            value: "1",
            defaultValue: "1",
            name: "string"
        }
        , {
            value: "str",
            defaultValue: "1",
            name: "string"
        }
        , {
            value: new Date(),
            defaultValue: new Date(0),
            name: "date"
        }
        , {
            value: function () { },
            defaultValue: function () { },
            name: "function"
        }
        , {
            value: new Map(),
            defaultValue: new Map(),
            name: "map"
        }
        , {
            value: new Set(),
            defaultValue:new Set(),
            name: "set"
        }
        , {
            value: new Buffer(0),
            defaultValue: new Buffer(0),
            name: "buffer"
        }
        , {
            value: Promise.resolve(0),
            defaultValue:Promise.resolve(0),
            name: "promise"
        }
        , {
            value: new Proxy({}, {}),
            defaultValue: new Proxy({},{}),
            name: "proxy"
        }
        , {
            value: new RegExp("[a-z]"),
            defaultValue: new RegExp("[a-z]"),
            name: "regexp"
        }
        , {
            value: new addon.base_class(),
            defaultValue: new addon.base_class(),
            name: "base_class"
        }
        , {
            value: new addon.derived_class(),
            defaultValue: new addon.base_class(),
            name: "derived_class"
        }
        , {
            value: { "prop1": "val1", "prop2": "val2" },
            defaultValue: { "prop1": "val1", "prop2": "val2" },
            name: "struct_A"
        }
        , {
            value: { "prop1": "val1", "prop2": 2 },
            defaultValue: { "prop1": "val1", "prop2": 2 },
            name: "struct_B"
        }
        , {
            value: [],
            defaultValue: [],
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

    //test constructor overloads
    tape('constructor overload 1 parameter, no defaults', function (t) {
        t.doesNotThrow(function () {
            let ct = new addon.constructor_class_tester();
            t.equal(ct.ctype(), ".no_parameters", "constructor_tester no_params");

            for (var dt of dataTypes) {
                let ct = new addon.constructor_class_tester(dt.value);
                t.equal(ct.ctype(), "." + dt.name, "constructor_testers " + dt.name);
            }

        }, "executing all new addon.constructor_class_tester(...)");
        t.end();
    });


    //test static functions (non-instance)
    tape('static vs instance function overload 1 parameter, no defaults', function (t) {
        t.doesNotThrow(function () {
            let cs = new addon.constructor_class_tester();

            t.equal(addon.constructor_class_tester.static_function(), ".static.no_params", "constructor_class_tester.static_function no_params");
            t.equal(cs.static_function(), ".instance.no_params", "instance constructor_class_tester.static_function no_params");

            for (var dt of dataTypes) {
                t.equal(addon.constructor_class_tester.static_function(dt.value), ".static." + dt.name, "base_class.static_function " + dt.name);
                t.equal(cs.static_function(dt.value), ".instance." + dt.name, "instance constructor_class_tester.static_function " + dt.name);
            }

        },"executing all constructor_class_tester.static_function(...) instance and static");
        t.end();
    });




    tape('function overload 1 parameter, no defaults', function (t) {
        t.doesNotThrow(function () {
            t.equal(addon.number_testers(), ".no_parameters", "number_testers no_params");

            for (var dt of dataTypes) {
                t.equal(addon.number_testers(dt.value), "." + dt.name, "number_testers " + dt.name);
            }

        });
        t.end();
    });



    //test member functions

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

    //test structs, succes, fail, multiple
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
                        t.equal(addon.array_testers([dt1.value, dt2.value]), ".array", "array_testers array (multiple types - " + dt1.name + "," + dt2.name + ")");
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
                t.equal(addon.array_testers([[dt.value, dt.value]]), ".array<array<" + dt.name + ">>", "array_testers array<array<" + dt.name + ">>");
            }

        });
        t.end();
    });

    //test parameter defaults, test the default value is passed to function, test that passed parameter is overwriting the default value
    tape('function overload 1 parameter, 2nd parameter default', function (t) {
        t.doesNotThrow(function () {
            for (var dt1 of dataTypes) {
                var default_func = new Function("addon, val", "return addon.default_testers_" + dt1.name + "(val)");
                var default_func_2params = new Function("addon, val1,val2", "return addon.default_testers_" + dt1.name + "(val1,val2)");
                t.equal(default_func(addon), ".no_params", "default testers " + dt1.name + ", no parameters");
                for (var dt2 of dataTypes) {
                    t.equal(default_func(addon, dt2.value), "." + dt2.name + "(" + JSON.stringify(dt2.value) + ")." + dt1.name + "(" + JSON.stringify(dt1.defaultValue) + ")", "default testers " + dt2.name + ", default (2nd parameter):" + dt1.name);
                    t.equal(default_func_2params(addon, dt2.value,dt1.value), "." + dt2.name + "(" + JSON.stringify(dt2.value) + ")." + dt1.name + "(" + JSON.stringify(dt1.value) + ")", "default testers " + dt2.name + ", passed 2nd parameter (instead of default):" + dt1.name);
                }
            }

        });
        t.end();
    });

}