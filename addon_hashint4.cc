#include <nan.h>

typedef uint32_t uint32;
#define rot(x,k) (((x)<<(k)) | ((x)>>(32-(k))))
#define final(a,b,c) \
{ \
  c ^= b; c -= rot(b,14); \
  a ^= c; a -= rot(c,11); \
  b ^= a; b -= rot(a,25); \
  c ^= b; c -= rot(b,16); \
  a ^= c; a -= rot(c, 4); \
  b ^= a; b -= rot(a,14); \
  c ^= b; c -= rot(b,24); \
}

uint32 hash_bytes_uint32(uint32 k){
	uint32	a,b,c;
	a = b = c = 0x9e3779b9 + (uint32) sizeof(uint32) + 3923095;
	a += k;
	final(a, b, c);
	/* report the result */
	return c;
}


void HashInt4(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  v8::Local<v8::Context> context = info.GetIsolate()->GetCurrentContext();

  if (info.Length() < 1) {
    Nan::ThrowTypeError("Wrong number of arguments");
    return;
  }

  if (!info[0]->IsNumber()) {
    Nan::ThrowTypeError("Wrong arguments");
    return;
  }

  uint32_t arg0 = info[0]->NumberValue(context).FromJust();
  v8::Local<v8::Number> num = Nan::New(hash_bytes_uint32(arg0));

  info.GetReturnValue().Set(num);
}

void Init(v8::Local<v8::Object> exports) {
  v8::Local<v8::Context> context = exports->CreationContext();
  exports->Set(context,
               Nan::New("hashInt4").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(HashInt4)
                   ->GetFunction(context)
                   .ToLocalChecked());
}

NODE_MODULE(addon, Init)
