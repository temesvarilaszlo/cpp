/*
Feladat röviden, hogy csináld meg a array_view_operations template osztályt
kap egy pointert és egy tömbhosszot
aztán egy 
reverse() {megfordítja a pointer által mutatott tömb elemeinek sorrendjét}, 
reset(){visszaállítja az eredeti sorrendet; amikor meghal az osztály ez is lefut}, 
shift(){pozitív esetén jobbra, egyébként balra shiftel}, 
get_first_index_if(predikatum){kap egy predikátumot és aszerinti első elem indexét kell visszaadni, ha nincs olyen akkor -1}; 
sort(){ha nincs feltétel csak növekvő, ha kap predikátumot, akkor aszerint},
és egy kis extra, hogy hogyan lehet úgy megírni, hogy ne kelljen tömb méretét átadni
*/

#ifndef ARVIOPS
#define ARVIOPS

#include <vector>
#include <algorithm>
#include <iostream>

template<typename T>
class array_view_operations
{
private:
    int size;
    T* original;
    T* modified;

public:
    template<int ArraySize>
    array_view_operations(T (&a)[ArraySize])
    {
        modified = a;
        size = ArraySize;
        original = new T[size];
    }

    array_view_operations(T a[], int _size) : size(_size), original(new T[_size]), modified(a)
    {
        for (int i = 0; i < _size; i++) {
            original[i] = a[i];
        }
    }
    ~array_view_operations(){
        reset();
        if (original != nullptr) delete[] original;
    }

    void reverse(){
        for (int i = 0; i < size / 2; i++){
            T temp = modified[i];
            modified[i] = modified[size-1-i];
            modified[size-1-i] = temp;
        }
    }

    void reset(){
        for (int i = 0; i < size; i++) {
            modified[i] = original[i];
        }
    }

    void shift(int shiftAmount) {
        if (shiftAmount > 0) {
            // Right shift
            shiftAmount %= size; // Adjust for multiple rotations
            std::rotate(modified, modified + size - shiftAmount, modified + size);
        } else if (shiftAmount < 0) {
            // Left shift
            shiftAmount = -shiftAmount % size; // Adjust for multiple rotations
            std::rotate(modified, modified + shiftAmount, modified + size);
        }
    }

    template<typename Functor>
    int get_first_index_if(Functor f){
        int i = 0;
        while(i < size && !f(modified[i])){
            i++;
        }
        if (i < size) return i;
        return -1;
    }

    template<typename Functor = std::less<T>>
    void sort(const Functor& f = Functor()){
        std::sort(modified, modified + size, f);
    }

    void print(){
        std::cout << "Original: ";
        for (int i = 0; i < size; i++)
        {
            std::cout << original[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Modified: ";
        for (int i = 0; i < size; i++)
        {
            std::cout << modified[i] << " ";
        }
        std::cout << std::endl;
    }
};




#endif 