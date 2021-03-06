#pragma once
#include "StringIterator.h"
#include <iostream>
class NodeVisitor;
/**
 * @brief
 * Base clas for all nodes in a regex
 */
class NodeI
{
  public:
	virtual ~NodeI();
	virtual bool test(char c);
	virtual StringIterator in(StringIterator it);
	virtual NodeI *link(NodeI *Next);
	virtual NodeI *getPred() const;
	virtual NodeI *getNext() const;
	virtual void setPred(NodeI *n);
	virtual void setNext(NodeI *n);
	virtual NodeI *accept(NodeVisitor *v);
	virtual NodeI* get()
	{
		return this;
	}

protected:
	NodeI *pred = nullptr;
	NodeI *next = nullptr;
};