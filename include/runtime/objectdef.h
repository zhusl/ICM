#pragma once
//#pragma message("===Compiling objectdef.h===")
#include "basic.h"
#include "object.h"
#include "typebase.h"

namespace ICM
{
	namespace Types
	{
#define DEFTYPE(_TE, _T) template <> struct TType<T_##_TE> { using Type = _T;  static TypeName Name; }; using _TE = TType<T_##_TE>::Type;

		DEFTYPE(Null, TypeBase::VoidType);
		DEFTYPE(Object, TypeBase::VoidType);
		DEFTYPE(Nil, TypeBase::VoidType);
		DEFTYPE(Vary, TypeBase::VoidType);
		DEFTYPE(Void, TypeBase::VoidType);
		DEFTYPE(Error, TypeBase::ErrorType);
		// Literal Types
		DEFTYPE(Boolean, TypeBase::BooleanType);
		DEFTYPE(Number, TypeBase::NumberType);
		DEFTYPE(String, TypeBase::StringType);
		DEFTYPE(Symbol, TypeBase::SymbolType);
		// Identifier Types
		DEFTYPE(Function, TypeBase::FunctionType);
		DEFTYPE(Keyword, TypeBase::KeywordType);
		DEFTYPE(Type, TypeBase::TypeType);
		// List Types
		DEFTYPE(List, TypeBase::ListType);
		DEFTYPE(Disperse, TypeBase::DisperseType);
		// Compile Types (Platform Dependent)
		DEFTYPE(Int, int_t);
		DEFTYPE(UInt, uint_t);
		DEFTYPE(Float, float);
		DEFTYPE(Double, double);
		DEFTYPE(CPointer, void*);
		// Compile Types (Platform Independent)
		DEFTYPE(Byte, byte);
		DEFTYPE(Word, word);
		DEFTYPE(DWord, dword);
		DEFTYPE(QWord, qword);
		DEFTYPE(Int8, int8_t);
		DEFTYPE(Int16, int16_t);
		DEFTYPE(Int32, int32_t);
		DEFTYPE(Int64, int64_t);
		DEFTYPE(UInt8, uint8_t);
		DEFTYPE(UInt16, uint16_t);
		DEFTYPE(UInt32, uint32_t);
		DEFTYPE(UInt64, uint64_t);
		// Test
		struct Test
		{
			Test() { println("Init Test"); }
			~Test() { println("Destory Test"); }
			Test(const Test &) { println("Copy Test"); }
			bool operator==(const Test&) const { return true; }
		};
		DEFTYPE(Test, Test);

#undef DEFTYPE

#define DEFTYPE(_T, _TE) template <> struct CType<_T> { constexpr static TypeUnit index = T_##_TE; };

		DEFTYPE(int32_t, Number);
		DEFTYPE(int64_t, Number);
		DEFTYPE(double, Double);
		DEFTYPE(float, Float);
		DEFTYPE(unsigned, UInt);

#undef DEFTYPE
	}

	namespace Objects
	{
		// TODO : Delete this class.
		//=======================================
		// * Class DataObject<_Type>
		//=======================================
		template <DefaultType _Type>
		class DataObject : public Object
		{
			using T = typename TType<_Type>::Type;
		public:
			DataObject() : Object(_Type) { this->data = new T(); }
			DataObject(const T &dat) : Object(_Type) { this->data = new T(dat); }
		};
		
		using Nil = DataObject<T_Nil>;
		using Error = DataObject<T_Error>;
		using Boolean = DataObject<T_Boolean>;
		using Number = DataObject<T_Number>;
		using String = DataObject<T_String>;

		using List = DataObject<T_List>;
		using Disperse = DataObject<T_Disperse>;
		using Keyword = DataObject<T_Keyword>;
		using Function = DataObject<T_Function>;
		using Type = DataObject<T_Type>;

		vector<Object*>::iterator begin(Disperse *disp);
		vector<Object*>::iterator end(Disperse *disp);
	}
}
