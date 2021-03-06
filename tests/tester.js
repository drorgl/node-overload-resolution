//var SegfaultHandler = require('segfault-handler');
//SegfaultHandler.registerHandler("crash.log");

console.log("starting");
var tape = require("tape");
var chalk = require("chalk");

var versionGroup = process.version.match(/^v(\d+\.)?(\d+\.)?(\*|\d+)$/);
var nodeVersion = [Number(versionGroup[1]), Number(versionGroup)[2], Number(versionGroup)[3]].join(".");

//http://stackoverflow.com/questions/6832596/how-to-compare-software-version-number-using-js-only-number
function isVersionValid(b) {
    var a = nodeVersion;
    if (a === b) {
        return true;
    }

    var a_components = a.split(".");
    var b_components = b.split(".");

    var len = Math.min(a_components.length, b_components.length);

    // loop while the components are equal
    for (var i = 0; i < len; i++) {
        // A bigger than B
        if (parseInt(a_components[i]) > parseInt(b_components[i])) {
            return true;
        }

        // B bigger than A
        if (parseInt(a_components[i]) < parseInt(b_components[i])) {
            console.log("not valid", a, b);
            return false;
        }
    }

    // If one's a prefix of the other, the longer one is greater.
    if (a_components.length > b_components.length) {
        return true;
    }

    if (a_components.length < b_components.length) {
        console.log("not valid", a, b);
        return false;
    }

    // Otherwise they are the same.
    return true;
}


var proxy = global.Proxy || null;
if (!isVersionValid('6')) {
    proxy = function () { };
}
Proxy = proxy;

var errorColor = chalk.red.bold;
var okColor = chalk.green.bold;
var level = 0;

function logger(module, level, message) {
    //if (level < 99) {
    //console.log(module, level, message);
    //}
}
function tablevel() {
    var retval = "";
    for (var i = 0; i < level; i++) {
        retval += "\t";
    }
    return retval;
}

var results = {
    passed: 0,
    failed: 0
};

var tapestream = tape.createStream({ objectMode: true });

tapestream.on('data', function (row) {
    if (typeof row == typeof "") {
        console.log(tablevel() + row);
    }
    else if (row.type == "end") {
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
            console.log(tablevel() + errorColor("\t expected: %s actual: %s"), row.expected, row.actual);
        }
    }
    //console.log(JSON.stringify(row))
});

tapestream.on('end', function (r) {
    console.log("passed:", results.passed);
    console.log("failed:", results.failed);
});



function showObject(tobj) {
    var objstr = JSON.stringify(tobj, null, '\t');
    var showObjectContents = false;
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
    console.log("failed to load addon");
    console.log("release:", aoRelease);
    console.log("debug:", aoDebug);
}

function getLogLevel(logLevel) {
    switch (logLevel) {
        case 0: return "TRACE";
        case 1: return "DEBUG";
        case 2: return "INFO";
        case 3: return "WARN";
        case 4: return "ERROR";
        case 5: return "FATAL";
    }
    return "unknown";
}

addon.log_level = 2;

addon.RegisterLogger(function (module, logLevel, message) {
    console.log(module, getLogLevel(logLevel), message);
});

addon.Flush();

for (var i = 0; i < 1; i++) {

    //tape('test function without overload resolution', function (t) {
    //    t.equal(addon.testfunction_no_overload_resolution(), "testfunction_no_overload_resolution", "function without overload returned true");
    //    t.end();
    //});
    //addon.Flush();

    //tape('base_function on base_class', function (t) {
    //    var bc = new addon.base_class();
    //    t.ok(bc, "base class created successfully");
    //    t.ok(bc.base_function(), "function called on base_class");
    //    t.end();
    //});
    //addon.Flush();

    //tape('function on derived class', function (t) {
    //    var dc = new addon.derived_class();
    //    t.ok(dc, "derived class created successfully");
    //    t.ok(dc.derived_function(), "function called on derived_class");
    //    t.ok(dc.this_check(), "function got This()");
    //    dc.this_check(function (err, res) {
    //        if (err) {
    //            t.fail("This() doesn't work in async");
    //        }
    //        t.ok(res, "async function got This()");
    //        t.end();
    //    });

    //});
    //addon.Flush();

    //tape('base_class.base_function  test function on derived class', function (t) {
    //    var dc = new addon.derived_class();
    //    t.ok(dc, "derived class created successfully");
    //    t.ok(dc.base_function(), "base_class.base_function function called on derived_class");
    //    t.end();
    //});
    //addon.Flush();


    var dataTypes = [
        {
            minNodeVersion: '0',
            value_converter_exists: true,
            value: 1,
            defaultValue: 1,
            name: "number"

        }
        , {
            minNodeVersion: '0',
            value_converter_exists: true,
            value: 2 ^ 33,
            defaultValue: 1,
            name: "number"
        }
        , {
            minNodeVersion: '0',
            value_converter_exists: true,
            value: true,
            defaultValue: true,
            name: "bool"
        }
        , {
            minNodeVersion: '0',
            value_converter_exists: true,
            value: false,
            defaultValue: true,
            name: "bool"
        }
        , {
            minNodeVersion: '0',
            value_converter_exists: true,
            value: "1",
            defaultValue: "1",
            name: "string"
        }
        , {
            minNodeVersion: '0',
            value_converter_exists: true,
            value: "str",
            defaultValue: "1",
            name: "string"
        }
        , {
            minNodeVersion: '0',
            value_converter_exists: true,
            value: new Date(1234 * 1000),
            defaultValue: new Date(0),
            name: "date"
        }
        , {
            minNodeVersion: '0',
            value_converter_exists: true,
            value: function () { console.log("value function was called", arguments); },
            defaultValue: function () { console.log("defaultValue function was called", arguments); },
            name: "function"
        }
        , {
            minNodeVersion: '4',
            value_converter_exists: true,
            value: new Map([["s1", 1], ["s2", 2]]),
            defaultValue: new Map([["s1", 1], ["s2", 2]]),
            name: "map"
        }
        , {
            minNodeVersion: '4',
            value_converter_exists: true,
            value: new Set(["k1", "k2"]),
            defaultValue: new Set(["k1", "k2"]),
            name: "set"
        }
        , {
            minNodeVersion: '0',
            value_converter_exists: true,
            value: new Buffer([1, 2, 3]),
            defaultValue: new Buffer([]),
            name: "buffer"
        }
        , {
            minNodeVersion: '0.11',
            value_converter_exists: false,
            value: Promise.resolve(0),
            defaultValue: Promise.resolve(0),
            name: "promise"
        }
        , {
            minNodeVersion: '6',
            value_converter_exists: false,
            value: new Proxy({}, {}),
            defaultValue: new Proxy({}, {}),
            name: "proxy"
        }
        , {
            minNodeVersion: '0',
            value_converter_exists: false,
            value: new RegExp("[a-z]"),
            defaultValue: new RegExp("[a-z]"),
            name: "regexp"
        }
        , {
            minNodeVersion: '0',
            value_converter_exists: true,
            value: new addon.base_class(),
            defaultValue: new addon.base_class(),
            name: "base_class"
        }
        , {
            minNodeVersion: '0',
            value_converter_exists: true,
            value: new addon.derived_class(),
            defaultValue: new addon.base_class(),
            name: "derived_class"
        }
        , {
            minNodeVersion: '0',
            value_converter_exists: true,
            value: { "prop1": "val1", "prop2": "val2" },
            defaultValue: { "prop1": "val1", "prop2": "val2" },
            name: "struct_A"
        }
        , {
            minNodeVersion: '0',
            value_converter_exists: true,
            value: { "prop1": "val1", "prop2": 2 },
            defaultValue: { "prop1": "val1", "prop2": 2 },
            name: "struct_B"
        }
        , {
            minNodeVersion: '0',
            value_converter_exists: true,
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
            var ct = new addon.constructor_class_tester();
            t.equal(ct.ctype(), ".no_parameters", "constructor_tester no_params");

            dataTypes.forEach(function (dt) {
                if (!isVersionValid(dt.minNodeVersion)) {
                    return;
                }
                var ct = new addon.constructor_class_tester(dt.value);
                t.equal(ct.ctype(), "." + dt.name, "constructor_testers " + dt.name);
                addon.Flush();
            });

        }, "executing all new addon.constructor_class_tester(...)");
        addon.Flush();
        t.end();
    });


    //test static functions (non-instance)
    tape('static vs instance function overload 1 parameter, no defaults', function (t) {
        t.doesNotThrow(function () {
            var cs = new addon.constructor_class_tester();

            t.equal(addon.constructor_class_tester.static_function(), ".static.no_params", "constructor_class_tester.static_function no_params");
            t.equal(cs.static_function(), ".instance.no_params", "instance constructor_class_tester.static_function no_params");

            dataTypes.forEach(function (dt) {
                if (!isVersionValid(dt.minNodeVersion)) {
                    return;
                }
                t.equal(addon.constructor_class_tester.static_function(dt.value), ".static." + dt.name, "base_class.static_function " + dt.name);
                t.equal(cs.static_function(dt.value), ".instance." + dt.name, "instance constructor_class_tester.static_function " + dt.name);
                addon.Flush();
            });

        }, "executing all constructor_class_tester.static_function(...) instance and static");
        addon.Flush();
        t.end();
    });




    tape('function overload 1 parameter, no defaults', function (t) {
        t.doesNotThrow(function () {
            t.equal(addon.number_testers(), ".no_parameters", "number_testers no_params");

            dataTypes.forEach(function (dt) {
                if (!isVersionValid(dt.minNodeVersion)) {
                    return
                }
                t.equal(addon.number_testers(dt.value), "." + dt.name, "number_testers " + dt.name);
                addon.Flush();
            });

        });
        addon.Flush();
        t.end();
    });



    //test member functions

    tape('member function overload 1 parameter, no defaults', function (t) {
        t.doesNotThrow(function () {
            var bc = new addon.base_class();

            t.equal(bc.base_function(), "base_class.base_function.no_parameters_testers", "no_params");

            dataTypes.forEach(function (dt) {
                if (!isVersionValid(dt.minNodeVersion)) {
                    return;
                }
                t.equal(bc.base_function(dt.value), "base_class.base_function." + dt.name, "number_testers " + dt.name);
                addon.Flush();
            });

        });
        addon.Flush();
        t.end();
    });

    //TODO: test class inheritance chain calls
    //e.g. derived class overload implements function x and base class overload implement function x, which will be called when and on which parameters? 
    //overload should be across class graph, otherwise no true inheritance will be implemented.
    //also, what happens when calling function inherited from base but not overloaded in derived?

    tape('derived member function overload 1 parameter, no defaults', function (t) {
        t.doesNotThrow(function () {
            var bc = new addon.derived_class();

            t.equal(bc.base_function(), "derived_class.base_function.no_parameters_testers", "no_params");

            dataTypes.forEach(function (dt) {
                if (!isVersionValid(dt.minNodeVersion)) {
                    return;
                }
                t.equal(bc.base_function(dt.value), "derived_class.base_function." + dt.name, "derived_class.base_function " + dt.name);
                addon.Flush();
            });

        });
        addon.Flush();
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
        addon.Flush();
        t.end();
    });





    //test multiple parameters
    tape('function overload 2 parameter, no defaults', function (t) {
        t.doesNotThrow(function () {

            dataTypes.forEach(function (dt1) {
                if (!isVersionValid(dt1.minNodeVersion)) {
                    return;
                }
                dataTypes.forEach(function (dt2) {
                    if (!isVersionValid(dt2.minNodeVersion)) {
                        return;
                    }
                    t.equal(addon.two_testers(dt1.value, dt2.value), "." + dt1.name + "." + dt2.name, "two_testers " + dt1.name + " " + dt2.name);
                    addon.Flush();
                });
            });

        });
        addon.Flush();
        t.end();
    });

    tape('function overload for empty array', function (t) {
        t.doesNotThrow(function () {
            t.equal(addon.array_fallback_testers([]), '.array<int>', "array_fallback_testers([])");
            t.equal(addon.array_fallback_testers([1]), '.array<int>', "array_fallback_testers([1])");
            t.equal(addon.array_fallback_testers(["1"]), '.array<int>', "array_fallback_testers([1])");
            t.throws(function () {
                t.notEqual(addon.array_fallback_testers([["1"]]), '.array<int>', "array_fallback_testers([1])");
            });
            t.end();
        });
    });

    //test array types, array types overloads, array types defaults, array<struct>, array<array<struct>>
    tape('function overload for arrays, no defaults', function (t) {
        t.doesNotThrow(function () {
            t.equal(addon.array_testers(), ".no_parameters_testers", "array_testers()");

            dataTypes.forEach(function (dt) {
                if (!isVersionValid(dt.minNodeVersion)) {
                    return;
                }
                t.equal(addon.array_testers([dt.value]), ".array<" + dt.name + ">", "array_testers array<" + dt.name + ">");
                addon.Flush();
            });

            dataTypes.forEach(function (dt) {
                if (!isVersionValid(dt.minNodeVersion)) {
                    return;
                }
                t.equal(addon.array_testers([[dt.value]]), ".array<array<" + dt.name + ">>", "array_testers array<array<" + dt.name + ">>");
                addon.Flush();
            });

            //test array with multiple types

            dataTypes.forEach(function (dt1) {
                if (!isVersionValid(dt1.minNodeVersion)) {
                    return;
                }
                dataTypes.forEach(function (dt2) {
                    if (!isVersionValid(dt2.minNodeVersion)) {
                        return;
                    }
                    if (dt1.name != dt2.name) {
                        t.equal(addon.array_testers([dt1.value, dt2.value]), ".array", "array_testers array (multiple types - " + dt1.name + "," + dt2.name + ")");
                        addon.Flush();
                    }
                });
            });

            dataTypes.forEach(function (dt1) {
                if (!isVersionValid(dt1.minNodeVersion)) {
                    return;
                }
                dataTypes.forEach(function (dt2) {
                    if (!isVersionValid(dt2.minNodeVersion)) {
                        return;
                    }
                    if (dt1.name != dt2.name) {
                        t.equal(addon.array_testers([[dt1.value, dt2.value]]), ".array<array>", "array_testers array<array> (multiple types - " + dt1.name + "," + dt2.name + ")");
                        addon.Flush();
                    }
                });
            });

            dataTypes.forEach(function (dt1) {
                if (!isVersionValid(dt1.minNodeVersion)) {
                    return;
                }
                dataTypes.forEach(function (dt2) {
                    if (!isVersionValid(dt2.minNodeVersion)) {
                        return;
                    }
                    if (dt1 != dt2) {
                        t.equal(addon.array_testers([[dt1.value], dt2.value]), ".array", "array_testers array<array> (multiple types - " + dt1.name + "," + dt2.name + ")");
                        addon.Flush();
                    }
                });
            });

            //test array with multiple values of the same type

            dataTypes.forEach(function (dt) {
                if (!isVersionValid(dt.minNodeVersion)) {
                    return;
                }
                t.equal(addon.array_testers([dt.value, dt.value]), ".array<" + dt.name + ">", "array_testers array<" + dt.name + ">");
                addon.Flush();
            });

            dataTypes.forEach(function (dt) {
                if (!isVersionValid(dt.minNodeVersion)) {
                    return;
                }
                t.equal(addon.array_testers([[dt.value, dt.value]]), ".array<array<" + dt.name + ">>", "array_testers array<array<" + dt.name + ">>");
                addon.Flush();
            });

        });
        addon.Flush();
        t.end();
    });

    //test parameter defaults, test the default value is passed to function, test that passed parameter is overwriting the default value
    tape('function overload 1 parameter, 2nd parameter default', function (t) {
        t.doesNotThrow(function () {
            dataTypes.forEach(function (dt1) {
                if (!isVersionValid(dt1.minNodeVersion)) {
                    return;
                }
                var default_func_no_params = new Function("addon", "return addon.default_testers_" + dt1.name + "()");
                var default_func = new Function("addon, val", "return addon.default_testers_" + dt1.name + "(val)");
                var default_func_2params = new Function("addon, val1,val2", "return addon.default_testers_" + dt1.name + "(val1,val2)");
                t.equal(default_func_no_params(addon), ".no_params", "default testers " + dt1.name + ", no parameters");
                dataTypes.forEach(function (dt2) {
                    if (!isVersionValid(dt2.minNodeVersion)) {
                        return;
                    }
                    t.equal(default_func(addon, dt2.value), "." + dt2.name + "(" + JSON.stringify(dt2.value) + ")." + dt1.name + "(" + JSON.stringify(dt1.defaultValue) + ")", "default testers " + dt2.name + ", default (2nd parameter):" + dt1.name);
                    t.equal(default_func_2params(addon, dt2.value, dt1.value), "." + dt2.name + "(" + JSON.stringify(dt2.value) + ")." + dt1.name + "(" + JSON.stringify(dt1.value) + ")", "default testers " + dt2.name + ", passed 2nd parameter (instead of default):" + dt1.name);
                    addon.Flush();
                });
            });

        });
        addon.Flush();
        t.end();
    });


    tape('function overload 1 parameter, no defaults, with value converter', function (t) {
        t.doesNotThrow(function () {
            t.equal(addon.value_converter(), ".no_parameters", "value_converter no_params");

            dataTypes.forEach(function (dt) {
                if (!isVersionValid(dt.minNodeVersion)) {
                    return;
                }
                if (!dt.value_converter_exists) {
                    t.comment("value converter doesn't exist for " + dt.name + ", skipping");
                    return;
                }
                t.doesNotThrow(function () {
                    var c_result = addon.value_converter(dt.value);
                    if (c_result.hasOwnProperty('value')) {
                        //special return_struct

                        //check if callback, if so, call it
                        if (c_result.type == "function") {
                            console.log("calling");
                            c_result.value("c_result");
                            dt.value("dt");
                        }

                        //string value for tests
                        c_result = "." + c_result.type + "(" + JSON.stringify(c_result.value) + ")";


                    }
                    t.equal(c_result, "." + dt.name + "(" + JSON.stringify(dt.value) + ")", "value_converter " + dt.name);
                    addon.Flush();
                }, "value converter executed successfully for " + dt.name);
            });

        });
        addon.Flush();
        t.end();
    });




    tape('async function overload 1 parameter, no defaults, with value converter', function (t) {
        var executions = 0;
        t.doesNotThrow(function () {
            t.equal(addon.value_converter(), ".no_parameters", "value_converter no_params");

            dataTypes.forEach(function (dt) {
                if (!isVersionValid(dt.minNodeVersion)) {
                    return;
                }
                if (!dt.value_converter_exists) {
                    t.comment("value converter doesn't exist for " + dt.name + ", skipping");
                    return;
                }

                t.doesNotThrow(function () {
                    executions++;
                    (function () {
                        var dtlocal = dt;
                        var tlocal = t;
                        addon.value_converter(dt.value, function (err, c_result) {
                            if (err) {
                                tlocal.error(err, "while executing async value_converter " + dtlocal.name);
                                executions--;
                                return;
                            }
                            if (c_result.hasOwnProperty('value')) {
                                //special return_struct

                                //check if callback, if so, call it
                                if (c_result.type == "function") {
                                    console.log("calling");
                                    c_result.value("c_result");
                                    dtlocal.value("dt");
                                }

                                //string value for tests
                                c_result = "." + c_result.type + "(" + JSON.stringify(c_result.value) + ")";


                            }
                            tlocal.equal(c_result, "." + dtlocal.name + "(" + JSON.stringify(dtlocal.value) + ")", "value_converter " + dtlocal.name);
                            executions--;
                        });
                        addon.Flush();
                    })();

                }, "value converter executed successfully for " + dt.name);
            });

        });
        var shouldEnd = function () {
            if (executions == 0) {
                addon.Flush();
                t.end();
            } else {
                setTimeout(shouldEnd, 1);
            }
        }
        shouldEnd();

    });


    tape("namespace and class wrappers", function (t) {
        //t.class_constructs
        t.equals(addon.standalone_function_construct(), "standalone_function_construct", "standalone function construct");

        t.equals(addon.namespace_construct.nc_standalone_function_construct(), "nc_standalone_function_construct_nc", "nc standalone function construct 1");
        t.equals(addon.namespace_construct.standalone_function_construct_nc(), "standalone_function_construct_nc", "nc standalone function construct 2");

        t.equals(addon.class_constructs.test_static(), "test_static", "test static");

        var cc = new addon.class_constructs();
        t.equals(cc.test_member(), "test_member", "test member");

        t.equal(cc.test_property, "preset_value", "test member property preset value");
        t.doesNotThrow(function () { cc.test_property = "new_value"; }, "set member property value");
        t.equal(cc.test_property, "new_value", "test member property set value");

        t.ok(cc[10] == null, "check numeric indexer position 10 is empty");
        t.doesNotThrow(function () { cc[10] = "text_value"; }, "assign numeric indexer position 10 to 'text_value'");
        t.equal(cc[10], "text_value", "check numeric indexer position 10 is 'text_value'");

        t.ok(cc["string_key"] == null, "check numeric indexer name 'string_key' is empty");
        t.doesNotThrow(function () { cc["string_key"] = "text_value"; }, "assign numeric indexer name 'string_key' to 'text_value'");
        t.equal(cc[10], "text_value", "check numeric indexer name 'string_key' is 'text_value'");

        t.ok(addon.test_enum, "test enum exists");
        t.equal(addon.test_enum.e1, 1, "test_enum.e1 == 1");
        t.equal(addon.test_enum.e2, 2, "test_enum.e2 == 2");

        t.end();
    });

}


tape('async function callback from stand alone thread', function (t) {
    var counter = 5;
    t.doesNotThrow(function () {
        addon.async_callback(counter, function () {
            counter--;
        });
    });

    var shouldEnd = function () {
        if (counter == 0) {
            t.pass("async called 5 times");
            t.end();
        } else {
            setTimeout(shouldEnd, 1);
        }
    }
    shouldEnd();
});

//TODO: 
//add make_param<T>("name","type",default T) test
//add instantiate one type from another type test

