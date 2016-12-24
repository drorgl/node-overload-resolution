//#include "return_struct.h"
//
//std::vector<std::shared_ptr<overload_info>> return_struct::_definition = { 
//	make_param("type","String") ,
//	make_param("value","String")
//};
//
//
//bool return_struct::verify(overload_resolution * ovres, v8::Local<v8::Value> obj) {
//	return ovres->verifyObject(return_struct::_definition, obj);
//}
//
//bool return_struct::parse(overload_resolution * ovres, v8::Local<v8::Value> obj) {
//	this->type = *Nan::Utf8String(ovres->GetFromObject(obj, "type").ToLocalChecked());
//	this->value = *Nan::Utf8String(ovres->GetFromObject(obj, "value").ToLocalChecked());
//
//	return true;
//}
//
//
//v8::Local<v8::Value> return_struct::ToObject() {
//	auto retval = Nan::New<v8::Object>();
//	retval->Set(Nan::New<v8::String>("type").ToLocalChecked(), Nan::New<v8::String>(this->type).ToLocalChecked());
//	retval->Set(Nan::New<v8::String>("value").ToLocalChecked(), Nan::New<v8::String>(this->value).ToLocalChecked());
//	return retval;
//}
