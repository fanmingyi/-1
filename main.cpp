#include <stdio.h>
#include <string.h>


char Paswword[20]="aaaaaaaaaaaaaaaaaaa";


int main(){
	
	char cPas[20]={0};

	int iResult;
	
	FILE * pFile =NULL;
	
	pFile = fopen("pd.txt","r");
	
	fscanf(pFile,"%s",cPas);

	iResult =strcmp(Paswword,cPas);
	
	if(iResult==0){
		printf("Welcome \r\n");
	}else{
		printf("fail \r\n");
	}
	getchar();
	return 0;
}