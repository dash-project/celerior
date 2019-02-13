#include "fixture_base.h"
#include <sstream>

class Results{
public:
	Results(std::vector<std::string> name ){
		_names = name;
	}

	void add_time(double time){
		_times.push_back(time);
	}

	std::vector<double> get_times() const{
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
	std::vector<double>           _times;
	std::vector<std::string>      _names;
	int                           WIDTH = 30;


};
std::ostream& operator<< (std::ostream &out, const Results &r){

		std::stringstream ss;
		//Table header
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
		for(int k = 0; k < r.get_times().size(); k++){
			ss << "|";
			for(int i = 0; i <= r.names().size(); i++){
				if(i == r.names().size()){
					ss.width(r.width());
					ss << r.get_times()[k];
				}
			
				else{
					for(int j = 0; j < r.width(); j++){
						ss << " ";
					}
					ss << "|";
				}
			}
			ss << "|\n";

		}




		out << ss.str();
		return out;


	}

