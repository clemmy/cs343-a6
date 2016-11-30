#include <iostream>
#include "config.h"

using namespace std;

void uMain::main() {
  const char *configFile = "soda.config";

  ConfigParms params;
  processConfigFile(configFile, params);

  cout << params.sodaCost << endl;
  cout << params.numCouriers << endl;
  cout << params.maxPurchases << endl;
}
