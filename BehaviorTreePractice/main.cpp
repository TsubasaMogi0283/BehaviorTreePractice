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
	//�����Ă�����̂�S������
	~SequenceNode() {
		for (auto behavior : behaviors) {
			delete behavior;
		}
	}

	//�ǉ�
	void AddBehavior(BehaviorNode* behavior) {
		behaviors.push_back(behavior);
	}

	void Execute() override {
		for (auto behavior : behaviors) {
			behavior->Execute();
		}
	}

};


// ����̏����Ɋ�Â��ē����I�����邽�߂̃Z���N�^�[
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





// �V���v���ȓ���̗�
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
	// �r�w�C�r�A�c���[�̍\�z
	Selector* root = new Selector();

	SequenceNode* exploreSequence = new SequenceNode();
	exploreSequence->AddBehavior(new MoveForward());
	exploreSequence->AddBehavior(new TurnLeft());
	exploreSequence->AddBehavior(new MoveForward());
	exploreSequence->AddBehavior(new TurnRight());

	root->AddBehavior(exploreSequence);

	// �r�w�C�r�A�c���[�̎��s
	root->Execute();

	// �������̉��
	delete root;



	return 0;
}