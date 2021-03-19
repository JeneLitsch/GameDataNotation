#pragma once

#include "Visitor.hxx"
#include <string>
namespace GDN{
	class Printer : public Visitor{
	public:
		Printer(bool pretty);
		// add value to string
		virtual void visitValue(Value & val) override;
		
		// add object to string
		virtual void visitObject(Object & ob) override;

		// add array to string
		virtual void visitArray(Array & arr) override;

		// clears str
		void clear();

		// returns str
		std::string get() const;
	private:
		// determines if the printer performs pretty printing
		// e.g. tabs and newlines
		bool pretty;

		// add addional string to str
		void add(const std::string & newStr);

		// for adding comma for previous line
		void comma(bool & firstline);

		// returns a couple tabs if pretty is acivated
		std::string indent();
		
		// returns a new line if pretty printing is activated
		std::string newline();

		// depth for indentation
		int depth = 0;

		// GDN/Json string
		std::string str;
	};
}