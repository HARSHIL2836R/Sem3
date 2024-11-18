#include "server_requests.h"

#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
// You should NOT modify ANYTHING in this file.

extern bool __evaluate_testcase_one(void);
extern bool __evaluate_testcase_two(void);
extern bool __evaluate_testcase_three(void);
extern bool __evaluate_testcase_four(void);
extern bool __evaluate_testcase_five(void);
extern bool __evaluate_testcase_six(void);
extern bool __evaluate_testcase_seven(void);

void __handle_sigchld(int __sig) {
    int status;
    waitpid(-1, &status, WNOHANG);
    if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == SIGALRM) {
            exit(3);
        } else {
            exit(1);
        }
    }
    if (WIFEXITED(status)) {
        if (WEXITSTATUS(status) == 0) {
            exit(0);
        } else if (WEXITSTATUS(status) == 1) {
            exit(1);
        }
        exit(2);
    }
    exit(4);
}

void __execute_testcase(std::function<bool(void)> testcase_function, 
        std::string testcase_name, double time_limit) {
    signal(SIGCHLD, __handle_sigchld);
    int pid;
    if ((pid = fork()) == 0) {
        exit(2 - 2 * static_cast<int>(testcase_function()));
    }
    usleep(static_cast<long long>(time_limit * 1.0e+6));
    kill(pid, SIGALRM);
    exit(3);
}

void __testcase_wrapper(std::function<bool(void)> testcase_function, 
        std::string testcase_name, double time_limit, int &result) {
    int pid;
    if ((pid = fork()) == 0) {
        __execute_testcase(testcase_function, testcase_name, time_limit);
    }
    int status;
    waitpid(pid, &status, 0);
    if (!WIFEXITED(status)) {
        std::cout << "Unknown error in " << testcase_name << std::endl;
        exit(1);
    }
    switch (WEXITSTATUS(status)) {
    case 0:
        std::cout << testcase_name << " passed!" << std::endl;
        result++;
        break;
    case 2:
        std::cout << "Wrong answer in " << testcase_name << std::endl;
        break;
    case 1:
        std::cout << "Runtime error in " << testcase_name << std::endl;
        break;
    case 3:
        std::cout << "Time limit exceeded in " << testcase_name << std::endl;
        break;
    default:
        std::cout << "Unknown error in " << testcase_name << std::endl;
        break;
    }
}

int main(void) {
    int result = 0;
    __testcase_wrapper(__evaluate_testcase_one, "Testcase 1", 1.0, result);
    __testcase_wrapper(__evaluate_testcase_two, "Testcase 2", 1.0, result);
    __testcase_wrapper(__evaluate_testcase_three, "Testcase 3", 2.0, result);
    __testcase_wrapper(__evaluate_testcase_four, "Testcase 4", 3.0, result);
    __testcase_wrapper(__evaluate_testcase_five, "Testcase 5", 5.0, result);
    __testcase_wrapper(__evaluate_testcase_six, "Testcase 6", 13.0, result);
    __testcase_wrapper(__evaluate_testcase_seven, "Testcase 7", 20.0, result);
    std::cout << "RESULTS : " << result << " / 7" << std::endl;
    return 0;
}
