#include "Electronics.h"

#include <iostream>
using namespace std;

// Fill in here
Electronics::Electronics(int aSize){
    size = aSize;
}
void Electronics::SetSize(int aSize){
    size = aSize;
}
int Electronics::GetSize(void){
    return (size);
}

// TV
TV::TV(int aSize) : Electronics(aSize){
    price = size * 1.8;
}
void TV::PrintSelf(void){
    cout << "It is a TV, Size=" << size <<", Price="<< price << endl;
}
//Computer
Computer::Computer(int aSize) : Electronics(aSize){
    price = size * 0.6;
}
void Computer::PrintSelf(void){
    cout << "It is a Computer, Size=" << size <<", Price="<< price << endl;
}
// Cellphone
Cellphone::Cellphone(int aSize) : Electronics(aSize){
    price = size * 0.7;
}
void Cellphone::PrintSelf(void){
    cout << "It is a Cellphone, Size=" << size <<", Price="<< price << endl;
}



Laptop::Laptop(int aSize) : Computer(aSize){
    totalPrice = price;
}
void Laptop::PrintSelf(void){
    cout << "It is a Laptop with "<< numGPU <<" GPU(s), Size=" << size <<", Price="<< price << ", Total Price="<< totalPrice << endl;
}
void Laptop::AddGPU(Electronics *aGPU){
    if (numGPU < 2){
        numGPU = numGPU + 1;
        price = size * 0.6 * 2;
        totalPrice = totalPrice + aGPU->GetSize() * 0.6;
    }
}