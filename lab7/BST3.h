#ifndef BST2_H
#define BST2_H

#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
/* BST2.h
Author:  Marvin Joshi
Date:    November 14,2017

This program reads in a text file that contains numbers that
will be inserted into a binary tree. The program inserts each 
node and inserts the node to its correct position. While the 
program inserts each key, it sets created a particular ID for 
each key. After all numbers are inserted into the tree, the
program prints out the node key, its node ID, the parent ID, 
and the left and right subtree IDs, they exist.
*/
using namespace std;

template <class TKey>
class bst {
	struct node {
		node(int num);

		void print();

		TKey key;

		int nodeId;//id that is created every time a new node is made

		node *parent;//parent node 
		node *link[2];
	};

	public:
	class iterator {
		public:
			iterator() 
			{
				p = NULL;
			}
			//default constructor (no argument)
			//overloaded operators (++, *, ==, !=)
			iterator & operator++();
			bool operator!=(const iterator & rhs) const
			{
				return p != rhs.p;
			} 
			bool operator==(const iterator & rhs) const
			{
				return p == rhs.p;
			}
			TKey operator*() 
			{
				return p->key;
			}
		private:
			friend class bst<TKey>;
			//constructor (with argument)
			iterator(node *np) 
			{
				p = np; 
			}
			node *p;
	};

	iterator begin()
	{
  node *m = Troot;
  while(m->link[0])
    m = m->link[0];
    
		return iterator(m);
	}
	iterator end() 
	{
		return iterator();
	}
  iterator lower_bound(const TKey &);
	iterator upper_bound(const TKey &);

	public:
	bst() { Troot=NULL; id = 0; }//sets the id to 0 everytime it is created
	~bst() { clear(Troot); }

	bool empty() { return Troot==NULL; }

	void insert(TKey &);

	

	void print_bylevel();

	private:
	void clear(node *);
	node *insert(node *, TKey &);
	
	int id;//node Id that gets updated each time
	node *Troot;
};
	template <class TKey>
bst<TKey>::node :: node(int num = 0 )
{
	nodeId = num;//sets each id to 0
	parent = NULL;//sets the parent to NULL

}

	template<class TKey>
class bst<TKey>::iterator & bst<TKey>::iterator::operator++()
{
	bst<TKey>::node * m;
  if (p->link[1])
	{				
		p = p->link[1];						
		while (p->link[0])
		{				
			p = p->link[0];					
		}
	} 
	else 
	{
		m = p->parent;				
		while ( m != NULL && p == m->link[1] )
		{	
			p = m;
			m = m->parent;			
		}
		p = m;
	}
	return *this;
}
	template <class TKey>
void bst<TKey>::node::print()
{
	cout << setw(3) << key<< setw(4) <<nodeId << " :";//prints out the node id of each node

	//output node and parent ID information
	// change below to output subtree ID information
	if (parent == NULL) cout<< setw(3) << " ROOT ";//prints out ROOT if this is the first node entered
	else  cout << " P=" << setw(3) << parent->nodeId;//prints out the parent id if otherwise
	if (link[0]) cout << " L=" << setw(3) << link[0]->nodeId;//prints the left subtree id
	else cout << "      ";
	if (link[1]) cout << " R=" << setw(3) << link[1]->nodeId;//prints the right subtree id
	else cout << "      ";

	cout << "\n";
}

//bst<TKey>::iterator functions not defined above go here

	template <class TKey>
void bst<TKey>::clear(node *T)
{
	if (T) {
		clear(T->link[0]);
		clear(T->link[1]);
		delete T;
		T = NULL;
	}
}

	template <class TKey>
void bst<TKey>::insert(TKey &key)
{ 
	Troot = insert(Troot, key);
}

	template <class TKey>
class bst<TKey>::node *bst<TKey>::insert(node *T, TKey &key)
{
	if (T == NULL) {
		id++;//update and set node ID
		T = new node(id);
		T->key = key;
	} else if (T->key == key) {
		;
	} else {
		int dir = T->key < key;
		T->link[dir] = insert(T->link[dir], key);
		T->link[dir]->parent = T;//sets the parent link
	}

	return T;
}

	template<class TKey>
typename bst<TKey>::iterator bst<TKey>::lower_bound(const TKey &key)
{
  node *current = Troot;
  node *bound = NULL ;
  
  while (current!=NULL )
  {
    if(key<=current->key)
    {
      bound   = current;
      current = current->link[0];
      
    }
    else
    {
      current = current->link[1];
	  //bound = current->link[0];
    }
  }
  return iterator(bound);
  } 
 	
  template<class TKey>
typename bst<TKey>::iterator bst<TKey>::upper_bound(const TKey &key)
{
  node *current = Troot;
  node *bound = NULL ;
  while (current)
  {
    if(key < current->key)
    {
      bound   = current;
      current = current->link[0];
      
    }
    else
    {
      current = current->link[1];
    }
  }
  return iterator(bound);
  }
//bst<TKey>::lower_bound function goes here

//bst<TKey>::upper_bound function goes here

	template <class TKey>
void bst<TKey>::print_bylevel()
{
	if (Troot == NULL)
		return;

	queue<node *> Q;
	node *T;

	Q.push(Troot);
	while (!Q.empty()) {
		T = Q.front();
		Q.pop();

		T->print();
		if (T->link[0]) Q.push(T->link[0]);
		if (T->link[1]) Q.push(T->link[1]);
	}
}
#endif
