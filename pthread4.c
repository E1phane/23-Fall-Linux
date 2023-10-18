#include <pthread.h>
#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES
#define N 4

struct ThreadData {
	int thread_id;
	int num_threads;
	int num_elements;
	int terms;
	double* x;
	double* result;
};

void sinx_taylor(void* data) {
	struct ThreadData* thread_data = (struct ThreadData*) data;
	int thread_id = thread_data -> thread_id;
	int num_threads = thread_data -> num_threads;
	int num_elements = thread_data -> num_elements;
	int terms = thread_data -> terms;
	double* x = thread_data -> x;
	double* result = thread_data -> result;

        for(int i = thread_id; i < num_elements; i+= num_threads){
                double value = x[i];
                double numer = x[i] * x[i] * x[i];
                double denom = 6.; // 3!
                int sign = -1;

                for(int j = 1; j <= terms; j++){
                        value += (double) sign * numer / denom;
                        numer *= x[i] * x[i];
                        denom *= (2.*(double)j+2.) * (2.*(double)j+3.);
                        sign *= -1;
                }
                result[i] = value;
        }
}

int main() {
        double x[N] = {0, M_PI/6., M_PI/3., 0.134};
        double res[N];

	int num_threads = 4;
	pthread_t threads[num_threads];
	struct ThreadData thread_data[num_threads];

	for(int i = 0; i < num_threads; i++) {
		thread_data[i].thread_id = i;
		thread_data[i].num_threads = num_threads;
		thread_data[i].num_elements = N;
		thread_data[i].terms = 3;
		thread_data[i].x = x;
		thread_data[i].result = res;

		pthread_create(&threads[i], NULL, (void*(*)(void*))sinx_taylor, &thread_data[i]);
	}

	for(int i = 0; i < num_threads; i++)
		pthread_join(threads[i], NULL);
	
        for(int i = 0; i < N; i++){
                printf("sin(%.2f) by Taylor series = %f\n", x[i], res[i]);
                printf("sin(%.2f) = %f\n", x[i], sin(x[i]));
        }
        return 0;
}
