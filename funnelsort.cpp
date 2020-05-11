#include <bits/stdc++.h>
using namespace std;
#define SIZE 16
#define CACHELINE_SIZE 64

typedef int (*cmp_t)(const void *, const void *);

int nums[SIZE];

int intcmp(const void *p_a, const void *p_b)
{
	return *(int*)p_a - *(int*)p_b;
}

void generate(int *data, int size)
{
	srand(time(0));
	for(int i=0;i<size;i++){
		data[i] = rand()%10;
	}
}

void output(int *data, int size){
	for (int i = 0; i < size; i++)
		cout<<data[i]<<" ";
  cout<<endl;
}

struct Funnel {
	Funnel* lr[2];
	void *out;
	void *in;
	int size;
	int nmemb;
	int pos;
	cmp_t cmp;
};


Funnel* Funnel_create(void *in, void *out, size_t nmemb, size_t size, cmp_t cmp){
  Funnel *funnel = (Funnel*)malloc(sizeof(funnel));
	funnel->in = in;
	funnel->out = out;
	funnel->nmemb = nmemb;
	funnel->size = size;
	funnel->pos = 0;
	funnel->cmp = cmp;

  if (size * nmemb > CACHELINE_SIZE) {
		size_t nmemb_left = nmemb/2;
		size_t nmemb_right = nmemb - nmemb_left;
		void *out = malloc(nmemb * size);
		funnel->lr[0] = Funnel_create(funnel->in, out, nmemb_left,
					      size, cmp);
		funnel->lr[1] = Funnel_create((char*)funnel->in + nmemb_left * size,
					      (char*)out + nmemb_left * size,
					      nmemb_right, size, cmp);
	} else {
		funnel->lr[0] = funnel->lr[1] = NULL;
	}
	return funnel;
}

void* Funnel_pop(Funnel *funnel){
	if (funnel->pos >= funnel->nmemb)
		return NULL;
	return (char*)funnel->out + funnel->pos * funnel->size;
  funnel->pos++;
}

void Funnel_fill(Funnel *funnel){
	if (funnel->lr[0] == NULL) {
		qsort(funnel->in, funnel->nmemb, funnel->size, funnel->cmp);
		memcpy(funnel->out, funnel->in, funnel->nmemb *funnel->size);
		return;
	}

	Funnel_fill(funnel->lr[0]);
	Funnel_fill(funnel->lr[1]);

	void *lr[2] = { NULL, NULL };
	int res = 0, i = 0;
	int size = funnel->size;

	lr[res] = Funnel_pop(funnel->lr[res]);
	assert(lr[res]);
	res = !res;
	while (i < funnel->nmemb) {
		lr[res] = Funnel_pop(funnel->lr[res]);
		if (lr[res] == NULL) {
			res = !res;
			do {
				memcpy((char*)funnel->out + size * i++, lr[res], size);
				lr[res] = Funnel_pop(funnel->lr[res]);
			} while (lr[res]);
			assert(i == funnel->nmemb);
			return;
		}
		res = funnel->cmp(lr[0], lr[1]) > 0 ? 1 : 0;
		memcpy((char*)funnel->out + size * i++, lr[res], size);
		lr[res] = NULL;
	}
}

void Funnelsort(void *ptr, int nmemb, size_t size, cmp_t cmp){
	void *out = malloc(size * nmemb);
	Funnel* funnel = Funnel_create(ptr, out, nmemb, size, cmp);
	Funnel_fill(funnel);
	memcpy(ptr, out, size * nmemb);
}

int main(){
  generate(nums,SIZE);
  output(nums,SIZE);
  Funnelsort(nums,SIZE,sizeof(nums[0]),intcmp);
  cout<<"SORTED ORDER:\n";
  output(nums,SIZE);
  return 0;
}
