#pragma once
#include "ObjectPtrBase.h"

namespace BDXKEngine {
	template<typename TObject>
	struct ObjectPtr :public ObjectPtrBase
	{
	public:
		ObjectPtr() :ObjectPtrBase() {
		}
		ObjectPtr(Object* object) :ObjectPtrBase(object)
		{
			ptr = (TObject*)ToObjectBase();
		}
		ObjectPtr(const ObjectPtrBase& objectPtr) :ObjectPtrBase(objectPtr) {
			ptr = (TObject*)ToObjectBase();
		}

		template<typename TTargetObject>
		ObjectPtr<TTargetObject> ToObjectPtr()
		{
			Object* object = ToObjectBase();
			return dynamic_cast<TTargetObject*>(object);
		}
		TObject* ToObject()
		{
			return static_cast<TObject*>(ToObjectBase());
		}
		TObject* operator->()const
		{
			Object* object = ToObjectBase();
			if (object == nullptr)
				throw std::exception("目标引用为空");
			return static_cast<TObject*>(object);
		}
	protected:
		TObject* ptr = nullptr;

		virtual void AddRef(const unsigned int refInstanceID)override
		{
			ObjectPtrBase::AddRef(refInstanceID);
			ptr = (TObject*)ToObjectBase();
		}
		virtual void RemoveRef()override
		{
			ObjectPtrBase::RemoveRef();
			ptr = nullptr;
		}

	};
}

//class Data :public Object {
//public:
//	Data(String name)
//	{
//		this->name = name;
//		Debug::Log(L"Create " + name);
//	}
//
//	~Data()
//	{
//		Debug::Log(L"Delete " + name);
//	}
//
//	String name;
//};
//
//int main()
//{
//	ObjectPtr<Data> A = { new Data{ L"A"} };
//	ObjectPtr<Object> A0 = { (Object*)A };
//	A0 = nullptr;
//	ObjectPtr<Data> B = A;
//	Debug::Log(A->name);
//	Object::DestroyImmediate(B);
//	if (A != nullptr)Debug::Log(A->name);
//
//	ObjectPtr<Data> C = { new Data{ L"C"} };
//	ObjectPtr<Data> D = C;
//	Debug::Log(C->name);
//	C = nullptr;
//	Debug::Log(C == B);
//	Debug::Log(C == D);
//}