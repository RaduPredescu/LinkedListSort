#include <iostream>
#include <vector>
struct Node
{
    float grade;
    std::string name;
    Node *next = nullptr;
    int pz;

    Node() = default;
    Node(float grade, std::string name, Node *next) : grade(grade), name(name), next(next){};

    virtual ~Node() = default;

    Node *Next()
    {
        return next;
    }
};
class Lista
{
    Node *head = nullptr;
    Node *tail = nullptr;
    std::vector<int> v;
    int szVect = 0;
    int i = 0;

public:
    Lista() = default;
    Lista(Node *head) : head(head){};

    virtual ~Lista()
    {
        auto curr = head;

        while (curr != nullptr)
        {
            auto next = curr->next;

            curr->next = nullptr;
            delete curr;

            curr = next;
        }

        head = nullptr;
    }
    void adaugaStudent(std::string name, float grade)
    {
        if (!head)
        {
            head = new Node(grade, name, nullptr);
            tail = head;
        }
        else
        {
            tail->next = new Node(grade, name, nullptr);
            tail = tail->next;
        }
        // head=new Node(grade,name,head);
    }
    Node *begin()
    {
        return head;
    }

    Node *getMax(Node *a, Node *b)
    {
        if (a->grade > b->grade)
        {
            return a;
        }
        else if (a->grade == b->grade)
        {
            if (a->name < b->name)
            {
                return a;
            }
            if (a->name > b->name)
            {
                return b;
            }
        }
        else
        {
            return b;
        }
    }
    Node *merge(Node *a, Node *b)
    {
        if (a == NULL)
            return b;
        if (b == NULL)
            return a;
        Node *head = getMax(a, b);
        Node *result = head;
        if (head == a)
            a = a->next;
        else
            b = b->next;

        while (a != NULL && b != NULL)
        {
            Node *curr = getMax(a, b);
            head->next = curr;
            head = curr;
            curr = curr->next;
            if (head == a)
                a = a->next;
            else
                b = b->next;
        }

        if (a == NULL)
            head->next = b;
        else
            head->next = a;

        return result;
    }
    void setIdx()
    {
        for (auto it = begin(); it != nullptr; it = it->next)
        {
            it->pz = i;
            ++i;
        }
    }

    void split(Node *head, Node *&a, Node *&b)
    {
        Node *fast;
        Node *slow;
        slow = head;
        fast = head->next;

        while (fast != NULL)
        {
            fast = fast->next;
            if (fast != NULL)
            {
                slow = slow->next;
                fast = fast->next;
            }
        }

        a = head;
        b = slow->next;
        slow->next = NULL;
    }

    Node *mergeSort(Node *head)
    {
        if (head == NULL || head->next == NULL)
            return head;

        Node *a;
        Node *b;
        split(head, a, b);

        a = mergeSort(a);
        b = mergeSort(b);

        return merge(a, b);
    }

    std::vector<int> returneazaIndecsiSortati()
    {
        setIdx();
        head = mergeSort(head);
        for (auto it = head; it; it = it->next)
            v.push_back(it->pz);
        return v;
    }

    friend std::ostream &operator<<(std::ostream &out, Lista const &myList)
    {
        for (auto ptr = myList.head; ptr != nullptr; ptr = ptr->next)
        {
            out << ptr->name << " " << ptr->grade;
            out << std::endl;
        }

        return out;
    }
};
int main()
{
    Lista l;
    l.adaugaStudent("gigi",10);
    l.adaugaStudent("radu",10);
    l.adaugaStudent("serban",10);
    l.adaugaStudent("mimi",10);
    std::vector<int> ans = l.returneazaIndecsiSortati();
    for (auto it : ans)
        std::cout << it << std::endl;
    return 0;
}