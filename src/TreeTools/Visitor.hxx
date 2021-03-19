#pragma once
namespace GDN {
	class Array;
	class Object;
	class Value;
	class Visitor{
	public:
		virtual void visitValue(Value & val) = 0;
		virtual void visitObject(Object & ob) = 0;
		virtual void visitArray(Array & arr) = 0;
	};
}
