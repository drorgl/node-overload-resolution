#ifndef _O_R_STRUCT_TESTER_H_
#define _O_R_STRUCT_TESTER_H_
#include "../overload_resolution.h"
using namespace v8;

namespace or_struct_tester {

	namespace general_callback {
		std::shared_ptr<overload_resolution> overload;
		NAN_METHOD(tester_callback) {
			return overload->execute("or_struct_tester", info);
		}
	}

	NAN_METHOD(structs_testers) {
		info.GetReturnValue().Set(Nan::New("structs_testers.no_parameters").ToLocalChecked());
	}

	NAN_METHOD(structs_testers_struct_A) {
		info.GetReturnValue().Set(Nan::New("structs_testers.struct_A").ToLocalChecked());
	}

	NAN_METHOD(structs_testers_struct_B) {
		info.GetReturnValue().Set(Nan::New("structs_testers.struct_B").ToLocalChecked());
	}

	NAN_METHOD(structs_testers_struct_A_struct_B) {
		info.GetReturnValue().Set(Nan::New("structs_testers.struct_A_struct_B").ToLocalChecked());
	}

	NAN_METHOD(structs_testers_struct_B_struct_A) {
		info.GetReturnValue().Set(Nan::New("structs_testers.struct_B_struct_A").ToLocalChecked());
	}

	NAN_METHOD(structs_testers_struct_A_struct_A) {
		info.GetReturnValue().Set(Nan::New("structs_testers.struct_A_struct_A").ToLocalChecked());
	}

	NAN_METHOD(structs_testers_struct_B_struct_B) {
		info.GetReturnValue().Set(Nan::New("structs_testers.struct_B_struct_B").ToLocalChecked());
	}

	void RegisterORTesters(Handle<Object> target, std::shared_ptr<overload_resolution> overload) {
		auto loverload = overload;
		overload->addOverload("or_struct_tester", "", "structs_testers", {}, structs_testers);
		overload->addOverload("or_struct_tester", "", "structs_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, structs_testers_struct_A);
		overload->addOverload("or_struct_tester", "", "structs_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, structs_testers_struct_B);
		overload->addOverload("or_struct_tester", "", "structs_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()),std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, structs_testers_struct_A_struct_A);
		overload->addOverload("or_struct_tester", "", "structs_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()),std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, structs_testers_struct_B_struct_B);

		overload->addOverload("or_struct_tester", "", "structs_testers", { std::make_shared<overload_info>("a","struct_A",Nan::Undefined()),std::make_shared<overload_info>("a","struct_B",Nan::Undefined()) }, structs_testers_struct_A_struct_B);
		overload->addOverload("or_struct_tester", "", "structs_testers", { std::make_shared<overload_info>("a","struct_B",Nan::Undefined()),std::make_shared<overload_info>("a","struct_A",Nan::Undefined()) }, structs_testers_struct_B_struct_A);

		general_callback::overload = overload;
		Nan::SetMethod(target, "structs_testers", general_callback::tester_callback);
	}

}

#endif