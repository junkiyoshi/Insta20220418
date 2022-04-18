#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetColor(255);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(250, 3);
	this->base_mesh = ico_sphere.getMesh();
	this->draw_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

}

//--------------------------------------------------------------
void ofApp::update() {

	this->draw_mesh.clear();

	for (auto v : this->base_mesh.getVertices()) {

		for (int i = 0; i < 4; i++) {

			auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.002, ofGetFrameNum() * 0.005)), 0, 1, -90, 90) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
			auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.002, ofGetFrameNum() * 0.005)), 0, 1, -90, 90) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
			auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.002, ofGetFrameNum() * 0.005)), 0, 1, -90, 90) * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));

			v = glm::vec4(v, 0) * rotation_z * rotation_y * rotation_x;
		}

		this->draw_mesh.addVertex(v);
	}

	for (int i = 0; i < this->draw_mesh.getNumVertices(); i++) {

		for (int k = i; k < this->draw_mesh.getNumVertices(); k++) {

			if (glm::distance(this->draw_mesh.getVertex(i), this->draw_mesh.getVertex(k)) < 30) {

				this->draw_mesh.addIndex(i);
				this->draw_mesh.addIndex(k);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 3.5);

	for (auto& vertex : this->draw_mesh.getVertices()) {

		ofDrawSphere(vertex, 2);
	}

	this->draw_mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}