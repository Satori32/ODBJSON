#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <memory>

class JsonDocument {
public:

	JsonDocument() {}//book cover.
	class Item {
	public:
		typedef std::shared_ptr<Item> SheardJsonItem;

		Item(){ }
		Item(const std::initializer_list<std::string>& In) : D(In.begin(), In.end()) {}

		bool Push(const std::string& In) {
			D.push_back(In);
			return true;
		}
		bool Push(const std::string& Tag, const std::string& Value) {
			D.push_back(Tag + " : " + Value);
			return true;
		}
		const std::vector<std::string>& Get() {
			return D;
		}

		bool Push(SheardJsonItem In) {
			V.push_back(In);
			return true;
		}
		bool Push(const std::string& Tag, SheardJsonItem In) {
			M[Tag] = In;
			return true;
		}

		SheardJsonItem operator [](std::size_t P) {
			return V[P];
		}
		SheardJsonItem operator [](const std::string& In) {
			auto it = M.find(In);
			return it->second;
		}
		std::vector<SheardJsonItem>& GetVector() {
			return V;
		}
		std::map<std::string, SheardJsonItem>& GetMap() {
			return M;
		}

		std::vector<std::string>::iterator begin() {
			return D.begin();
		}
		std::vector<std::string>::iterator end() {
			return D.end();
		}
	protected:
		std::vector<std::string> D;
		std::vector<SheardJsonItem> V;
		std::map<std::string,SheardJsonItem> M;
	};

	bool Set(Item::SheardJsonItem In) {
		J = In;
		return true;
	}
	Item::SheardJsonItem New(const std::initializer_list<std::string>& In) {
		return std::make_shared<Item>(In);
	}

	Item::SheardJsonItem Get() {
		return J;
	}

protected:
	Item::SheardJsonItem J = std::make_shared<Item>();
};

int main() {
	JsonDocument J;

	auto X = J.New({});
	X->Push("hoge");
	J.Set(X);

	X->Push("hage");

	auto Y = J.New({});
	Y->Push("huga");
	X->Push(Y);

	return 0;

}