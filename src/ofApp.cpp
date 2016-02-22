#include "ofApp.h"

using namespace ofxCv;
using namespace cv;

void ofApp::setup() {
    ofSetVerticalSync(true);
    cam.initGrabber(640, 480);

    tracker.setup();
    tracker.setRescale(.5);

    classifier.load("expressions");
}

void ofApp::update() {
    cam.update();
    if(cam.isFrameNew()) {
        if(tracker.update(toCv(cam))) {
            classifier.classify(tracker);
        }
    }
}

void ofApp::draw() {
    ofSetColor(255);
    cam.draw(0, 0);
    // In your actual application, you can get rid of this; no more lines.
    tracker.draw();

    int w = 100, h = 12;
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(5, 10);
    int n = classifier.size();
    int primary = classifier.getPrimaryExpression();
  for(int i = 0; i < n; i++){
        ofSetColor(i == primary ? ofColor::red : ofColor::black);
        ofRect(0, 0, w * classifier.getProbability(i) + .5, h);
        ofSetColor(255);
        ofDrawBitmapString(classifier.getDescription(i), 5, 9);
        ofTranslate(0, h + 5);
  }
    ofPopMatrix();
    ofPopStyle();
}

void ofApp::keyPressed(int key) {
}
