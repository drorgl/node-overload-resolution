#ifndef _O_R_DEFAULT_PARAMETERS_TESTER_H_
#define _O_R_DEFAULT_PARAMETERS_TESTER_H_
#include "../overload_resolution.h"


#include "base_class.h"
#include "derived_class.h"
#include "struct_A.h"
#include "struct_B.h"

namespace overres_default_parameters_tester {

	namespace general_callback {
		std::shared_ptr<overload_resolution> overload;
		NAN_METHOD(tester_callback) {
			return overload->execute("or_default_tester", info);
		}
	}

	v8::Local<v8::String> JSONstringify(v8::Local<v8::Value> val) {
		auto global = Nan::GetCurrentContext()->Global();

		auto JSON = Nan::To<v8::Object>(Nan::Get(global,Nan::New<v8::String>("JSON").ToLocalChecked()).ToLocalChecked()).ToLocalChecked();
		auto stringifyFunc = Nan::To<v8::Function>(Nan::Get(JSON,Nan::New<v8::String>("stringify").ToLocalChecked()).ToLocalChecked()).ToLocalChecked();

		v8::Local<v8::Value> args[] = { val };
		auto callResult = Nan::Call(stringifyFunc,JSON, 1, args);
		v8::Local<v8::String> result = Nan::To<v8::String>(callResult.ToLocalChecked()).ToLocalChecked();
		return result;
	}

	std::string stringify(v8::Local<v8::Value> val) {
		std::string retval = *Nan::Utf8String(JSONstringify(val));
		return retval;
	}

	POLY_METHOD(number_testers_number_number) {
		std::string retval = ".number(" + stringify(info[0]) + ").number(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_number_string) {
		std::string retval = ".number(" + stringify(info[0]) + ").string(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_number_bool) {
		std::string retval = ".number(" + stringify(info[0]) + ").bool(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_number_date) {
		std::string retval = ".number(" + stringify(info[0]) + ").date(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_number_function) {
		std::string retval = ".number(" + stringify(info[0]) + ").function(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_number_buffer) {
		std::string retval = ".number(" + stringify(info[0]) + ").buffer(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_number_map) {
		std::string retval = ".number(" + stringify(info[0]) + ").map(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_number_set) {
		std::string retval = ".number(" + stringify(info[0]) + ").set(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_number_promise) {
		std::string retval = ".number(" + stringify(info[0]) + ").promise(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_number_proxy) {
		std::string retval = ".number(" + stringify(info[0]) + ").proxy(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_number_regexp) {
		std::string retval = ".number(" + stringify(info[0]) + ").regexp(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_number_base_class) {
		std::string retval = ".number(" + stringify(info[0]) + ").base_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_number_derived_class) {
		std::string retval = ".number(" + stringify(info[0]) + ").derived_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_number_struct_A) {
		std::string retval = ".number(" + stringify(info[0]) + ").struct_A(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_number_struct_B) {
		std::string retval = ".number(" + stringify(info[0]) + ").struct_B(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_number_array) {
		std::string retval = ".number(" + stringify(info[0]) + ").array(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}


	POLY_METHOD(number_testers_string_number) {
		std::string retval = ".string(" + stringify(info[0]) + ").number(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_string_string) {
		std::string retval = ".string(" + stringify(info[0]) + ").string(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_string_bool) {
		std::string retval = ".string(" + stringify(info[0]) + ").bool(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_string_date) {
		std::string retval = ".string(" + stringify(info[0]) + ").date(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_string_function) {
		std::string retval = ".string(" + stringify(info[0]) + ").function(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_string_buffer) {
		std::string retval = ".string(" + stringify(info[0]) + ").buffer(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_string_map) {
		std::string retval = ".string(" + stringify(info[0]) + ").map(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_string_set) {
		std::string retval = ".string(" + stringify(info[0]) + ").set(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_string_promise) {
		std::string retval = ".string(" + stringify(info[0]) + ").promise(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_string_proxy) {
		std::string retval = ".string(" + stringify(info[0]) + ").proxy(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_string_regexp) {
		std::string retval = ".string(" + stringify(info[0]) + ").regexp(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_string_base_class) {
		std::string retval = ".string(" + stringify(info[0]) + ").base_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_string_derived_class) {
		std::string retval = ".string(" + stringify(info[0]) + ").derived_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_string_struct_A) {
		std::string retval = ".string(" + stringify(info[0]) + ").struct_A(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_string_struct_B) {
		std::string retval = ".string(" + stringify(info[0]) + ").struct_B(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_string_array) {
		std::string retval = ".string(" + stringify(info[0]) + ").array(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}





	POLY_METHOD(number_testers_bool_number) {
		std::string retval = ".bool(" + stringify(info[0]) + ").number(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_bool_string) {
		std::string retval = ".bool(" + stringify(info[0]) + ").string(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_bool_bool) {
		std::string retval = ".bool(" + stringify(info[0]) + ").bool(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_bool_date) {
		std::string retval = ".bool(" + stringify(info[0]) + ").date(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_bool_function) {
		std::string retval = ".bool(" + stringify(info[0]) + ").function(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_bool_buffer) {
		std::string retval = ".bool(" + stringify(info[0]) + ").buffer(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_bool_map) {
		std::string retval = ".bool(" + stringify(info[0]) + ").map(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_bool_set) {
		std::string retval = ".bool(" + stringify(info[0]) + ").set(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_bool_promise) {
		std::string retval = ".bool(" + stringify(info[0]) + ").promise(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_bool_proxy) {
		std::string retval = ".bool(" + stringify(info[0]) + ").proxy(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_bool_regexp) {
		std::string retval = ".bool(" + stringify(info[0]) + ").regexp(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_bool_base_class) {
		std::string retval = ".bool(" + stringify(info[0]) + ").base_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_bool_derived_class) {
		std::string retval = ".bool(" + stringify(info[0]) + ").derived_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_bool_struct_A) {
		std::string retval = ".bool(" + stringify(info[0]) + ").struct_A(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_bool_struct_B) {
		std::string retval = ".bool(" + stringify(info[0]) + ").struct_B(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_bool_array) {
		std::string retval = ".bool(" + stringify(info[0]) + ").array(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}




	POLY_METHOD(number_testers_date_number) {
		std::string retval = ".date(" + stringify(info[0]) + ").number(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_date_string) {
		std::string retval = ".date(" + stringify(info[0]) + ").string(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_date_bool) {
		std::string retval = ".date(" + stringify(info[0]) + ").bool(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_date_date) {
		std::string retval = ".date(" + stringify(info[0]) + ").date(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_date_function) {
		std::string retval = ".date(" + stringify(info[0]) + ").function(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_date_buffer) {
		std::string retval = ".date(" + stringify(info[0]) + ").buffer(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_date_map) {
		std::string retval = ".date(" + stringify(info[0]) + ").map(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_date_set) {
		std::string retval = ".date(" + stringify(info[0]) + ").set(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_date_promise) {
		std::string retval = ".date(" + stringify(info[0]) + ").promise(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_date_proxy) {
		std::string retval = ".date(" + stringify(info[0]) + ").proxy(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_date_regexp) {
		std::string retval = ".date(" + stringify(info[0]) + ").regexp(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_date_base_class) {
		std::string retval = ".date(" + stringify(info[0]) + ").base_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_date_derived_class) {
		std::string retval = ".date(" + stringify(info[0]) + ").derived_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_date_struct_A) {
		std::string retval = ".date(" + stringify(info[0]) + ").struct_A(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_date_struct_B) {
		std::string retval = ".date(" + stringify(info[0]) + ").struct_B(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_date_array) {
		std::string retval = ".date(" + stringify(info[0]) + ").array(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}







	POLY_METHOD(number_testers_function_number) {
		std::string retval = ".function(" + stringify(info[0]) + ").number(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_function_string) {
		std::string retval = ".function(" + stringify(info[0]) + ").string(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_function_bool) {
		std::string retval = ".function(" + stringify(info[0]) + ").bool(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_function_date) {
		std::string retval = ".function(" + stringify(info[0]) + ").date(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_function_function) {
		std::string retval = ".function(" + stringify(info[0]) + ").function(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_function_buffer) {
		std::string retval = ".function(" + stringify(info[0]) + ").buffer(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_function_map) {
		std::string retval = ".function(" + stringify(info[0]) + ").map(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_function_set) {
		std::string retval = ".function(" + stringify(info[0]) + ").set(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_function_promise) {
		std::string retval = ".function(" + stringify(info[0]) + ").promise(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_function_proxy) {
		std::string retval = ".function(" + stringify(info[0]) + ").proxy(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_function_regexp) {
		std::string retval = ".function(" + stringify(info[0]) + ").regexp(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_function_base_class) {
		std::string retval = ".function(" + stringify(info[0]) + ").base_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_function_derived_class) {
		std::string retval = ".function(" + stringify(info[0]) + ").derived_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_function_struct_A) {
		std::string retval = ".function(" + stringify(info[0]) + ").struct_A(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_function_struct_B) {
		std::string retval = ".function(" + stringify(info[0]) + ").struct_B(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_function_array) {
		std::string retval = ".function(" + stringify(info[0]) + ").array(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}





	POLY_METHOD(number_testers_buffer_number) {
		std::string retval = ".buffer(" + stringify(info[0]) + ").number(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_buffer_string) {
		std::string retval = ".buffer(" + stringify(info[0]) + ").string(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_buffer_bool) {
		std::string retval = ".buffer(" + stringify(info[0]) + ").bool(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_buffer_date) {
		std::string retval = ".buffer(" + stringify(info[0]) + ").date(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_buffer_function) {
		std::string retval = ".buffer(" + stringify(info[0]) + ").function(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_buffer_buffer) {
		std::string retval = ".buffer(" + stringify(info[0]) + ").buffer(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_buffer_map) {
		std::string retval = ".buffer(" + stringify(info[0]) + ").map(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_buffer_set) {
		std::string retval = ".buffer(" + stringify(info[0]) + ").set(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_buffer_promise) {
		std::string retval = ".buffer(" + stringify(info[0]) + ").promise(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_buffer_proxy) {
		std::string retval = ".buffer(" + stringify(info[0]) + ").proxy(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_buffer_regexp) {
		std::string retval = ".buffer(" + stringify(info[0]) + ").regexp(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_buffer_base_class) {
		std::string retval = ".buffer(" + stringify(info[0]) + ").base_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_buffer_derived_class) {
		std::string retval = ".buffer(" + stringify(info[0]) + ").derived_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_buffer_struct_A) {
		std::string retval = ".buffer(" + stringify(info[0]) + ").struct_A(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_buffer_struct_B) {
		std::string retval = ".buffer(" + stringify(info[0]) + ").struct_B(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_buffer_array) {
		std::string retval = ".buffer(" + stringify(info[0]) + ").array(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}






	POLY_METHOD(number_testers_map_number) {
		std::string retval = ".map(" + stringify(info[0]) + ").number(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_map_string) {
		std::string retval = ".map(" + stringify(info[0]) + ").string(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_map_bool) {
		std::string retval = ".map(" + stringify(info[0]) + ").bool(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_map_date) {
		std::string retval = ".map(" + stringify(info[0]) + ").date(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_map_function) {
		std::string retval = ".map(" + stringify(info[0]) + ").function(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_map_buffer) {
		std::string retval = ".map(" + stringify(info[0]) + ").buffer(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_map_map) {
		std::string retval = ".map(" + stringify(info[0]) + ").map(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_map_set) {
		std::string retval = ".map(" + stringify(info[0]) + ").set(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_map_promise) {
		std::string retval = ".map(" + stringify(info[0]) + ").promise(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_map_proxy) {
		std::string retval = ".map(" + stringify(info[0]) + ").proxy(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_map_regexp) {
		std::string retval = ".map(" + stringify(info[0]) + ").regexp(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_map_base_class) {
		std::string retval = ".map(" + stringify(info[0]) + ").base_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_map_derived_class) {
		std::string retval = ".map(" + stringify(info[0]) + ").derived_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_map_struct_A) {
		std::string retval = ".map(" + stringify(info[0]) + ").struct_A(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_map_struct_B) {
		std::string retval = ".map(" + stringify(info[0]) + ").struct_B(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_map_array) {
		std::string retval = ".map(" + stringify(info[0]) + ").array(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}





	POLY_METHOD(number_testers_set_number) {
		std::string retval = ".set(" + stringify(info[0]) + ").number(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_set_string) {
		std::string retval = ".set(" + stringify(info[0]) + ").string(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_set_bool) {
		std::string retval = ".set(" + stringify(info[0]) + ").bool(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_set_date) {
		std::string retval = ".set(" + stringify(info[0]) + ").date(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_set_function) {
		std::string retval = ".set(" + stringify(info[0]) + ").function(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_set_buffer) {
		std::string retval = ".set(" + stringify(info[0]) + ").buffer(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_set_map) {
		std::string retval = ".set(" + stringify(info[0]) + ").map(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_set_set) {
		std::string retval = ".set(" + stringify(info[0]) + ").set(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_set_promise) {
		std::string retval = ".set(" + stringify(info[0]) + ").promise(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_set_proxy) {
		std::string retval = ".set(" + stringify(info[0]) + ").proxy(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_set_regexp) {
		std::string retval = ".set(" + stringify(info[0]) + ").regexp(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_set_base_class) {
		std::string retval = ".set(" + stringify(info[0]) + ").base_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_set_derived_class) {
		std::string retval = ".set(" + stringify(info[0]) + ").derived_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_set_struct_A) {
		std::string retval = ".set(" + stringify(info[0]) + ").struct_A(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_set_struct_B) {
		std::string retval = ".set(" + stringify(info[0]) + ").struct_B(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_set_array) {
		std::string retval = ".set(" + stringify(info[0]) + ").array(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}





	POLY_METHOD(number_testers_promise_number) {
		std::string retval = ".promise(" + stringify(info[0]) + ").number(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_promise_string) {
		std::string retval = ".promise(" + stringify(info[0]) + ").string(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_promise_bool) {
		std::string retval = ".promise(" + stringify(info[0]) + ").bool(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_promise_date) {
		std::string retval = ".promise(" + stringify(info[0]) + ").date(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_promise_function) {
		std::string retval = ".promise(" + stringify(info[0]) + ").function(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_promise_buffer) {
		std::string retval = ".promise(" + stringify(info[0]) + ").buffer(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_promise_map) {
		std::string retval = ".promise(" + stringify(info[0]) + ").map(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_promise_set) {
		std::string retval = ".promise(" + stringify(info[0]) + ").set(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_promise_promise) {
		std::string retval = ".promise(" + stringify(info[0]) + ").promise(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_promise_proxy) {
		std::string retval = ".promise(" + stringify(info[0]) + ").proxy(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_promise_regexp) {
		std::string retval = ".promise(" + stringify(info[0]) + ").regexp(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_promise_base_class) {
		std::string retval = ".promise(" + stringify(info[0]) + ").base_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_promise_derived_class) {
		std::string retval = ".promise(" + stringify(info[0]) + ").derived_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_promise_struct_A) {
		std::string retval = ".promise(" + stringify(info[0]) + ").struct_A(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_promise_struct_B) {
		std::string retval = ".promise(" + stringify(info[0]) + ").struct_B(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_promise_array) {
		std::string retval = ".promise(" + stringify(info[0]) + ").array(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}




	POLY_METHOD(number_testers_proxy_number) {
		std::string retval = ".proxy(" + stringify(info[0]) + ").number(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_proxy_string) {
		std::string retval = ".proxy(" + stringify(info[0]) + ").string(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_proxy_bool) {
		std::string retval = ".proxy(" + stringify(info[0]) + ").bool(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_proxy_date) {
		std::string retval = ".proxy(" + stringify(info[0]) + ").date(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_proxy_function) {
		std::string retval = ".proxy(" + stringify(info[0]) + ").function(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_proxy_buffer) {
		std::string retval = ".proxy(" + stringify(info[0]) + ").buffer(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_proxy_map) {
		std::string retval = ".proxy(" + stringify(info[0]) + ").map(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_proxy_set) {
		std::string retval = ".proxy(" + stringify(info[0]) + ").set(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_proxy_promise) {
		std::string retval = ".proxy(" + stringify(info[0]) + ").promise(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_proxy_proxy) {
		std::string retval = ".proxy(" + stringify(info[0]) + ").proxy(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_proxy_regexp) {
		std::string retval = ".proxy(" + stringify(info[0]) + ").regexp(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_proxy_base_class) {
		std::string retval = ".proxy(" + stringify(info[0]) + ").base_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_proxy_derived_class) {
		std::string retval = ".proxy(" + stringify(info[0]) + ").derived_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_proxy_struct_A) {
		std::string retval = ".proxy(" + stringify(info[0]) + ").struct_A(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_proxy_struct_B) {
		std::string retval = ".proxy(" + stringify(info[0]) + ").struct_B(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_proxy_array) {
		std::string retval = ".proxy(" + stringify(info[0]) + ").array(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}




	POLY_METHOD(number_testers_regexp_number) {
		std::string retval = ".regexp(" + stringify(info[0]) + ").number(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_regexp_string) {
		std::string retval = ".regexp(" + stringify(info[0]) + ").string(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_regexp_bool) {
		std::string retval = ".regexp(" + stringify(info[0]) + ").bool(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_regexp_date) {
		std::string retval = ".regexp(" + stringify(info[0]) + ").date(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_regexp_function) {
		std::string retval = ".regexp(" + stringify(info[0]) + ").function(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_regexp_buffer) {
		std::string retval = ".regexp(" + stringify(info[0]) + ").buffer(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_regexp_map) {
		std::string retval = ".regexp(" + stringify(info[0]) + ").map(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_regexp_set) {
		std::string retval = ".regexp(" + stringify(info[0]) + ").set(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_regexp_promise) {
		std::string retval = ".regexp(" + stringify(info[0]) + ").promise(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_regexp_proxy) {
		std::string retval = ".regexp(" + stringify(info[0]) + ").proxy(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_regexp_regexp) {
		std::string retval = ".regexp(" + stringify(info[0]) + ").regexp(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_regexp_base_class) {
		std::string retval = ".regexp(" + stringify(info[0]) + ").base_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_regexp_derived_class) {
		std::string retval = ".regexp(" + stringify(info[0]) + ").derived_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_regexp_struct_A) {
		std::string retval = ".regexp(" + stringify(info[0]) + ").struct_A(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_regexp_struct_B) {
		std::string retval = ".regexp(" + stringify(info[0]) + ").struct_B(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_regexp_array) {
		std::string retval = ".regexp(" + stringify(info[0]) + ").array(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}





	POLY_METHOD(number_testers_base_class_number) {
		std::string retval = ".base_class(" + stringify(info[0]) + ").number(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_base_class_string) {
		std::string retval = ".base_class(" + stringify(info[0]) + ").string(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_base_class_bool) {
		std::string retval = ".base_class(" + stringify(info[0]) + ").bool(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_base_class_date) {
		std::string retval = ".base_class(" + stringify(info[0]) + ").date(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_base_class_function) {
		std::string retval = ".base_class(" + stringify(info[0]) + ").function(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_base_class_buffer) {
		std::string retval = ".base_class(" + stringify(info[0]) + ").buffer(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_base_class_map) {
		std::string retval = ".base_class(" + stringify(info[0]) + ").map(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_base_class_set) {
		std::string retval = ".base_class(" + stringify(info[0]) + ").set(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_base_class_promise) {
		std::string retval = ".base_class(" + stringify(info[0]) + ").promise(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_base_class_proxy) {
		std::string retval = ".base_class(" + stringify(info[0]) + ").proxy(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_base_class_regexp) {
		std::string retval = ".base_class(" + stringify(info[0]) + ").regexp(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_base_class_base_class) {
		std::string retval = ".base_class(" + stringify(info[0]) + ").base_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_base_class_derived_class) {
		std::string retval = ".base_class(" + stringify(info[0]) + ").derived_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_base_class_struct_A) {
		std::string retval = ".base_class(" + stringify(info[0]) + ").struct_A(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_base_class_struct_B) {
		std::string retval = ".base_class(" + stringify(info[0]) + ").struct_B(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_base_class_array) {
		std::string retval = ".base_class(" + stringify(info[0]) + ").array(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}





	POLY_METHOD(number_testers_derived_class_number) {
		std::string retval = ".derived_class(" + stringify(info[0]) + ").number(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_derived_class_string) {
		std::string retval = ".derived_class(" + stringify(info[0]) + ").string(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_derived_class_bool) {
		std::string retval = ".derived_class(" + stringify(info[0]) + ").bool(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_derived_class_date) {
		std::string retval = ".derived_class(" + stringify(info[0]) + ").date(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_derived_class_function) {
		std::string retval = ".derived_class(" + stringify(info[0]) + ").function(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_derived_class_buffer) {
		std::string retval = ".derived_class(" + stringify(info[0]) + ").buffer(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_derived_class_map) {
		std::string retval = ".derived_class(" + stringify(info[0]) + ").map(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_derived_class_set) {
		std::string retval = ".derived_class(" + stringify(info[0]) + ").set(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_derived_class_promise) {
		std::string retval = ".derived_class(" + stringify(info[0]) + ").promise(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_derived_class_proxy) {
		std::string retval = ".derived_class(" + stringify(info[0]) + ").proxy(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_derived_class_regexp) {
		std::string retval = ".derived_class(" + stringify(info[0]) + ").regexp(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_derived_class_base_class) {
		std::string retval = ".derived_class(" + stringify(info[0]) + ").base_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_derived_class_derived_class) {
		std::string retval = ".derived_class(" + stringify(info[0]) + ").derived_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_derived_class_struct_A) {
		std::string retval = ".derived_class(" + stringify(info[0]) + ").struct_A(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_derived_class_struct_B) {
		std::string retval = ".derived_class(" + stringify(info[0]) + ").struct_B(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_derived_class_array) {
		std::string retval = ".derived_class(" + stringify(info[0]) + ").array(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}




	POLY_METHOD(number_testers_struct_A_number) {
		std::string retval = ".struct_A(" + stringify(info[0]) + ").number(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_A_string) {
		std::string retval = ".struct_A(" + stringify(info[0]) + ").string(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_A_bool) {
		std::string retval = ".struct_A(" + stringify(info[0]) + ").bool(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_A_date) {
		std::string retval = ".struct_A(" + stringify(info[0]) + ").date(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_A_function) {
		std::string retval = ".struct_A(" + stringify(info[0]) + ").function(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_A_buffer) {
		std::string retval = ".struct_A(" + stringify(info[0]) + ").buffer(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_A_map) {
		std::string retval = ".struct_A(" + stringify(info[0]) + ").map(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_A_set) {
		std::string retval = ".struct_A(" + stringify(info[0]) + ").set(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_A_promise) {
		std::string retval = ".struct_A(" + stringify(info[0]) + ").promise(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_A_proxy) {
		std::string retval = ".struct_A(" + stringify(info[0]) + ").proxy(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_A_regexp) {
		std::string retval = ".struct_A(" + stringify(info[0]) + ").regexp(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_A_base_class) {
		std::string retval = ".struct_A(" + stringify(info[0]) + ").base_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_A_derived_class) {
		std::string retval = ".struct_A(" + stringify(info[0]) + ").derived_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_A_struct_A) {
		std::string retval = ".struct_A(" + stringify(info[0]) + ").struct_A(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_A_struct_B) {
		std::string retval = ".struct_A(" + stringify(info[0]) + ").struct_B(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_A_array) {
		std::string retval = ".struct_A(" + stringify(info[0]) + ").array(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}





	POLY_METHOD(number_testers_struct_B_number) {
		std::string retval = ".struct_B(" + stringify(info[0]) + ").number(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_B_string) {
		std::string retval = ".struct_B(" + stringify(info[0]) + ").string(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_B_bool) {
		std::string retval = ".struct_B(" + stringify(info[0]) + ").bool(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_B_date) {
		std::string retval = ".struct_B(" + stringify(info[0]) + ").date(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_B_function) {
		std::string retval = ".struct_B(" + stringify(info[0]) + ").function(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_B_buffer) {
		std::string retval = ".struct_B(" + stringify(info[0]) + ").buffer(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_B_map) {
		std::string retval = ".struct_B(" + stringify(info[0]) + ").map(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_B_set) {
		std::string retval = ".struct_B(" + stringify(info[0]) + ").set(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_B_promise) {
		std::string retval = ".struct_B(" + stringify(info[0]) + ").promise(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_B_proxy) {
		std::string retval = ".struct_B(" + stringify(info[0]) + ").proxy(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_B_regexp) {
		std::string retval = ".struct_B(" + stringify(info[0]) + ").regexp(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_B_base_class) {
		std::string retval = ".struct_B(" + stringify(info[0]) + ").base_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_B_derived_class) {
		std::string retval = ".struct_B(" + stringify(info[0]) + ").derived_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_B_struct_A) {
		std::string retval = ".struct_B(" + stringify(info[0]) + ").struct_A(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_B_struct_B) {
		std::string retval = ".struct_B(" + stringify(info[0]) + ").struct_B(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_struct_B_array) {
		std::string retval = ".struct_B(" + stringify(info[0]) + ").array(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}



	POLY_METHOD(number_testers_array_number) {
		std::string retval = ".array(" + stringify(info[0]) + ").number(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_array_string) {
		std::string retval = ".array(" + stringify(info[0]) + ").string(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_array_bool) {
		std::string retval = ".array(" + stringify(info[0]) + ").bool(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_array_date) {
		std::string retval = ".array(" + stringify(info[0]) + ").date(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_array_function) {
		std::string retval = ".array(" + stringify(info[0]) + ").function(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_array_buffer) {
		std::string retval = ".array(" + stringify(info[0]) + ").buffer(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_array_map) {
		std::string retval = ".array(" + stringify(info[0]) + ").map(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_array_set) {
		std::string retval = ".array(" + stringify(info[0]) + ").set(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_array_promise) {
		std::string retval = ".array(" + stringify(info[0]) + ").promise(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_array_proxy) {
		std::string retval = ".array(" + stringify(info[0]) + ").proxy(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_array_regexp) {
		std::string retval = ".array(" + stringify(info[0]) + ").regexp(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_array_base_class) {
		std::string retval = ".array(" + stringify(info[0]) + ").base_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_array_derived_class) {
		std::string retval = ".array(" + stringify(info[0]) + ").derived_class(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_array_struct_A) {
		std::string retval = ".array(" + stringify(info[0]) + ").struct_A(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_array_struct_B) {
		std::string retval = ".array(" + stringify(info[0]) + ").struct_B(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}
	POLY_METHOD(number_testers_array_array) {
		std::string retval = ".array(" + stringify(info[0]) + ").array(" + stringify(info[1]) + ")";
		info.GetReturnValue().Set(Nan::New(retval).ToLocalChecked());
	}



	POLY_METHOD(number_testers) {
		info.GetReturnValue().Set(Nan::New(".no_params").ToLocalChecked());
		
	}

	//void(*FunctionCallback)(const FunctionCallbackInfo<Value>& info);

	void ORFunctionCallback(const Nan::FunctionCallbackInfo<v8::Value>& info) {
		//NOP
	}


	


	void RegisterORTesters(v8::Local<v8::Object> target, std::shared_ptr<overload_resolution> overload) {

		//auto loverload = overload;
		
		//register function in overload resolution engine
		overload->addOverload("or_default_tester", "", "default_testers_number", { make_param("a","Number",Nan::Undefined()),make_param("a","Number",Nan::New<v8::Number>(1)) }, number_testers_number_number);
		overload->addOverload("or_default_tester", "", "default_testers_number", { make_param("a","String",Nan::Undefined()),make_param("a","Number",Nan::New<v8::Number>(1)) }, number_testers_string_number);
		overload->addOverload("or_default_tester", "", "default_testers_number", { make_param("a","Boolean",Nan::Undefined()),make_param("a","Number",Nan::New<v8::Number>(1)) }, number_testers_bool_number);
		overload->addOverload("or_default_tester", "", "default_testers_number", { make_param("a","Date",Nan::Undefined()),make_param("a","Number",Nan::New<v8::Number>(1)) }, number_testers_date_number);
		overload->addOverload("or_default_tester", "", "default_testers_number", { make_param("a","Function",Nan::Undefined()) ,make_param("a","Number",Nan::New<v8::Number>(1)) }, number_testers_function_number);
		overload->addOverload("or_default_tester", "", "default_testers_number", { make_param("a","Buffer",Nan::Undefined()),make_param("a","Number",Nan::New<v8::Number>(1)) }, number_testers_buffer_number);
#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_number", { make_param("a","Map",Nan::Undefined()),make_param("a","Number",Nan::New<v8::Number>(1)) }, number_testers_map_number);
		overload->addOverload("or_default_tester", "", "default_testers_number", { make_param("a","Set",Nan::Undefined()),make_param("a","Number",Nan::New<v8::Number>(1)) }, number_testers_set_number);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_number", { make_param("a","Promise",Nan::Undefined()),make_param("a","Number",Nan::New<v8::Number>(1)) }, number_testers_promise_number);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_number", { make_param("a","Proxy",Nan::Undefined()),make_param("a","Number",Nan::New<v8::Number>(1)) }, number_testers_proxy_number);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_number", { make_param("a","RegExp",Nan::Undefined()),make_param("a","Number",Nan::New<v8::Number>(1)) }, number_testers_regexp_number);
		overload->addOverload("or_default_tester", "", "default_testers_number", { make_param("a","base_class",Nan::Undefined()),make_param("a","Number",Nan::New<v8::Number>(1)) }, number_testers_base_class_number);
		overload->addOverload("or_default_tester", "", "default_testers_number", { make_param("a","derived_class",Nan::Undefined()),make_param("a","Number",Nan::New<v8::Number>(1)) }, number_testers_derived_class_number);
		overload->addOverload("or_default_tester", "", "default_testers_number", { make_param("a","struct_A",Nan::Undefined()), make_param("a","Number",Nan::New<v8::Number>(1)) }, number_testers_struct_A_number);
		overload->addOverload("or_default_tester", "", "default_testers_number", { make_param("a","struct_B",Nan::Undefined()),make_param("a","Number",Nan::New<v8::Number>(1)) }, number_testers_struct_B_number);
		overload->addOverload("or_default_tester", "", "default_testers_number", { make_param("a","Array",Nan::Undefined()),make_param("a","Number",Nan::New<v8::Number>(1)) }, number_testers_array_number);
		overload->addOverload("or_default_tester", "", "default_testers_number", {}, number_testers);




		overload->addOverload("or_default_tester", "", "default_testers_string", { make_param("a","Number",Nan::Undefined()),			make_param("a","String",Nan::New<v8::String>("1").ToLocalChecked()) }, number_testers_number_string);
		overload->addOverload("or_default_tester", "", "default_testers_string", { make_param("a","String",Nan::Undefined()),			make_param("a","String",Nan::New<v8::String>("1").ToLocalChecked()) }, number_testers_string_string);
		overload->addOverload("or_default_tester", "", "default_testers_string", { make_param("a","Boolean",Nan::Undefined()),			make_param("a","String",Nan::New<v8::String>("1").ToLocalChecked()) }, number_testers_bool_string);
		overload->addOverload("or_default_tester", "", "default_testers_string", { make_param("a","Date",Nan::Undefined()),			make_param("a","String",Nan::New<v8::String>("1").ToLocalChecked()) }, number_testers_date_string);
		overload->addOverload("or_default_tester", "", "default_testers_string", { make_param("a","Function",Nan::Undefined()) ,		make_param("a","String",Nan::New<v8::String>("1").ToLocalChecked()) }, number_testers_function_string);
		overload->addOverload("or_default_tester", "", "default_testers_string", { make_param("a","Buffer",Nan::Undefined()),			make_param("a","String",Nan::New<v8::String>("1").ToLocalChecked()) }, number_testers_buffer_string);
#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_string", { make_param("a","Map",Nan::Undefined()),				make_param("a","String",Nan::New<v8::String>("1").ToLocalChecked()) }, number_testers_map_string);
		overload->addOverload("or_default_tester", "", "default_testers_string", { make_param("a","Set",Nan::Undefined()),				make_param("a","String",Nan::New<v8::String>("1").ToLocalChecked()) }, number_testers_set_string);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_string", { make_param("a","Promise",Nan::Undefined()),			make_param("a","String",Nan::New<v8::String>("1").ToLocalChecked()) }, number_testers_promise_string);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_string", { make_param("a","Proxy",Nan::Undefined()),			make_param("a","String",Nan::New<v8::String>("1").ToLocalChecked()) }, number_testers_proxy_string);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_string", { make_param("a","RegExp",Nan::Undefined()),			make_param("a","String",Nan::New<v8::String>("1").ToLocalChecked()) }, number_testers_regexp_string);
		overload->addOverload("or_default_tester", "", "default_testers_string", { make_param("a","base_class",Nan::Undefined()),		make_param("a","String",Nan::New<v8::String>("1").ToLocalChecked()) }, number_testers_base_class_string);
		overload->addOverload("or_default_tester", "", "default_testers_string", { make_param("a","derived_class",Nan::Undefined()),	make_param("a","String",Nan::New<v8::String>("1").ToLocalChecked()) }, number_testers_derived_class_string);
		overload->addOverload("or_default_tester", "", "default_testers_string", { make_param("a","struct_A",Nan::Undefined()),		make_param("a","String",Nan::New<v8::String>("1").ToLocalChecked()) }, number_testers_struct_A_string);
		overload->addOverload("or_default_tester", "", "default_testers_string", { make_param("a","struct_B",Nan::Undefined()),		make_param("a","String",Nan::New<v8::String>("1").ToLocalChecked()) }, number_testers_struct_B_string);
		overload->addOverload("or_default_tester", "", "default_testers_string", { make_param("a","Array",Nan::Undefined()),			make_param("a","String",Nan::New<v8::String>("1").ToLocalChecked()) }, number_testers_array_string);
		overload->addOverload("or_default_tester", "", "default_testers_string", {}, number_testers);




		overload->addOverload("or_default_tester", "", "default_testers_bool", { make_param("a","Number",Nan::Undefined()),make_param("a","Boolean",Nan::New<v8::Boolean>(true)) }, number_testers_number_bool);
		overload->addOverload("or_default_tester", "", "default_testers_bool", { make_param("a","String",Nan::Undefined()),make_param("a","Boolean",Nan::New<v8::Boolean>(true)) }, number_testers_string_bool);
		overload->addOverload("or_default_tester", "", "default_testers_bool", { make_param("a","Boolean",Nan::Undefined()), make_param("a","Boolean",Nan::New<v8::Boolean>(true)) }, number_testers_bool_bool);
		overload->addOverload("or_default_tester", "", "default_testers_bool", { make_param("a","Date",Nan::Undefined()),make_param("a","Boolean",Nan::New<v8::Boolean>(true)) }, number_testers_date_bool);
		overload->addOverload("or_default_tester", "", "default_testers_bool", { make_param("a","Function",Nan::Undefined()) , make_param("a","Boolean",Nan::New<v8::Boolean>(true)) }, number_testers_function_bool);
		overload->addOverload("or_default_tester", "", "default_testers_bool", { make_param("a","Buffer",Nan::Undefined()), make_param("a","Boolean",Nan::New<v8::Boolean>(true)) }, number_testers_buffer_bool);
#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_bool", { make_param("a","Map",Nan::Undefined()), make_param("a","Boolean",Nan::New<v8::Boolean>(true)) }, number_testers_map_bool);
		overload->addOverload("or_default_tester", "", "default_testers_bool", { make_param("a","Set",Nan::Undefined()), make_param("a","Boolean",Nan::New<v8::Boolean>(true)) }, number_testers_set_bool);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_bool", { make_param("a","Promise",Nan::Undefined()), make_param("a","Boolean",Nan::New<v8::Boolean>(true)) }, number_testers_promise_bool);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_bool", { make_param("a","Proxy",Nan::Undefined()), make_param("a","Boolean",Nan::New<v8::Boolean>(true)) }, number_testers_proxy_bool);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_bool", { make_param("a","RegExp",Nan::Undefined()), make_param("a","Boolean",Nan::New<v8::Boolean>(true)) }, number_testers_regexp_bool);
		overload->addOverload("or_default_tester", "", "default_testers_bool", { make_param("a","base_class",Nan::Undefined()), make_param("a","Boolean",Nan::New<v8::Boolean>(true)) }, number_testers_base_class_bool);
		overload->addOverload("or_default_tester", "", "default_testers_bool", { make_param("a","derived_class",Nan::Undefined()), make_param("a","Boolean",Nan::New<v8::Boolean>(true)) }, number_testers_derived_class_bool);
		overload->addOverload("or_default_tester", "", "default_testers_bool", { make_param("a","struct_A",Nan::Undefined()), make_param("a","Boolean",Nan::New<v8::Boolean>(true)) }, number_testers_struct_A_bool);
		overload->addOverload("or_default_tester", "", "default_testers_bool", { make_param("a","struct_B",Nan::Undefined()), make_param("a","Boolean",Nan::New<v8::Boolean>(true)) }, number_testers_struct_B_bool);
		overload->addOverload("or_default_tester", "", "default_testers_bool", { make_param("a","Array",Nan::Undefined()), make_param("a","Boolean",Nan::New<v8::Boolean>(true)) }, number_testers_array_bool);
		overload->addOverload("or_default_tester", "", "default_testers_bool", {}, number_testers);


		overload->addOverload("or_default_tester", "", "default_testers_date", { make_param("a","Number",Nan::Undefined()),        make_param("a","Date",Nan::New<v8::Date>(0).ToLocalChecked()) }, number_testers_number_date);
		overload->addOverload("or_default_tester", "", "default_testers_date", { make_param("a","String",Nan::Undefined()),        make_param("a","Date",Nan::New<v8::Date>(0).ToLocalChecked()) }, number_testers_string_date);
		overload->addOverload("or_default_tester", "", "default_testers_date", { make_param("a","Boolean",Nan::Undefined()),       make_param("a","Date",Nan::New<v8::Date>(0).ToLocalChecked()) }, number_testers_bool_date);
		overload->addOverload("or_default_tester", "", "default_testers_date", { make_param("a","Date",Nan::Undefined()),          make_param("a","Date",Nan::New<v8::Date>(0).ToLocalChecked()) }, number_testers_date_date);
		overload->addOverload("or_default_tester", "", "default_testers_date", { make_param("a","Function",Nan::Undefined()) ,     make_param("a","Date",Nan::New<v8::Date>(0).ToLocalChecked()) }, number_testers_function_date);
		overload->addOverload("or_default_tester", "", "default_testers_date", { make_param("a","Buffer",Nan::Undefined()),        make_param("a","Date",Nan::New<v8::Date>(0).ToLocalChecked()) }, number_testers_buffer_date);
#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_date", { make_param("a","Map",Nan::Undefined()),           make_param("a","Date",Nan::New<v8::Date>(0).ToLocalChecked()) }, number_testers_map_date);
		overload->addOverload("or_default_tester", "", "default_testers_date", { make_param("a","Set",Nan::Undefined()),           make_param("a","Date",Nan::New<v8::Date>(0).ToLocalChecked()) }, number_testers_set_date);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_date", { make_param("a","Promise",Nan::Undefined()),       make_param("a","Date",Nan::New<v8::Date>(0).ToLocalChecked()) }, number_testers_promise_date);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_date", { make_param("a","Proxy",Nan::Undefined()),         make_param("a","Date",Nan::New<v8::Date>(0).ToLocalChecked()) }, number_testers_proxy_date);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_date", { make_param("a","RegExp",Nan::Undefined()),        make_param("a","Date",Nan::New<v8::Date>(0).ToLocalChecked()) }, number_testers_regexp_date);
		overload->addOverload("or_default_tester", "", "default_testers_date", { make_param("a","base_class",Nan::Undefined()),    make_param("a","Date",Nan::New<v8::Date>(0).ToLocalChecked()) }, number_testers_base_class_date);
		overload->addOverload("or_default_tester", "", "default_testers_date", { make_param("a","derived_class",Nan::Undefined()), make_param("a","Date",Nan::New<v8::Date>(0).ToLocalChecked()) }, number_testers_derived_class_date);
		overload->addOverload("or_default_tester", "", "default_testers_date", { make_param("a","struct_A",Nan::Undefined()),      make_param("a","Date",Nan::New<v8::Date>(0).ToLocalChecked()) }, number_testers_struct_A_date);
		overload->addOverload("or_default_tester", "", "default_testers_date", { make_param("a","struct_B",Nan::Undefined()),      make_param("a","Date",Nan::New<v8::Date>(0).ToLocalChecked()) }, number_testers_struct_B_date);
		overload->addOverload("or_default_tester", "", "default_testers_date", { make_param("a","Array",Nan::Undefined()),         make_param("a","Date",Nan::New<v8::Date>(0).ToLocalChecked()) }, number_testers_array_date);
		overload->addOverload("or_default_tester", "", "default_testers_date", {}, number_testers);
		
		overload->addOverload("or_default_tester", "", "default_testers_function", { make_param("a","Number",Nan::Undefined()),		make_param("a","Function",Nan::New<v8::Function>(ORFunctionCallback)) }, number_testers_number_function);
		overload->addOverload("or_default_tester", "", "default_testers_function", { make_param("a","String",Nan::Undefined()),		make_param("a","Function",Nan::New<v8::Function>(ORFunctionCallback)) }, number_testers_string_function);
		overload->addOverload("or_default_tester", "", "default_testers_function", { make_param("a","Boolean",Nan::Undefined()),		make_param("a","Function",Nan::New<v8::Function>(ORFunctionCallback)) }, number_testers_bool_function);
		overload->addOverload("or_default_tester", "", "default_testers_function", { make_param("a","Date",Nan::Undefined()),			make_param("a","Function",Nan::New<v8::Function>(ORFunctionCallback)) }, number_testers_date_function);
		overload->addOverload("or_default_tester", "", "default_testers_function", { make_param("a","Function",Nan::Undefined()) ,		make_param("a","Function",Nan::New<v8::Function>(ORFunctionCallback)) }, number_testers_function_function);
		overload->addOverload("or_default_tester", "", "default_testers_function", { make_param("a","Buffer",Nan::Undefined()),		make_param("a","Function",Nan::New<v8::Function>(ORFunctionCallback)) }, number_testers_buffer_function);
#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_function", { make_param("a","Map",Nan::Undefined()),			make_param("a","Function",Nan::New<v8::Function>(ORFunctionCallback)) }, number_testers_map_function);
		overload->addOverload("or_default_tester", "", "default_testers_function", { make_param("a","Set",Nan::Undefined()),			make_param("a","Function",Nan::New<v8::Function>(ORFunctionCallback)) }, number_testers_set_function);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_function", { make_param("a","Promise",Nan::Undefined()),		make_param("a","Function",Nan::New<v8::Function>(ORFunctionCallback)) }, number_testers_promise_function);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_function", { make_param("a","Proxy",Nan::Undefined()),			make_param("a","Function",Nan::New<v8::Function>(ORFunctionCallback)) }, number_testers_proxy_function);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_function", { make_param("a","RegExp",Nan::Undefined()),		make_param("a","Function",Nan::New<v8::Function>(ORFunctionCallback)) }, number_testers_regexp_function);
		overload->addOverload("or_default_tester", "", "default_testers_function", { make_param("a","base_class",Nan::Undefined()),	make_param("a","Function",Nan::New<v8::Function>(ORFunctionCallback)) }, number_testers_base_class_function);
		overload->addOverload("or_default_tester", "", "default_testers_function", { make_param("a","derived_class",Nan::Undefined()), make_param("a","Function",Nan::New<v8::Function>(ORFunctionCallback)) }, number_testers_derived_class_function);
		overload->addOverload("or_default_tester", "", "default_testers_function", { make_param("a","struct_A",Nan::Undefined()),		make_param("a","Function",Nan::New<v8::Function>(ORFunctionCallback)) }, number_testers_struct_A_function);
		overload->addOverload("or_default_tester", "", "default_testers_function", { make_param("a","struct_B",Nan::Undefined()),		make_param("a","Function",Nan::New<v8::Function>(ORFunctionCallback)) }, number_testers_struct_B_function);
		overload->addOverload("or_default_tester", "", "default_testers_function", { make_param("a","Array",Nan::Undefined()),			make_param("a","Function",Nan::New<v8::Function>(ORFunctionCallback)) }, number_testers_array_function);
		overload->addOverload("or_default_tester", "", "default_testers_function", {}, number_testers);




		overload->addOverload("or_default_tester", "", "default_testers_buffer", { make_param("a","Number",Nan::Undefined()),		  make_param("a","Buffer",Nan::NewBuffer(0).ToLocalChecked()) }, number_testers_number_buffer);
		overload->addOverload("or_default_tester", "", "default_testers_buffer", { make_param("a","String",Nan::Undefined()),		  make_param("a","Buffer",Nan::NewBuffer(0).ToLocalChecked()) }, number_testers_string_buffer);
		overload->addOverload("or_default_tester", "", "default_testers_buffer", { make_param("a","Boolean",Nan::Undefined()),		  make_param("a","Buffer",Nan::NewBuffer(0).ToLocalChecked()) }, number_testers_bool_buffer);
		overload->addOverload("or_default_tester", "", "default_testers_buffer", { make_param("a","Date",Nan::Undefined()),		  make_param("a","Buffer",Nan::NewBuffer(0).ToLocalChecked()) }, number_testers_date_buffer);
		overload->addOverload("or_default_tester", "", "default_testers_buffer", { make_param("a","Function",Nan::Undefined()) ,	  make_param("a","Buffer",Nan::NewBuffer(0).ToLocalChecked()) }, number_testers_function_buffer);
		overload->addOverload("or_default_tester", "", "default_testers_buffer", { make_param("a","Buffer",Nan::Undefined()),		  make_param("a","Buffer",Nan::NewBuffer(0).ToLocalChecked()) }, number_testers_buffer_buffer);
#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_buffer", { make_param("a","Map",Nan::Undefined()),			  make_param("a","Buffer",Nan::NewBuffer(0).ToLocalChecked()) }, number_testers_map_buffer);
		overload->addOverload("or_default_tester", "", "default_testers_buffer", { make_param("a","Set",Nan::Undefined()),			  make_param("a","Buffer",Nan::NewBuffer(0).ToLocalChecked()) }, number_testers_set_buffer);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_buffer", { make_param("a","Promise",Nan::Undefined()),		  make_param("a","Buffer",Nan::NewBuffer(0).ToLocalChecked()) }, number_testers_promise_buffer);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_buffer", { make_param("a","Proxy",Nan::Undefined()),		  make_param("a","Buffer",Nan::NewBuffer(0).ToLocalChecked()) }, number_testers_proxy_buffer);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_buffer", { make_param("a","RegExp",Nan::Undefined()),		  make_param("a","Buffer",Nan::NewBuffer(0).ToLocalChecked()) }, number_testers_regexp_buffer);
		overload->addOverload("or_default_tester", "", "default_testers_buffer", { make_param("a","base_class",Nan::Undefined()),	  make_param("a","Buffer",Nan::NewBuffer(0).ToLocalChecked()) }, number_testers_base_class_buffer);
		overload->addOverload("or_default_tester", "", "default_testers_buffer", { make_param("a","derived_class",Nan::Undefined()), make_param("a","Buffer",Nan::NewBuffer(0).ToLocalChecked()) }, number_testers_derived_class_buffer);
		overload->addOverload("or_default_tester", "", "default_testers_buffer", { make_param("a","struct_A",Nan::Undefined()),      make_param("a","Buffer",Nan::NewBuffer(0).ToLocalChecked()) }, number_testers_struct_A_buffer);
		overload->addOverload("or_default_tester", "", "default_testers_buffer", { make_param("a","struct_B",Nan::Undefined()),      make_param("a","Buffer",Nan::NewBuffer(0).ToLocalChecked()) }, number_testers_struct_B_buffer);
		overload->addOverload("or_default_tester", "", "default_testers_buffer", { make_param("a","Array",Nan::Undefined()),         make_param("a","Buffer",Nan::NewBuffer(0).ToLocalChecked()) }, number_testers_array_buffer);
		overload->addOverload("or_default_tester", "", "default_testers_buffer", {}, number_testers);



#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_map", { make_param("a","Number",Nan::Undefined()),make_param("a","Map",v8::Map::New(v8::Isolate::GetCurrent())) }, number_testers_number_map);
		overload->addOverload("or_default_tester", "", "default_testers_map", { make_param("a","String",Nan::Undefined()),make_param("a","Map",v8::Map::New(v8::Isolate::GetCurrent())) }, number_testers_string_map);
		overload->addOverload("or_default_tester", "", "default_testers_map", { make_param("a","Boolean",Nan::Undefined()), make_param("a","Map",v8::Map::New(v8::Isolate::GetCurrent())) }, number_testers_bool_map);
		overload->addOverload("or_default_tester", "", "default_testers_map", { make_param("a","Date",Nan::Undefined()),make_param("a","Map",v8::Map::New(v8::Isolate::GetCurrent())) }, number_testers_date_map);
		overload->addOverload("or_default_tester", "", "default_testers_map", { make_param("a","Function",Nan::Undefined()) , make_param("a","Map",v8::Map::New(v8::Isolate::GetCurrent())) }, number_testers_function_map);
		overload->addOverload("or_default_tester", "", "default_testers_map", { make_param("a","Buffer",Nan::Undefined()), make_param("a","Map",v8::Map::New(v8::Isolate::GetCurrent())) }, number_testers_buffer_map);
		overload->addOverload("or_default_tester", "", "default_testers_map", { make_param("a","Map",Nan::Undefined()), make_param("a","Map",v8::Map::New(v8::Isolate::GetCurrent())) }, number_testers_map_map);
		overload->addOverload("or_default_tester", "", "default_testers_map", { make_param("a","Set",Nan::Undefined()), make_param("a","Map",v8::Map::New(v8::Isolate::GetCurrent())) }, number_testers_set_map);
		overload->addOverload("or_default_tester", "", "default_testers_map", { make_param("a","Promise",Nan::Undefined()), make_param("a","Map",v8::Map::New(v8::Isolate::GetCurrent())) }, number_testers_promise_map);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_map", { make_param("a","Proxy",Nan::Undefined()), make_param("a","Map",v8::Map::New(v8::Isolate::GetCurrent())) }, number_testers_proxy_map);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_map", { make_param("a","RegExp",Nan::Undefined()), make_param("a","Map",v8::Map::New(v8::Isolate::GetCurrent())) }, number_testers_regexp_map);
		overload->addOverload("or_default_tester", "", "default_testers_map", { make_param("a","base_class",Nan::Undefined()), make_param("a","Map",v8::Map::New(v8::Isolate::GetCurrent())) }, number_testers_base_class_map);
		overload->addOverload("or_default_tester", "", "default_testers_map", { make_param("a","derived_class",Nan::Undefined()), make_param("a","Map",v8::Map::New(v8::Isolate::GetCurrent())) }, number_testers_derived_class_map);
		overload->addOverload("or_default_tester", "", "default_testers_map", { make_param("a","struct_A",Nan::Undefined()), make_param("a","Map",v8::Map::New(v8::Isolate::GetCurrent())) }, number_testers_struct_A_map);
		overload->addOverload("or_default_tester", "", "default_testers_map", { make_param("a","struct_B",Nan::Undefined()), make_param("a","Map",v8::Map::New(v8::Isolate::GetCurrent())) }, number_testers_struct_B_map);
		overload->addOverload("or_default_tester", "", "default_testers_map", { make_param("a","Array",Nan::Undefined()), make_param("a","Map",v8::Map::New(v8::Isolate::GetCurrent())) }, number_testers_array_map);
		overload->addOverload("or_default_tester", "", "default_testers_map", {}, number_testers);
#endif


#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_set", { make_param("a","Number",Nan::Undefined()),make_param("a","Set",v8::Set::New(v8::Isolate::GetCurrent())) }, number_testers_number_set);
		overload->addOverload("or_default_tester", "", "default_testers_set", { make_param("a","String",Nan::Undefined()),make_param("a","Set",v8::Set::New(v8::Isolate::GetCurrent())) }, number_testers_string_set);
		overload->addOverload("or_default_tester", "", "default_testers_set", { make_param("a","Boolean",Nan::Undefined()), make_param("a","Set",v8::Set::New(v8::Isolate::GetCurrent())) }, number_testers_bool_set);
		overload->addOverload("or_default_tester", "", "default_testers_set", { make_param("a","Date",Nan::Undefined()),make_param("a","Set",v8::Set::New(v8::Isolate::GetCurrent())) }, number_testers_date_set);
		overload->addOverload("or_default_tester", "", "default_testers_set", { make_param("a","Function",Nan::Undefined()) , make_param("a","Set",v8::Set::New(v8::Isolate::GetCurrent())) }, number_testers_function_set);
		overload->addOverload("or_default_tester", "", "default_testers_set", { make_param("a","Buffer",Nan::Undefined()), make_param("a","Set",v8::Set::New(v8::Isolate::GetCurrent())) }, number_testers_buffer_set);
		overload->addOverload("or_default_tester", "", "default_testers_set", { make_param("a","Map",Nan::Undefined()), make_param("a","Set",v8::Set::New(v8::Isolate::GetCurrent())) }, number_testers_map_set);
		overload->addOverload("or_default_tester", "", "default_testers_set", { make_param("a","Set",Nan::Undefined()), make_param("a","Set",v8::Set::New(v8::Isolate::GetCurrent())) }, number_testers_set_set);
		overload->addOverload("or_default_tester", "", "default_testers_set", { make_param("a","Promise",Nan::Undefined()), make_param("a","Set",v8::Set::New(v8::Isolate::GetCurrent())) }, number_testers_promise_set);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_set", { make_param("a","Proxy",Nan::Undefined()), make_param("a","Set",v8::Set::New(v8::Isolate::GetCurrent())) }, number_testers_proxy_set);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_set", { make_param("a","RegExp",Nan::Undefined()), make_param("a","Set",v8::Set::New(v8::Isolate::GetCurrent())) }, number_testers_regexp_set);
		overload->addOverload("or_default_tester", "", "default_testers_set", { make_param("a","base_class",Nan::Undefined()), make_param("a","Set",v8::Set::New(v8::Isolate::GetCurrent())) }, number_testers_base_class_set);
		overload->addOverload("or_default_tester", "", "default_testers_set", { make_param("a","derived_class",Nan::Undefined()), make_param("a","Set",v8::Set::New(v8::Isolate::GetCurrent())) }, number_testers_derived_class_set);
		overload->addOverload("or_default_tester", "", "default_testers_set", { make_param("a","struct_A",Nan::Undefined()), make_param("a","Set",v8::Set::New(v8::Isolate::GetCurrent())) }, number_testers_struct_A_set);
		overload->addOverload("or_default_tester", "", "default_testers_set", { make_param("a","struct_B",Nan::Undefined()), make_param("a","Set",v8::Set::New(v8::Isolate::GetCurrent())) }, number_testers_struct_B_set);
		overload->addOverload("or_default_tester", "", "default_testers_set", { make_param("a","Array",Nan::Undefined()), make_param("a","Set",v8::Set::New(v8::Isolate::GetCurrent())) }, number_testers_array_set);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_set", {}, number_testers);



#if NODE_MODULE_VERSION >= NODE_0_12_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_promise", { make_param("a","Number",Nan::Undefined()),make_param("a","Promise",v8::Promise::New(v8::Isolate::GetCurrent())) }, number_testers_number_promise);
		overload->addOverload("or_default_tester", "", "default_testers_promise", { make_param("a","String",Nan::Undefined()),make_param("a","Promise",v8::Promise::New(v8::Isolate::GetCurrent())) }, number_testers_string_promise);
		overload->addOverload("or_default_tester", "", "default_testers_promise", { make_param("a","Boolean",Nan::Undefined()), make_param("a","Promise",v8::Promise::New(v8::Isolate::GetCurrent())) }, number_testers_bool_promise);
		overload->addOverload("or_default_tester", "", "default_testers_promise", { make_param("a","Date",Nan::Undefined()),make_param("a","Promise",v8::Promise::New(v8::Isolate::GetCurrent())) }, number_testers_date_promise);
		overload->addOverload("or_default_tester", "", "default_testers_promise", { make_param("a","Function",Nan::Undefined()) , make_param("a","Promise",v8::Promise::New(v8::Isolate::GetCurrent())) }, number_testers_function_promise);
		overload->addOverload("or_default_tester", "", "default_testers_promise", { make_param("a","Buffer",Nan::Undefined()), make_param("a","Promise",v8::Promise::New(v8::Isolate::GetCurrent())) }, number_testers_buffer_promise);
		overload->addOverload("or_default_tester", "", "default_testers_promise", { make_param("a","Map",Nan::Undefined()), make_param("a","Promise",v8::Promise::New(v8::Isolate::GetCurrent())) }, number_testers_map_promise);
		overload->addOverload("or_default_tester", "", "default_testers_promise", { make_param("a","Set",Nan::Undefined()), make_param("a","Promise",v8::Promise::New(v8::Isolate::GetCurrent())) }, number_testers_set_promise);
		overload->addOverload("or_default_tester", "", "default_testers_promise", { make_param("a","Promise",Nan::Undefined()), make_param("a","Promise",v8::Promise::New(v8::Isolate::GetCurrent())) }, number_testers_promise_promise);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_promise", { make_param("a","Proxy",Nan::Undefined()), make_param("a","Promise",v8::Promise::New(v8::Isolate::GetCurrent())) }, number_testers_proxy_promise);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_promise", { make_param("a","RegExp",Nan::Undefined()), make_param("a","Promise",v8::Promise::New(v8::Isolate::GetCurrent())) }, number_testers_regexp_promise);
		overload->addOverload("or_default_tester", "", "default_testers_promise", { make_param("a","base_class",Nan::Undefined()), make_param("a","Promise",v8::Promise::New(v8::Isolate::GetCurrent())) }, number_testers_base_class_promise);
		overload->addOverload("or_default_tester", "", "default_testers_promise", { make_param("a","derived_class",Nan::Undefined()), make_param("a","Promise",v8::Promise::New(v8::Isolate::GetCurrent())) }, number_testers_derived_class_promise);
		overload->addOverload("or_default_tester", "", "default_testers_promise", { make_param("a","struct_A",Nan::Undefined()), make_param("a","Promise",v8::Promise::New(v8::Isolate::GetCurrent())) }, number_testers_struct_A_promise);
		overload->addOverload("or_default_tester", "", "default_testers_promise", { make_param("a","struct_B",Nan::Undefined()), make_param("a","Promise",v8::Promise::New(v8::Isolate::GetCurrent())) }, number_testers_struct_B_promise);
		overload->addOverload("or_default_tester", "", "default_testers_promise", { make_param("a","Array",Nan::Undefined()), make_param("a","Promise",v8::Promise::New(v8::Isolate::GetCurrent())) }, number_testers_array_promise);
		overload->addOverload("or_default_tester", "", "default_testers_promise", {}, number_testers);
#endif


#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_proxy", { make_param("a","Number",Nan::Undefined()),			make_param("a","Proxy",v8::Proxy::New(Nan::GetCurrentContext(),Nan::New<v8::Object>(), Nan::New<v8::Object>()).ToLocalChecked()) }, number_testers_number_proxy);
		overload->addOverload("or_default_tester", "", "default_testers_proxy", { make_param("a","String",Nan::Undefined()),			make_param("a","Proxy",v8::Proxy::New(Nan::GetCurrentContext(),Nan::New<v8::Object>(), Nan::New<v8::Object>()).ToLocalChecked()) }, number_testers_string_proxy);
		overload->addOverload("or_default_tester", "", "default_testers_proxy", { make_param("a","Boolean",Nan::Undefined()),			make_param("a","Proxy",v8::Proxy::New(Nan::GetCurrentContext(),Nan::New<v8::Object>(), Nan::New<v8::Object>()).ToLocalChecked()) }, number_testers_bool_proxy);
		overload->addOverload("or_default_tester", "", "default_testers_proxy", { make_param("a","Date",Nan::Undefined()),				make_param("a","Proxy",v8::Proxy::New(Nan::GetCurrentContext(),Nan::New<v8::Object>(), Nan::New<v8::Object>()).ToLocalChecked()) }, number_testers_date_proxy);
		overload->addOverload("or_default_tester", "", "default_testers_proxy", { make_param("a","Function",Nan::Undefined()) ,		make_param("a","Proxy",v8::Proxy::New(Nan::GetCurrentContext(),Nan::New<v8::Object>(), Nan::New<v8::Object>()).ToLocalChecked()) }, number_testers_function_proxy);
		overload->addOverload("or_default_tester", "", "default_testers_proxy", { make_param("a","Buffer",Nan::Undefined()),			make_param("a","Proxy",v8::Proxy::New(Nan::GetCurrentContext(),Nan::New<v8::Object>(), Nan::New<v8::Object>()).ToLocalChecked()) }, number_testers_buffer_proxy);
		overload->addOverload("or_default_tester", "", "default_testers_proxy", { make_param("a","Map",Nan::Undefined()),				make_param("a","Proxy",v8::Proxy::New(Nan::GetCurrentContext(),Nan::New<v8::Object>(), Nan::New<v8::Object>()).ToLocalChecked()) }, number_testers_map_proxy);
		overload->addOverload("or_default_tester", "", "default_testers_proxy", { make_param("a","Set",Nan::Undefined()),				make_param("a","Proxy",v8::Proxy::New(Nan::GetCurrentContext(),Nan::New<v8::Object>(), Nan::New<v8::Object>()).ToLocalChecked()) }, number_testers_set_proxy);
		overload->addOverload("or_default_tester", "", "default_testers_proxy", { make_param("a","Promise",Nan::Undefined()),			make_param("a","Proxy",v8::Proxy::New(Nan::GetCurrentContext(),Nan::New<v8::Object>(), Nan::New<v8::Object>()).ToLocalChecked()) }, number_testers_promise_proxy);
		overload->addOverload("or_default_tester", "", "default_testers_proxy", { make_param("a","Proxy",Nan::Undefined()),			make_param("a","Proxy",v8::Proxy::New(Nan::GetCurrentContext(),Nan::New<v8::Object>(), Nan::New<v8::Object>()).ToLocalChecked()) }, number_testers_proxy_proxy);
		overload->addOverload("or_default_tester", "", "default_testers_proxy", { make_param("a","RegExp",Nan::Undefined()),			make_param("a","Proxy",v8::Proxy::New(Nan::GetCurrentContext(),Nan::New<v8::Object>(), Nan::New<v8::Object>()).ToLocalChecked()) }, number_testers_regexp_proxy);
		overload->addOverload("or_default_tester", "", "default_testers_proxy", { make_param("a","base_class",Nan::Undefined()),		make_param("a","Proxy",v8::Proxy::New(Nan::GetCurrentContext(),Nan::New<v8::Object>(), Nan::New<v8::Object>()).ToLocalChecked()) }, number_testers_base_class_proxy);
		overload->addOverload("or_default_tester", "", "default_testers_proxy", { make_param("a","derived_class",Nan::Undefined()),	make_param("a","Proxy",v8::Proxy::New(Nan::GetCurrentContext(),Nan::New<v8::Object>(), Nan::New<v8::Object>()).ToLocalChecked()) }, number_testers_derived_class_proxy);
		overload->addOverload("or_default_tester", "", "default_testers_proxy", { make_param("a","struct_A",Nan::Undefined()),			make_param("a","Proxy",v8::Proxy::New(Nan::GetCurrentContext(),Nan::New<v8::Object>(), Nan::New<v8::Object>()).ToLocalChecked()) }, number_testers_struct_A_proxy);
		overload->addOverload("or_default_tester", "", "default_testers_proxy", { make_param("a","struct_B",Nan::Undefined()),			make_param("a","Proxy",v8::Proxy::New(Nan::GetCurrentContext(),Nan::New<v8::Object>(), Nan::New<v8::Object>()).ToLocalChecked()) }, number_testers_struct_B_proxy);
		overload->addOverload("or_default_tester", "", "default_testers_proxy", { make_param("a","Array",Nan::Undefined()),			make_param("a","Proxy",v8::Proxy::New(Nan::GetCurrentContext(),Nan::New<v8::Object>(), Nan::New<v8::Object>()).ToLocalChecked()) }, number_testers_array_proxy);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_proxy", {}, number_testers);




		overload->addOverload("or_default_tester", "", "default_testers_regexp", { make_param("a","Number",Nan::Undefined()),		  make_param("a","RegExp",Nan::New<v8::RegExp>(Nan::New<v8::String>("[a-z]").ToLocalChecked(),v8::RegExp::Flags::kNone).ToLocalChecked()) }, number_testers_number_regexp);
		overload->addOverload("or_default_tester", "", "default_testers_regexp", { make_param("a","String",Nan::Undefined()),		  make_param("a","RegExp",Nan::New<v8::RegExp>(Nan::New<v8::String>("[a-z]").ToLocalChecked(),v8::RegExp::Flags::kNone).ToLocalChecked()) }, number_testers_string_regexp);
		overload->addOverload("or_default_tester", "", "default_testers_regexp", { make_param("a","Boolean",Nan::Undefined()),		  make_param("a","RegExp",Nan::New<v8::RegExp>(Nan::New<v8::String>("[a-z]").ToLocalChecked(),v8::RegExp::Flags::kNone).ToLocalChecked()) }, number_testers_bool_regexp);
		overload->addOverload("or_default_tester", "", "default_testers_regexp", { make_param("a","Date",Nan::Undefined()),		  make_param("a","RegExp",Nan::New<v8::RegExp>(Nan::New<v8::String>("[a-z]").ToLocalChecked(),v8::RegExp::Flags::kNone).ToLocalChecked()) }, number_testers_date_regexp);
		overload->addOverload("or_default_tester", "", "default_testers_regexp", { make_param("a","Function",Nan::Undefined()) ,	  make_param("a","RegExp",Nan::New<v8::RegExp>(Nan::New<v8::String>("[a-z]").ToLocalChecked(),v8::RegExp::Flags::kNone).ToLocalChecked()) }, number_testers_function_regexp);
		overload->addOverload("or_default_tester", "", "default_testers_regexp", { make_param("a","Buffer",Nan::Undefined()),		  make_param("a","RegExp",Nan::New<v8::RegExp>(Nan::New<v8::String>("[a-z]").ToLocalChecked(),v8::RegExp::Flags::kNone).ToLocalChecked()) }, number_testers_buffer_regexp);
		overload->addOverload("or_default_tester", "", "default_testers_regexp", { make_param("a","Map",Nan::Undefined()),			  make_param("a","RegExp",Nan::New<v8::RegExp>(Nan::New<v8::String>("[a-z]").ToLocalChecked(),v8::RegExp::Flags::kNone).ToLocalChecked()) }, number_testers_map_regexp);
		overload->addOverload("or_default_tester", "", "default_testers_regexp", { make_param("a","Set",Nan::Undefined()),			  make_param("a","RegExp",Nan::New<v8::RegExp>(Nan::New<v8::String>("[a-z]").ToLocalChecked(),v8::RegExp::Flags::kNone).ToLocalChecked()) }, number_testers_set_regexp);
		overload->addOverload("or_default_tester", "", "default_testers_regexp", { make_param("a","Promise",Nan::Undefined()),		  make_param("a","RegExp",Nan::New<v8::RegExp>(Nan::New<v8::String>("[a-z]").ToLocalChecked(),v8::RegExp::Flags::kNone).ToLocalChecked()) }, number_testers_promise_regexp);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_regexp", { make_param("a","Proxy",Nan::Undefined()),		  make_param("a","RegExp",Nan::New<v8::RegExp>(Nan::New<v8::String>("[a-z]").ToLocalChecked(),v8::RegExp::Flags::kNone).ToLocalChecked()) }, number_testers_proxy_regexp);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_regexp", { make_param("a","RegExp",Nan::Undefined()),		  make_param("a","RegExp",Nan::New<v8::RegExp>(Nan::New<v8::String>("[a-z]").ToLocalChecked(),v8::RegExp::Flags::kNone).ToLocalChecked()) }, number_testers_regexp_regexp);
		overload->addOverload("or_default_tester", "", "default_testers_regexp", { make_param("a","base_class",Nan::Undefined()),	  make_param("a","RegExp",Nan::New<v8::RegExp>(Nan::New<v8::String>("[a-z]").ToLocalChecked(),v8::RegExp::Flags::kNone).ToLocalChecked()) }, number_testers_base_class_regexp);
		overload->addOverload("or_default_tester", "", "default_testers_regexp", { make_param("a","derived_class",Nan::Undefined()), make_param("a","RegExp",Nan::New<v8::RegExp>(Nan::New<v8::String>("[a-z]").ToLocalChecked(),v8::RegExp::Flags::kNone).ToLocalChecked()) }, number_testers_derived_class_regexp);
		overload->addOverload("or_default_tester", "", "default_testers_regexp", { make_param("a","struct_A",Nan::Undefined()),      make_param("a","RegExp",Nan::New<v8::RegExp>(Nan::New<v8::String>("[a-z]").ToLocalChecked(),v8::RegExp::Flags::kNone).ToLocalChecked()) }, number_testers_struct_A_regexp);
		overload->addOverload("or_default_tester", "", "default_testers_regexp", { make_param("a","struct_B",Nan::Undefined()),      make_param("a","RegExp",Nan::New<v8::RegExp>(Nan::New<v8::String>("[a-z]").ToLocalChecked(),v8::RegExp::Flags::kNone).ToLocalChecked()) }, number_testers_struct_B_regexp);
		overload->addOverload("or_default_tester", "", "default_testers_regexp", { make_param("a","Array",Nan::Undefined()),         make_param("a","RegExp",Nan::New<v8::RegExp>(Nan::New<v8::String>("[a-z]").ToLocalChecked(),v8::RegExp::Flags::kNone).ToLocalChecked()) }, number_testers_array_regexp);
		overload->addOverload("or_default_tester", "", "default_testers_regexp", {}, number_testers);




		overload->addOverload("or_default_tester", "", "default_testers_base_class", { make_param("a","Number",Nan::Undefined()),make_param<base_class*>("a","base_class",base_class::New()) }, number_testers_number_base_class);
		overload->addOverload("or_default_tester", "", "default_testers_base_class", { make_param("a","String",Nan::Undefined()),make_param<base_class*>("a","base_class",base_class::New()) }, number_testers_string_base_class);
		overload->addOverload("or_default_tester", "", "default_testers_base_class", { make_param("a","Boolean",Nan::Undefined()), make_param<base_class*>("a","base_class",base_class::New()) }, number_testers_bool_base_class);
		overload->addOverload("or_default_tester", "", "default_testers_base_class", { make_param("a","Date",Nan::Undefined()),make_param<base_class*>("a","base_class",base_class::New()) }, number_testers_date_base_class);
		overload->addOverload("or_default_tester", "", "default_testers_base_class", { make_param("a","Function",Nan::Undefined()) , make_param<base_class*>("a","base_class",base_class::New()) }, number_testers_function_base_class);
		overload->addOverload("or_default_tester", "", "default_testers_base_class", { make_param("a","Buffer",Nan::Undefined()), make_param<base_class*>("a","base_class",base_class::New()) }, number_testers_buffer_base_class);
		overload->addOverload("or_default_tester", "", "default_testers_base_class", { make_param("a","Map",Nan::Undefined()), make_param<base_class*>("a","base_class",base_class::New()) }, number_testers_map_base_class);
		overload->addOverload("or_default_tester", "", "default_testers_base_class", { make_param("a","Set",Nan::Undefined()), make_param<base_class*>("a","base_class",base_class::New()) }, number_testers_set_base_class);
		overload->addOverload("or_default_tester", "", "default_testers_base_class", { make_param("a","Promise",Nan::Undefined()), make_param<base_class*>("a","base_class",base_class::New()) }, number_testers_promise_base_class);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_base_class", { make_param("a","Proxy",Nan::Undefined()), make_param<base_class*>("a","base_class",base_class::New()) }, number_testers_proxy_base_class);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_base_class", { make_param("a","RegExp",Nan::Undefined()), make_param<base_class*>("a","base_class",base_class::New()) }, number_testers_regexp_base_class);
		overload->addOverload("or_default_tester", "", "default_testers_base_class", { make_param("a","base_class",Nan::Undefined()), make_param<base_class*>("a","base_class",base_class::New()) }, number_testers_base_class_base_class);
		overload->addOverload("or_default_tester", "", "default_testers_base_class", { make_param("a","derived_class",Nan::Undefined()), make_param<base_class*>("a","base_class",base_class::New()) }, number_testers_derived_class_base_class);
		overload->addOverload("or_default_tester", "", "default_testers_base_class", { make_param("a","struct_A",Nan::Undefined()), make_param<base_class*>("a","base_class",base_class::New()) }, number_testers_struct_A_base_class);
		overload->addOverload("or_default_tester", "", "default_testers_base_class", { make_param("a","Array",Nan::Undefined()), make_param<base_class*>("a","base_class",base_class::New()) }, number_testers_array_base_class);
		overload->addOverload("or_default_tester", "", "default_testers_base_class", { make_param("a","struct_B",Nan::Undefined()), make_param<base_class*>("a","base_class",base_class::New()) }, number_testers_struct_B_base_class);
		overload->addOverload("or_default_tester", "", "default_testers_base_class", {}, number_testers);




		overload->addOverload("or_default_tester", "", "default_testers_derived_class", { make_param("a","Number",Nan::Undefined()),make_param<derived_class*>("a","derived_class",derived_class::New()) }, number_testers_number_derived_class);
		overload->addOverload("or_default_tester", "", "default_testers_derived_class", { make_param("a","String",Nan::Undefined()),make_param<derived_class*>("a","derived_class",derived_class::New()) }, number_testers_string_derived_class);
		overload->addOverload("or_default_tester", "", "default_testers_derived_class", { make_param("a","Boolean",Nan::Undefined()), make_param<derived_class*>("a","derived_class",derived_class::New()) }, number_testers_bool_derived_class);
		overload->addOverload("or_default_tester", "", "default_testers_derived_class", { make_param("a","Date",Nan::Undefined()),make_param<derived_class*>("a","derived_class",derived_class::New()) }, number_testers_date_derived_class);
		overload->addOverload("or_default_tester", "", "default_testers_derived_class", { make_param("a","Function",Nan::Undefined()) , make_param<derived_class*>("a","derived_class",derived_class::New()) }, number_testers_function_derived_class);
		overload->addOverload("or_default_tester", "", "default_testers_derived_class", { make_param("a","Buffer",Nan::Undefined()), make_param<derived_class*>("a","derived_class",derived_class::New()) }, number_testers_buffer_derived_class);
		overload->addOverload("or_default_tester", "", "default_testers_derived_class", { make_param("a","Map",Nan::Undefined()), make_param<derived_class*>("a","derived_class",derived_class::New()) }, number_testers_map_derived_class);
		overload->addOverload("or_default_tester", "", "default_testers_derived_class", { make_param("a","Set",Nan::Undefined()), make_param<derived_class*>("a","derived_class",derived_class::New()) }, number_testers_set_derived_class);
		overload->addOverload("or_default_tester", "", "default_testers_derived_class", { make_param("a","Promise",Nan::Undefined()), make_param<derived_class*>("a","derived_class",derived_class::New()) }, number_testers_promise_derived_class);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_derived_class", { make_param("a","Proxy",Nan::Undefined()), make_param<derived_class*>("a","derived_class",derived_class::New()) }, number_testers_proxy_derived_class);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_derived_class", { make_param("a","RegExp",Nan::Undefined()), make_param<derived_class*>("a","derived_class",derived_class::New()) }, number_testers_regexp_derived_class);
		overload->addOverload("or_default_tester", "", "default_testers_derived_class", { make_param("a","base_class",Nan::Undefined()), make_param<derived_class*>("a","derived_class",derived_class::New()) }, number_testers_base_class_derived_class);
		overload->addOverload("or_default_tester", "", "default_testers_derived_class", { make_param("a","derived_class",Nan::Undefined()), make_param<derived_class*>("a","derived_class",derived_class::New()) }, number_testers_derived_class_derived_class);
		overload->addOverload("or_default_tester", "", "default_testers_derived_class", { make_param("a","struct_A",Nan::Undefined()), make_param<derived_class*>("a","derived_class",derived_class::New()) }, number_testers_struct_A_derived_class);
		overload->addOverload("or_default_tester", "", "default_testers_derived_class", { make_param("a","struct_B",Nan::Undefined()), make_param<derived_class*>("a","derived_class",derived_class::New()) }, number_testers_struct_B_derived_class);
		overload->addOverload("or_default_tester", "", "default_testers_derived_class", { make_param("a","Array",Nan::Undefined()), make_param<derived_class*>("a","derived_class",derived_class::New()) }, number_testers_array_derived_class);
		overload->addOverload("or_default_tester", "", "default_testers_derived_class", {}, number_testers);




		overload->addOverload("or_default_tester", "", "default_testers_struct_A", { make_param("a","Number",Nan::Undefined()),		make_param("a","struct_A",struct_A::New("val1","val2")) }, number_testers_number_struct_A);
		overload->addOverload("or_default_tester", "", "default_testers_struct_A", { make_param("a","String",Nan::Undefined()),		make_param("a","struct_A",struct_A::New("val1","val2")) }, number_testers_string_struct_A);
		overload->addOverload("or_default_tester", "", "default_testers_struct_A", { make_param("a","Boolean",Nan::Undefined()),		make_param("a","struct_A",struct_A::New("val1","val2")) }, number_testers_bool_struct_A);
		overload->addOverload("or_default_tester", "", "default_testers_struct_A", { make_param("a","Date",Nan::Undefined()),			make_param("a","struct_A",struct_A::New("val1","val2")) }, number_testers_date_struct_A);
		overload->addOverload("or_default_tester", "", "default_testers_struct_A", { make_param("a","Function",Nan::Undefined()) ,		make_param("a","struct_A",struct_A::New("val1","val2")) }, number_testers_function_struct_A);
		overload->addOverload("or_default_tester", "", "default_testers_struct_A", { make_param("a","Buffer",Nan::Undefined()),		make_param("a","struct_A",struct_A::New("val1","val2")) }, number_testers_buffer_struct_A);
		overload->addOverload("or_default_tester", "", "default_testers_struct_A", { make_param("a","Map",Nan::Undefined()),			make_param("a","struct_A",struct_A::New("val1","val2")) }, number_testers_map_struct_A);
		overload->addOverload("or_default_tester", "", "default_testers_struct_A", { make_param("a","Set",Nan::Undefined()),			make_param("a","struct_A",struct_A::New("val1","val2")) }, number_testers_set_struct_A);
		overload->addOverload("or_default_tester", "", "default_testers_struct_A", { make_param("a","Promise",Nan::Undefined()),		make_param("a","struct_A",struct_A::New("val1","val2")) }, number_testers_promise_struct_A);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_struct_A", { make_param("a","Proxy",Nan::Undefined()),			make_param("a","struct_A",struct_A::New("val1","val2")) }, number_testers_proxy_struct_A);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_struct_A", { make_param("a","RegExp",Nan::Undefined()),		make_param("a","struct_A",struct_A::New("val1","val2")) }, number_testers_regexp_struct_A);
		overload->addOverload("or_default_tester", "", "default_testers_struct_A", { make_param("a","base_class",Nan::Undefined()),	make_param("a","struct_A",struct_A::New("val1","val2")) }, number_testers_base_class_struct_A);
		overload->addOverload("or_default_tester", "", "default_testers_struct_A", { make_param("a","derived_class",Nan::Undefined()), make_param("a","struct_A",struct_A::New("val1","val2")) }, number_testers_derived_class_struct_A);
		overload->addOverload("or_default_tester", "", "default_testers_struct_A", { make_param("a","struct_A",Nan::Undefined()),		make_param("a","struct_A",struct_A::New("val1","val2")) }, number_testers_struct_A_struct_A);
		overload->addOverload("or_default_tester", "", "default_testers_struct_A", { make_param("a","Array",Nan::Undefined()),			make_param("a","struct_A",struct_A::New("val1","val2")) }, number_testers_array_struct_A);
		overload->addOverload("or_default_tester", "", "default_testers_struct_A", { make_param("a","struct_B",Nan::Undefined()),		make_param("a","struct_A",struct_A::New("val1","val2")) }, number_testers_struct_B_struct_A);
		overload->addOverload("or_default_tester", "", "default_testers_struct_A", {}, number_testers);




		overload->addOverload("or_default_tester", "", "default_testers_struct_B", { make_param("a","Number",Nan::Undefined()),		make_param("a","struct_B",struct_B::New("val1",2)) }, number_testers_number_struct_B);
		overload->addOverload("or_default_tester", "", "default_testers_struct_B", { make_param("a","String",Nan::Undefined()),		make_param("a","struct_B",struct_B::New("val1",2)) }, number_testers_string_struct_B);
		overload->addOverload("or_default_tester", "", "default_testers_struct_B", { make_param("a","Boolean",Nan::Undefined()),		make_param("a","struct_B",struct_B::New("val1",2)) }, number_testers_bool_struct_B);
		overload->addOverload("or_default_tester", "", "default_testers_struct_B", { make_param("a","Date",Nan::Undefined()),			make_param("a","struct_B",struct_B::New("val1",2)) }, number_testers_date_struct_B);
		overload->addOverload("or_default_tester", "", "default_testers_struct_B", { make_param("a","Function",Nan::Undefined()) ,		make_param("a","struct_B",struct_B::New("val1",2)) }, number_testers_function_struct_B);
		overload->addOverload("or_default_tester", "", "default_testers_struct_B", { make_param("a","Buffer",Nan::Undefined()),		make_param("a","struct_B",struct_B::New("val1",2)) }, number_testers_buffer_struct_B);
		overload->addOverload("or_default_tester", "", "default_testers_struct_B", { make_param("a","Map",Nan::Undefined()),			make_param("a","struct_B",struct_B::New("val1",2)) }, number_testers_map_struct_B);
		overload->addOverload("or_default_tester", "", "default_testers_struct_B", { make_param("a","Set",Nan::Undefined()),			make_param("a","struct_B",struct_B::New("val1",2)) }, number_testers_set_struct_B);
		overload->addOverload("or_default_tester", "", "default_testers_struct_B", { make_param("a","Promise",Nan::Undefined()),		make_param("a","struct_B",struct_B::New("val1",2)) }, number_testers_promise_struct_B);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_struct_B", { make_param("a","Proxy",Nan::Undefined()),			make_param("a","struct_B",struct_B::New("val1",2)) }, number_testers_proxy_struct_B);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_struct_B", { make_param("a","RegExp",Nan::Undefined()),		make_param("a","struct_B",struct_B::New("val1",2)) }, number_testers_regexp_struct_B);
		overload->addOverload("or_default_tester", "", "default_testers_struct_B", { make_param("a","base_class",Nan::Undefined()),	make_param("a","struct_B",struct_B::New("val1",2)) }, number_testers_base_class_struct_B);
		overload->addOverload("or_default_tester", "", "default_testers_struct_B", { make_param("a","derived_class",Nan::Undefined()), make_param("a","struct_B",struct_B::New("val1",2)) }, number_testers_derived_class_struct_B);
		overload->addOverload("or_default_tester", "", "default_testers_struct_B", { make_param("a","struct_A",Nan::Undefined()),		make_param("a","struct_B",struct_B::New("val1",2)) }, number_testers_struct_A_struct_B);
		overload->addOverload("or_default_tester", "", "default_testers_struct_B", { make_param("a","struct_B",Nan::Undefined()),		make_param("a","struct_B",struct_B::New("val1",2)) }, number_testers_struct_B_struct_B);
		overload->addOverload("or_default_tester", "", "default_testers_struct_B", { make_param("a","Array",Nan::Undefined()),			make_param("a","struct_B",struct_B::New("val1",2)) }, number_testers_array_struct_B);
		overload->addOverload("or_default_tester", "", "default_testers_struct_B", {}, number_testers);



		overload->addOverload("or_default_tester", "", "default_testers_array", { make_param("a","Number",Nan::Undefined()),			make_param("a","Array",Nan::New<v8::Array>()) }, number_testers_number_array);
		overload->addOverload("or_default_tester", "", "default_testers_array", { make_param("a","String",Nan::Undefined()),			make_param("a","Array",Nan::New<v8::Array>()) }, number_testers_string_array);
		overload->addOverload("or_default_tester", "", "default_testers_array", { make_param("a","Boolean",Nan::Undefined()),			make_param("a","Array",Nan::New<v8::Array>()) }, number_testers_bool_array);
		overload->addOverload("or_default_tester", "", "default_testers_array", { make_param("a","Date",Nan::Undefined()),				make_param("a","Array",Nan::New<v8::Array>()) }, number_testers_date_array);
		overload->addOverload("or_default_tester", "", "default_testers_array", { make_param("a","Function",Nan::Undefined()),			make_param("a","Array",Nan::New<v8::Array>()) }, number_testers_function_array);
		overload->addOverload("or_default_tester", "", "default_testers_array", { make_param("a","Buffer",Nan::Undefined()),			make_param("a","Array",Nan::New<v8::Array>()) }, number_testers_buffer_array);
#if NODE_MODULE_VERSION >= NODE_4_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_array", { make_param("a","Map",Nan::Undefined()),				make_param("a","Array",Nan::New<v8::Array>()) }, number_testers_map_array);
		overload->addOverload("or_default_tester", "", "default_testers_array", { make_param("a","Set",Nan::Undefined()),				make_param("a","Array",Nan::New<v8::Array>()) }, number_testers_set_array);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_array", { make_param("a","Promise",Nan::Undefined()),			make_param("a","Array",Nan::New<v8::Array>()) }, number_testers_promise_array);
#if NODE_MODULE_VERSION >= NODE_6_0_MODULE_VERSION
		overload->addOverload("or_default_tester", "", "default_testers_array", { make_param("a","Proxy",Nan::Undefined()),			make_param("a","Array",Nan::New<v8::Array>()) }, number_testers_proxy_array);
#endif
		overload->addOverload("or_default_tester", "", "default_testers_array", { make_param("a","RegExp",Nan::Undefined()),			make_param("a","Array",Nan::New<v8::Array>()) }, number_testers_regexp_array);
		overload->addOverload("or_default_tester", "", "default_testers_array", { make_param("a","base_class",Nan::Undefined()),		make_param("a","Array",Nan::New<v8::Array>()) }, number_testers_base_class_array);
		overload->addOverload("or_default_tester", "", "default_testers_array", { make_param("a","derived_class",Nan::Undefined()),	make_param("a","Array",Nan::New<v8::Array>()) }, number_testers_derived_class_array);
		overload->addOverload("or_default_tester", "", "default_testers_array", { make_param("a","struct_A",Nan::Undefined()),			make_param("a","Array",Nan::New<v8::Array>()) }, number_testers_struct_A_array);
		overload->addOverload("or_default_tester", "", "default_testers_array", { make_param("a","Array",Nan::Undefined()),			make_param("a","Array",Nan::New<v8::Array>()) }, number_testers_array_array);
		overload->addOverload("or_default_tester", "", "default_testers_array", { make_param("a","struct_B",Nan::Undefined()),			make_param("a","Array",Nan::New<v8::Array>()) }, number_testers_struct_B_array);
		overload->addOverload("or_default_tester", "", "default_testers_array", {}, number_testers);


		//register functions in v8
		general_callback::overload = overload;
		Nan::SetMethod(target, "default_testers_number", general_callback::tester_callback, Nan::New("default_testers_number").ToLocalChecked());
		Nan::SetMethod(target, "default_testers_string", general_callback::tester_callback, Nan::New("default_testers_string").ToLocalChecked());
		Nan::SetMethod(target, "default_testers_bool", general_callback::tester_callback, Nan::New("default_testers_bool").ToLocalChecked());
		Nan::SetMethod(target, "default_testers_date", general_callback::tester_callback, Nan::New("default_testers_date").ToLocalChecked());
		Nan::SetMethod(target, "default_testers_function", general_callback::tester_callback, Nan::New("default_testers_function").ToLocalChecked());
		Nan::SetMethod(target, "default_testers_buffer", general_callback::tester_callback, Nan::New("default_testers_buffer").ToLocalChecked());
		Nan::SetMethod(target, "default_testers_map", general_callback::tester_callback, Nan::New("default_testers_map").ToLocalChecked());
		Nan::SetMethod(target, "default_testers_set", general_callback::tester_callback, Nan::New("default_testers_set").ToLocalChecked());
		Nan::SetMethod(target, "default_testers_promise", general_callback::tester_callback, Nan::New("default_testers_promise").ToLocalChecked());
		Nan::SetMethod(target, "default_testers_proxy", general_callback::tester_callback, Nan::New("default_testers_proxy").ToLocalChecked());
		Nan::SetMethod(target, "default_testers_regexp", general_callback::tester_callback, Nan::New("default_testers_regexp").ToLocalChecked());
		Nan::SetMethod(target, "default_testers_base_class", general_callback::tester_callback, Nan::New("default_testers_base_class").ToLocalChecked());
		Nan::SetMethod(target, "default_testers_derived_class", general_callback::tester_callback, Nan::New("default_testers_derived_class").ToLocalChecked());
		Nan::SetMethod(target, "default_testers_struct_A", general_callback::tester_callback, Nan::New("default_testers_struct_A").ToLocalChecked());
		Nan::SetMethod(target, "default_testers_struct_B", general_callback::tester_callback, Nan::New("default_testers_struct_B").ToLocalChecked());
		Nan::SetMethod(target, "default_testers_array", general_callback::tester_callback, Nan::New("default_testers_array").ToLocalChecked());
	}

}

#endif