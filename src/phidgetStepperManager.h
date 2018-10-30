#include "ofMain.h"
#include "phidgetStepper.h"
#include "ofxGui.h"

class phidgetStepperManager
{

    public:
        vector<motor> motors;
        void setup(string filename);
        void setupGui();

    ofJson settings;

    ofxPanel guiMotors;

} ;