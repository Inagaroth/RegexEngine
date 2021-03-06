#include "DecoratorVisitor.h"
void DecoratorVisitor::setMode(char c)
{
	mode =c ;
}
DecoratorVisitor::DecoratorVisitor()
{

 }


 NodeI *DecoratorVisitor::visit(NodeI *node)
 {
	 Counter *temp_beg;
	switch (mode)
	 {
		case '?':
			temp_beg = new Counter(node,0,1);
			break;
		case '*':
			temp_beg = new Counter(node,0,-1);
			break;
		case '+':
			temp_beg = new Counter(node,1,-1);
			break;
	 }
	temp_beg->setPred(node->getPred());
	temp_beg->setEnd(node);
	node->getPred()->setNext(temp_beg);
	node->link(temp_beg);
	return temp_beg;
 }
 NodeI *DecoratorVisitor::visit(Counter *node)
 {
	 switch (mode)
	 {
	 case '?':
		 return new Lazy(node);
		 break;
	 case '*':
		 throw exceptionCounter();
		 break;
	 case '+':
		 throw exceptionCounter();
		 break;
	 }
	 return nullptr;
 }
 NodeI *DecoratorVisitor::visit(GroupEndNode *node)
 {
	 Counter *temp_beg;
	switch (mode)
	 {
		case '?':
			temp_beg = new Counter(node->getPred(),0,1);
			break;
		case '*':
			temp_beg = new Counter(node->getPred(),0,-1);
			break;
		case '+':
			temp_beg = new Counter(node->getPred(),1,-1);
			break;
	 }
	temp_beg->setPred(node->getPred()->getPred());
	temp_beg->setEnd(node);
	node->getPred()->getPred()->setNext(temp_beg);
	node->link(temp_beg);
	return temp_beg;
 }
 NodeI *DecoratorVisitor::visit(NonCapturingGroupEndNode *node)
 {
	 Counter *temp_beg;
	 switch (mode)
	 {
	 case '?':
		 temp_beg = new Counter(node->getPred(), 0, 1);
		 break;
	 case '*':
		 temp_beg = new Counter(node->getPred(), 0, -1);
		 break;
	 case '+':
		 temp_beg = new Counter(node->getPred(), 1, -1);
		 break;
	 }
	 temp_beg->setPred(node->getPred()->getPred());
	 temp_beg->setEnd(node);
	 node->getPred()->getPred()->setNext(temp_beg);
	 node->link(temp_beg);
	 return temp_beg;
 }
 NodeI *DecoratorVisitor::visit(LookAheadNode *node)
 {
	 Counter* temp = (Counter*)node->groupLast->accept(this);
	 temp->setNext(node->valider);
	 return node;
 }

 NodeI *DecoratorVisitor::visit(NegLookAheadNode *node)
 {
	 Counter *temp = (Counter *)node->groupLast->accept(this);
	 temp->setNext(node->valider);
	 return node;
 }
