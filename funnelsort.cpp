#include <bits/stdc++.h>
using namespace std;
#define SIZE 1000000
#define MAXNUM 10000000
#define CACHELINE_SIZE 64
int nums[SIZE],nums_copy[SIZE];
int K=0;

typedef int (*cmp_t)(const void *, const void *);
int intcmp(const void *ptr_a, const void *ptr_b)
{
	return *(int*)ptr_a - *(int*)ptr_b;
}

void GenerateRandomNumers(int *nums, int size)
{
	srand(time(0));
	for(int i=0;i<size;i++){
		nums[i] = rand()%MAXNUM;
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
  Funnel *funnel = (Funnel*)malloc(sizeof(Funnel));
	funnel->in = in;
	funnel->out = out;
	funnel->nmemb = nmemb;
	funnel->size = size;
	funnel->pos = 0;
	funnel->cmp = cmp;

	if(nmemb > K){
		int closest2 = (1<<(int)ilogb(nmemb));
		size_t nmemb_left=0, nmemb_right=0;
		if(nmemb >= 2*K){
			nmemb_left = closest2/2;
			nmemb_right = nmemb - nmemb_left;
		}else{
			nmemb_left = K;
			nmemb_right = nmemb - nmemb_left;
		}
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
	return (char*)funnel->out + funnel->pos++ * funnel->size;
}

void FunnelFill(Funnel *funnel){
	if (funnel->ptr[0] == NULL) {
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

void DeAllocateSpace(Funnel* funnel, bool left){
	if(funnel->ptr[0]==NULL){
		if(left==true){
			free(funnel->out);
			funnel->out=NULL;
		}
		free(funnel->ptr[0]);
		funnel->ptr[0]=NULL;
		free(funnel->ptr[1]);
		funnel->ptr[1]=NULL;
		return;
	}
	DeAllocateSpace(funnel->ptr[0],true);
	DeAllocateSpace(funnel->ptr[1],false);

	if(left==true){
		free(funnel->out);
		funnel->out=NULL;
	}
	free(funnel->ptr[0]);
	funnel->ptr[0]=NULL;
	free(funnel->ptr[1]);
	funnel->ptr[1]=NULL;
}

void KMerge(void *nums_address, int nmemb, size_t size, cmp_t cmp){
	void *out = malloc(size*nmemb);
	Funnel* funnel = FunnelCreate(nums_address, out, nmemb, size, cmp);
	FunnelFill(funnel);
	memcpy(nums_address, out, size*nmemb);
	DeAllocateSpace(funnel,true);
}

void Funnelsort(void *nums, int nmemb, size_t size, cmp_t cmp){
	if(nmemb <= 8){
		qsort(nums,nmemb,size,cmp);
		return;
	}
	int step = ilogb((double)pow(nmemb,1.0/3));
	int step_size = 1<<step, jump=step_size;
	void* fromhere = NULL;
	int iters = (nmemb+step_size-1)/step_size;
	for(int i=1;i<=iters;i++){
		fromhere = (char*)nums+(i-1)*step_size*(size);
		if(i==iters)
			jump = nmemb - (i-1)*step_size;
		Funnelsort(fromhere,jump,size,cmp);
	}
	K = step_size;
	KMerge(nums,nmemb,size,cmp);
}

int main(){
  GenerateRandomNumers(nums,SIZE);
	for(int i=0;i<SIZE;i++)
		nums_copy[i] = nums[i];
  //Display(nums,SIZE);
	double s,e,t;

	s=clock();
	qsort(nums_copy,SIZE,sizeof(nums[0]),intcmp);
	e=clock();
	t=((double)(e-s)/CLOCKS_PER_SEC);
  cout<<"QuickSort time : "<<t<<endl;

	s=clock();
  Funnelsort(nums,SIZE,sizeof(nums[0]),intcmp);
	e=clock();
	t=((double)(e-s)/CLOCKS_PER_SEC);
  cout<<"Funnelsort time : "<<t<<endl;


	//cout<<"SORTED ORDER:\n";
  //Display(nums,SIZE);
	if(is_sorted(nums,nums+SIZE))
		cout<<"SORTED :)\n";
	else{
		cout<<"NOT SORTED :(\n";
		for(int i=1;i<SIZE;i++){
			if(nums[i]<nums[i-1]){
				cout<<nums[i-1]<<" "<<nums[i]<<endl;
				break;
			}
		}
	}
  return 0;
}
