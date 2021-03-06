#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>

#include <string>


using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace web::json;
using namespace concurrency::streams;
/**
 * sends rest request to openweathermap and write results to file specified
 * by the second input parameter
 */
void displayAllResults(json::value value){

	if (!value.is_null()){
		if (value.is_object())
		{
			web::json::object foo = value.as_object();
			for (auto p1 : value.as_object()){
				std::cout<<"KEY = "<<p1.first;
				std::cout<<" Value = "<<p1.second<<std::endl;
				displayAllResults(p1.second);
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
/**
 * process the json values returned getting selected values
 * demonstrates getting values, numeric values and array values
 *
 */
void getSpecificInfo(json::value value){
	if (!value.is_null())
	    {

			std::cout<<std::endl<<"location = "<< value.at("name")<<std::endl;
			//below reads in a number value and does rounding on the value
			std::cout<<"temperature as presented from the server --> "<<value.at("main").at("temp")<<std::endl;
			std::cout<<"temperature = " << value.at("main").at("temp").as_number().to_double()<<std::endl;
			std::cout<<"humidity = " << value.at("main").at("humidity")<<std::endl;
			std::cout<<"pressure = "<<value.at("main").at("pressure")<<std::endl;

			//get the values contained in the array
			json::object foo2 = value.as_object();
			auto ptr = foo2.find("weather");
			json::array doo = ptr->second.as_array();
			std::cout<<ptr->first<<" ARRAY VALUES "<<std::endl;
			auto iter = doo.cbegin();
			std::cout<<"description = "<<iter->at("description")<<std::endl;
			std::cout<<"icon = "<<iter->at("icon")<<std::endl;
			std::cout<<"main = "<<iter->at("main")<<std::endl;

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
   string_t OPEN_WEATHER_ID = "get one from openweathermap.org";
   string_t MODE = "&mode";
   string_t MODE_VALUE = "json";
   const string_t UNIT = "&units";
   string_t UNIT_VALUE = "imperial";
   string_t foo;


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

					getSpecificInfo(v);
				}
				catch (http_exception const & e){
					std::cout <<e.what() << std::endl;
				}
        	})
		    .wait();


    return 0;

}

