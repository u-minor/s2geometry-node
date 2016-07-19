#include "point.h"

using namespace v8;

namespace s2geo{
Persistent<FunctionTemplate> Point::constructor;

void Point::Init(Handle<Object> exports) {
    Isolate* isolate = exports->GetIsolate();

    // Prepare constructor template
      Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
      tpl->SetClassName(String::NewFromUtf8(isolate, "S2Point"));
      tpl->InstanceTemplate()->SetInternalFieldCount(1);

      // Prototype
      NODE_SET_PROTOTYPE_METHOD(tpl, "x", X);
      NODE_SET_PROTOTYPE_METHOD(tpl, "y", Y);
      NODE_SET_PROTOTYPE_METHOD(tpl, "z", Z);

      constructor.Reset(isolate, tpl);
      exports->Set(String::NewFromUtf8(isolate, "S2Point"),
                   tpl->GetFunction());
}

Point::Point()
    : ObjectWrap(),
      this_() {}
Point::~Point() {
}

void Point::New(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

    if (!args.IsConstructCall()) {
        isolate->ThrowException(Exception::TypeError(
                String::NewFromUtf8(isolate, "Use the new operator to create instances of this object.")));
            return;
    }

    if (args[0]->IsExternal()) {
            Local<External> ext = Local<External>::Cast(args[0]);
            void* ptr = ext->Value();
            Point* p = static_cast<Point*>(ptr);
            p->Wrap(args.This());
            args.GetReturnValue().Set(args.This());
        }

        if (args.Length() != 3) {
        isolate->ThrowException(Exception::TypeError(
                        String::NewFromUtf8(isolate, "(number, number, number) required")));
                    return;
        }

        Point* obj = new Point();

        obj->Wrap(args.This());

        obj->this_ = S2Point(
            args[0]->ToNumber()->Value(),
            args[1]->ToNumber()->Value(),
            args[2]->ToNumber()->Value());

        args.GetReturnValue().Set(args.This());
}

Local<Object> Point::New(S2Point s2cell) {
    Isolate* isolate = Isolate::GetCurrent();
    EscapableHandleScope scope(isolate);
    Point* obj = new Point();
    obj->this_ = s2cell;
    Local<Value> ext = External::New(isolate,obj);
    Local<FunctionTemplate> cons = Local<FunctionTemplate>::New(isolate, constructor);
    Local<Context> context = isolate->GetCurrentContext();
        Local<Object> result =
            cons->GetFunction()->NewInstance(context, 1, &ext).ToLocalChecked();
    return scope.Escape(result);
}

void Point::X(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  Point* obj = ObjectWrap::Unwrap<Point>(args.Holder());

  args.GetReturnValue().Set(Boolean::New(isolate, obj->this_.x()));
}

void Point::Y(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  Point* obj = ObjectWrap::Unwrap<Point>(args.Holder());

    args.GetReturnValue().Set(Boolean::New(isolate, obj->this_.y()));
}

void Point::Z(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

 Point* obj = ObjectWrap::Unwrap<Point>(args.Holder());

   args.GetReturnValue().Set(Boolean::New(isolate, obj->this_.z()));
}
}