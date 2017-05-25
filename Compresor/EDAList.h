template<typename Type>
class EDAList
{
public:
	
	EDAList();
	~EDAList();

	void addElement(Type& element, unsigned long pos);
	void removeElement(unsigned long pos);
	Type getElement(unsigned long pos);
	
private:

	template<typename Type>
	struct node
	{
		Type data;
		nodo *nextNode;
	};

	node<Type> firstNode;
	node<Type> lastNode;
	unsigned long size;

};

