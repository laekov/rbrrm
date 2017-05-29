#include <router.h>
#include <costflow.h>
#include <dinic.h>
#include <map>
#include <string>

using std::string;
using std::map;

map<string, RouterCreator> g_routers;

REGISTERROUTER("costflow", CostFlowRouter);
REGISTERROUTER("dinic", DinicFlowRouter);

