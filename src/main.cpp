#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "xphysx.h"

class xApp : public ofBaseApp {

	public:
		ofEasyCam cam;
		int w,h;

		void setup(){
			ofSetFrameRate(150);
			w=ofGetScreenWidth();
			h=ofGetScreenHeight();
			InitPhysX();
		}

		void exit(){
			shutdown();
		}

		void update(){
			ofSetWindowTitle(ofToString(ofGetFrameRate()));
		}

		void draw(){
			ofBackgroundGradient(255,0);

			cam.begin();
		        int timeSinceStart = ofGetElapsedTimef(); 
		        float deltaTime = (timeSinceStart - oldTimeSinceStart)/1000.0f;
		        oldTimeSinceStart = timeSinceStart;
		        mAccumulator  += deltaTime;
		        while(mAccumulator > gTimeStep) {
		                mAccumulator -= gTimeStep;
		         	stepPhysX();
		        }
		        if(gScene)
		                stepPhysX();

		        RenderData(gScene->getRenderBuffer());
			cam.end();
		}

		void keyPressed(int key){

		}
};

int main( ){
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1280, 720, OF_WINDOW);
	ofRunApp(new xApp());
}
