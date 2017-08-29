#pragma once
#include <nan.h>

namespace mbtiles_geostats {

class MBTilesGeostats : public Nan::ObjectWrap
{
  public:
    static void Init(v8::Local<v8::Object> target);
    static NAN_METHOD(New);
    static Nan::Persistent<v8::Function>& create_once();
    static NAN_METHOD(addBuffer);
    static NAN_METHOD(getStats);

    // constructor
    MBTilesGeostats();

  private:
  	// We dont want it to be static since we need it to be tied to an instance of the class
  	// See: https://github.com/mapbox/cpp/blob/master/glossary.md#static-member
  	std::string statsMap = "abc"; 
    std::string _name;
};
}
