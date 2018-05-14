#ifndef BST_H
#define BST_H

#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
/* BST.h
Author:  Marvin Joshi
Date:    November 19,2017

This program reads in a text file that contains numbers that
will be inserted into a binary tree. It then outputs the 
content of the binary search tree in a lexicographically sorted
order. THe program then lets the user enter in two numbers, 
the first being the lower bound and the other being the upper
bound. For the lower bound, it tries to find the key the user
entered  and if not found it returns the next key after that. 
For the upper bound, the program find the node that is the next
greater than than the number entered in by the user and if not
found, it returns a NULL node.
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
			iterator & operator++();
			bool operator!=(const iterator & rhs) const
			{
				return p != rhs.p;//returns whether or not the keys are not equal to each other
			} 
			bool operator==(const iterator & rhs) const
			{
				return p == rhs.p;//returns whether or not the keys are equal to each other
			}
			TKey operator*() 
			{
				return p->key;//derefrences the node and gets the node key
			}
		private:
			friend class bst<TKey>;
			iterator(node *np) 
			{
				p = np; //sets node p to wat the parameter node is
			}
			node *p;
	};

	iterator begin()
	{
  node *m = Troot;
  while(m->link[0])//moves to the left if possible
    m = m->link[0];
    
		return iterator(m);//returns the lft most key
	}
	iterator end() 
	{
		return iterator();//returns a null node
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
	bst<TKey>::node * m;//
  if (p->link[1])//checks if it is possible to move to the right
	{				
		p = p->link[1];//moves to the right
		while (p->link[0])//check to see if it is possible to move the left
		{				
			p = p->link[0];//moves to the left
		}
	} 
	else //if it cant move to the right
	{
		m = p->parent;//sets a dummy node to the parent of p
		while ( m != NULL && p == m->link[1] )//checks to see if m hold anything and if m can move to the right
		{	
			p = m;//sets p to the m node
			m = m->parent;//moves up to the next parent		
		}
		p = m;//sets p to the parent
	}
	return *this;//return the p node
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
  node *m = Troot;
  node *answer = NULL ;
  
  while (m!=NULL )
  {
    if(key <= m->key)//if node key is larger than or equal to wanted key
    {
      answer = m;//set as lower bound
      m = m->link[0];//if possible go to the left
      
    }
    else//if smaller than wanted key
    {
      m = m->link[1];//move to the right
	  }
  }
  return iterator(answer);//returns the wanted node
  } 
 	
  template<class TKey>
typename bst<TKey>::iterator bst<TKey>::upper_bound(const TKey &key)
{
  node *m = Troot;
  node *answer = NULL ;
  while (m)
  {
    if(key < m->key)//if node key is larger than wanted key
    {
      answer = m;//set as lower bound
      m = m->link[0];//if possible go to the left
      
    }
    else//if smaller than wanted key
    {
      m = m->link[1];//move to the right
    }
  }
  return iterator(answer);//returns the wanted node
  }


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
