#include <node.h>
#include "point.h"
#include "latlng.h"
#include "cellid.h"


using namespace v8;
namespace s2geo{
void InitAll(Local<Object> exports) {
    Point::Init(exports);
    LatLng::Init(exports);
    CellId::Init(exports);
}

NODE_MODULE(NativeExtension, InitAll)
}