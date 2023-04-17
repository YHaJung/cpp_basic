#include<iostream>
#include<vector>
using namespace std;

void nextUpdate(vector<int>& seats, int num, int max){
    if (num <= max){
        // cout << num << endl;
        seats[num-1] = 1;
        // cout << seats[num-1] << endl;
        nextUpdate(seats, num*2, max);
        nextUpdate(seats, num*2 + 1, max);
    }
}

int checkPrev(vector<int>& seats, int num){
    if ((int) seats[num / 2 - 1] == 0){
        return num;
    }
    else{
        return checkPrev(seats, (int) num / 2);
    }
}

int seatArrange(int N, int Q, vector<int>& queue){
    //N: number of seats in GSDS
    //Q: number of students
    //queue: desired seat for each student in a row

    /* Your code here */
    vector<int> seats(N, 0);
    for (int v : queue){
        vector<int> result;
        if (seats[v-1] == 0){
            nextUpdate(seats, v, N);
            cout << v << ' ';
        }else{
            cout << checkPrev(seats, v) << ' ';
        }
        // string s(result.begin(), result.end());
    }
    cout << endl;
    return 0;
}

/* Do not modify below */
int main(){
    int N1 = 6;          
    int Q1 = 4;             
    vector<int> queue1 = {3, 5, 6, 2};
    seatArrange(N1, Q1, queue1);

    int N2 = 10;
    int Q2 = 5;
    vector<int> queue2 = {2, 8, 6, 7, 10};
    seatArrange(N2, Q2, queue2);

    int N3 = 13;
    int Q3 = 7;
    vector<int> queue3 = {8, 7, 6, 9, 10, 12, 13};
    seatArrange(N3, Q3, queue3);

    int N4 = 8;
    int Q4 = 4;
    vector<int> queue4 = {1, 2, 3, 4};
    seatArrange(N4, Q4, queue4);
}