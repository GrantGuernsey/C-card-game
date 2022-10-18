#ifndef SIDE
#define SIDE

class Side {
private:
	int* data;
	int len, max;
	
	class Overflow{};
	class Underflow{};

public:
	//Constructor
	Side() {
		data = new int[5];
		max = 5;
		len = 0;
	}

	//Error handling
	bool isFull(){
		return len >= max;
	}
	bool isEmpty(){
		return len <= 0;
	}

	//Stack methods
	void push(int value) {
		if (isFull()) throw Overflow();
		
		data[len] = value;
		len += 1;
	}
	int pop() {
		if (isEmpty()) throw Underflow();

		int retValue = data[len-1];
		len -= 1;
		return retValue;
	}
	int length(){
		return len;
	}
};

#endif