#include <stdio.h>
#include <stdlib.h>

#include "code_gen.h"


char *vhost_code(char *webiste, char *xammp_path)
{
    int buff = 1028;
    char *vhost_content = malloc(sizeof(char) * buff);

    snprintf(vhost_content, buff,
            "\n<VirtualHost *:80>\n"    
            "   ServerAdmin webmaster@%s\n"
            "   DocumentRoot \"%s\" \n"
            "   ServerName %s\n"
            "   ErrorLog \"logs/%s-error.log\"\n"
            "   CustomLog \"logs/%s-access.log\" common\n"
            "</VirtualHost>\n", 
            webiste, xammp_path, webiste, webiste, webiste
    );

    return vhost_content;

}

char *host_code(char *webiste)
{
    int buff = 1028;
    char *host_content = malloc(sizeof(char) * buff);
    snprintf(host_content, buff, "\n127.0.0.1   %s\n127.0.0.1   www.%s\n", webiste, webiste);
    return host_content;
}
