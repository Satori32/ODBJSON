#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <memory>

//hogeeeeeeeeeeeeeeee

class ObjectDataBase {
public:
	class Item;

	typedef std::shared_ptr<Item> SharedItem;
	typedef std::vector<SharedItem> SharedItems;
	SharedItems Find(const std::string& Tag) {
		SharedItems R;
		for (auto& oo : Data) {
			for (auto& o : *oo) {
				if (std::get<0>(o) == Tag) {
					R.push_back(oo);
					break;
				}
			}
		}
		return R;
	}

	bool Add(SharedItem In) {
		Data.push_back(In);
		return true;
	}
	bool Clear() {
		Data.clear();

		return true;
	}




protected:

	SharedItems Data;

public:
	class Item {
	public:

		Item() {};
		Item(const std::initializer_list<std::tuple<std::string, std::string>>& In):Data(In.begin(),In.end()) {}

		const std::string& Speak(const std::string& Tag) {
			auto& A = Find(Tag);
			return std::get<1>(A);
		}

		const std::tuple<std::string,std::string>& Find(const std::string& Tag) const{
			auto it = std::find_if(Data.begin(), Data.end(), [&](auto& In) { return std::get<0>(In) == Tag; });

			if (it == Data.end()) {
				return { "false","false" };
			}
			return *it;
		}

		bool Add(const std::string& Tag, const std::string& Data_) {
			auto it = std::find_if(Data.begin(), Data.end(), [&](auto& In) { return std::get<0>(In) == Tag; });
			if (it == Data.end()) {
				Data.push_back({ Tag,Data_ });
			}
			else {
				std::get<1>(*it) += Data_;
			}

			return true;
		}
		bool Change(const std::string& Tag, const std::string& Data_) {
			auto it = std::find_if(Data.begin(), Data.end(), [&](auto& In) { return std::get<0>(In) == Tag; });
			if (it != Data.end()){
				std::get<1>(*it) = Data_;
			}

			return false;
		}

		bool Erase(const std::string& Tag) {
			auto it = std::find_if(Data.begin(), Data.end(), [&](auto& In) { return std::get<0>(In) == Tag; });
			if (it != Data.end()){
				Data.erase(it);
				return true;
			}

			return false;
		}

		std::size_t Size() {
			return Data.size();
		}

		std::tuple<std::string, std::string> operator [](const std::size_t& Idx) {
			return Data[Idx];
		}
		std::tuple<std::string, std::string> operator [](const std::string& Idx) {
			return Find(Idx);
		}
		std::vector<std::tuple< std::string, std::string>>::iterator begin() {
			return Data.begin();
		}
		std::vector<std::tuple< std::string, std::string>>::iterator end() {
			return Data.end();
		}
		std::vector<std::tuple< std::string, std::string>>::const_iterator cbegin() const{
			return Data.cbegin();
		}
		std::vector<std::tuple< std::string, std::string>>::const_iterator cend() const{
			return Data.cend();
		}
	protected:
		std::vector<std::tuple<std::string, std::string>> Data;
	};
};

int main() {
	ObjectDataBase::SharedItem A = std::make_shared<ObjectDataBase::Item>();
	ObjectDataBase::SharedItem B = std::make_shared<ObjectDataBase::Item>();
	//if (A == nullptr) { std::cout << "why??" << std::endl; }

	A->Add("A", "hoge");
	A->Add("A", "hoge");
	A->Add("B", "hoge");

	B->Add("X", "moge");
	B->Add("B", "moge");

	std::cout << A->Speak("A") << std::endl;

	ObjectDataBase ODB;

	ODB.Add(A);
	ODB.Add(B);

	auto Z = ODB.Find("A");

	return 0;
}


//開発日記：ItemはうまくかけたがDBそのものがタコになってしまった。がっくし。SQL入れたいけど力がない。