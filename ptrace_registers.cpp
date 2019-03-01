#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/reg.h>   /* For constants ORIG_EAX etc */
#include <sys/user.h>
#include <sys/syscall.h> /* SYS_write */
int main() {
    pid_t child;
    long orig_rax;
    int status;
    int iscalling = 0;
    struct user_regs_struct regs;

    child = fork();
    if(child == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execl("/bin/ls", "ls", "-l", "-h", NULL);
    } else {
        while(1) {
            wait(&status);
            if(WIFEXITED(status))
                break;
            orig_rax = ptrace(PTRACE_PEEKUSER,
                              child, 8 * ORIG_RAX,
                              NULL);
            if(orig_rax == SYS_write) {
                ptrace(PTRACE_GETREGS, child, NULL, &regs);
                if(!iscalling) {
                    iscalling = 1;
                    printf("SYS_write call with %lld, %lld, %lld\n",
                            regs.rdi, regs.rsi, regs.rdx);
                }
                else {
                    printf("SYS_write call return %lld\n", regs.rax);
                    iscalling = 0;
                }
            }
            ptrace(PTRACE_SYSCALL, child, NULL, NULL);
        }
    }
    return 0;
}
