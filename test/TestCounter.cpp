/*
lidor mondel
207478256
lidormon20@gmail.com
*/

#include "assets.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

using namespace doctest;
using namespace std;

const int MIN_TESTS = 20;

int return_code = -1;

struct ReporterCounter : public ConsoleReporter
{
    ReporterCounter(const ContextOptions &input_options)
        : ConsoleReporter(input_options) {}

    void test_run_end(const TestRunStats &run_stats) override
    {
        if (run_stats.numAsserts >= MIN_TESTS)
        {
            if (run_stats.numAssertsFailed == 0)
            {
                cout << "All tests passed!" << endl;
            }
            return_code = 0;
        }
        else
        {
            cout << "Please write at least " << MIN_TESTS << " tests! " << endl;
            return_code = 1;
        }
    }
};

REGISTER_REPORTER("counter", 1, ReporterCounter);

int mainTest(int argc, char **argv)
{
    // Load all data from files.
    Assets::init();
    Context context;
    context.addFilter("reporters", "counter");
    context.run();
    // Release all data from files.
    Assets::release();
    return return_code;
}
