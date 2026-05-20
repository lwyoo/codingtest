#include <iostream>

class SinglyLinkedList {
private:
	struct Node {
		int mData;
		Node* mNext;
		Node(int data): mData(data), mNext(nullptr) {}
	};
	Node* mHead;
	int mSize;
public:
	// 1. 생성자
	// 2. 소멸자
	// 3. 데이터 입력
	// 4. 데이터 제거
	// 5. 탐색
	// 6. 초기화

	// 1. 생성자
	SinglyLinkedList(): mHead(nullptr), mSize(0) {
		std::cout << "SignlyLinkedList()" << std::endl;
	}

	// 2. 소멸자
	~SinglyLinkedList() {
		std::cout << "~SinglyLinkedList()" << std::endl;
		clear();
	}

	// 3. 데이터 입력
	void push_back(int data) {
		std::cout << "push_back()" << std::endl;
		Node* node = new Node(data);
		if (mHead == nullptr) {
			mHead = node;
		} else {
			Node* currentNode = mHead;
			while(currentNode->mNext != nullptr) {
				currentNode = currentNode->mNext;
			}
			currentNode->mNext = node;
		}
		++mSize;
	}

	void push_front(int data) {
		std::cout << "push_front()" << std::endl;
		Node* node = new Node(data);
		if (mHead == nullptr) {
			mHead = node;
		} else {
			node->mNext = mHead;
			mHead = node;
		}
		++mSize;
	}

	// 4. 데이터 제거(가장 앞 제거, 가장 뒤 제거, 같은 데이터 제거)
	bool pop_front() {
		bool res = false;
		if (mHead == nullptr) {
		} else {
			Node* delNode = mHead;
			mHead = mHead->mNext;
			delete delNode;
			--mSize;
			res = true;
		}
		return res;
	}

	bool pop_back() {
		bool res = false;
		if (mHead == nullptr) {
		} else {
			if (mHead->mNext == nullptr) {
				delete mHead;
				mHead = nullptr;
				--mSize;
				return true;
			}
			Node* currentNode = mHead;
			Node* prevNode = nullptr;
			while(currentNode->mNext != nullptr) {
				prevNode = currentNode;
				currentNode = currentNode->mNext;
			}

			prevNode->mNext = nullptr;
			delete currentNode;
			--mSize;
			res = true;
		}
		return res;
	}
	

	// 가장 앞에 있는 같은 값제거 (수정 필요)
	bool remove(int value) {
		std::cout << "push_front()" << std::endl;

		Node* currentNode = mHead;
		Node* prevNode = nullptr;
		while(currentNode != nullptr && currentNode->mData != value) {
			prevNode = currentNode;
			currentNode = currentNode->mNext;
		}

		if (currentNode == nullptr) {
			std::cout << "not found" << std::endl;
			return false;
		}
		
		// header
		if (prevNode == nullptr) {
			mHead = currentNode->mNext;
		} else {
			prevNode->mNext = currentNode->mNext;
		}
		delete currentNode;
		--mSize;
		return true;
	}
	

	// 6. 초기화 (수정 필요)
	void clear() {
		std::cout << "clear()" << std::endl;
		while(mHead != nullptr) {
			Node* temp = mHead;
			mHead = mHead->mNext;
			delete temp;
		}
		mSize = 0;
	}

	void show() {
		std::cout << "show()" << std::endl;
		Node* currentNode = mHead;
		int index = 0;
		while(currentNode != nullptr) {
			std::cout << "index[ " << index << " ] data: " << currentNode->mData << std::endl;
			currentNode = currentNode->mNext;
			++index;
		}
	}

};

int main() {
	std::cout << "main()" << std::endl;
	SinglyLinkedList sll;

	std::cout << "push_back 테스트 1 -> 2" << std::endl;
	sll.push_back(1);
	sll.push_back(2);
	sll.show();

	
	std::cout << "push_front 테스트 0 -> 1 -> 2" << std::endl;
	sll.push_front(0);
	sll.show();


	std::cout << "push_back 테스트 0 -> 1 -> 2 -> 2" << std::endl;
	sll.push_back(2);
	sll.show();


	std::cout << "pop_front 테스트 1 -> 2 -> 2" << std::endl;
	sll.pop_front();
	sll.show();

	
	std::cout << "pop_back 테스트 1 -> 2" << std::endl;
	sll.pop_back();
	sll.show();


	std::cout << "clean() 테스트 " << std::endl;
	sll.clear();
	sll.show();

	return 0;
}
