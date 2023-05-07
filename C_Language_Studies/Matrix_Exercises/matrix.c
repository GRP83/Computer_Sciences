#include <stdio.h>
#include<unistd.h>
void print(int ip){
  printf("X %d", ip);
}

int main()
{
int i;
for (i=0; i<1000; i++){
	usleep(1000000);
	printf("%d,\n",i);
	}

return 0;
}
