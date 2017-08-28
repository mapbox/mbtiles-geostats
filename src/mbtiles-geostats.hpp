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

    MBTilesGeostats(std::string&& name);

  private:
    std::string _name;
    int _number_of_buffers = 0;
};
}
