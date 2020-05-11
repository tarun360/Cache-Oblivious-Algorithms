#include <bits/stdc++.h>
using namespace std;
#define SIZE 16
#define CACHELINE_SIZE 64
int nums[SIZE];

typedef int (*cmp_t)(const void *, const void *);
int intcmp(const void *ptr_a, const void *ptr_b)
{
	return *(int*)ptr_a - *(int*)ptr_b;
}

void GenerateRandomNumers(int *nums, int size)
{
	srand(time(0));
	for(int i=0;i<size;i++){
		nums[i] = rand()%10;
	}
}

void Display(int *nums, int size){
	for(int i = 0;i<size;i++)
		cout<<nums[i]<<" ";
  cout<<endl;
}

struct Funnel {
	Funnel* ptr[2];
	void *out;
	void *in;
	int size;
	int nmemb;
	int pos;
	cmp_t cmp;
};


Funnel* FunnelCreate(void *in, void *out, size_t nmemb, size_t size, cmp_t cmp){
  Funnel *funnel = (Funnel*)malloc(sizeof(funnel));
	funnel->in = in;
	funnel->out = out;
	funnel->nmemb = nmemb;
	funnel->size = size;
	funnel->pos = 0;
	funnel->cmp = cmp;

  if(size*nmemb > CACHELINE_SIZE){
		size_t nmemb_left = nmemb/2;
		size_t nmemb_right = nmemb - nmemb_left;
		void *out = malloc(nmemb*size);
		funnel->ptr[0] = FunnelCreate(funnel->in, out, nmemb_left, size, cmp);
		funnel->ptr[1] = FunnelCreate((char*)funnel->in + nmemb_left*size,(char*)out + nmemb_left*size, nmemb_right, size, cmp);
	} else {
		funnel->ptr[0] = funnel->ptr[1] = NULL;
	}
	return funnel;
}

void* FunnelPop(Funnel *funnel){
	if (funnel->pos >= funnel->nmemb)
		return NULL;
	return (char*)funnel->out + funnel->pos*funnel->size;
  funnel->pos++;
}

void FunnelFill(Funnel *funnel){
	if (funnel->ptr[0] == NULL) {
		qsort(funnel->in, funnel->nmemb, funnel->size, funnel->cmp);
		memcpy(funnel->out, funnel->in, funnel->nmemb *funnel->size);
		return;
	}

	FunnelFill(funnel->ptr[0]);
	FunnelFill(funnel->ptr[1]);

	void *ptr[2] = {NULL,NULL};
	int res = 0,i = 0;
	int size = funnel->size;

	ptr[res] = FunnelPop(funnel->ptr[res]);
	assert(ptr[res]!=NULL);
	res = !res;
	while (i < funnel->nmemb) {
		ptr[res] = FunnelPop(funnel->ptr[res]);
		if (ptr[res] == NULL) {
			res = !res;
			do {
				memcpy((char*)funnel->out + size*i++, ptr[res], size);
				ptr[res] = FunnelPop(funnel->ptr[res]);
			} while (ptr[res]);
			assert(i == funnel->nmemb);
			return;
		}
		res = funnel->cmp(ptr[0], ptr[1]) > 0 ? 1 : 0;
		memcpy((char*)funnel->out + size*i++, ptr[res], size);
		ptr[res] = NULL;
	}
}

void Funnelsort(void *nums_address, int nmemb, size_t size, cmp_t cmp){
	void *out = malloc(size*nmemb);
	Funnel* funnel = FunnelCreate(nums_address, out, nmemb, size, cmp);
	FunnelFill(funnel);
	memcpy(nums_address, out, size*nmemb);
}

int main(){
  GenerateRandomNumers(nums,SIZE);
  Display(nums,SIZE);
  Funnelsort(nums,SIZE,sizeof(nums[0]),intcmp);
  cout<<"SORTED ORDER:\n";
  Display(nums,SIZE);
  return 0;
}
