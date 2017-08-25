#include "mbtiles-geostats.hpp"

/**
 * Create an mbtiles geostats class
 * @class MBTilesGeostats
 * @example
 * var MBTilesGeostats = require('@mapbox/mbtiles-geostats');
 * var mbs = new MBTilesGeostats();
 */

namespace mbtiles_geostats {

MBTilesGeostats::MBTilesGeostats(std::string&& name) : name_(std::move(name)) {}

NAN_METHOD(MBTilesGeostats::New)
{
    if (info.IsConstructCall())
    {
        // create some sort of map for the stats object
        Nan::Utf8String utf8_value(info[0]);
        int len = utf8_value.length();
        std::string name(*utf8_value, len);

        // create new geostats class, which will have ownerhip of this map object
        auto* const self = new MBTilesGeostats(std::move(name));
        self->Wrap(info.This());

        info.GetReturnValue().Set(info.This());
    }
    else
    {
        return Nan::ThrowTypeError("Cannot call constructor as function, you need to use 'new' keyword");
    }
}

/**
 * Add a buffer to the stats object
 *
 * @name addBuffer
 * @memberof MBTilesGeostats
 * @param {Buffer} buffer - a gzipped buffer representing a Mapbox Vector Tile
 * @example
 * var MBTilesGeostats = require('@mapbox/mbtiles-geostats');
 * var mbs = new MBTilesGeostats();
 * buffers.forEach(function(buffer) {
 *   mbs.addBuffer(buffer);
 * });
 */
NAN_METHOD(MBTilesGeostats::addBuffer)
{
    /**
     * Note: a HandleScope is automatically included inside NAN_METHOD. See the
     * docs at NAN that say:
     * 'Note that an implicit HandleScope is created for you on
     * JavaScript-accessible methods so you do not need to insert one yourself.'
     * at
     * https://github.com/nodejs/nan/blob/2dfc5c2d19c8066903a19ced6a72c06d2c825dec/doc/scopes.md#nanhandlescope

     * "What is node::ObjectWrap???" The short version is that node::ObjectWrap
     * and wrapping/unwrapping objects
     * is the somewhat clumsy way it is possible to bind Node and C++. The main
     * points to remember:
     *   - To access a class instance inside a C++ static method, you must unwrap
     * the object.
     *   - The C++ methods must be static to make them available at startup across
     * the language boundary (JS <-> C++).
     */
    auto* h = Nan::ObjectWrap::Unwrap<MBTilesGeostats>(info.Holder());

    // "info" comes from the NAN_METHOD macro, which returns differently
    // according to the version of node
    info.GetReturnValue().Set(
        Nan::New<v8::String>("...initialized an object..." + h->name_)
            .ToLocalChecked());
}

// This is a Singleton, which is a general programming design concept for
// creating an instance once within a process.
Nan::Persistent<v8::Function>& MBTilesGeostats::create_once()
{
    static Nan::Persistent<v8::Function> init;
    return init;
}

void MBTilesGeostats::Init(v8::Local<v8::Object> target)
{
    // A handlescope is needed so that v8 objects created in the local memory
    // space (this function in this case)
    // are cleaned up when the function is done running (and the handlescope is
    // destroyed)
    // Fun trivia: forgetting a handlescope is one of the most common causes of
    // memory leaks in node.js core
    // https://www.joyent.com/blog/walmart-node-js-memory-leak
    Nan::HandleScope scope;

    // This is saying:
    // "Node, please allocate a new Javascript string object
    // inside the V8 local memory space, with the value 'MBTilesGeostats' "
    v8::Local<v8::String> whoami = Nan::New("MBTilesGeostats").ToLocalChecked();

    // Officially create the MBTilesGeostats
    auto fnTp = Nan::New<v8::FunctionTemplate>(
        MBTilesGeostats::New); // Passing the MBTilesGeostats::New method above
    fnTp->InstanceTemplate()->SetInternalFieldCount(
        1);                     // It's 1 when holding the ObjectWrap itself and nothing else
    fnTp->SetClassName(whoami); // Passing the Javascript string object above

    // Add custom methods here.
    // This is how hello() is exposed as part of MBTilesGeostats.
    // This line is attaching the "hello" method to a JavaScript function
    // prototype.
    // "hello" is therefore like a property of the fnTp object
    // ex: console.log(MBTilesGeostats.hello) --> [Function: hello]
    SetPrototypeMethod(fnTp, "addBuffer", addBuffer);

    // Create an unique instance of the MBTilesGeostats function template,
    // then set this unique instance to the target
    const auto fn = Nan::GetFunction(fnTp).ToLocalChecked();
    create_once().Reset(fn); // calls the static &MBTilesGeostats::create_once method
                             // above. This ensures the instructions in this Init
                             // function are retained in memory even after this
                             // code block ends.
    Nan::Set(target, whoami, fn);
}

} // namespace object_sync
