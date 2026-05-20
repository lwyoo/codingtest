#include <iostream>
#include <memory>
template <typename T>
class DoubleLinkedList {
private:
    struct Node {
        T sData;
        Node* sPrevNode;
        Node* sNextNode;
        Node(const T& data) : sData(data), sPrevNode(nullptr), sNextNode(nullptr) {}
    };
    Node* mHeadNode;
    Node* mTailNode;
    int mSize;

public:
    // 1. 생성자
    DoubleLinkedList() : mHeadNode(nullptr), mTailNode(nullptr), mSize(0) {
    }
    DoubleLinkedList(const DoubleLinkedList&) = delete;
    DoubleLinkedList& operator=(const DoubleLinkedList&) = delete;
    // 2. 소멸자
    ~DoubleLinkedList() {
        clear();
    }
    // 3. 데이터 입력
    void push_back(const T& data) {
        Node* node = new Node(data);
        if (mHeadNode == nullptr) {
            mHeadNode = node;
            mTailNode = node;
        } else {
            // mTailNode 을 이용해 만들면 될것 같은데
            node->sPrevNode = mTailNode;
            mTailNode->sNextNode = node;
            mTailNode = node;
        }
        ++mSize;
    }
    void push_front(const T& data) {
        Node* node = new Node(data);
        if (mHeadNode == nullptr) {
            mHeadNode = node;
            node->sNextNode = mTailNode;
            mTailNode = node;
        } else {
            node->sNextNode = mHeadNode;
            mHeadNode->sPrevNode = node;
            mHeadNode = node;
        }
        ++mSize;
    }
    // 4. 데이터 삭제
    void pop_back() {
        if (mTailNode == nullptr) {
            // node 가 하나도 없다
            return;
        } else {
            if (mTailNode->sPrevNode != nullptr) {
                std::cout << "delete data : " << mTailNode->sData << std::endl;
                Node* node = mTailNode->sPrevNode;
                node->sNextNode = mTailNode->sNextNode;
                delete mTailNode;
                mTailNode = node;
            } else {
                std::cout << "delete data2 : " << mTailNode->sData << std::endl;
                delete mTailNode;
                mTailNode = nullptr;
                mHeadNode = nullptr;
            }
            --mSize;
        }
    }
    void pop_front() {
        if (mHeadNode == nullptr) {
            return;
        } else {
            if (mHeadNode->sNextNode == nullptr) {
                delete mHeadNode;
                mHeadNode = nullptr;
                mTailNode = nullptr;
            } else {
                Node* node = mHeadNode->sNextNode;
                node->sPrevNode = nullptr;
                delete mHeadNode;
                mHeadNode = node;
            }
            --mSize;
        }
    }
    // 5. 모든 데이터 제거
    void clear() {
        if (mHeadNode == nullptr) {
            return;
        } else {
            Node* node = mHeadNode;
            while (node != nullptr) {
                node = node->sNextNode;
                delete mHeadNode;
                mHeadNode = node;
            }
            mTailNode = nullptr;
        }
        mSize = 0;
    }
    // 6. debug
    void show() const {
        if (mHeadNode == nullptr) {
            std::cout << "double linked list is empty" << std::endl;
        } else {
            Node* cur = mHeadNode;
            int index = 0;
            while (cur != nullptr) {
                std::cout << "index [ " << index << " ] data: " << cur->sData << std::endl;
                cur = cur->sNextNode;
                ++index;
            }
        }
    }

    /**
     * 문제 1. 특정 위치에 삽입 (insertAt) - ⭐⭐ 보통
     * index 위치에 새 노드를 삽입하세요. 이중 연결 리스트의 진가가 드러나는 함수입니다.
     * bool insertAt(int index, const T& data);
     */
    // bool insertAt(int index, const T& data) {
    //     std::cout << "index: " << index << std::endl;
    //     Node* newNode = new Node(data);
    //     if (mHeadNode == nullptr) {
    //         push_front(data);
    //     } else {
    //         Node* cur = mHeadNode;
    //         int _index = 0;
    //         while (cur != nullptr) {
    //             if (index == 0) {
    //                 push_front(data);
    //                 break;
    //             } else {
    //                 if (_index == index) {
    //                     std::cout << "11" << std::endl;
    //                     Node* prev = cur->sPrevNode;
    //                     if (prev != nullptr) {
    //                         prev->sNextNode = newNode;
    //                     }
    //                     newNode->sPrevNode = prev;
    //                     Node* next = cur->sNextNode;
    //                     if (next != nullptr) {
    //                         next->sPrevNode = newNode;
    //                     }
    //                     newNode->sNextNode = next;
    //                     if (newNode->sNextNode == nullptr) {
    //                         mTailNode = newNode;
    //                     }
    //                     break;
    //                 } else {
    //                     std::cout << "22" << std::endl;
    //                     cur = cur->sNextNode;
    //                 }
    //                 ++_index;
    //             }
    //         }
    //     }
    // }
    bool insertAt(int index, const T& data) {
        // 1. 범위 검증
        if (index < 0 || index > mSize) {
            return false;
        }

        // 2. 경계 케이스는 기존 함수 재활용 (DRY)
        if (index == 0) {
            push_front(data);
            return true;
        }
        if (index == mSize) {
            push_back(data);
            return true;
        }

        // 3. index번째 노드까지 이동 (중간 삽입)
        Node* cur = mHeadNode;
        for (int i = 0; i < index; ++i) {
            cur = cur->sNextNode;
        }
        // 이제 cur은 "밀려날" 위치의 노드

        // 4. cur 앞에 newNode 삽입
        Node* newNode = new Node(data);
        Node* prev = cur->sPrevNode;  // 중간 삽입이므로 prev는 반드시 존재

        newNode->sPrevNode = prev;
        newNode->sNextNode = cur;
        prev->sNextNode = newNode;
        cur->sPrevNode = newNode;

        ++mSize;
        return true;
    }

    /**
     * 문제 2. 역방향 출력 (showReverse) - ⭐ 쉬움
     * 리스트를 뒤에서부터 출력하는 함수를 작성하세요. mTail을 활용하면 매우 간단합니다.
     * void showReverse() const;
     */
    void showReverse() const {
        if (mTailNode != nullptr) {
            Node* cur = mTailNode;
            int index = 0;
            while (cur != nullptr) {
                std::cout << "index[ " << index << " ] data: " << cur->sData << std::endl;
                cur = cur->sPrevNode;
                ++index;
            }
        } else {
            std::cout << "double linked list is empty" << std::endl;
        }
    }

    /**
     * 문제 3. 리스트 뒤집기 (reverse) - ⭐⭐ 보통
     * 리스트의 노드 순서를 in-place로 뒤집습니다. 단일 연결 리스트와 달리 이중 연결 리스트는 prev/next 포인터를 서로 swap하는 깔끔한 방법이 있어요.
     * void reverse();
     */
    /**
     * 문제 4. 값으로 노드 삭제 (removeFirst) - ⭐⭐ 보통
     * 리스트에서 value와 같은 첫 번째 노드를 찾아 삭제하세요. 양방향이라 prev/next 처리가 단일보다 깔끔합니다.
     * bool removeFirst(const T& value);
     */
};

int main() {
    // DoubleLinkedList<int>* dll = new DoubleLinkedList<int>();
    auto dll = std::make_unique<DoubleLinkedList<int>>();
    std::cout << "push_back [테스트] 1 -> 2 -> 3 -> 4" << std::endl;
    dll->push_back(1.1);
    dll->push_back(2.1);
    dll->push_back(3.1);
    dll->push_back(4.1);
    dll->show();

    std::cout << "push_front [테스트] 11 -> 66 -> 99 -> 1 -> 2 -> 3 -> 4" << std::endl;
    dll->push_front(99.1);
    dll->push_front(66.1);
    dll->push_front(11.1);
    dll->show();

    std::cout << "pop_back [테스트] 11 -> 66 -> 99 -> 1 -> 2 -> 3" << std::endl;
    dll->pop_back();
    dll->show();

    std::cout << "pop_front [테스트] 66 -> 99 -> 1 -> 2 -> 3" << std::endl;
    dll->pop_front();
    dll->show();

    std::cout << "clear [테스트] " << std::endl;
    dll->clear();
    dll->show();

    std::cout << "indexAt [테스트] 1 -> 2 -> 99 -> 3" << std::endl;
    dll->push_back(1);
    dll->push_back(2);
    dll->push_back(3);
    dll->insertAt(2, 99);
    dll->show();

    std::cout << "indexAt [테스트] 3 ->  99 -> 2 -> 1" << std::endl;
    dll->showReverse();

    return 0;
}
