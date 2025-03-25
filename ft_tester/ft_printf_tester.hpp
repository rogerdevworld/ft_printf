#ifndef FT_PRINTF_TESTER_HPP
#define FT_PRINTF_TESTER_HPP

#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <sstream>
#include <stdexcept>
#include <cstring>

// ANSI Color Codes
#define RESET       "\033[0m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define BOLD        "\033[1m"

#define BUFFER_SIZE 4096
#define TIMEOUT_US  500000 // 500ms timeout
#define TEST(n, func) if (test_number == 0 || test_number == n) { func; test_count++; }

// Global variables
extern int test_number;
extern int test_count;
extern int success_count;
extern bool show_details;

class Tester {
private:
    int pipefd[2];
    int saved_stdout;

    void setup_pipe() {
        if (pipe(pipefd) == -1) {
            throw std::runtime_error("Pipe creation failed");
        }
        saved_stdout = dup(STDOUT_FILENO);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
    }

    std::string read_output() {
        char buffer[BUFFER_SIZE];
        ssize_t bytes_read = read(pipefd[0], buffer, BUFFER_SIZE - 1);
        if (bytes_read <= 0) return "";
        buffer[bytes_read] = '\0';
        return std::string(buffer);
    }

    void restore_stdout() {
        dup2(saved_stdout, STDOUT_FILENO);
        close(pipefd[0]);
        close(saved_stdout);
    }

public:
    template<typename... Args>
    void compare(const std::string& format, Args... args) {
        pid_t pid = fork();
        if (pid < 0) {
            throw std::runtime_error("Fork failed");
        }
        else if (pid == 0) { // Child process
            // Test printf
            setup_pipe();
            int printf_ret = printf(format.c_str(), args...);
            std::string printf_out = read_output();
            restore_stdout();

            // Test ft_printf
            setup_pipe();
            int ft_printf_ret = ft_printf(format.c_str(), args...);
            std::string ft_printf_out = read_output();
            restore_stdout();

            // Compare results
            if (printf_out == ft_printf_out && printf_ret == ft_printf_ret) {
                exit(EXIT_SUCCESS);
            } else {
                if (show_details) {
                    std::cout << BOLD << "Test " << test_count << ":\n" << RESET;
                    std::cout << CYAN << "Format:    \"" << format << "\"\n" << RESET;
                    std::cout << GREEN << "printf:    [" << printf_out << "] (" << printf_ret << ")\n" << RESET;
                    std::cout << YELLOW << "ft_printf: [" << ft_printf_out << "] (" << ft_printf_ret << ")\n" << RESET;
                }
                exit(EXIT_FAILURE);
            }
        }
        else { // Parent process
            int status;
            usleep(TIMEOUT_US);
            if (waitpid(pid, &status, WNOHANG) == 0) {
                kill(pid, SIGKILL);
                if (show_details) {
                    std::cout << RED << "Test " << test_count << " timeout\n" << RESET;
                }
                return;
            }

            if (WIFEXITED(status)) {
                if (WEXITSTATUS(status) == EXIT_SUCCESS) {
                    success_count++;
                    if (show_details) {
                        std::cout << GREEN << "Test " << test_count << " passed\n" << RESET;
                    }
                } else if (show_details) {
                    std::cout << RED << "Test " << test_count << " failed\n" << RESET;
                }
            }
        }
    }

    void show_leaks() {
        pid_t pid = fork();
        if (pid == 0) {
            execlp("valgrind", "valgrind", "--leak-check=full", "--show-leak-kinds=all", 
                   "--track-origins=yes", "--quiet", "./ft_printf_tester", "leaks", NULL);
            exit(EXIT_FAILURE);
        } else {
            waitpid(pid, NULL, 0);
        }
    }
};

// Test macros
#define TEST_CASE(num, format, ...) \
    TEST(num, { \
        tester.compare(format, ##__VA_ARGS__); \
        if (show_details) std::cout << "------------------------\n"; \
    })

#define CATEGORY(name, min, max) \
    if (test_number == 0 || (test_number >= min && test_number <= max)) { \
        std::cout << BOLD << MAGENTA << "\n=== " << name << " ===\n" << RESET; \
    }

#endif