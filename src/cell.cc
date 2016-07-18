#include <node.h>
#include <nan.h>
#include "node_object_wrap.h"           // for Nan::Nan::ObjectWrap
#include "v8.h"                         // for Handle, String, Integer, etc

#include "s2.h"
#include "s2cell.h"
#include "s2cellid.h"
#include "s2latlng.h"
#include "cell.h"

NAN_METHOD(GenerateCellId) {
    bool bad_args = false;

    if (info[0]->IsUndefined()) bad_args = true;
    if (info[1]->IsUndefined()) bad_args = true;

    if (bad_args) {
        Nan::ThrowError("Invalid arguments: function requires three arguments, two doubles and an integer.");
        return;
    }

    double lat = Nan::To<double>(info[0]).FromJust();
    double lng = Nan::To<double>(info[1]).FromJust();
    uint32_t level = Nan::To<uint32_t>(info[2]).FromJust();

    S2CellId id(S2CellId::FromLatLng(S2LatLng::FromDegrees(lat, lng)));
    S2CellId ret = id.parent(level);

    auto buf = Nan::CopyBuffer(
        (char*)&ret,
        sizeof(ret)
    ).ToLocalChecked();

    info.GetReturnValue().Set(buf);
}


