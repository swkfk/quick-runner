#include "program.h"

#include <iostream>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static int child_program_status, child_pid;

void sigchld_handler(int sig) {
    if (sig == SIGCHLD) {
        int status;
        waitpid(child_pid, &status, WNOHANG);
        if ((status & 0x7F) > 0) {
            // killed by sig
            child_program_status = status & 0x7F; // only the sig is useful
        } else {
            // exit with a fault
            child_program_status = status;
        }
    }
}

void sigint_handler(int sig) {
    if (sig == SIGINT) {
        std::cout << std::endl << "Interrupted! Kill the program!" << std::endl;
        kill(child_pid, SIGKILL);
    }
}

namespace program {

int run(const std::vector<std::string> &args, int time_limit, const std::string &input) {
    // TODO: modify the exec name
    std::string cmd = "./a.out";
    for (auto &s : args) {
        cmd += " \"" + s + "\"";
    }

    bool has_input = input != "";

    // child to parent or parent to child
    // if `input` is specified, the fd_ptc will be used to fetch the file content
    // at any situation, the fd_ctp will be used
    int fd_ptc[2], fd_ctp[2];

    if (has_input) {
        if (~pipe(fd_ptc)) {
            // TODO: pipe error
        }
    }

    int pid = fork();
    if (pid < 0) {
        // TODO: fork error
    }
    if (pid > 0) {
        // parent
        child_pid = pid;
        signal(SIGCHLD, sigchld_handler);
        signal(SIGINT, sigint_handler);

        if (has_input) {
            close(fd_ptc[0]);
            FILE *fp = fopen(input.c_str(), "rb");
            char chrs[BUFSIZ];
            int sze_read;
            while ((sze_read = fread(chrs, sizeof(char), BUFSIZ, fp)) != 0) {
                write(fd_ptc[1], chrs, sze_read);
            }
            fclose(fp);
            close(fd_ptc[1]);
        }

        unsigned int msec = 0;

        while (1) {
            usleep(100000);

            msec += 100;
            if (time_limit && msec / 1000 >= time_limit) {
                // TODO: tle error
                kill(child_pid, SIGALRM); // It's important to kill first
                usleep(100000);           // And this
                std::cerr << "Time Limit Exceeded! (" << time_limit << "s)" << std::endl;
            }

            // check whether the child is over
            int ret = kill(pid, 0);
            if (ret < 0) {
                return child_program_status;
            }
        }
    } else {
        // child
        // close(fd_ctp[0]);
        if (has_input) {
            close(fd_ptc[1]);
            dup2(fd_ptc[0], STDIN_FILENO);
        }
        // dup2(fd_ctp[1], STDOUT_FILENO);

        int ret = system(cmd.c_str());

        if (has_input) {
            close(fd_ptc[0]);
        }
        exit((ret >> 8) & 0xFF);
    }
}

}; // namespace program