#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <memory>
#include <map>


class JsonDocument {//ポンコツすぎて辛い。
public:

	JsonDocument() {}//book cover.
	class Item {
	public:
		typedef std::shared_ptr<Item> SheardJsonItem;

		Item() { }
		Item(const std::initializer_list<std::string>& In) : D(In.begin(), In.end()) {}

		std::size_t Size() {
			return D.size();
		}

		bool Push(const std::string& In) {
			D.push_back(In);
			return true;
		}
		bool Push(const std::string& Tag, const std::string& Value) {
			D.push_back(Tag + " : " + Value);
			return true;
		}
		const std::vector<std::string>& Get() const{
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
		SheardJsonItem operator [](std::size_t P) const{
			return V[P];
		}
		SheardJsonItem operator [](std::size_t P) {
			return V[P];
		}
		SheardJsonItem operator [](const std::string& In) const{
			auto it = M.find(In);
			return it->second;
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
		std::map<std::string, SheardJsonItem> M;
	};

	bool Set(Item::SheardJsonItem In) {
		J = In;
		return true;
	}
	Item::SheardJsonItem New(const std::initializer_list<std::string>& In) {
		return std::make_shared<Item>(In);
	}

	Item::SheardJsonItem Get() const{
		return J;
	}

protected:
	Item::SheardJsonItem J = std::make_shared<Item>();
};

int main_Json() {
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
		Item(const std::initializer_list<std::tuple<std::string, JsonDocument>>& In) :Data(In.begin(), In.end()) {}

		const JsonDocument& Speak(const std::string& Tag) {
			auto& A = Find(Tag);
			return std::get<1>(A);
		}

		const std::tuple<std::string, JsonDocument>& Find(const std::string& Tag) const {
			auto it = std::find_if(Data.begin(), Data.end(), [&](auto& In) { return std::get<0>(In) == Tag; });

			if (it == Data.end()) {
				return *Data.end();
			}
			return *it;
		}

		bool Add(const std::string& Tag, const std::string& Data_) {
			auto it = std::find_if(Data.begin(), Data.end(), [&](auto& In) { return std::get<0>(In) == Tag; });
			if (it == Data.end()) {
				JsonDocument J;
				auto X = J.New({ Data_ });
				J.Set(X);
				Data.push_back({ Tag,J });
			}
			else {
				std::get<1>(*it).Get()->Push( Data_);
			}

			return true;
		}
		bool Change(const std::string& Tag, const JsonDocument& Data_) {
			auto it = std::find_if(Data.begin(), Data.end(), [&](auto& In) { return std::get<0>(In) == Tag; });
			if (it != Data.end()) {
				std::get<1>(*it) = Data_;
			}

			return false;
		}

		bool Erase(const std::string& Tag) {
			auto it = std::find_if(Data.begin(), Data.end(), [&](auto& In) { return std::get<0>(In) == Tag; });
			if (it != Data.end()) {
				Data.erase(it);
				return true;
			}

			return false;
		}

		std::size_t Size() {
			return Data.size();
		}

		std::tuple<std::string,JsonDocument> operator [](const std::size_t& Idx) {
			return Data[Idx];
		}
		std::tuple<std::string, JsonDocument> operator [](const std::string& Idx) {
			return Find(Idx);
		}
		std::vector<std::tuple< std::string, JsonDocument>>::iterator begin() {
			return Data.begin();
		}
		std::vector<std::tuple< std::string, JsonDocument>>::iterator end() {
			return Data.end();
		}
		std::vector<std::tuple< std::string, JsonDocument>>::const_iterator cbegin() const {
			return Data.cbegin();
		}
		std::vector<std::tuple< std::string, JsonDocument>>::const_iterator cend() const {
			return Data.cend();
		}
	protected:
		std::vector<std::tuple<std::string, JsonDocument>> Data;
	};
};

int main_ODB() {
	ObjectDataBase::SharedItem A = std::make_shared<ObjectDataBase::Item>();
	ObjectDataBase::SharedItem B = std::make_shared<ObjectDataBase::Item>();
	//if (A == nullptr) { std::cout << "why??" << std::endl; }

	JsonDocument JA;
	JsonDocument JB;

	auto XA = JA.New({});


	A->Add("A", "Hoge");
	A->Add("A", "hoge");
	A->Add("B", "hoge");

	B->Add("X", "moge");
	B->Add("B", "moge");

	std::cout << A->Speak("A").Get()->Get().back().c_str() << std::endl;

	ObjectDataBase ODB;

	ODB.Add(A);
	ODB.Add(B);

	auto Z = ODB.Find("A");

	return 0;
}

int main() {
	ObjectDataBase::SharedItem A = std::make_shared<ObjectDataBase::Item>();
	A->Add("A", "Hoge");
	A->Add("A", "Bake");
	
	ObjectDataBase::SharedItem B = std::make_shared<ObjectDataBase::Item>();
	B->Add("A", "koke");

	ObjectDataBase ODB;

	ODB.Add(A);
	ODB.Add(B);

	return 0;
}