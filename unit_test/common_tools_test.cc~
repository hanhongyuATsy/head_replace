#include "gtest/gtest.h"
#include "../common_tools.h"

//using ::testing::Return; 
//using ::testing::_;
//using ::testing::DoAll;
//
using namespace std;

class ListFileValidationTest: public testing::Test
{

protected:
    void SetUp();
    void TearDown();

public:
    void operatorTest();

};

TEST_F(ListFileValidationTest, operatorTest)
{
    operatorTest();
}

void ListFileValidationTest::SetUp()
{
    cout << "ListFile gtest setup"<<endl;
}

void ListFileValidationTest::TearDown()
{
    cout << "ListFile gtest teardown()"<<endl;
}

void ListFileValidationTest::operatorTest()
{
    cout<< "operatorTest"<<endl;
    ListFile   proj_dir("/home/hhy/cpp_test/my");    
    EXPECT_EQ(14, proj_dir.get_all_file_count());
}
