#include "crow_all.h"

using namespace std;

string get_car_json(){
	int count = 2;
	static double lat = 28.1128547;
	static double lng = 112.8668242;
	static double angle = 50.0;
	static int 	  n = 0;


	ostringstream result;
	result.precision(7);
	result.setf(std::ios::fixed);
	result << "{\"cars\":[";
	for(int i=0;i<count;i++){
		result << "{";
		result << "\"id\":" << "\"000" << i << "\",";
		result << "\"lat\":"<< (lat-(n%20-10)*0.0000100+i*0.0002000) << ",";
		result << "\"lng\":"<< (lng-(n%20-10)*0.0000100+i*0.0001000) << ",";
		result << "\"angle\":"<< (angle+i*10);
		result << "}";
		if(i < count-1)result << ",";
	}
	result << "]}";

	angle += (n%100-50);
	n++;
	return result.str();
}

int main()
{
	crow::SimpleApp app;
	CROW_ROUTE(app,"/")([](){

		auto res = crow::response{"hello world"};
		res.add_header("Access-Control-Allow-Origin","*");
		res.add_header("Content-Type","application/json");
		return res;
	});	

	CROW_ROUTE(app, "/cars").methods("POST"_method)
	([](const crow::request& req){
	    auto x = crow::json::load(req.body);
	    if (!x)return crow::response(400);
	    if(!x.has("position"))return crow::response(400);

	    string str = get_car_json();
		auto res = crow::response{str};
		res.add_header("Access-Control-Allow-Origin","*");
		res.add_header("Content-Type","application/json");
		return res;
//	    std::ostringstream os;
//	    os << "111";
//	    return crow::response{os.str()};
	});


	app.port(54321).multithreaded().run();
	return 0;

}
