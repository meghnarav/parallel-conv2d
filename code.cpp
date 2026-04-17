#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<omp.h>
using namespace std;
#define N 1000  // Change to 1500 or 2000 in next iterations (for better performance analysis)

vector<vector<int>> input(N, vector<int>(N));
vector<vector<int>> output_seq(N, vector<int>(N));
vector<vector<int>> output_par(N, vector<int>(N));

// Initialize matrix with random pixel values (0–255)
void initialize(){
    for(int i=0; i< N; i++)
        for(int j=0; j< N; j++)
            input[i][j]=rand() % 256;
}

// Sequential Convolution
void sequential(){
    for(int i=1; i< N-1; i++){
        for(int j=1; j< N-1; j++){
            int sum=0;
            for(int ki= -1; ki<=1; ki++){
                for(int kj= -1; kj<=1; kj++){
                    sum +=input[i + ki][j + kj];
                }
            }
            output_seq[i][j]=sum/9;
        }
    }
}
// Parallel Convolution using OpenMP
void parallel(int num_threads){
    omp_set_num_threads(num_threads);

    #pragma omp parallel for schedule(static)
    for(int i=1; i< N-1; i++){
        for(int j=1; j< N-1; j++){
            int sum=0;
            for(int ki= -1; ki<=1; ki++){
                for(int kj= -1; kj<=1; kj++){
                    sum +=input[i + ki][j + kj];
                }
            }
            output_par[i][j]=sum/9;
        }
    }
}

int main(){
    srand(time(0));
    initialize();
    double start, end;

    // Sequential Execution
    start=omp_get_wtime();
    sequential();
    end=omp_get_wtime();
    double seq_time=end-start;
    cout<< "Sequential Time: "<< seq_time<< " seconds\n";

    // Thread counts to test
    int thread_counts[]={1, 2, 4, 8};
    for(int t : thread_counts){
        start=omp_get_wtime();
        parallel(t);
        end=omp_get_wtime();
        double par_time=end-start;
        double speedup=seq_time/par_time;
        double efficiency=speedup/t;
        cout<< "\nThreads: "<< t;
        cout<< "\nTime: "<< par_time<< " seconds";
        cout<< "\nSpeedup: "<< speedup;
        cout<< "\nEfficiency: "<< efficiency<< endl;
    }
    return 0;
}
