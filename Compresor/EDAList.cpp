#include "EDAList.h"

template<typename Type>
EDAList<Type>::EDAList() :size(0), firstNode(nullptr), lastNode(nullptr) {}

template<typename Type>
void EDAList<Type>::addElement(Type& element, unsigned long pos)
{
	if (pos <= size)
	{
		if (firstNode == nullptr)
		{
			node<Type> * tempNode = new node;
			tempNode->data = element;
			tempNode->nextNode = nullptr;
			firstNode = tempNode;
			lastNode = tempNode;
		}
		else
		{
			if (pos > 0)
			{
				node<Type> * currentNode = firstNode;
				for (unsigned long i = 1; i < pos; i++)
				{
					currentNode = currentNode->nextNode;
				}
				node<Type> * tempNode = new node;
				tempNode->nextNode = currentNode->nextNode;
				currentNode->nextNode = tempNode;
				tempNode->data = element;
				if (pos == size)
				{
					lastNode = tempNode;
				}
			}
			else	//Pos = 0
			{
				node<Type> * tempNode = new node;
				tempNode->nextNode = firstNode;
				firstNode = tempNode;
				tempNode->data = element;
			}
		}
		size++;
	}
}

template<typename Type>
void EDAList<Type>::removeElement(unsigned long pos)
{
	if (pos <= size)
	{

	}
}


