#include "list.h"

namespace Modal{
	List::List(){
		vide=1;
	}
	List::List(int i,List* l){
		v=i;
		n=l;
		vide=0;
	}
	List::~List(){
	}
	int List::value(){
		return v;
	}
	List* List::next(){
		return n;
	}
	bool List::isEmpty(){
		return (vide?true:false);
	}
	int List::setvalue(int n){
		v=n;
		vide=0;
	}
}
