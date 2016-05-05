#include <thread>
#include <cstdio>
#include <chrono>
#include <vector>
#include <sched.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <QString>
#include <QtCore>
using namespace std;

#define NUMTHREADS 4
#define TAMANHO 100*1000*1000

//--------------------------Variavel Global--------------------------------

//iniciliza com TAMANHO por não poder dar vetor.size(), já que é float
float vetor [TAMANHO];

//-------------------------Criaçao do Vetor----------------------------

double criaVetor(){
    auto t1 = std::chrono::high_resolution_clock::now();

    srand((unsigned)time(NULL));
    for(int i = 0; i < TAMANHO; i++){
        vetor[i] = (rand() % 3) -1;
    }

    auto t2 =  std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo = t2 - t1;
    return tempo.count();
}

//-----------------------------Funçao 1---------------------------------

int funcao1(){
    int soma = 0;
    for(int i = 0; i < TAMANHO; i++){
        soma += vetor[i];
    }
    return soma;
}

//-----------------------------Funçao 1---------------------------------

int funcao2(){
   int soma = 0;
    for(int i = 0; i < TAMANHO; i++){
        soma += sin(vetor[i]);
    }
    return soma;
}

//-----------------------------Funçao 1---------------------------------

int funcao3(){
    int soma = 0;
    for(int i = 0; i < TAMANHO; i++){
        soma += log(vetor[i]);
    }
    return soma;
}


//-----------------------------Analise 1-------------------------------

//calcular o tempo de execução de uma thread em um core
double analise1(int i){
    auto t1 = std::chrono::high_resolution_clock::now();

    cpu_set_t cpuset;

    if (i == 1){
        thread a1(funcao1);
        CPU_ZERO(&cpuset);
        CPU_SET(0, &cpuset);
        pthread_setaffinity_np(a1.native_handle(), sizeof(cpu_set_t), &cpuset);
        a1.join();
    }
    else if (i == 2){
        thread a1(funcao2);
        CPU_ZERO(&cpuset);
        CPU_SET(0, &cpuset);
        pthread_setaffinity_np(a1.native_handle(), sizeof(cpu_set_t), &cpuset);
        a1.join();
    }
    else if (i == 3){
        thread a1(funcao3);
        CPU_ZERO(&cpuset);
        CPU_SET(0, &cpuset);
        pthread_setaffinity_np(a1.native_handle(), sizeof(cpu_set_t), &cpuset);
        a1.join();
    }

    auto t2 =  std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo = t2 - t1;
    return tempo.count();
}

//-----------------------------Analise 2-------------------------------

//calcular o tempo de execução de 2 threads com a mesma função
//cada uma rodando em um core diferente

double analise2(int i){
    auto t1 = std::chrono::high_resolution_clock::now();

    cpu_set_t cpuset;

    if (i == 1){
        thread a2_0(funcao1);
        thread a2_1(funcao1);
        CPU_ZERO(&cpuset);
        CPU_SET(0, &cpuset);
        pthread_setaffinity_np(a2_0.native_handle(), sizeof(cpu_set_t), &cpuset);
        CPU_ZERO(&cpuset);
        CPU_SET(1, &cpuset);
        pthread_setaffinity_np(a2_1.native_handle(), sizeof(cpu_set_t), &cpuset);
        a2_0.join();
        a2_1.join();
    }
    else if (i == 2){
        thread a2_0(funcao2);
        thread a2_1(funcao2);
        CPU_ZERO(&cpuset);
        CPU_SET(0, &cpuset);
        pthread_setaffinity_np(a2_0.native_handle(), sizeof(cpu_set_t), &cpuset);
        CPU_ZERO(&cpuset);
        CPU_SET(1, &cpuset);
        pthread_setaffinity_np(a2_1.native_handle(), sizeof(cpu_set_t), &cpuset);
        a2_0.join();
        a2_1.join();
    }
    else if (i == 3){
        thread a2_0(funcao3);
        thread a2_1(funcao3);
        CPU_ZERO(&cpuset);
        CPU_SET(0, &cpuset);
        pthread_setaffinity_np(a2_0.native_handle(), sizeof(cpu_set_t), &cpuset);
        CPU_ZERO(&cpuset);
        CPU_SET(1, &cpuset);
        pthread_setaffinity_np(a2_1.native_handle(), sizeof(cpu_set_t), &cpuset);
        a2_0.join();
        a2_1.join();
    }
    auto t2 =  std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo = t2 - t1;
    return tempo.count();
}

//-----------------------------Analise 3-------------------------------

//calcular o tempo de execução de 2 threads com a mesma função
//ambas rodando no mesmo core

double analise3(int i){
    auto t1 = std::chrono::high_resolution_clock::now();

    cpu_set_t cpuset;

    if (i == 1){
        thread a3_0(funcao1);
        thread a3_1(funcao1);
        CPU_ZERO(&cpuset);
        CPU_SET(0, &cpuset);
        pthread_setaffinity_np(a3_0.native_handle(), sizeof(cpu_set_t), &cpuset);
        CPU_ZERO(&cpuset);
        CPU_SET(0, &cpuset);
        pthread_setaffinity_np(a3_1.native_handle(), sizeof(cpu_set_t), &cpuset);
        a3_0.join();
        a3_1.join();
    }
    else if (i == 2){
        thread a3_0(funcao2);
        thread a3_1(funcao2);
        CPU_ZERO(&cpuset);
        CPU_SET(0, &cpuset);
        pthread_setaffinity_np(a3_0.native_handle(), sizeof(cpu_set_t), &cpuset);
        CPU_ZERO(&cpuset);
        CPU_SET(0, &cpuset);
        pthread_setaffinity_np(a3_1.native_handle(), sizeof(cpu_set_t), &cpuset);
        a3_0.join();
        a3_1.join();
    }
    else if (i == 3){
        thread a3_0(funcao3);
        thread a3_1(funcao3);CPU_ZERO(&cpuset);
        CPU_SET(0, &cpuset);
        pthread_setaffinity_np(a3_0.native_handle(), sizeof(cpu_set_t), &cpuset);
        CPU_ZERO(&cpuset);
        CPU_SET(0, &cpuset);
        pthread_setaffinity_np(a3_1.native_handle(), sizeof(cpu_set_t), &cpuset);
        a3_0.join();
        a3_1.join();
    }
    auto t2 =  std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tempo = t2 - t1;
    return tempo.count();
}

//-------------------------Salvar em Arquivo---------------------------

/*
 * Funçao que salva os resultados de cada teste e colocar num .txt
 *        no formato aceito pelo gnuplot
 *
 */

//------------------------------MAIN-----------------------------------

int main(){
    double value;


    ofstream file("output.txt");
    if(!file){
        cout << "Erro ao criar arquivo\n";
        return -1;
    }

    value = criaVetor();
    cout << "Tempo de Criação do Vetor: " << value << endl;

    cout << "Iniciando os testes, aguarde\n";

    file << "Title Function1 Function2 Function3" << endl;
    file << "Analise1 ";
     value = analise1(1);
    file << " " << value << " ";

    value = analise1(2);
    file << " " << value << " ";

    value = analise1(3);
    file << " " << value << endl;

    file << "Analise2 ";
    value = analise2(1);
    file << " " << value << " ";

    value = analise2(2);
    file << " " << value << " ";

    value = analise2(3);
    file << " " << value << endl;

    file << "Analise3 ";
    value = analise3(1);
    file << " " << value << " ";

    value = analise3(2);
    file << " " << value << " ";

    value = analise3(3);
    file << " " << value << endl;

    cout << "Testes finalizados\n";
    file.close();

    return 0;
}
