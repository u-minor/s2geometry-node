#ifndef CELL_HPP
#define CELL_HPP

#include <node.h>
#include "s2cell.h"
#include "s2cellid.h"
#include "s2.h"
#include "s2latlng.h"
#include "latlng.h"
#include "point.h"
#include "cap.h"
#include "cellid.h"
namespace s2geo{
class Cell : public node::ObjectWrap {
public:
    static v8::Persistent<v8::FunctionTemplate> constructor;
    static void Init(v8::Local<v8::Object> target);
    inline S2Cell get() { return this_; }
    static v8::Local<v8::Value> New(const S2Cell c);
    static v8::Local<v8::Value> New(const S2CellId c);

protected:
    Cell();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    // static v8::Handle<v8::Value> ApproxArea(const v8::Arguments& args);
    static NAN_METHOD(ApproxArea);
    static NAN_METHOD(ExactArea);
    static NAN_METHOD(Face);
    static NAN_METHOD(Level);
    static NAN_METHOD(AverageArea);
    static NAN_METHOD(Orientation);
    static NAN_METHOD(IsLeaf);
    static NAN_METHOD(GetCapBound);
    static NAN_METHOD(GetCenter);
    static NAN_METHOD(GetVertex);
    static NAN_METHOD(ToString);
    static NAN_METHOD(Id);

    S2Cell this_;
};
}
#endif
