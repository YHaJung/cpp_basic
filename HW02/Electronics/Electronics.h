#pragma once

// Fill in here

class Electronics {
    public:
        Electronics(int aSize);

        void SetSize(int aSize);
        int GetSize(void);

        virtual void PrintSelf(void) = 0;

    protected:
        int size;
        int price;
};

class TV: public Electronics{
    public:
        TV(int aSize);
        virtual void PrintSelf(void);
};
class Computer: public Electronics{
    public:
        Computer(int aSize);
        virtual void PrintSelf(void);
};
class Cellphone: public Electronics{
    public:
        Cellphone(int aSize);
        virtual void PrintSelf(void);
};

class Laptop: public Computer{
    public:
        Laptop(int aSize);
        virtual void PrintSelf(void);
        void AddGPU(Electronics *aGPU);
    protected:
        int totalPrice;
        int numGPU;
};