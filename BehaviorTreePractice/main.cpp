#include <vector>
#include <iostream>


class BehaviorNode {
public:
	virtual ~BehaviorNode() {};

	virtual void Execute() = 0;
};


class SequenceNode :public BehaviorNode {
private:
	std::vector<BehaviorNode*>behaviors;

public:
	//入っているものを全部消す
	~SequenceNode() {
		for (auto behavior : behaviors) {
			delete behavior;
		}
	}

	//追加
	void AddBehavior(BehaviorNode* behavior) {
		behaviors.push_back(behavior);
	}

	void Execute() override {
		for (auto behavior : behaviors) {
			behavior->Execute();
		}
	}

};


// 特定の条件に基づいて動作を選択するためのセレクター
class Selector : public BehaviorNode {
private:
	std::vector<BehaviorNode*> behaviors;

public:
	~Selector() {
		for (auto behavior : behaviors) {
			delete behavior;
		}
	}

	void AddBehavior(BehaviorNode* behavior) {
		behaviors.push_back(behavior);
	}

	void Execute() override {
		for (auto behavior : behaviors) {
			behavior->Execute();
		}
	}
};





// シンプルな動作の例
class MoveForward : public BehaviorNode {
public:
	void Execute() override {
		std::cout << "Moving forward" << std::endl;
	}
};

class TurnLeft : public BehaviorNode {
public:
	void Execute() override {
		std::cout << "Turning left" << std::endl;
	}
};

class TurnRight : public BehaviorNode {
public:
	void Execute() override {
		std::cout << "Turning right" << std::endl;
	}
};





int main() {
	// ビヘイビアツリーの構築
	Selector* root = new Selector();

	SequenceNode* exploreSequence = new SequenceNode();
	exploreSequence->AddBehavior(new MoveForward());
	exploreSequence->AddBehavior(new TurnLeft());
	exploreSequence->AddBehavior(new MoveForward());
	exploreSequence->AddBehavior(new TurnRight());

	root->AddBehavior(exploreSequence);

	// ビヘイビアツリーの実行
	root->Execute();

	// メモリの解放
	delete root;



	return 0;
}