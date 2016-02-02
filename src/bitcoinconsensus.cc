#include <nan.h>
#include <bitcoinconsensus.h>
#include <stdint.h>
#include "util.h"

void VersionMethod(const Nan::FunctionCallbackInfo<v8::Value>& info) {
    int result = bitcoinconsensus_version();
    info.GetReturnValue().Set(Nan::New<v8::Integer>(result));
}


void VerifyScriptMethod(const Nan::FunctionCallbackInfo<v8::Value>& info) {

    if (info.Length() < 4) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }
    v8::Local<v8::Object> script_buffer = info[0].As<v8::Object>();
    CHECK_TYPE_BUFFER(script_buffer, "ScriptPubKey must be a Buffer");
    int scriptPubKeyLen = node::Buffer::Length(script_buffer);

    v8::Local<v8::Object> tx_buffer = info[1].As<v8::Object>();
    CHECK_TYPE_BUFFER(tx_buffer, "Transaction must be a Buffer");
    int txLen = node::Buffer::Length(tx_buffer);

    v8::Local<v8::Object> nIn_object = info[2].As<v8::Object>();
    CHECK_TYPE_NUMBER(nIn_object, "nInput must be an integer");
    unsigned int nInput = nIn_object->IntegerValue();

    v8::Local<v8::Object> flags_object = info[3].As<v8::Object>();
    CHECK_TYPE_NUMBER(flags_object, "flags must be an integer");
    unsigned int flags = flags_object->IntegerValue();

    const unsigned char* scriptPubKey = (const unsigned char*) node::Buffer::Data(script_buffer);
    const unsigned char* tx = (const unsigned char*) node::Buffer::Data(tx_buffer);

    bitcoinconsensus_error err;
    int result = bitcoinconsensus_verify_script(scriptPubKey, scriptPubKeyLen, tx, txLen, nInput, flags, &err);

    info.GetReturnValue().Set(Nan::New<v8::Boolean>(result));
}


void VerifyScriptWithAmountMethod(const Nan::FunctionCallbackInfo<v8::Value>& info) {

    if (info.Length() < 5) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }

    v8::Local<v8::Object> script_buffer = info[0].As<v8::Object>();
    CHECK_TYPE_BUFFER(script_buffer, "ScriptPubKey must be a Buffer");
    int scriptPubKeyLen = node::Buffer::Length(script_buffer);

    v8::Local<v8::Object> nAmount_object = info[1].As<v8::Object>();
    CHECK_TYPE_NUMBER(nAmount_object, "Amount must be an integer");
    uint64_t amount = nAmount_object->IntegerValue();

    v8::Local<v8::Object> tx_buffer = info[2].As<v8::Object>();
    CHECK_TYPE_BUFFER(tx_buffer, "Transaction must be a Buffer");
    int txLen = node::Buffer::Length(tx_buffer);

    v8::Local<v8::Object> nIn_object = info[3].As<v8::Object>();
    CHECK_TYPE_NUMBER(nIn_object, "nInput must be an integer");
    unsigned int nInput = nIn_object->IntegerValue();

    v8::Local<v8::Object> flags_object = info[4].As<v8::Object>();
    CHECK_TYPE_NUMBER(flags_object, "flags must be an integer");
    unsigned int flags = flags_object->IntegerValue();

    const unsigned char* scriptPubKey = (const unsigned char*) node::Buffer::Data(script_buffer);
    const unsigned char* tx = (const unsigned char*) node::Buffer::Data(tx_buffer);

    bitcoinconsensus_error err;
    int result = bitcoinconsensus_verify_script_with_amount(scriptPubKey, scriptPubKeyLen, amount, tx, txLen, nInput, flags, &err);

    info.GetReturnValue().Set(Nan::New<v8::Boolean>(result));
}


void Init(v8::Local<v8::Object> exports) {
    exports->Set(Nan::New("version").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(VersionMethod)->GetFunction());
    exports->Set(Nan::New("verifyScript").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(VerifyScriptMethod)->GetFunction());
    exports->Set(Nan::New("verifyScriptWithAmount").ToLocalChecked(),
                 Nan::New<v8::FunctionTemplate>(VerifyScriptWithAmountMethod)->GetFunction());

}

NODE_MODULE(bitcoinconsensus, Init)
