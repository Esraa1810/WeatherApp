
#include <iostream>
#include "WeatherClient.h"
#include "WeatherUI.h"

int main() {
    std::string apiKey = "49840e8459e8e435fb3a74b63acc9408";
    WeatherClient weatherClient(apiKey);
    WeatherUI weatherUI;

    while (true) {
        std::string city;
        std::cout << "Enter city name (or 'exit' to quit): ";
        std::getline(std::cin, city);

        if (city == "exit") break;

        std::cout << "Fetching weather data...\n";

        weatherClient.fetchWeatherDataAsync(city, [&](std::string weatherData) {
            weatherUI.showWindow(weatherData);
            });
    }

    return 0;
}
