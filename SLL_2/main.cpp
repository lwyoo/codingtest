#include <iostream>
#include <string>
template <typename T>
class SinglyLinkedList {
private:
    struct Node {
        T mData;
        Node* mNext;
        Node(const T& data) : mData(data), mNext(nullptr) {}
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
    SinglyLinkedList() : mHead(nullptr), mSize(0) {
        std::cout << "SignlyLinkedList()" << std::endl;
    }

    // 2. 소멸자
    ~SinglyLinkedList() {
        std::cout << "~SinglyLinkedList()" << std::endl;
        clear();
    }

    // 3. 데이터 입력
    void push_back(const T& data) {
        std::cout << "push_back()" << std::endl;
        Node* node = new Node(data);
        if (mHead == nullptr) {
            mHead = node;
        } else {
            Node* currentNode = mHead;
            while (currentNode->mNext != nullptr) {
                currentNode = currentNode->mNext;
            }
            currentNode->mNext = node;
        }
        ++mSize;
    }

    void push_front(const T& data) {
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
            while (currentNode->mNext != nullptr) {
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
    bool remove(const T& value) {
        std::cout << "push_front()" << std::endl;

        Node* currentNode = mHead;
        Node* prevNode = nullptr;
        while (currentNode != nullptr && currentNode->mData != value) {
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
        while (mHead != nullptr) {
            Node* temp = mHead;
            mHead = mHead->mNext;
            delete temp;
        }
        mSize = 0;
    }

    void show() {
        Node* currentNode = mHead;
        int index = 0;
        while (currentNode != nullptr) {
            std::cout << "index[ " << index << " ] data: " << currentNode->mData << std::endl;
            currentNode = currentNode->mNext;
            ++index;
        }
    }
    void reverse() {
        Node* prev = nullptr;
        Node* currentNode = mHead;
        while (currentNode) {
            Node* next = currentNode->mNext;
            currentNode->mNext = prev;
            prev = currentNode;
            currentNode = next;
        }
        mHead = prev;
    }

    /*
    문제 2. 중간 노드 찾기 (find middle)
    리스트의 중간 노드의 데이터를 반환하세요.
    노드 개수가 짝수면 두 번째 중간 노드를 반환합니다. (1,2,3,4) -> 3 반환
    빈 리스트면 false를 반환하고, 그렇지 않으면 true와 함께 결과를 out 파라미터에 담아주세요.
    bool findMiddle(int& out) const;
    */
    // bool findMiddle(T& out) const {
    //     int index = (mSize / 2);
    //     std::cout << "중간 인덱스: " << index << std::endl;
    //     Node* node = mHead;
    //     for (int i = 0; i < index; i++) {
    //         node = node->mNext;
    //     }
    //     std::cout << "중간 값: " << node->mData << std::endl;
    //     out = node->mData;
    //     return true;
    // }
    bool findMiddle(T& out) const {
        // 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7

        /**
         * 1cycle 완료
         * slow: 2
         * fast: 3
         * 2cycle 완료
         * slow: 3
         * fast: 5
         * 2cycle 완료
         * slow: 4
         * fast: 7
         */
        if (mHead == nullptr) return false;
        Node* slow = mHead;
        Node* fast = mHead;
        while (fast != nullptr && fast->mNext != nullptr) {
            slow = slow->mNext;
            fast = fast->mNext->mNext;
        }
        out = slow->mData;
        return true;
    }
};

int main() {
    std::cout << "main()" << std::endl;
    SinglyLinkedList<std::string> sll;

    std::cout << "push_back 테스트 1 -> 2" << std::endl;
    sll.push_back("1");
    sll.push_back("2");
    sll.show();

    std::cout << "push_front 테스트 0 -> 1 -> 2" << std::endl;
    sll.push_front("0");
    sll.show();

    std::cout << "push_back 테스트 0 -> 1 -> 2 -> 2" << std::endl;
    sll.push_back("2");
    sll.show();

    std::cout << "pop_front 테스트 1 -> 2 -> 2" << std::endl;
    sll.pop_front();
    sll.show();

    std::cout << "pop_back 테스트 1 -> 2" << std::endl;
    sll.pop_back();
    sll.show();

    std::cout << "reverse 테스트 2 -> 1" << std::endl;
    sll.reverse();
    sll.show();

    std::cout << "clean() 테스트 " << std::endl;
    sll.clear();
    sll.show();

    std::cout << "push_back 테스트 1 -> 2" << std::endl;
    sll.push_back("1");
    sll.push_back("2");
    sll.push_back("3");
    sll.push_back("4");
    sll.push_back("5");
    sll.push_back("6");
    sll.show();
    std::string out;

    sll.findMiddle(out);

    std::cout << "중간값: " << out << std::endl;

    return 0;
}
