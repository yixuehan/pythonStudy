#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include <assert.h>
using namespace std;

// 结果先定为三种，获得，不能获得，和未决
enum class Result { Unknown, Y, N, C };

// 节点
class Node
{
public:
    // 构造对应的结果
	void push_back(const string& condition, const Result& r)
	{
		_decision[condition] = r;
	}
    // 获取某个条件对应的结果
	Result result(const string& condition)
	{
		auto iter = _decision.find(condition);
		if (iter == _decision.end()) {
			return Result::Unknown;
		}
		return iter->second;
	}
    // 虚析构，子类正常释放
	virtual ~Node()
	{
    }
private:
	map<string, Result> _decision;
};

// 体测
class PE : public Node
{
};

// 排名
class Rank : public Node
{
};

// 综合学科
class Social : public Node
{
};

class DecisionTree
{
public:
	DecisionTree()
	{
		init();
	}
    // 输入本次的判断条件
    // 如[P E A]
    // 输出结果
	Result result(vector<string> conditions)
	{
		// 每个条件一个节点，那么节点和条件数应该相同
		if (conditions.size() < _nodes.size()) {
			cout << "条件数不足,例如: [P E A]\n";
			return Result::Unknown;
		}
		if (conditions.size() > _nodes.size()) {
			cout << "warning! 条件数过多，丢弃多余的条件\n";
		}
        // 逐个结点判断，没有得出最终结果则继续
		for (size_t i = 0; i < _nodes.size(); ++i) {
			auto r = _nodes[i]->result(conditions[i]);
			switch (r) {
			case Result::Y:
			case Result::N:
				return r;
			case Result::Unknown:
				cout << "错误的条件[" << conditions[i] << "]\n";
				return r;
			default:
				break;
			}
		}
		assert(false && "逻辑错误");
		return Result::Unknown;
	}
	/*
	 PE --F--> N
	 |
	 (P)
	 |
	 Ranking--NE-->N
	 |
	 (E)
	 |
	 social--C-->N
	 |
	 (A|B)
	 |
	 Y
	*/
	void init()
	{
		// PE 第一个结点
		shared_ptr<Node> node(new PE);
		node->push_back("P", Result::C);
		node->push_back("F", Result::N);
		_nodes.push_back(node);
		// Rank  第二个结点
		node.reset(new Rank);
		node->push_back("E", Result::C);
		node->push_back("NE", Result::N);
		_nodes.push_back(node);
		// Social  第三个结点
		node.reset(new Social);
		node->push_back("A", Result::Y);
		node->push_back("B", Result::Y);
		node->push_back("C", Result::N);
		_nodes.push_back(node);

	}
private:
    // 这棵决策树的结点
	vector<shared_ptr<Node>> _nodes;
};

// 获取输入，输入("0")则抛出异常
string getcin(const string& prompt)
{
	string r;
	cout << "输入0退出\n";
	cout << prompt;
	cin >> r;
	if (r == "0") throw string("程序结束");
	return r;
}

void printResult(Result r)
{
	cout << "****************\n";
	switch (r) {
	case Result::Y:
		
		cout << "*可以获得奖学金*\n";
		break;
	case Result::N:
		cout << "*不能获得奖学金*\n";
		break;
	default:
		cout << "*尚未取得结果*\n";
		break;
	}
	cout << "****************\n";
}

int main()
{
	DecisionTree dt;
	string condition;
	while (true) {
        try {
		    vector<string> conditions;
		    // 体测
		    condition = getcin("请输入体测成绩(P|F):");
		    conditions.push_back(condition);
		    // 排名
		    condition = getcin("请输入排名成绩(E|NE):");
		    conditions.push_back(condition);
		    // 综合
		    condition = getcin("请输入综合成绩(A|B|C):");
		    conditions.push_back(condition);
		    printResult(dt.result(conditions));
        }
        // 捕获异常并退出循环
        catch (string &e) {
            cout << e << endl;
            break;
        }
	}
}
