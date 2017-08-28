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

    // constructor
    MBTilesGeostats(std::string statsMap);

  private:
  	dedupe();
  	// Will this tie to the MBTilesGeostats instance? 
  	// Or does the statsMap have to more expliclty be tied to the instance in cpp?
  	// Also, we'd would NOT want it to be static, so that it is tied to an instance of the class
  	std::string statsMap = "abc"; 
    std::string _name;
    int _number_of_buffers = 0;
};
}
