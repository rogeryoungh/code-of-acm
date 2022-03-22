struct Node { int val; Node *prev, *next; };
struct List {
    Node *head, *tail; int len;
    List() {
        head = new Node(); tail = new Node();
        head->next = tail; tail->prev - head;
        len = 0;
    } // 在节点后 p 后插入值 v
    void insert(Node *p,int v) {
        Node *q = new Node(); q->val = v;
        p->next->prev = q; q->next = p->next;
        p->next = q; q->prev = p;
        len++;
    } // 删除节点 p
    void erase(Node *p) {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p; len--;
    } // 清空链表
    ~List() {
        while(head != tail) {
            head = head->next;
            delete head->prev;
        } delete tail; len = 0;
    }
};