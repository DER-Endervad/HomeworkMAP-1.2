#include <iostream>
#include <thread>
#include <Windows.h>
#include <vector>

void one_flow(std::vector<int> t, std::vector<int> t_t, std::vector<int> o_h_t, std::vector<int> m);
void one_flow2(std::vector<int>& one, std::vector<int>& sum);

void two_flow(std::vector<int> t, std::vector<int> t_t, std::vector<int> o_h_t, std::vector<int> m);
void two_flow2(std::vector<int>& one, std::vector<int>& sum);

void four_flow(std::vector<int> t, std::vector<int> t_t, std::vector<int> o_h_t, std::vector<int> m);
void four_flow2(std::vector<int>& one, std::vector<int>& sum);

void eight_flow(std::vector<int> t, std::vector<int> t_t, std::vector<int> o_h_t, std::vector<int> m);
void eight_flow2(std::vector<int>& one, std::vector<int>& sum);

void sixteen_flow(std::vector<int> t, std::vector<int> t_t, std::vector<int> o_h_t, std::vector<int> m);
void sixteen_flow2(std::vector<int>& one, std::vector<int>& sum);

void flow(const int& one_size, const int& two_size, std::vector<int>& one, std::vector<int>& sum);

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "Количество аппаратных ядер: " << std::thread::hardware_concurrency() << std::endl;
    int thousand = 1000, ten_thousand = 10000, one_hundred_thousand = 100000, million = 1000000;
    std::vector<int> t(thousand), t_t(ten_thousand), o_h_t(one_hundred_thousand), m(million);
    std::cout << "Элементы: 1.000       10.000      100.000     1.000.000" << std::endl;

    one_flow(t, t_t, o_h_t, m); //1 поток
    two_flow(t, t_t, o_h_t, m); //2 потокa
    four_flow(t, t_t, o_h_t, m); //4 потокa
    eight_flow(t, t_t, o_h_t, m); //8 потоков
    sixteen_flow(t, t_t, o_h_t, m); //16 потоков
}

void one_flow(std::vector<int> t, std::vector<int> t_t, std::vector<int> o_h_t, std::vector<int> m) {
    std::cout << "1 поток   ";
    std::vector<int> number(10000000);

    // 1.000 + 1.000
    two_flow2(t, number);

    // 10.000 + 10.000
    two_flow2(t_t, number);

    // 100.000 + 100.000
    two_flow2(o_h_t, number);

    // 1.000.000 + 1.000.000
    two_flow2(m, number);
    std::cout << std::endl;
}

void one_flow2(std::vector<int>& one, std::vector<int>& sum) {
    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < one.size(); ++i) {
        sum[i] = one[i] + one[i];
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> time = end - start;
    std::cout << time.count() << "      ";
}

void two_flow(std::vector<int> t, std::vector<int> t_t, std::vector<int> o_h_t, std::vector<int> m) {
    std::cout << "2 потока  ";
    std::vector<int> number(10000000);
    
    // 1.000 + 1.000
    two_flow2(t, number);

    // 10.000 + 10.000
    two_flow2(t_t, number);

    // 100.000 + 100.000
    two_flow2(o_h_t, number);

    // 1.000.000 + 1.000.000
    two_flow2(m, number);
    std::cout << std::endl;
}

void two_flow2(std::vector<int>& one, std::vector<int>& sum) {
    auto start = std::chrono::steady_clock::now();
    const int null = 0; int size1 = 0, size2 = 0;

    size1 = one.size() / 8; size2 = one.size();
    std::thread t1(flow, std::ref(null), std::ref(size1), std::ref(one), std::ref(sum));
    std::thread t2(flow, std::ref(size1), std::ref(size2), std::ref(one), std::ref(sum));
    t1.join(); t2.join();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> time = end - start;
    std::cout << time.count() << "      ";
}

void four_flow(std::vector<int> t, std::vector<int> t_t, std::vector<int> o_h_t, std::vector<int> m) {
    std::cout << "4 потока  ";
    std::vector<int> number(10000000);

    // 1.000 + 1.000
    four_flow2(t, number);

    // 10.000 + 10.000
    four_flow2(t_t, number);

    // 100.000 + 100.000
    four_flow2(o_h_t, number);

    // 1.000.000 + 1.000.000
    four_flow2(m, number);
    std::cout << std::endl;
}

void four_flow2(std::vector<int>& one, std::vector<int>& sum) {
    auto start = std::chrono::steady_clock::now();
    const int null = 0; int size1 = 0, size2 = 0, size3 = 0, size4 = 0;

    size1 = one.size() / 8; size2 = size1 * 2; size3 = size1 * 3; size4 = one.size();
    std::thread t1(flow, std::ref(null), std::ref(size1), std::ref(one), std::ref(sum));
    std::thread t2(flow, std::ref(size1), std::ref(size2), std::ref(one), std::ref(sum));
    std::thread t3(flow, std::ref(size2), std::ref(size3), std::ref(one), std::ref(sum));
    std::thread t4(flow, std::ref(size3), std::ref(size4), std::ref(one), std::ref(sum));
    t1.join(); t2.join(); t3.join(); t4.join();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> time = end - start;
    std::cout << time.count() << "      ";
}

void eight_flow(std::vector<int> t, std::vector<int> t_t, std::vector<int> o_h_t, std::vector<int> m) {
    std::cout << "8 потоков ";
    std::vector<int> number(10000000);

    // 1.000 + 1.000
    eight_flow2(t, number);

    // 10.000 + 10.000
    eight_flow2(t_t, number);

    // 100.000 + 100.000
    eight_flow2(o_h_t, number);

    // 1.000.000 + 1.000.000
    eight_flow2(m, number);
    std::cout << std::endl;
}

void eight_flow2(std::vector<int>& one, std::vector<int>& sum) {
    auto start = std::chrono::steady_clock::now();
    const int null = 0; int size1 = 0, size2 = 0, size3 = 0, size4 = 0, size5 = 0, size6 = 0, size7 = 0, size8 = 0;

    size1 = one.size() / 8; size2 = size1 * 2; size3 = size1 * 3; size4 = size1 * 4; size5 = size1 * 5; size6 = size1 * 6; size7 = size1 * 7; size8 = one.size();
    std::thread t1(flow, std::ref(null), std::ref(size1), std::ref(one), std::ref(sum));
    std::thread t2(flow, std::ref(size1), std::ref(size2), std::ref(one), std::ref(sum));
    std::thread t3(flow, std::ref(size2), std::ref(size3), std::ref(one), std::ref(sum));
    std::thread t4(flow, std::ref(size3), std::ref(size4), std::ref(one), std::ref(sum));
    std::thread t5(flow, std::ref(size4), std::ref(size5), std::ref(one), std::ref(sum));
    std::thread t6(flow, std::ref(size5), std::ref(size6), std::ref(one), std::ref(sum));
    std::thread t7(flow, std::ref(size6), std::ref(size7), std::ref(one), std::ref(sum));
    std::thread t8(flow, std::ref(size7), std::ref(size8), std::ref(one), std::ref(sum));
    t1.join(); t2.join(); t3.join(); t4.join(); t5.join(); t6.join(); t7.join(); t8.join();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> time = end - start;
    std::cout << time.count() << "      ";
}

void sixteen_flow(std::vector<int> t, std::vector<int> t_t, std::vector<int> o_h_t, std::vector<int> m) {
    std::cout << "16 потоков ";
    std::vector<int> number(10000000);

    // 1.000 + 1.000
    sixteen_flow2(t, number);

    // 10.000 + 10.000
    sixteen_flow2(t_t, number);

    // 100.000 + 100.000
    sixteen_flow2(o_h_t, number);

    // 1.000.000 + 1.000.000
    sixteen_flow2(m, number);
}

void sixteen_flow2(std::vector<int>& one, std::vector<int>& sum) {
    auto start = std::chrono::steady_clock::now();
    const int null = 0; int size1, size2, size3, size4, size5, size6, size7, size8, size9, size10, size11, size12, size13, size14, size15, size16;

    size1 = one.size() / 16; size2 = size1 * 2; size3 = size1 * 3; size4 = size1 * 4; size5 = size1 * 5; size6 = size1 * 6; size7 = size1 * 7; size8 = size1 * 8;
    size9 = size1 * 9; size10 = size1 * 10; size11 = size1 * 11; size12 = size1 * 12; size13 = size1 * 13; size14 = size1 * 14; size15 = size1 * 15; size16 = one.size();
    std::thread t1(flow, std::ref(null), std::ref(size1), std::ref(one), std::ref(sum));
    std::thread t2(flow, std::ref(size1), std::ref(size2), std::ref(one), std::ref(sum));
    std::thread t3(flow, std::ref(size2), std::ref(size3), std::ref(one), std::ref(sum));
    std::thread t4(flow, std::ref(size3), std::ref(size4), std::ref(one), std::ref(sum));
    std::thread t5(flow, std::ref(size4), std::ref(size5), std::ref(one), std::ref(sum));
    std::thread t6(flow, std::ref(size5), std::ref(size6), std::ref(one), std::ref(sum));
    std::thread t7(flow, std::ref(size6), std::ref(size7), std::ref(one), std::ref(sum));
    std::thread t8(flow, std::ref(size7), std::ref(size8), std::ref(one), std::ref(sum));
    std::thread t9(flow, std::ref(size8), std::ref(size9), std::ref(one), std::ref(sum));
    std::thread t10(flow, std::ref(size9), std::ref(size10), std::ref(one), std::ref(sum));
    std::thread t11(flow, std::ref(size10), std::ref(size11), std::ref(one), std::ref(sum));
    std::thread t12(flow, std::ref(size11), std::ref(size12), std::ref(one), std::ref(sum));
    std::thread t13(flow, std::ref(size12), std::ref(size13), std::ref(one), std::ref(sum));
    std::thread t14(flow, std::ref(size13), std::ref(size14), std::ref(one), std::ref(sum));
    std::thread t15(flow, std::ref(size14), std::ref(size15), std::ref(one), std::ref(sum));
    std::thread t16(flow, std::ref(size15), std::ref(size16), std::ref(one), std::ref(sum));
    t1.join(); t2.join(); t3.join(); t4.join(); t5.join(); t6.join(); t7.join(); t8.join(); t9.join(); t10.join(); t11.join(); t12.join(); t13.join(); t14.join(); t15.join(); t16.join();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> time = end - start;
    std::cout << time.count() << "      ";
}

void flow(const int& one_size, const int& two_size, std::vector<int>& one, std::vector<int>& sum){
    for (int i = one_size; i < two_size; ++i) {
        sum[i] = one[i] + one[i];
    }
}
