#pragma once

#include "ofMain.h"

class Object {

	float param1;
	ofParameter<float> param2;

	public:
		class Builder;

		Object(float _param1, ofParameter<float>& _param2):
			param1{_param1} 
		{
			param2.makeReferenceTo(_param2);
			param2.addListener(this, &Object::changeParam2);
			
			generate();
		}

		~Object(){
			param2.removeListener(this, &Object::changeParam2);
		}

		void generate();
		void regenerate();
		
		void draw();

	private:
		void changeParam2(float& p);
};

class Object::Builder {

	public:
		Builder& setParam1(float p) { param1 = p; return *this; };
		Builder& setParam2(ofParameter<float>& p) { param2.makeReferenceTo(p); return *this; };

		shared_ptr<Object> build(){
			shared_ptr<Object> ptr(new Object{param1, param2});
			return ptr;
		}

	private:
		float param1 = 0.0;
		ofParameter<float> param2;
};
