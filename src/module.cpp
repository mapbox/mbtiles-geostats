#include "mbtiles-geostats.hpp"
#include <nan.h>

static void init(v8::Local<v8::Object> target)
{
    mbtiles_geostats::MBTilesGeostats::Init(target);
}

NODE_MODULE(module, init) // NOLINT
