void LinkedList::print() const
{
//invoke recursive private member function
print(head);
}
void LinkedList::print(Node * first) const
{
if(first)
{
cout << first->data << endl;
//recursive call to print the rest of the list
print(first->next);
}
}
void LinkedList::append(Node *& first, int data)
{
if(!first)//the end of the list
{
first = new Node(data);
}
else
{
//recursive call to append to the smaller list
append(first->next, data);
}
}
