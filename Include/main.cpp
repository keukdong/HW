
#pragma once
#include "Test.h"
#include "time.h"
#include <crtdbg.h>


int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    cvector::insert_test();
    cvector::erase_test();
    cvector::copy_test();
    cvector::copy_this_test();
    cvector::move_test();
    cvector::swap_test();


    matrix::IdentityMatrix();


    return 0;
}

