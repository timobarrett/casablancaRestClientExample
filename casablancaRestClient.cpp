#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <sstream>
#include <string>


using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::json;
using namespace concurrency::streams;
/**
 * this piss poor example sends rest request to openweatherapi and write results to file specified
 * by the second input parameter
 */
void displayAllResults(json::value value){

	if (!value.is_null()){
		if (value.is_object())
		{
			web::json::object foo = value.as_object();
			for (auto p1 : value.as_object()){
				const json::value val = p1.second;
				std::cout<<"KEY = "<<p1.first;
					if (!val.is_null() && val.is_string()){
						std::cout<<"VAL = " <<val.as_string()<<std::endl;
					}
					displayAllResults(val);
			}
		}
		else if (value.is_array()){
            for(auto ptr: value.as_array())
            {
            	for (auto p2: ptr.as_object()){
            		std::cout<<"KEY = " <<p2.first<< " VALUE = "<<p2.second<<std::endl;
            	}
            }
		}
	}
}



int main(int argc, char *args[])
{
    if(argc != 2)

    {
        printf("Usage: Casablanca.exe zip code \n");
        return -1;
    }
    const string_t searchTerm = args[1];


    //Openweather values
   const string_t OPEN_WEATHER_URL = "api.openweathermap.org";
   const string_t OPEN_WEATHER_PATH_FRCAST = "/data/2.5/weather";
   string_t zipCode = args[1];
   string_t OPEN_WEATHER_ID = "get one from openweatherapi.org";
   string_t MODE = "&mode";
   string_t MODE_VALUE = "json";
   const string_t UNIT = "&units";
   string_t UNIT_VALUE = "imperial";


//GOAL - http://api.openweathermap.org/data/2.5/weather?appid=0da6960ae510202d1f8633e08e075162&zip=03031&mode=json&units=imperial
    // Open a stream to the file to write the HTTP response body into.
    auto fileBuffer = std::make_shared<streambuf<uint8_t>>();


        // Create an HTTP request.
        /* Encode the URI query since it could contain special characters like spaces. */

        http_client weatherClient(U("http://" + OPEN_WEATHER_URL + OPEN_WEATHER_PATH_FRCAST));
        auto query = uri_builder()
        			.append_query("appid", OPEN_WEATHER_ID)
             		.append_query("zip",zipCode)
             		.append_query(MODE,MODE_VALUE)
             		.append_query(UNIT, UNIT_VALUE)
             		.to_string();
        std::cout<<"QUERY="<<query<<std::endl;
        weatherClient.request(methods::GET, query)
		 .then([](http_response response) -> pplx::task<json::value>
		    {
        		if (response.status_code() == status_codes::OK){
        			std::cout<<"STATUS = " <<response.status_code()<<std::endl;
        			return response.extract_json();
        		}
        		std::cout<<"STATUS = " <<response.status_code()<<std::endl;
        		return pplx::task_from_result(json::value());
		    })
		    .then([](pplx::task<json::value> previousTask){
				try{
					json::value v = previousTask.get();
					std::cout<<"STARTING JSON" << v << std::endl;
					displayAllResults(v);
				}
				catch (http_exception const & e){
					std::cout <<e.what() << std::endl;
				}
        	})
		    .wait();


    return 0;

}

