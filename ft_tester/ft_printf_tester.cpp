#include "ft_printf_tester.hpp"
#include "../include/ft_printf.h"

// Global variables
int test_number = 0;
int test_count = 0;
int success_count = 0;
bool show_details = false;

int main(int argc, char **argv) {
    if (argc > 1) {
        if (strcmp(argv[1], "leaks") == 0) {
            Tester tester;
            tester.show_leaks();
            return 0;
        }
        test_number = atoi(argv[1]);
        show_details = true;
    }

    Tester tester;

    // Mandatory tests
    CATEGORY("MANDATORY TESTS", 1, 50)
    TEST_CASE(1, "%c", 'A');
    TEST_CASE(2, "%s", "Hello");
    TEST_CASE(3, "%p", (void *)0x1234);
    TEST_CASE(4, "%d", 42);
    TEST_CASE(5, "%i", -42);
    TEST_CASE(6, "%u", 4294967295);
    TEST_CASE(7, "%x", 255);
    TEST_CASE(8, "%X", 255);
    TEST_CASE(9, "%%");
    TEST_CASE(10, "Char: %c, Str: %s, Num: %d", 'X', "test", 42);

    // Bonus tests
    CATEGORY("BONUS TESTS", 51, 100)
    TEST_CASE(51, "%-10s", "left");
    TEST_CASE(52, "%010d", 42);
    TEST_CASE(53, "%.5s", "precision");
    TEST_CASE(54, "%#x", 42);
    TEST_CASE(55, "% d", 42);
    TEST_CASE(56, "%+d", 42);
    TEST_CASE(57, "%+-10.5d", 42);

    // Summary
    std::cout << BOLD << "\n=== SUMMARY ===\n" << RESET;
    std::cout << "Tests run: " << test_count << "\n";
    std::cout << GREEN << "Passed: " << success_count << RESET << "\n";
    std::cout << RED << "Failed: " << (test_count - success_count) << RESET << "\n";

    if (test_count == success_count) {
        std::cout << GREEN << BOLD << "All tests passed!\n" << RESET;
    } else {
        std::cout << RED << BOLD << "Some tests failed\n" << RESET;
    }

    return 0;
}