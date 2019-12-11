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
	void push_back(const string& condition, const Result& r)
	{
		_decision[condition] = r;
	}
	Result result(const string& condition)
	{
		auto iter = _decision.find(condition);
		if (iter == _decision.end()) {
			return Result::Unknown;
		}
		return iter->second;
	}
	virtual ~Node()
	{
    }
private:
	map<string, Result> _decision;
};

class PE : public Node
{
};

class Rank : public Node
{
};

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
		// PE
		shared_ptr<Node> node(new PE);
		node->push_back("P", Result::C);
		node->push_back("F", Result::N);
		_nodes.push_back(node);
		// Rank
		node.reset(new Rank);
		node->push_back("E", Result::C);
		node->push_back("NE", Result::N);
		_nodes.push_back(node);
		// Social
		node.reset(new Social);
		node->push_back("A", Result::Y);
		node->push_back("B", Result::Y);
		node->push_back("C", Result::N);
		_nodes.push_back(node);

	}
private:
	vector<shared_ptr<Node>> _nodes;
};

string getcin(const string& prompt)
{
	string r;
	// cout << endl;
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
        catch (string &e) {
            cout << e << endl;
            break;
        }
	}
}
