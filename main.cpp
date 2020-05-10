#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <bitset>
#include <string>
#include <chrono>


std::mutex mtx1;
std::mutex mtx2;
std::mutex mtx3;
std::mutex mtx4;

int Tackt;

std::vector<long> setVector();
std::vector<std::bitset<6>> ToBit(long, long,int);
void showVector(std::vector<long>);
void Conveer(long, long,std::vector<long>&,int,int);
long ToLong(std::bitset<6>,int);
std::vector<long> vectorMultiplication(std::vector<long> firstVec, std::vector<long> SecondVec);
std::bitset<6> bitsetMult(std::bitset<6>, std::bitset<6>, int, int);
std::vector<int> translateStrtoInt(std::string);
std::vector<int> Umnoj(std::vector<int>, int);
void showBinaryVector(std::vector<std::bitset<6>>);
std::bitset<6> translateIntToBit(std::vector<int>);

[[noreturn]] void TacktCount();

int main() {
    setlocale(LC_ALL, "rus");
    std::vector<long>firstVector, secondVector;
    std::vector<long>RezVector;


    firstVector = setVector();

    secondVector = setVector();

    showVector(firstVector);

    showVector(secondVector);

    RezVector = vectorMultiplication(firstVector, secondVector);

    showVector(RezVector);


    return 0;
}
std::vector<long> setVector() {
    std::vector<long> firstVector;
    bool isEnd;
    isEnd = true;
    do
    {
        std::string str;
        int a;
        std::cout << "Введите число в десятичной системе для вектора" << std::endl;
        std::cin >> a;
        firstVector.push_back(a);
        std::cout << "Продолжить?(y/n)" << std::endl;
        std::getline(std::cin, str);
        std::getline(std::cin, str);
        if (str == "y") {
            isEnd = false;
        }
        else {

            isEnd = true;
        }
    } while (!isEnd);
    return firstVector;
}

void showVector(std::vector<long> Vector) {
    for (auto i : Vector) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

std::vector<long> vectorMultiplication(std::vector<long> firstVec, std::vector<long>SecondVec) {
    std::vector<long> vec;
    Tackt = 0;
    Tackt -= firstVec.size();
    std::thread thr(TacktCount);
    thr.detach();
    for (int j = 0, i = 0; i < firstVec.size() && j < SecondVec.size(); i++, j++) {
        std::thread th1(Conveer, firstVec[i], SecondVec[j], std::ref(vec),i,Tackt);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (i + 1 == firstVec.size() || j + 1 == SecondVec.size()) {
            th1.join();
        }
        else {
            th1.detach();
            Tackt++;
        }

    }

    return vec;
}

std::bitset<6> bitsetMult(std::bitset<6>, std::bitset<6>, int, int) {
    std::lock_guard<std::mutex> guard(mtx1);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    unsigned int t = 0;
    std::bitset<6> rez;
    std::vector<int>one = translateStrtoInt(a.to_string());
    std::vector<int>two = translateStrtoInt(b.to_string());
    std::vector<int> umnojRez, tempRez{0,0,0,0,0,0};
    for (auto i = 0; i < two.size();i++) {
        umnojRez = Umnoj(one, two[i]);
        for (auto j = 1; j <= umnojRez.size(); j++) {
            tempRez[tempRez.size() - j] += umnojRez[umnojRez.size() - j];
        }
        for (int j = tempRez.size() - 1; j >= 0; j--) {
            if (tempRez[j] > 1) {
                if (j == 0) {
                    tempRez.insert(tempRez.begin(), 1);
                }
                else {
                    tempRez[j - 1]++;
                }
                tempRez[j] = 0;
            }
        }
        if (i + 1 != two.size()) {
            tempRez.push_back(0);
        }
    }
    rez = translateIntToBit(tempRez);
    while (tackt + 1 > Tackt) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return rez;
}

std::vector<int> translateStrtoInt(std::string str) {
    std::vector<int>vec;
    for (auto i = 0; i < str.size(); i++) {
        if (str[i] == '0') {
            vec.push_back(0);
        }
        else {
            vec.push_back(1);
        }
    }
    return vec;
}

std::vector<int> Umnoj(std::vector<int> vec, int num ) {
    std::vector<int> rez;
    for (auto i = 0; i < vec.size(); i++) {
        rez.push_back(vec[i] * num);
    }
    return rez;
}

void showBinaryVector(std::vector<std::bitset<6>> vec) {
    for (auto i = 0; i < vec.size(); i++) {
        std::cout << "Число номер № " << i << " : ";
        std::cout << vec[i].to_string() << std::endl;
    }
    std::cout << std::endl;
}

std::bitset<6> translateIntToBit(std::vector<int> vec) {
    std::string str = "";
    while (vec.size() > 6)
    {
        vec.erase(vec.begin());
    }
    for (auto i = 0; i < vec.size(); i++) {
        if (vec[i] == 0) {
            str += '0';
        }
        else {
            str += '1';
        }
    }
    return std::bitset<6>(str);
}

void Conveer(long first, long second, std::vector<long>&rez, int PairNum,int tackt) {
    std::vector<std::bitset<6>>Nums;
    std::bitset<6>result;
    std::cout << "" << std::endl;
    Nums = ToBit(first, second,tackt);
    mtx4.lock();
    std::cout << "Пара " << PairNum << " Переведена в двоичное" << std::endl;
    std::cout << "Номер такта : " << Tackt << std::endl;
    showBinaryVector(Nums);
    mtx4.unlock();
    result = bitsetMult(Nums[0], Nums[1], PairNum, tackt);
    mtx4.lock();
    std::cout << "Пара " << PairNum << " подсчитана" << std::endl;
    std::cout << "Номер такта : " << Tackt << std::endl;
    std::cout << "Результат в двоичной форме : " << result.to_string() << std::endl;
    std::cout << std::endl;
    mtx4.unlock();
    mtx4.lock();
    rez.push_back(ToLong(result,tackt));
    std::cout << "Пара " << PairNum << " Переведена в десятиричное" << std::endl;
    std::cout << "Номер такта : " << Tackt << std::endl;
    std::cout << "Результат в десятиричной форме : " << result.to_ulong() << std::endl;
    std::cout << std::endl;
    mtx4.unlock();
}

std::vector<std::bitset<6>> ToBit(long first, long second,int TempTackt) {
    std::lock_guard<std::mutex> guard(mtx2);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::vector<std::bitset<6>> rez;
    rez.push_back(std::bitset<6>(first));
    rez.push_back(std::bitset<6>(second));
    while (TempTackt + 1 > Tackt) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return rez;
}

long ToLong(std::bitset<6>bit,int tackt) {
    std::lock_guard<std::mutex> guard(mtx3);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    while (tackt + 1 > Tackt) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return bit.to_ulong();
}

[[noreturn]] void TacktCount() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        Tackt++;
    }
}