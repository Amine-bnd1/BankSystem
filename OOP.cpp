#include <iostream>
#include "Lib/clsInputValidate.h"
#include "Lib/clsString.h" 
#include "Lib/clsDate.h"
#include "Lib/clsUtil.h"
#include "Screens/User/clsLoginScreen.h"
#include "Screens/clsScreen.h"
#include "Screens/clsMainScreen.h"

    using namespace std;

int main()
{
    
    while (true)
    {
        if(!clsLoginScreen::ShowLoginScreen())
            break;
    }

    return 0;
    
};