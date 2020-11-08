#include <iostream>
#include <fstream>
#include "List.cpp"

using std::cout;
using std::endl;
using std::string;


//-------------класс дерева общего вида-----------------------
template <class T>
class Tree
{
    //элемент дерева
    struct Node
    {
        T     item;    //значение
        Node* son;     //нижний элемент 
        Node* brother; //соседний элемнт

        
        Node(T _item, Node *_son=NULL, Node* _brother=NULL) : 
            item(_item), son(_son), brother(_brother) {}
    };

    Node* root; //корень дерева

public:
    static void input_tree(const string& file_input, Tree<int>& tree);
    static bool is_check_maxlen_way(const string& file_output, List<int>& maxlen_way);

    //---создание пустого дерева---
    Tree() : root(NULL) {} 

    //---удаление дерева---
    ~Tree()
    {
        delete_subtree(root);
    }

    //---добавление элемента в дерево---
    void add(const T& elem)
    {
        add(root, elem);
    }

    //-----вывод дерева на экран-----
    void print()
    {
        cout << "tree:" << endl;
        print(root, 0);
        cout << endl;
    }

    //---поиск максимально длинного пути с возрастающими номерами вершин--
    List<T> maxlen_way_upper_value()
    { 
        return _maxlen_way_upper_value();
    }

private:
    //внутренне методы для реализации внешних методов
    void    add                   (Node*& node, const T& item);   //добавление элемента в дерево
    void    delete_subtree        (Node*  node);                  //удаление дерева
    void    print                 (Node*  node, int num_margins); //вывод дерева
    List<T> _maxlen_way_upper_value(); //поиск максимально длинного пути с возрастающими номерами вершин
};


//-----------реализация класса --------------------------
template <class T>
void Tree<T>::input_tree(const string& file_input, Tree<int>& tree)
//ф-я для безопасного заполнения дерева
{
    int N; //количество узлов дерева
    int node;
    std::ifstream f(file_input);
        
    if (f.is_open())
    {
        f >> N;

        if (N == 0)
            throw std::invalid_argument("Tree empty");

        //заполнение дерева
        for (int i = 0; i < N && !f.eof(); i++)
        {
            f >> node;
            tree.add(node);
        }

        f.close();
        return;
    }
    
    throw std::invalid_argument("Exeption! File dont open(" + file_input + ")");
}

template <class T>
bool Tree<T>::is_check_maxlen_way(const string& file_output, List<int>& maxlen_way)
{
    int node;
    std::ifstream f(file_output);

    if (f.is_open())
    {
        for (int i = 0; i < maxlen_way.size() && !f.eof(); i++)
        {
            f >> node;

            if (maxlen_way[i] != node)
                return false;
        }

        f.close();
        return true;
    }
    
    throw std::invalid_argument("Exeption! File dont open(" + file_output + ")");    
}

template <class T>
void Tree<T>::add(Node*& node, const T& item)
//добавление элемента в дерево
{
    if (node == NULL) //если пустое место нашлось
    {
        node = new Node(item); //создай элемент дерева
    }
    else if (item < node->item) //если добавляемое значение меньше текущей вершины
    {
        add(node->son, item); //переди к сыну
    }
    else
    {
        add(node->brother, item); //иначе к брату
    }
}

template <class T>
void Tree<T>::delete_subtree(Node* node)
//удаление дерева: спускайся в сымый нижний элемнт и удаляй с листьев
{
    if (node)
    {
        delete_subtree(node->son);
        delete_subtree(node->brother);
        delete node;
    }
}

template <class T>
void Tree<T>::print(Node* node, int num_margins)
//вывод дерева
{
    if (node)
    {
        //делай отступ для иерархии
        for (int i = 0; i < num_margins; i++)
            cout << ' ';
        //выводи зачения элемента
        cout << node->item << endl; 

        print(node->son,     num_margins+5);
        print(node->brother, num_margins);
    }
}

template <class T>
List<T> Tree<T>::_maxlen_way_upper_value()
//поиск максимально длинного пути с возрастающими номерами вершин
//пройди от корня по всем братьям до конца, тем самым определив максимально длинный
//путь с возрастающими вершинами
{
    List<T> maxlen_way;
    Node* cur_node = root;

    while (cur_node != NULL)
    {
        maxlen_way.push_back(cur_node->item); //добавление элемента в путь
        cur_node = cur_node->brother; //перехожу к следующему брату
    }

    return maxlen_way;
}