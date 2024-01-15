#ifndef LINEEDIT
#define LINEEDIT

#include <iostream>
#include <list>
#include <algorithm>

template<typename Cont, typename T = typename Cont::value_type>
class line_editor
{
private:
    std::list<T> line;
    typename std::list<T>::iterator cursor;
    bool isInsert;
public:
    line_editor() : cursor(line.end()), isInsert(false)
    {}
    ~line_editor(){}

    void press(T elem){
        if (isInsert && cursor != line.end()){
            *cursor = elem;
        }
        else {
            cursor = line.insert(cursor, elem);
        }
        cursor++;
    }

    void home(){
        cursor = line.begin();
    }

    Cont enter(){
        Cont ret(line.begin(), line.end());
        line.clear();
        cursor = line.end();
        return ret;
    }

    void insert(){
        isInsert = !isInsert;
    }

    void backspace(){
        if (cursor != line.begin()){
            cursor = line.erase(--cursor);
        }
    }

    void del(){
        if (cursor != line.end()){
            cursor = line.erase(cursor);
        }
    }

    template<typename C, typename U>
    void swap(line_editor<C, U> &le){
        std::swap(line, le.line);
        std::swap(cursor, le.cursor);
        std::swap(isInsert, le.isInsert);
    }
    template<typename C, typename U>
    friend class line_editor;
};



#endif //LINEEDIT