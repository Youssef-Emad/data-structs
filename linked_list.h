#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include<iostream>
#include"edge.h"

template <class type>
struct item
{
	type data ;
	item* next ;
};

template <class type>
class linked_list
{
private:
	item<type>* first ;
	int size ;
	void split(linked_list&,linked_list&) ;
	void merge(linked_list&,linked_list&) ;

public:
	class Iterator
	{
		friend class linked_list ;
	private:
		item<type>* position;
	public:

		Iterator()
		{
			position = NULL ;
		}

		Iterator(item<type>* input)
		{
			position = input ;
		}

		Iterator& operator++(int)
		{
			if(position !=NULL)
			{
				position = position->next ;
			}
			return *this ;
		}

		Iterator next()
		{
			Iterator temp ;
			if(position !=NULL)
			{
				temp.position = this->position->next ;
			}
			return temp ;
		}

		bool operator==(Iterator in)
		{
			return position == in.position ;
		}

		bool operator!=(Iterator in)
		{
			return !(position == in.position) ;
		}
	};


	linked_list()
	{
		first = NULL ;
		size = 0 ;
	}
	
	void add_item(type)  ;
	void remove_item(type) ;
	type return_item() ;
	type return_head() ;
	type return_last_item() ;
	type return_last_value() ;
	int get_size() ;
	void mergesort() ;

	Iterator begin() ;
	Iterator end() ;
	type& operator[](Iterator input) ;
};

template <class type>
void linked_list<type>::add_item(type num)
{
	item<type>* new_item = new item<type> ;
	new_item->data = num ;
	new_item->next = first ;
	first = new_item ;
	size ++ ;
}

template <class type>
void linked_list<type>::remove_item(type it)
{
	item<type>* temp = first ;
	item<type>* temp2 ;

	bool found = 0 ;

	if(first->data == it)
	{
		temp2 = first ;
		if(first->next != NULL)
		{
			first = first->next ;
		}
		else
		{
			first = NULL ;
		}
		delete temp2 ;
		found = 1 ;
	}
	else
	{
		temp2 = temp->next ;

		while(temp2 != NULL && found == 0)
		{
			if(temp2->data == it)
			{
				item<type>* tempdel = temp2 ;
				temp->next = temp2->next ;
				found = 1 ;
				delete tempdel ;
			}
			temp = temp->next ;
			temp2 = temp2->next ;
		}
	}
	size-- ;
}

template <class type>
type linked_list<type>::return_head()
{
	type val = first->data ;
	return val ;
}

template <class type>
type linked_list<type>::return_item() 
{
	item<type>* temp = first ;
	type val = first->data ;
	first = first->next ;
	delete temp ;
	size -- ;
	return val ;
}

template <class type>
type linked_list<type>::return_last_item()
{
	if (size > 0)
	{
		item<type>* temp = first ;
		if(size == 1 )
		{
			type val = temp->data ;
			size-- ;
			delete temp ;
			first = NULL ;
			return val ;
		} 
		else
		{
			item<type>* temp2 = temp->next ;
			while(temp2->next != NULL)
			{
				temp = temp->next ;
				temp2 = temp2->next ;
			}
			temp->next = NULL ;
			type val = temp2->data ;
			delete temp2 ;
			size-- ;
			return val ;
		}
	}
}

template <class type>
type linked_list<type>::return_last_value()
{
	if (size > 0)
	{
		item<type>* temp = first ;
		while(temp->next != NULL)
		{
			temp = temp->next ;
		}
		type val = temp->data ;
		return val ;
	}
}

template <class type>
int linked_list<type>::get_size()
{
	return size ;
}

template <class type>
void linked_list<type>::split(linked_list& a ,linked_list& b)
{

	item<type>* temp = first ;
	for(int i =0 ; i<size ; i++)
	{
		if(i<size/2)
			a.add_item(temp->data) ;
		else
			b.add_item(temp->data) ;

		temp=temp->next ;
	}

}

template <class type>
 void linked_list<type>::mergesort()
 {
	 if(size == 1)
	 {}
	else
	{
		linked_list a,b ;
		split(a,b);
		a.mergesort() ;
		b.mergesort() ;
		merge(a,b) ;
	}

 }

 template <class type>
 void linked_list<type>::merge(linked_list& a,linked_list& b)
 {
	item<type>* temp = first ;

	while(a.size != 0 && b.size !=0) 
	{
		if(a.return_head() < b.return_head()) 
		{
			temp->data = a.return_item() ;
		} else
		{
			temp->data = b.return_item() ;
		}
		temp = temp->next ;
	}
	while(a.size !=0)
	{
		temp->data = a.return_item() ;
		temp = temp->next ;
	}
	while(b.size !=0)
	{
		temp->data = b.return_item() ;
		temp = temp->next ;
	}
 }

template <class type>
typename linked_list<type>::Iterator linked_list<type>::begin() 
{
	Iterator  temp(first) ;
	return  temp ;
}

template <class type>
typename linked_list<type>::Iterator linked_list<type>::end() 
{
	return NULL ;
}

template <class type>
type& linked_list<type>::operator[](Iterator input)
{
	return input.position->data;
}
#endif