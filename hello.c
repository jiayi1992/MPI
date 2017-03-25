#include <stdio.h>
#include <stdlib.h>


int main() {

	int number=0;
	printf("This is my first program!\n");

	FILE *fp = fopen("C:\\Users\\jiayi\\Desktop\\P\\numbers.txt", "rt+"); 
	if(fp==NULL)
    printf("The file fscanf.out was not opened\n");
	else
	fscanf(fp,"%d",&number);
	//int *souceArray = new int[number];
	//for(int i=0;i<number;i++)
	//{
	//	fscanf(fp,"%d",&souceArray[i]);
	//}
	printf("%d",number);




  return 0;
}
