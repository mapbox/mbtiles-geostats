#include "mbtiles-geostats.hpp"
#include <string>
#include <iostream>

/**
 * Create an mbtiles geostats class
 * @class MBTilesGeostats
 * @example
 * var MBTilesGeostats = require('@mapbox/mbtiles-geostats');
 * var mbs = new MBTilesGeostats();
 */

namespace mbtiles_geostats {

inline void CallbackError(std::string message, v8::Local<v8::Function> callback) {
    v8::Local<v8::Value> argv[1] = { Nan::Error(message.c_str()) };
    Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callback, 1, argv);
}

MBTilesGeostats::MBTilesGeostats() {
    // create some sort of map for the stats object (std::map)
    std::string statsMap = "abc";
}

NAN_METHOD(MBTilesGeostats::New)
{
    if (info.IsConstructCall())
    {
        // create new geostats class
        auto* const self = new MBTilesGeostats();
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
 * 
 * buffers.forEach(function(buffer) {
 *   mbs.addBuffer(buffer, function(err) {
 *       if (err) return new Error();
 *   });
 * });
 */
NAN_METHOD(MBTilesGeostats::addBuffer)
{
    // Peek into buffer (decompress), 
    // grab stats 
    // put them to Map object (with some deduping logic)
    // then ditch Buffer



    // This is returning our MBTilesGeostats instance/object
    auto* h = Nan::ObjectWrap::Unwrap<MBTilesGeostats>(info.Holder());  


    if (info.Length() >= 2) {
      // CALLBACK: ensure callback is a function
      v8::Local<v8::Value> callback_val = info[info.Length()-1];
      if (!callback_val->IsFunction()) {
          Nan::ThrowError("last argument must be a callback function");
          return;
      }
      v8::Local<v8::Function> callback = callback_val.As<v8::Function>();

      v8::Local<v8::Value> buffer_val = info[0];

      if (buffer_val->IsNull() ||
        buffer_val->IsUndefined()) {
        CallbackError("first arg 'buffer' must be a Protobuf buffer object", callback);
        return;
      }
      // fast access to the buffer
      v8::Local<v8::Object> buffer = buffer_val->ToObject();

      if (buffer->IsNull() ||
          buffer->IsUndefined() ||
          !node::Buffer::HasInstance(buffer)) {
          CallbackError("first arg 'buffer' must be a Protobuf buffer object", callback);
          return;
      }

      /**
      // "h" is a pointer to the class we defined
      // In order to access the class's vars (ex: statsMap):
      // - you can either use pointer indexing to reach through the pointer to the actual value
      //            OR
      // - you can derefence the pointer
      // No difference in performance

     
      // Dereference example:
      // You have to make the class object modifiable (dont use "const") if you plan to modify a value within it
      MBTilesGeostats & stats = *h; // derefencing (when I want the value out of the pointer)
      
      // not const because we're modifying the maps
      std::string & statsMap = stats.statsMap;
      
      */
      
      // Pointer index example:
      // "->"" is reaching through the pointer to get the actual object val
      std::string & oldString = h->statsMap; // This is a reference to statsMap var, since it's using "&"
      
      // This is a fancy string function that take a buffer and its length,
      // and returns a char pointer/c string (const char*)
      // Beware: This is copying the data
      std::string data(node::Buffer::Data(buffer), node::Buffer::Length(buffer));

      // Reset old string reference to the new value
      oldString = oldString + data; 

    // now try gunzipping buffer
        // if it is already unzipped, go ahead
        // if not, unzip, if it fails, throw an error

      // Return callback
      v8::Local<v8::Value> argv[1] = { Nan::Null() };
      Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callback, 1, argv);

    }
    else {
        return Nan::ThrowTypeError("must provide buffer arg");
    }



}

NAN_METHOD(MBTilesGeostats::getStats)
{

    auto* h = Nan::ObjectWrap::Unwrap<MBTilesGeostats>(info.Holder());

    // taking string in c++, turning it into JS string, and sending it back to JS world
    // Synchronous
    info.GetReturnValue().Set(
        Nan::New<v8::String>(h->statsMap)
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
    SetPrototypeMethod(fnTp, "getStats", getStats);

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
