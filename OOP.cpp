#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cctype>
#include <iomanip>
#include "clsString.h"
#include "clsDate.h"
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsMainScreen.h"
#include "clsScreen.h"
#include "clsShowClientList.h"
#include "clsLoginScreen.h"
  
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