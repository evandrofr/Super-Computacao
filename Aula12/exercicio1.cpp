#include <iostream>
#include <unistd.h>
#include <omp.h>

double funcao1() {
    sleep(4);
    return 47;
}

double funcao2() {
    sleep(1);
    return -11.5;
}

int main() {
    double res_func1, res_func2;

    #pragma omp parallel 
    {
        #pragma omp master
        {
            #pragma omp task
            {
                std::cout << "Estou rodando na thread:" << omp_get_thread_num() << "\n";
                res_func1 = funcao1();
            }
            #pragma omp task
            {   
                std::cout << "Estou rodando na thread:" << omp_get_thread_num() << "\n";
                res_func2 = funcao2();
            }
        }
    }

    
    

    std::cout << res_func1 << " " << res_func2 << "\n";
}
