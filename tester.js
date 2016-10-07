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
            console.log(tablevel() + okColor("%d. \t %s \t %s"), row.id, row.ok, row.name);
            if (row.operator == "throws" && row.actual != undefined) {
                console.log(tablevel() + okColor(" threw: %s"), row.actual);
            }
        }
        else {
            console.log(tablevel() + errorColor("%d. \t %s \t %s"), row.id, row.ok, row.name);
            console.log(tablevel() + errorColor("\t %s"), row.actual);
        }
    }
    //row.
    //console.log(JSON.stringify(row))
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
        addon = require('./build/Release/tester');
    } catch (e) {
        aoRelease = e;
    }
}

if (addon == null) {
    try {
        addon = require('./build/Debug/tester');
    } catch (e) {
        aoDebug = e;
    }
}

//console.log("addon", addon);

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


tape('function overload 1 parameter, no defaults', function (t) {
    t.doesNotThrow(function () {
        t.equal(addon.number_testers(1), ".number_testers", "number_testers number");
        t.equal(addon.number_testers(1), ".number_testers", "number_testers number");
        t.equal(addon.number_testers(1.1), ".number_testers", "number_testers float");
        t.equal(addon.number_testers(2 ^ 33), ".number_testers", "number_testers long");
        
        t.equal(addon.number_testers("1"), ".string_testers", "number_testers string");
        
        t.equal(addon.number_testers(true), ".bool_testers", "number_testers boolean");
        
        t.equal(addon.number_testers(new Date()), ".date_testers", "number_testers date");
        
        t.equal(addon.number_testers(function () { }), ".function_testers", "number_testers function");
        
        t.equal(addon.number_testers(new Buffer(0)), ".buffer_testers", "number_testers buffer");
        
        t.equal(addon.number_testers(new Map()), ".map_testers", "number_testers map");
        
        t.equal(addon.number_testers(new Set()), ".set_testers", "number_testers set");
        
        t.equal(addon.number_testers(Promise.resolve(0)), ".promise_testers", "number_testers promise");
        
        t.equal(addon.number_testers(new Proxy({}, {})), ".proxy_testers", "number_testers promise");
        
        t.equal(addon.number_testers(new RegExp("[a-z]")), ".regexp_testers", "number_testers regexp");

        t.equal(addon.number_testers(new addon.base_class()), ".base_class_testers", "number_testers base_class");

        t.equal(addon.number_testers(new addon.derived_class()), ".derived_class_testers", "number_testers derived_class");
        
        t.equal(addon.number_testers({ "prop1": "val1", "prop2": "val2" }), ".struct_A_testers", "number_testers propstruct");
        
        t.equal(addon.number_testers(), ".no_parameters_testers", "number_testers no_params");
    });
    t.end();
});



//TODO: test member/static functions

tape('member function overload 1 parameter, no defaults', function (t) {
    t.doesNotThrow(function () {
        let bc = new addon.base_class();
        t.equal(bc.base_function(1), "base_class.base_function.number", "number");
        t.equal(bc.base_function(1), "base_class.base_function.number", "number");
        t.equal(bc.base_function(1.1), "base_class.base_function.number", "number double");
        t.equal(bc.base_function(2 ^ 33), "base_class.base_function.number", "number long");
        t.equal(bc.base_function("1"), "base_class.base_function.string", "string");
        t.equal(bc.base_function(true), "base_class.base_function.bool", "boolean");
        t.equal(bc.base_function(new Date()), "base_class.base_function.date", "date");
        t.equal(bc.base_function(function () { }), "base_class.base_function.function", "function");
        t.equal(bc.base_function(new Buffer(0)), "base_class.base_function.buffer", "buffer");
        t.equal(bc.base_function(new Map()), "base_class.base_function.map", "map");
        t.equal(bc.base_function(new Set()), "base_class.base_function.set", "set");
        t.equal(bc.base_function(Promise.resolve(0)), "base_class.base_function.promise", "promise");
        t.equal(bc.base_function(new Proxy({}, {})), "base_class.base_function.proxy", "promise");
        t.equal(bc.base_function(new RegExp("[a-z]")), "base_class.base_function.regexp", "regexp");
        t.equal(bc.base_function(new addon.base_class()), "base_class.base_function.base_class", "base_class");
        t.equal(bc.base_function(new addon.derived_class()), "base_class.base_function.derived_class", "derived_class");
        t.equal(bc.base_function({ "prop1": "val1", "prop2": "val2" }), "base_class.base_function.struct_A", "propstruct");
        t.equal(bc.base_function(), "base_class.base_function.no_parameters_testers", "no_params");
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
        t.equal(bc.base_function(1), "derived_class.base_function.number", "number");
        t.equal(bc.base_function(1), "derived_class.base_function.number", "number");
        t.equal(bc.base_function(1.1), "derived_class.base_function.number", "number double");
        t.equal(bc.base_function(2 ^ 33), "derived_class.base_function.number", "number long");
        t.equal(bc.base_function("1"), "derived_class.base_function.string", "string");
        t.equal(bc.base_function(true), "derived_class.base_function.bool", "boolean");
        t.equal(bc.base_function(new Date()), "derived_class.base_function.date", "date");
        t.equal(bc.base_function(function () { }), "derived_class.base_function.function", "function");
        t.equal(bc.base_function(new Buffer(0)), "derived_class.base_function.buffer", "buffer");
        t.equal(bc.base_function(new Map()), "derived_class.base_function.map", "map");
        t.equal(bc.base_function(new Set()), "derived_class.base_function.set", "set");
        t.equal(bc.base_function(Promise.resolve(0)), "derived_class.base_function.promise", "promise");
        t.equal(bc.base_function(new Proxy({}, {})), "derived_class.base_function.proxy", "promise");
        t.equal(bc.base_function(new RegExp("[a-z]")), "derived_class.base_function.regexp", "regexp");
        t.equal(bc.base_function(new addon.base_class()), "derived_class.base_function.base_class", "base_class");
        t.equal(bc.base_function(new addon.derived_class()), "derived_class.base_function.derived_class", "derived_class");
        t.equal(bc.base_function({ "prop1": "val1", "prop2": "val2" }), "derived_class.base_function.struct_A", "propstruct");
        t.equal(bc.base_function(), "derived_class.base_function.no_parameters_testers", "no_params");
    });
    t.end();
});

//TODO: test structs, succes, fail, multiple


//TODO: test multiple parameters