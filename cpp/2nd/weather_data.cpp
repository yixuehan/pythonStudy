#include <iostream>
#include <map>
#include <memory>
using namespace std;

#include <boost/timer/timer.hpp>
using namespace boost;

void updateWeatherScreens(float temperature, float humidity, float pressure);

class WeatherDataClientInterface
{
public:
    virtual void measurementsChanged() = 0;
    float getTemperature() {
        return 30.0f;
    }
    float getHumidity() {
        return 5.0f;
    }
    float getPressure() {
        return 1.0f;
    }
};
class WeatherDataClient : public WeatherDataClientInterface
{
public:
    WeatherDataClient()
    {
        // 接收数据变化
    }

    void measurementsChanged() override
    {
        float temperature = getTemperature();
        float humidity = getHumidity();
        float pressure = getPressure();
        updateWeatherScreens(temperature, humidity, pressure);
    }
};

class WeatherScreenBase
{
public:
    void update(float temperature, float humidity, float pressure)
    {
        _temperature = temperature;
        _humidity = humidity;
        _pressure = pressure;
        display();
    }
    virtual void display() = 0;
private:
    float _temperature, _humidity, _pressure;
};

class WeatherScreen1 : public WeatherScreenBase
{
public:
    void display() override
    {
        cout << "display1\n";
    }
};
class WeatherScreen2 : public WeatherScreenBase
{
public:
    void display() override
    {
        cout << "display2\n";
    }
};
class WeatherScreen3 : public WeatherScreenBase
{
public:
    void display() override
    {
        cout << "display3\n";
    }
};
class WeatherScreen4 : public WeatherScreenBase
{
public:
    void display() override
    {
        cout << "display4\n";
    }
};

class WeatherScreens
{
public:
    void append(const string &screenName, shared_ptr<WeatherScreenBase > s)
    {
        _screens[screenName] = s;
    }

    void updateWeatherScreens(float temperature, float humidity, float pressure)
    {
        for (auto &e : _screens) {
            e.second->update(temperature, humidity, pressure);
        }
    }
private:
    std::map<string, shared_ptr<WeatherScreenBase>> _screens;
};

WeatherScreens g_screens;

void updateWeatherScreens(float temperature, float humidity, float pressure)
{
    g_screens.updateWeatherScreens(temperature, humidity, pressure);
}


int main()
{
    g_screens.append("screen1", make_shared<WeatherScreen1>());
    g_screens.append("screen2", make_shared<WeatherScreen2>());
    g_screens.append("screen3", make_shared<WeatherScreen3>());
    g_screens.append("screen4", make_shared<WeatherScreen4>());
    WeatherDataClient client;
    // client auto update
    client.measurementsChanged();
    client.measurementsChanged();
    client.measurementsChanged();
}


