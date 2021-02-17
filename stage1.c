#include "stages.h"


/*
This function gets a file name and write it to a new file without comments.
*/

char * stage_one_func(char input_file_name[], char * output_file_name)
{
	
    char c;
    FILE * output_file_ptr;
    FILE * input_file_ptr;
    int in_commenct = False;
    int after_backlslash = False;
    int after_asterisk = False;
    
    output_file_name = (char *) malloc((strlen(input_file_name)+2)*sizeof(char));
    
    if (input_file_name[strlen(input_file_name)-1] != 'c' || input_file_name[strlen(input_file_name)-2] != '.' )    		/*check that file name is legal*/
	{
		printf("File name is invalid,and program will be closed. Ta Ta!\n");
        free(output_file_name);
		return (char *)1;
	}

    if (!(input_file_ptr = fopen(input_file_name,"r")))													/*open input file */
    {	
        printf("File is not found, and program will be closed. Ta Ta!\n");
        free(output_file_name);
        return (char *)1; 
    }

    sprintf(output_file_name, "%s%d",input_file_name,1);												/*make new file name*/
    
	if (!(output_file_ptr = fopen(output_file_name,"w")))												/*open output file */
    {
        printf("File hasn't created properly, and program will be closed. Ta Ta!\n");
        fclose(input_file_ptr);
        free(output_file_name);
        return (char *)1; 
    }
           
     
    while(True)																					/*scaning the file for comments*/
    {
        c = fgetc(input_file_ptr);
		if (feof(input_file_ptr)) break;

        if (c == '/') 
        {
            if(in_commenct)
            {
                if(after_asterisk) 
                {
                    after_asterisk = False;
                    in_commenct = False;
                }       
            }
            else after_backlslash = True;
        }
            
        else if (c == '*')
        {
            if (after_backlslash) 
            {
                in_commenct = True;
                after_backlslash = False;

            }
            else if (in_commenct) after_asterisk = True;
            else
            {
                fputc(c,output_file_ptr);
            }
        }
        else
        {   
            if (in_commenct)
            {
                if (after_asterisk) after_asterisk = False;
            }
            else
            {
                if (after_backlslash) 
                {
                    after_backlslash = False;
                    fputc('\\',output_file_ptr);
                }
			fputc(c,output_file_ptr);
            }
            
        }
    }
        fclose(output_file_ptr);
        fclose(input_file_ptr);
    return output_file_name;
}

