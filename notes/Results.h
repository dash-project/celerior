#include "Macros.h"
#include <chrono>
#include <sstream>

class Results{
public:
	Results(std::vector<std::string> name ){
		_names = name;
	}

	void add_time(std::vector<int> values, std::chrono::microseconds time){
		_times[values] = time;
	}

	std::map<std::vector<int>,std::chrono::microseconds> times() const{
		return _times;
	}
	std::vector<std::string> names () const{
		return _names;
	}

	int width() const{
		return WIDTH;
	}

	friend std::ostream& operator<< (std::ostream &out, const Results &r);
	
private:
	std::map<std::vector<int>,std::chrono::microseconds>    _times;
	std::vector<std::string>                                _names;
	int                                                     WIDTH = 30;


};
std::ostream& operator<< (std::ostream &out, const Results &r){

		std::stringstream ss;
		std::map<std::vector<int>, std::chrono::microseconds> map;
		std::vector<int> vector;
		//Table header
		ss << "\n";
		for(int i = 0; i <= r.names().size(); i++){
				ss.width(r.width() + 1);
				ss.fill('-');
				ss << "-";
		}
		ss << "\n";
		for(int i = 0; i <= r.names().size(); i++){
			if(i == r.names().size()){
				std::string time = "time";
				ss << "|";
				for(int j = 0; j < (r.width()-time.size())/2; j++){
					ss << " ";
				}
				ss << "time";
				for(int j = 0; j < (r.width()-time.size())/2; j++){
					ss << " ";
				}
			}
			else{
				ss << "|";
				for(int j = 0; j < (r.width()-r.names()[i].size())/2; j++){
					ss << " ";
				}

				ss << r.names()[i];
				if(r.names()[i].size() % 2 == 1){
					for(int j = 0; j <= (r.width()-r.names()[i].size())/2; j++){
						ss << " ";
					}
				}
				else{
					for(int j = 0; j < (r.width()-r.names()[i].size())/2; j++){
						ss << " ";
					}
				}

			}
		}
		ss << "|\n";
		for(int i = 0; i <= r.names().size(); i++){
			ss.width(r.width() + 1);
			ss.fill('-');
			ss << "-";
			ss.fill(' ');
		}
		ss << "\n";
		//Table values
		map = r.times();
		for(auto iter = map.begin(); iter != map.end(); ++iter){
			vector = iter -> first;
			ss << "|";
			for(auto iter2 = vector.begin(); iter2 != vector.end(); ++iter2){
				ss.width(r.width());
				ss << *iter2;
				ss << "|";
			}
			ss.width(r.width());
			ss << iter -> second.count();
			
			ss << "|\n";

		}




		out << ss.str();
		return out;


	}

