#include <iostream>

using namespace std;

struct node
{
    string text;
    node *next;
    node *prev;
};

class list
{
private:
    node *head;
    node *tail;

public:
    list()
    {
        head = NULL;
        tail = NULL;
    }

    void insertEndNode(string userInput)
    {
        node *initNode = new node;
        initNode->text = userInput;
        initNode->next = NULL;
        initNode->prev = NULL;

        if(head==NULL)
        {
            head = initNode;
            tail = initNode;
            initNode = NULL;
        }
        else
        {
            tail -> next = initNode;
            initNode -> prev = tail;
            initNode -> next = NULL;
            tail = initNode;
        };
    };


    void readAll(node *initRead)
    {
        cout << initRead -> text << endl;
        if(initRead -> next)
        {
            readAll(initRead -> next);
        };
    };

    node * getHead()
    {
        return head;
    };

    node * getTail()
    {
        return tail;
    };

};

class linkIterator
{

public:
    node *prev;
    node *current;
    node *next;

    linkIterator()
    {
        prev = NULL;
        current = NULL;
        next = NULL;
    };

    void bind(list linkedList)
    {
        current = linkedList.getHead();
        next = current -> next;
    };

    void getText()
    {
        cout << current -> text;
    };

    void goNext()
    {
        if(next)
        {
            prev = current;
            current = next;
            next = current -> next;
        }
    }

    void goPrev()
    {
        if(prev)
        {
            prev = prev -> prev;
            current = prev;
            next = current -> next;
        }
    }

    void reset(list linkedList){
        prev = NULL;
        current = linkedList.getHead();
        next = current -> next;
    }




};

void handleInsertEnd(string text, list * linkedList, linkIterator listIterator)
{
    linkedList -> insertEndNode(text);
}

void handleInsert(string text, int position, list linkedList, linkIterator listIterator)
{
    bool overFlow = false;
    node *initNode = new node;
        initNode->text = text;
        initNode->next = NULL;
        initNode->prev = NULL;

    listIterator.reset(linkedList);
    for(int a = 1; a < position; a++){
        listIterator.goNext();
        if(listIterator.current -> next == NULL && a < position){
            overFlow = true;
            break;
        }
    };

    if(!overFlow && position != 1){
    listIterator.prev -> next = initNode;
    initNode -> prev = listIterator.prev;
    initNode -> next = listIterator.current;
    listIterator.current -> prev = initNode;
    }

}

void handleDelete(int position, list linkedList, linkIterator listIterator)
{
    listIterator.reset(linkedList);
    for(int a = 1; a < position; a++){
        listIterator.goNext();
    };
    listIterator.prev -> next = listIterator.next;
    listIterator.next -> prev = listIterator.prev;
    delete listIterator.current;

}

void handleEdit(string text, int position, list linkedList, linkIterator listIterator)
{
    listIterator.reset(linkedList);
    for(int a = 1; a < position; a++){
        listIterator.goNext();
    };
    listIterator.current -> text = text;
}

void handlePrint(list  linkedList, linkIterator listIterator)
{
    listIterator.reset(linkedList);
    int a = 1;
    while(true){
    cout << a << " " << listIterator.current -> text << endl;
    if(listIterator.current -> next == NULL){
        break;
    }
    listIterator.goNext();
    a++;
    }
}

void handleSearch(string text, list linkedList, linkIterator listIterator)
{
    listIterator.reset(linkedList);
    int a = 1;
    while(true){
        if((listIterator.current -> text).find(text) != string::npos){
            cout << a << " " << listIterator.current -> text << endl;
            break;
        } else if (listIterator.current -> next == NULL){
            cout << "not found" << endl;
            break;
        }
        listIterator.goNext();
        a++;
    };
}

int main()
{
    list linkedList;
    linkIterator listIterator;


    string input, inputSave, command, text;
    int position;
    while(getline(cin, input))
    {
        command = input.substr(0, input.find(" "));
        if(command.compare("insertEnd") == 0)
        {
            text = input.substr(input.find('"') + 1);
            text = text.substr(0, text.size()-1);
            handleInsertEnd(text , &linkedList, listIterator);
        }
        else if(command.compare("insert") == 0)
        {
            text = input.substr(input.find('"') + 1);
            text = text.substr(0, text.size()-1);
            position = stoi(input.substr(input.find(" ") + 1, 1));
            handleInsert(text, position, linkedList, listIterator);
        }
        else if(command.compare( "delete") == 0)
        {
            position = stoi(input.substr(input.find(" ") + 1, 1));
            if(position != 1){
            handleDelete(position, linkedList, listIterator);
            }
        }
        else if(command.compare( "edit") == 0)
        {
             text = input.substr(input.find('"') + 1);
            text = text.substr(0, text.size()-1);
            position = stoi(input.substr(input.find(" ") + 1, 1));
            handleEdit(text, position, linkedList, listIterator);
        }
        else if(command.compare( "print") == 0)
        {
            handlePrint(linkedList, listIterator);
        }
        else if(command.compare( "search") == 0)
        {
             text = input.substr(input.find('"') + 1);
            text = text.substr(0, text.size()-1);
            handleSearch(text, linkedList, listIterator);
        }
        else if(command.compare( "quit") == 0)
        {
            return 0;
        };
    }
}
