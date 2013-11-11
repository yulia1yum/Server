#include <stdio.h>
#include <pthread.h>

int* a;
int size;

typedef struct task* task_t;//описание 

struct task
{
	int start;
	int end;
};

void* sort(void* par) {
	task_t t = (task_t)par;
	printf("Task was extracted\n");
	int start = t->start;
	int end = t->end; //сохраняем в структуру значение
	printf("%d %d\n", start, end);
	for (int i=start; i<end; i++){
        int temp=a[i];
        int j=i-1;
        while (j>=start && a[j]>temp){
                a[j+1]=a[j];
                j--;
        }
        a[j+1]=temp;
    }
}

void start_sort() {
	int midle = size / 2;
	pthread_t thr1, thr2;
	task_t t1 = malloc(sizeof(struct task));
	task_t t2 = malloc(sizeof(struct task));
	printf("Middle = %d\n", midle);
	t1->start = 0;
	t1->end = midle;
	t2->start = midle;
	t2->end = size;
	printf("Tasks was created!\n");
	int i = pthread_create(&thr1, NULL, &sort, (void*)t1);
	i = pthread_create(&thr2, NULL, &sort, (void*)t2);
	pthread_join(thr1, NULL);
	pthread_join(thr2, NULL);
	free(t1);
	free(t2);
}

void merge(int *dest, int second) { // второй массив, куда определям уже полностью отсортированный массив, начало второго куска в первом массиве
	int c1 = 0, c2 = second;
	for (int i = 0; i < size; i++) {
		if (c1 <= second && c2 <= size) {
			dest[i] = a[c1] > a[c2] ? a[c2++] : a[c1++]; // присваевается наименьший из кусочкоу и увеличивается счетчик там, откуда взяли элемент
		}
		if (c1 > second && c2 < size) {// если первый закончился, то копируем оставшийся 
			dest[i] = a[c2++];
		}
		if (c1 < second && c2 > size) {
			dest[i] = a[c1++];
		}
	}
}

int main(){
	scanf("%d", &size);
	printf("Size = %d\n", size);
	a=malloc(sizeof(int) * size);// захватить память под массив
	fflush(stdout);
	for (int i=0; i<size; i++){
		scanf("%d", a + i); //&a[i]
	}
	fflush(stdout);
	printf("%s\n");//печатаем пустую строку

	start_sort();
	int *final = malloc(sizeof(int) * size);
	merge(final, size / 2);


/*	for (int i=0; i<size; i++){
		printf("%d ", *(a + i));
	}
	printf("\n");	*/
	for (int i=0; i<size; i++){
		printf("%d ", *(final + i));
	}
	printf("\n");
	free(a);
	free(final);
	return 0;

}


