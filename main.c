#include <stdio.h>
#include <stdlib.h> 
#include <stdlib.h> 
#include <string.h>
#include <direct.h> // for _mkdir
#include "./helper/code_gen.h" // load helper function


typedef struct{
    char *addr;
    char *drive;
    char *addr_location;
    char *vhost;
} Cli_info;

static const char *host_path = "C:/Windows/System32/drivers/etc/hosts";

char* read_input(const char *msg, int len)
{
    char* buffer = (char *)malloc(sizeof(char) * (len+1));

    fputs(msg, stdout);
    fgets(buffer, len, stdin);

    // remove New line
    int last_char = strlen(buffer)-1;
    if (buffer[last_char] == '\n'){
        buffer[last_char] = '\0';
    }

    return buffer;
}

void file_append(const char *path, const char *text)
{
    FILE *fd;    
    fd = fopen(path, "a");

    if (fd == NULL){
        printf("Error: unable to Write to file %s\n", path);
        exit(1);
    }

    fprintf(fd, text);
    fclose(fd);
}

Cli_info *new_Cli()
{
    char *vhost = ":/xampp/apache/conf/extra/httpd-vhosts.conf";
    char *htdocs = ":/xampp/htdocs/";

    Cli_info *info = malloc(sizeof (Cli_info));
    info->addr = read_input("Web Name: ", 100);
    info->drive = read_input("XAMPP Location: ", 100);

    size_t len = strlen(htdocs)+strlen(info->addr)+strlen(info->drive)+1;
    info->addr_location = malloc(sizeof(char) * len);
    info->vhost = malloc(sizeof(char) * strlen(vhost)+strlen(info->drive)+1);

    // append 
    strcpy(info->addr_location, info->drive);
    strcat(info->addr_location, htdocs);
    strcat(info->addr_location, info->addr);

    strcpy(info->vhost, info->drive);
    strcat(info->vhost, vhost);
        
    return info;
}

int main()
{
    Cli_info *info = new_Cli();
    if (_mkdir(info->addr_location) == -1){
        printf("Error: unable to create Dir \"%s\"\n", info->addr_location);
        exit(1);
    }

    char *hosts_code = host_code(info->addr);
    file_append(host_path, hosts_code);

    char *vhost_content = vhost_code(info->addr, info->addr_location);
    file_append(info->vhost, vhost_content);
   
    free(vhost_content);
    free(hosts_code);
    free(info);

    return 0;
}



