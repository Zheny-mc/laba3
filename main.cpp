/*
краткое описание:
    Простая программа на языке c++  по теме "деревья общего вида".

Задача:
    Дано N-дерево. Найти в дереве длиннейший путь (пути), вдоль
    которого номера вершин упорядочены по возрастанию.

Автор: Бубнов Евгений 19-ивт-2 
*/


#include <iostream>
#include "Tree.cpp"

bool is_run(string& file_input, string& file_output);

int main()
{
    const int n_test = 2;
    string tests[n_test][2] = { {"test1/input.txt", "test1/output.txt"}, {"test2/input.txt", "test2/output.txt"} };
    int i;
    
    try
    {
        for (i = 0; i < n_test; i++)
        {    
            cout << endl << "----------test" << i+1 << " begin----------" << endl;

            if (is_run(tests[i][0], tests[i][1]))
                cout << endl << "----------test" << i+1 << " passed----------" << endl;
            else
                cout << endl << "----------test" << i+1 << " failed----------" << endl;
        }
    }
    catch (const std::exception& e)
    {
        cout << e.what() << endl;
        cout << endl << "----------test" << i+1 << " failed----------" << endl;
    }

    return 0;
}

bool is_run(string& file_input, string& file_output)
{
    Tree<int> tree;
    List<int> maxlen_way;

    Tree<int>::input_tree(file_input, tree);

    tree.print();
    
    maxlen_way = tree.maxlen_way_upper_value();

    cout << "maxlen_way_upper_value: " << endl;
    maxlen_way.print();

    return Tree<int>::is_check_maxlen_way(file_output, maxlen_way);
}
