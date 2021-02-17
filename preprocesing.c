#include "preprocesing.h"

/*
This program take a c file and return c1 file with out comments anf c2 file without comments and with included files in the right place.
--I assumed that max size of file name is 50--
*/


int main(int argc,char * argv[])
{	

	char file_name[MAX_FILE_NAME_SIZE];
    char * post_stage_one_file_name = 0;
    
	strcpy(file_name,argv[1]);

    if (check_cmd_input(argc)) return 0;    

	post_stage_one_file_name = stage_one_func(file_name, post_stage_one_file_name);

    if (post_stage_one_file_name == (char *)1 ) 
    {
    return 0;
    }
    

    else printf("stage one has ended successfully.\n");

    if (stage_two_func(post_stage_one_file_name)) return 0;

    else {
        printf("stage two has ended successfully.\n");
        printf("Program has ended the process successfully and will be closed. Ta Ta!.\n");
    }

    return 0;

}

