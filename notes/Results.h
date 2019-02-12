#include "fixture_base.h"

class Results{
public:
	Results(std::vector<std::string> name ){
		names = name;
	}

	void add_time(double time){
		times.push_back(time);
	}

	std::vector<double> get_times() const{
		return times;
	}

	void print_table(){

		//Table header
		std::string output = "";
		for(int i = 0; i <= names.size(); i++){
			for(int j = 0; j <= WIDTH; j++){
				output+="-";
			}
		}
		output += "\n";
		for(int i = 0; i <= names.size(); i++){
			if(i == names.size()){
				std::string time = "time";
				output += "|";
				for(int j = 0; j < (WIDTH-time.size())/2; j++){
					output += " ";
				}
				output += "time";
				for(int j = 0; j < (WIDTH-time.size())/2; j++){
					output += " ";
				}
			}
			else{
				output += "|";
				for(int j = 0; j < (WIDTH-names[i].size())/2; j++){
					output += " ";
				}

				output += names[i];
				if(names[i].size() % 2 == 1){
					for(int j = 0; j <= (WIDTH-names[i].size())/2; j++){
						output += " ";
					}
				}
				else{
					for(int j = 0; j < (WIDTH-names[i].size())/2; j++){
						output += " ";
					}
				}

			}
		}
		output += "|\n";
		for(int i = 0; i <= names.size(); i++){
			for(int j = 0; j <= WIDTH; j++){
				output+="-";
			}
		}
		output += "\n";
		//Table values
		for(int k = 0; k < times.size(); k++){
			output += "|";
			for(int i = 0; i <= names.size(); i++){
				if(i == names.size()){
					for(int j = 0; j < WIDTH-std::to_string(times[k]).size(); j++){
						output += " ";
					}
					output += std::to_string(times[k]);
				}
			
				else{
					for(int j = 0; j < WIDTH; j++){
						output += " ";
					}
					output += "|";
				}
			}
			output += "|\n";

		}




		std::cout << output;


	}
	
private:
	std::vector<double> times;
	std::vector<std::string> names;
	int WIDTH = 30;


};

