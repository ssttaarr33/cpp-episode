#include <sstream>

#include <cstdlib>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <json/json.h>
#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;

int main(int argc, char* argv[])
{

    try {
        curlpp::Cleanup cleaner;
        curlpp::Easy request;
        request.setOpt(new curlpp::options::Url("https://jsonplaceholder.typicode.com/todos"));

        std::ostringstream response;
        request.setOpt(new curlpp::options::WriteStream(&response));

        request.perform();

        std::string stringResponse = std::string(response.str());
        
        auto jsonObject = json::parse(stringResponse);

        //std::cout << jsonObject << std::endl;
        int completed = 0;

        for (auto it : jsonObject)
        {
            if (it["completed"] == true) {
                completed++;
            }            
        }
        std::cout << " completed: ";
        std::cout << completed << std::endl;
        std::cout << " NotCompleted: ";
        std::cout << jsonObject.size() - completed << std::endl;

       // ------ciobanie mai jos
        std::string::size_type pos = 0;
        std::string target = "true";
        int occurrences = 0;
        while ((pos = std::string(response.str()).find(target, pos)) != std::string::npos) {
            ++occurrences;
            pos += target.length();
        }
       // std::cout << " completed: ";
        //std::cout << occurrences << std::endl;

        pos = 0;
        target = "false";
        occurrences = 0;
        while ((pos = std::string(response.str()).find(target, pos)) != std::string::npos) {
            ++occurrences;
            pos += target.length();
        }
        //std::cout << " Notcompleted: ";
        //std::cout << occurrences << std::endl;

        return EXIT_SUCCESS;
    }
    catch (curlpp::LogicError& e) {
        std::cout << e.what() << std::endl;
    }
    catch (curlpp::RuntimeError& e) {
        std::cout << e.what() << std::endl;
    }

    return EXIT_FAILURE;
}