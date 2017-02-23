main()
{
	char cmd[MAXCMDLENGTH];
	char prompt[] = "tsh#";
	char *aCmd[MAXCMDS][MAXARGS];
	int cmdCounter. i, nargs, tooLong;
	char *nextCmd;
	while(1==1) {
		tooLong = 0;
		fputs(prompt, stdout);
		
		while(fgets(cmd,MAXCMDLENGTH,stdin)==NULL) {
			fputs(prompt, stdout);
		}
		
		while(strchr(cmd, '\n') == NULL) {
			tooLong = 1;
			fgets(cmd, MAXCMDLENGTH, stdin);
		}
		
		if(tooLong) {
			printf("Exceeded command length\n");
			continue;
		}
		
		cmdCounter = 0;
		
		while((nextCmd = (char *)strrchr(cmd, '|')) != NULL) {
			*nextCmd = '\0';
			nextCmd++;
			aCmd[cmdCounter][0] = nextCmd;
			cmdCounter++;
		}
		
		aCmd[cmdCounter][0] = cmd;
		cmdCounter++;
		
		for(i = 0; i < cmdCounter; i++) {
			printf("Command %d <%s>\n", i, aCmd[i][0]);
		}
		
		for(i = 0; i < cmdCounter; i++) {
			printf("-------- Command %d -------------\n", i);
			aCmd[i][0] = (char *)strtok(aCmd[i][0], " \n");
			printf("Arg 0 is <%s>. ", aCmd[i][0]);
			nargs = 1;
			aCmd[i][nargs] = (char *)strtok(NULL, " \n");
			
			while(aCmd[i][nargs] != NULL) {
				printf("Arg %d is <%s>. ", nargs, aCmd[i][nargs]);
				nargs++;
				aCmd[i][nargs] = (char *)strtok(NULL, " \n");
			}
			
			print("\n\n");
		}
	}
}