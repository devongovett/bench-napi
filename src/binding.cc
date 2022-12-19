#include <napi.h>
#include <node_api.h>
#include <v8.h>

using namespace Napi;

Value test(const CallbackInfo& info) {
  Env env = info.Env();
  Napi::Array arr = Napi::Array::New(env);
  auto foo = Napi::String::New(env, "foo");
  auto bar = Napi::String::New(env, "bar");
  auto hi = Napi::String::New(env, "hi");
  for (int i = 0; i < 100000; i++) {
    Napi::Object obj = Napi::Object::New(env);
    obj.Set(foo, Napi::Number::New(env, i));
    obj.Set(bar, hi);
    arr.Set(i, obj);
  }

  return env.Null();
}

Value tmpl(const CallbackInfo& info) {
  Env env = info.Env();
  v8::Isolate *isolate = v8::Isolate::GetCurrent();
  v8::Local<v8::Context> context = isolate->GetCurrentContext();
  v8::Local<v8::Array> arr = v8::Array::New(isolate, 0);
  
  v8::Local<v8::ObjectTemplate> tpl = v8::ObjectTemplate::New(isolate);
  tpl->Set(isolate, "foo", v8::Null(isolate));
  tpl->Set(isolate, "bar", v8::Null(isolate));

  auto foo = v8::String::NewFromUtf8(isolate, "foo").ToLocalChecked();
  auto bar = v8::String::NewFromUtf8(isolate, "bar").ToLocalChecked();
  auto hi = v8::String::NewFromUtf8(isolate, "hi").ToLocalChecked();

  for (int i = 0; i < 100000; i++) {
    auto obj = tpl->NewInstance(context).ToLocalChecked();
    obj->Set(context, foo, v8::Number::New(isolate, i));
    obj->Set(context, bar, hi);
    arr->Set(context, i, obj);
  }

  return env.Null();
}

Object Init(Env env, Object exports) {
  exports.Set(
    String::New(env, "test"),
    Function::New(env, test)
  );
  exports.Set(
    String::New(env, "tmpl"),
    Function::New(env, tmpl)
  );
  return exports;
}

NODE_API_MODULE(watcher, Init)
