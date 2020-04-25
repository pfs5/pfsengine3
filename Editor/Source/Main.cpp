#include <iostream>
#include "../../pfsengine3/Source/Rendering/Renderer.h"
// ----------------------------------------------------------------------------
using namespace std;
// ----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	PRenderer r;
	r.Test();

	cout << "Press ENTER to close ..." << endl;
	getchar();
}
// ----------------------------------------------------------------------------