main() {
	int len;
	char *ptr;
	char delim[]=" \t\n"; 
	char str[]=" ls\t \n-x \n ";
	int i;
	
	printf("str is <%s>\n",str);
	
	printf("str is <%s>\n",str);
	for (i=0;i<len;i++) {
		printf("Character %d is <%c> ASCII %d\n",i,str[i],str[i]);
	}
	
	len = strlen(str);
	ptr = strtok(str,delim); 
	
	while (ptr!=NULL) { 
		printf("Next token <%s>\n",ptr);
		ptr=strtok(NULL,delim);
	}
	
	printf("str is <%s>\n",str); 
}