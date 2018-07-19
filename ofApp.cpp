#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("Insta");

	ofBackground(239);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);

	vector<ofPoint> points;
	vector<int> sizes;
	vector<ofColor> colors;
	for (int i = 0; i < 512; i++) {

		ofPoint point = this->make_torus_point(300, ofRandom(10, 65), ofRandom(360) + ofGetFrameNum() * ofRandom(1), ofRandom(360) + ofGetFrameNum() * ofRandom(5));
		points.push_back(point);
		sizes.push_back(1);

		ofColor tmp_color;
		tmp_color.setHsb(ofRandom(255), 200, 255);
		colors.push_back(tmp_color);
	}

	for (int out_index = 0; out_index < points.size(); out_index++) {

		for (int in_index = out_index + 1; in_index < points.size(); in_index++) {

			if (points[out_index].distance(points[in_index]) < 50) {

				sizes[out_index]++;
				sizes[in_index]++;
			}
		}
	}

	// Draw Circle
	for (int i = 0; i < points.size(); i++) {

		ofSetColor(colors[i]);
		ofDrawSphere(points[i], sizes[i]);
	}

	this->cam.end();
}

//--------------------------------------------------------------
ofPoint ofApp::make_torus_point(float radius, float small_radius, float deg, float small_deg) {

	float x_1 = radius * cos(deg * DEG_TO_RAD);
	float y_1 = radius * sin(deg * DEG_TO_RAD);

	float x_2 = small_radius * cos(small_deg * DEG_TO_RAD) * cos(deg * DEG_TO_RAD);
	float y_2 = small_radius * cos(small_deg * DEG_TO_RAD) * sin(deg * DEG_TO_RAD);

	float x = x_1 + x_2;
	float y = y_1 + y_2;
	float z = small_radius * sin(small_deg * DEG_TO_RAD);

	return ofPoint(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}