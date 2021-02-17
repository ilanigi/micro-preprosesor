#include "stages.h"

/*
This method gets a file name and oprn a new file with all "#includewrite to it.
*/

int stage_two_func(char *input_file_name)
{
		
	FILE * output_file_ptr;
    FILE *includer_file_pntr;
	FILE * input_file_ptr;

	char buf1[MAX_CHAR_IN_LINE];
	char inc_file_name[MAX_FILE_NAME_SIZE];
	char check_inc[INC_SIZE+1] = {0};

	int i;
	int place;
    char c;
    boolean failed_search = False;
 
  	if (!(input_file_ptr = fopen(input_file_name,"r")))
    {
        printf("File is not found, and program will be closed. Ta Ta!\n");
        return 1; 
    }

	input_file_name[strlen(input_file_name)-1] = '2';

	if (!(output_file_ptr = fopen(input_file_name,"w")))
    {
        printf("File hasn't created properly, and program will be closed. Ta Ta!\n");
        return 1; 
    }
    	
    while (True)
    {
    	place = ftell(input_file_ptr);

		c = fgetc(input_file_ptr);    	
    	while(isspace(c))										/*go to first chat that is not a spcae*/
    	{
			if (feof(input_file_ptr)) break;
			c = fgetc(input_file_ptr);
    	}
    	
    	if (feof(input_file_ptr)) break;

    	if(c == '#')
    	{
    	
		/* check if next string is incluse, get file name, open it, copy its contne to output file and close it.*/    	
			for (i = 0; i < INC_SIZE; i += 1)	
			{
				if (feof(input_file_ptr)) break;	
				check_inc[i] = fgetc(input_file_ptr);							
			}
			check_inc[++i] = '\0';


			if (strcmp("include",check_inc) == 0)					/*check if buffer is "include"*/
			{

				c = fgetc(input_file_ptr);
				while(isspace(c))										/*go to first chat that is not a spcae*/
				{
					if (feof(input_file_ptr) || c == '\n') break;		/*if c is a new line - it means therre is a line after include which is not valid*/
					c = fgetc(input_file_ptr);
				}
				
				if ('\"' == c )
				{					
					c = fgetc(input_file_ptr);
					i = 0;
					while (c != '\"' && c != '\n' && i < MAX_FILE_NAME_SIZE)	/*find file name*/
					{
						inc_file_name[i] = c;
						c = fgetc(input_file_ptr);
						i++;
					}
					inc_file_name[i] = '\0';
										
					if (c == '\"')							
					{		
						while(c != '\n' && feof(input_file_ptr))			/*make sure rest of the line is empty*/
						{
							if (!isspace(c)) failed_search = True;
						}
					
						if (!failed_search){	
															
							if (!(includer_file_pntr = fopen(inc_file_name,"r")))			/*open included file and add it to output file*/
							{
								printf("Included file is not found, and program will be closed. Ta Ta!\n");
								fclose(output_file_ptr);
								fclose(input_file_ptr);
								return 1; 
							}
										
							while(True)
							{
								c = fgetc(includer_file_pntr);
								if (feof(includer_file_pntr)) break;
								fputc(c,output_file_ptr);						
							}							
							fputc('\n',output_file_ptr);	
							fclose(includer_file_pntr);
							printf("included file  added sucsesfully!\n");
							
						}
					}
					else failed_search = True;	
				}
				else failed_search = True;
			}
			else failed_search = True;
		}
    	else failed_search = True;
    	
    	if (failed_search)									/*if search faild in some point, pointer goes back to start of line and write it to output file.*/
    	{
			fseek(input_file_ptr,place,SEEK_SET);
			fgets(buf1,MAX_CHAR_IN_LINE,input_file_ptr);
			fputs(buf1,output_file_ptr);
			failed_search = False;
    	}
     		

	}
		  
	fclose(input_file_ptr);
	fclose(output_file_ptr);
	free(input_file_name);
    return 0;
}
