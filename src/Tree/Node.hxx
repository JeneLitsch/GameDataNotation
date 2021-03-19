#pragma once
#include "Visitor.hxx"
namespace GDN{
	class Node {
	public:
		virtual void accept(Visitor & visitor) = 0;
		virtual ~Node() = default;
	};
}