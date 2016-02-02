#include <nan.h>
#include <bitcoinconsensus.h>
#include "util.h"

void VersionMethod(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  int result = bitcoinconsensus_version();
  info.GetReturnValue().Set(Nan::New<v8::Integer>(result));
}


void VerifyScriptMethod(const Nan::FunctionCallbackInfo<v8::Value>& info) {



  v8::Local<v8::Object> script_buffer = info[0].As<v8::Object>();
  CHECK_TYPE_BUFFER(script_buffer, "ScriptPubKey wrong type");
  int scriptPubKeyLen = node::Buffer::Length(script_buffer);

  v8::Local<v8::Object> tx_buffer = info[1].As<v8::Object>();
  CHECK_TYPE_BUFFER(tx_buffer, "Tx wrong type");
  int txLen = node::Buffer::Length(tx_buffer);

  v8::Local<v8::Object> nIn_object = info[2].As<v8::Object>();
  CHECK_TYPE_NUMBER(nIn_object, "Bad nInput type");
  unsigned int nInput = nIn_object->IntegerValue();

  v8::Local<v8::Object> flags_object = info[3].As<v8::Object>();
  CHECK_TYPE_NUMBER(flags_object, "Bad flags");
  unsigned int flags = flags_object->IntegerValue();

  const unsigned char* scriptPubKey = (const unsigned char*) node::Buffer::Data(script_buffer);
  const unsigned char* tx = (const unsigned char*) node::Buffer::Data(tx_buffer);

  bitcoinconsensus_error err;
  int result = bitcoinconsensus_verify_script(scriptPubKey, scriptPubKeyLen, tx, txLen, nInput, flags, &err);

  info.GetReturnValue().Set(Nan::New<v8::Boolean>(result));
}


void Init(v8::Local<v8::Object> exports) {
  exports->Set(Nan::New("version").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(VersionMethod)->GetFunction());
  exports->Set(Nan::New("verifyScript").ToLocalChecked(),
               Nan::New<v8::FunctionTemplate>(VerifyScriptMethod)->GetFunction());

}

NODE_MODULE(bitcoinconsensus, Init)
